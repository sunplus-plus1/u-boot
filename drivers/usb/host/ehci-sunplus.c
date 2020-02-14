/*
 * This is a driver for the ehci controller found in Sunplus Gemini SoC
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <usb.h>
#include <asm/io.h>
#include <usb/ehci-ci.h>
#include <usb/ulpi.h>

#include "ehci.h"


#define REG_BASE           0x9c000000
#define RF_GRP(_grp, _reg) ((((_grp) * 32 + (_reg)) * 4) + REG_BASE)

#define RF_MASK_V(_mask, _val)       (((_mask) << 16) | (_val))
#define RF_MASK_V_SET(_mask)         (((_mask) << 16) | (_mask))
#define RF_MASK_V_CLR(_mask)         (((_mask) << 16) | 0)

// usb spec 2.0 Table 7-3  VHSDSC (min, max) = (525, 625)
// default = 586.5 mV (405 + 11 * 16.5)
// update  = 619.5 mV (405 + 13 * 16.5)
#define DEFAULT_UPHY_DISC   0xd   // 13 (=619.5mV)
#define ORIG_UPHY_DISC      0xb   // 11 (=586.5mV)


struct uphy_rn_regs {
	u32 cfg[28];		       // 150.0
	u32 gctrl[3];		       // 150.28
	u32 gsts;		       // 150.31
};
#define UPHY0_RN_REG ((volatile struct uphy_rn_regs *)RF_GRP(149, 0))
#define UPHY1_RN_REG ((volatile struct uphy_rn_regs *)RF_GRP(150, 0))

struct moon0_regs {
	unsigned int stamp;            // 0.0
	unsigned int clken[10];        // 0.1
	unsigned int gclken[10];       // 0.11
	unsigned int reset[10];        // 0.21
	unsigned int hw_cfg;           // 0.31
};
#define MOON0_REG ((volatile struct moon0_regs *)RF_GRP(0, 0))

struct moon1_regs {
	unsigned int sft_cfg[32];
};
#define MOON1_REG ((volatile struct moon1_regs *)RF_GRP(1, 0))

struct moon2_regs {
	unsigned int sft_cfg[32];
};
#define MOON2_REG ((volatile struct moon2_regs *)RF_GRP(2, 0))

struct moon3_regs {
	unsigned int sft_cfg[32];
};
#define MOON3_REG ((volatile struct moon3_regs *)RF_GRP(3, 0))

struct moon4_regs {
	unsigned int pllsp_ctl[7];	// 4.0
	unsigned int plla_ctl[5];	// 4.7
	unsigned int plle_ctl;		// 4.12
	unsigned int pllf_ctl;		// 4.13
	unsigned int plltv_ctl[3];	// 4.14
	unsigned int usbc_ctl;		// 4.17
	unsigned int uphy0_ctl[4];	// 4.18
	unsigned int uphy1_ctl[4];	// 4.22
	unsigned int pllsys;		// 4.26
	unsigned int clk_sel0;		// 4.27
	unsigned int probe_sel;		// 4.28
	unsigned int misc_ctl_0;	// 4.29
	unsigned int uphy0_sts;		// 4.30
	unsigned int otp_st;		// 4.31
};
#define MOON4_REG ((volatile struct moon4_regs *)RF_GRP(4, 0))

struct moon5_regs {
	unsigned int sft_cfg[32];
};
#define MOON5_REG ((volatile struct moon5_regs *)RF_GRP(5, 0))

struct hb_gp_regs {
        unsigned int hb_otp_data0;
        unsigned int hb_otp_data1;
        unsigned int hb_otp_data2;
        unsigned int hb_otp_data3;
        unsigned int hb_otp_data4;
        unsigned int hb_otp_data5;
        unsigned int hb_otp_data6;
        unsigned int hb_otp_data7;
        unsigned int hb_otp_ctl;
        unsigned int hb_otp_data;
        unsigned int g7_reserved[22];
};
#define HB_GP_REG ((volatile struct hb_gp_regs *)RF_GRP(350, 0))

struct sunplus_ehci_priv {
	struct ehci_ctrl ehcictrl;
	struct usb_ehci *ehci;
};

static void uphy_init(int port_num)
{
	// 1. enable UPHY 0/1 & USBC 0/1 HW CLOCK */
	if(0 == port_num){
		MOON0_REG->clken[2] = RF_MASK_V_SET(1 << 13);
		MOON0_REG->clken[2] = RF_MASK_V_SET(1 << 10);
	} else if(1 == port_num){
		MOON0_REG->clken[2] = RF_MASK_V_SET(1 << 14);
		MOON0_REG->clken[2] = RF_MASK_V_SET(1 << 11);
	}
	mdelay(1);

	// 2. reset UPHY 0/1
	if(0 == port_num){
		MOON0_REG->reset[2] = RF_MASK_V_SET(1 << 13);
		mdelay(1);
		MOON0_REG->reset[2] = RF_MASK_V_CLR(1 << 13);
	} else if(1 == port_num){
		MOON0_REG->reset[2] = RF_MASK_V_SET(1 << 14);
		mdelay(1);
		MOON0_REG->reset[2] = RF_MASK_V_CLR(1 << 14);
	}
	mdelay(1);

	// 3. Default value modification
	if(0 == port_num){
		UPHY0_RN_REG->gctrl[0] = 0x18888002;
	} else if(1 == port_num){
		UPHY1_RN_REG->gctrl[0] = 0x18888002;
	}
	mdelay(1);

	// 4. PLL power off/on twice
	if(0 == port_num){
		UPHY0_RN_REG->gctrl[2] = 0x88;
		mdelay(1);
		UPHY0_RN_REG->gctrl[2] = 0x80;
		mdelay(1);
		UPHY0_RN_REG->gctrl[2] = 0x88;
		mdelay(1);
		UPHY0_RN_REG->gctrl[2] = 0x80;;
		mdelay(20);
		UPHY0_RN_REG->gctrl[2] = 0x0;
	} else if(1 == port_num){
		UPHY1_RN_REG->gctrl[2] = 0x88;
		mdelay(1);
		UPHY1_RN_REG->gctrl[2] = 0x80;
		mdelay(1);
		UPHY1_RN_REG->gctrl[2] = 0x88;
		mdelay(1);
		UPHY1_RN_REG->gctrl[2] = 0x80;
		mdelay(20);
		UPHY1_RN_REG->gctrl[2] = 0x0;
	}

	// 5. USBC 0/1 reset
	if(0 == port_num){
		MOON0_REG->reset[2] = RF_MASK_V_SET(1 << 10);
		mdelay(1);
		MOON0_REG->reset[2] = RF_MASK_V_CLR(1 << 10);
	} else if(1 == port_num){
		MOON0_REG->reset[2] = RF_MASK_V_SET(1 << 11);
		mdelay(1);
		MOON0_REG->reset[2] = RF_MASK_V_CLR(1 << 11);
	}
	mdelay(1);

	// 6. HW workaround
	if(0 == port_num){
		UPHY0_RN_REG->cfg[19] |= 0x0f;
	} else if(1 == port_num){
		UPHY1_RN_REG->cfg[19] |= 0x0f;
	}
	// 7. USB DISC (disconnect voltage)
	if(0 == port_num){
		UPHY0_RN_REG->cfg[7] = 0x8b;
	} else if(1 == port_num){
		UPHY1_RN_REG->cfg[7] = 0x8b;
	}
	// 8. RX SQUELCH LEVEL
	if(0 == port_num){
		UPHY0_RN_REG->cfg[25] = 0x4;
	} else if(1 == port_num){
		UPHY1_RN_REG->cfg[25] = 0x4;
	}
}

static void usb_power_init(int is_host, int port_num)
{
    // a. enable pin mux control (sft_cfg_8, bit2/bit3)
    //    Host: enable
    //    Device: disable
	if (is_host) {
		MOON1_REG->sft_cfg[2] = RF_MASK_V_SET(1 << (12 + port_num));
	} else {
		MOON1_REG->sft_cfg[2] = RF_MASK_V_CLR(1 << (12 + port_num));
	}

    // b. USB control register:
    //    Host:   ctrl=1, host sel=1, type=1
    //    Device  ctrl=1, host sel=0, type=0
	if (is_host) {
		if(0 == port_num){
			MOON5_REG->sft_cfg[17] = RF_MASK_V_SET(7 << 4);
		} else if (1 == port_num){
			MOON5_REG->sft_cfg[17] = RF_MASK_V_SET(7 << 12);
		}
	} else {
		if(0 == port_num){
			MOON5_REG->sft_cfg[17] = RF_MASK_V_SET(1 << 4);
			MOON5_REG->sft_cfg[17] = RF_MASK_V_CLR(3 << 5);
		} else if (1 == port_num){
			MOON5_REG->sft_cfg[17] = RF_MASK_V_SET(1 << 12);
			MOON5_REG->sft_cfg[17] = RF_MASK_V_CLR(3 << 13);
		}
	}
}

static int ehci_sunplus_ofdata_to_platdata(struct udevice *dev)
{
	struct sunplus_ehci_priv *priv = dev_get_priv(dev);

	priv->ehci = (struct usb_ehci *)devfdt_get_addr_ptr(dev);
	if (!priv->ehci)
		return -EINVAL;

	return 0;
}

static int ehci_sunplus_probe(struct udevice *dev)
{
	struct usb_platdata *plat = dev_get_platdata(dev);
	struct sunplus_ehci_priv *priv = dev_get_priv(dev);
	struct ehci_hccr *hccr;
	struct ehci_hcor *hcor;

	hccr = (struct ehci_hccr *)((uint32_t)&priv->ehci->ehci_len_rev);
	hcor = (struct ehci_hcor *)((uint32_t)&priv->ehci->ehci_usbcmd);
	printf("%s.%d, dev_name:%s,port_num:%d\n",__FUNCTION__, __LINE__, dev->name, dev->seq);

	uphy_init(dev->seq);
	usb_power_init(1, dev->seq);

	return ehci_register(dev, hccr, hcor, NULL, 0, plat->init_type);
}

static int ehci_usb_remove(struct udevice *dev)
{
	printf("%s.%d, dev_name:%s,port_num:%d\n",__FUNCTION__, __LINE__, dev->name, dev->seq);
	usb_power_init(0, dev->seq);

	return ehci_deregister(dev);
}

static const struct udevice_id ehci_sunplus_ids[] = {
	{ .compatible = "sunplus,sunplus-i143-usb-ehci0" },
	{ .compatible = "sunplus,sunplus-i143-usb-ehci1" },
	{ }
};

U_BOOT_DRIVER(ehci_sunplus) = {
	.name	= "ehci_sunplus",
	.id	= UCLASS_USB,
	.of_match = ehci_sunplus_ids,
	.ofdata_to_platdata = ehci_sunplus_ofdata_to_platdata,
	.probe = ehci_sunplus_probe,
	.remove = ehci_usb_remove,
	.ops	= &ehci_usb_ops,
	.platdata_auto_alloc_size = sizeof(struct usb_platdata),
	.priv_auto_alloc_size = sizeof(struct sunplus_ehci_priv),
	.flags	= DM_FLAG_ALLOC_PRIV_DMA,
};

