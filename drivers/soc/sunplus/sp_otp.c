#include <common.h>
#include <asm/io.h>

#define OTP_WAIT_MICRO_SECONDS    100

#define OTPRX_2_BASE_ADR          0x9C002800
#define OTPRX_BASE_ADR            0x9C00AF80
#define HB_GPIO                   0x9C00AF00

/* OTP register map */
#define OTP_PROGRAM_CONTROL       0x0C
#define PIO_MODE                  0x07

#define OTP_PROGRAM_ADDRESS       0x10
#define PROG_OTP_ADDR             0x1FFF

#define OTP_PROGRAM_PGENB         0x20
#define PIO_PGENB                 0x01

#define OTP_PROGRAM_ENABLE        0x24
#define PIO_WR                    0x01

#define OTP_PROGRAM_VDD2P5        0x28
#define PROGRAM_OTP_DATA          0xFF00
#define PROGRAM_OTP_DATA_SHIFT    8
#define REG25_PD_MODE_SEL         0x10
#define REG25_POWER_SOURCE_SEL    0x02
#define OTP2REG_PD_N_P            0x01

#define OTP_PROGRAM_STATE         0x2C
#define OTPRSV_CMD3               0xE0
#define OTPRSV_CMD3_SHIFT         5
#define TSMC_OTP_STATE            0x1F

#define OTP_CONTROL               0x44
#define PROG_OTP_PERIOD           0xFFE0
#define PROG_OTP_PERIOD_SHIFT     5
#define OTP_EN_R                  0x01

#define OTP_CONTROL2              0x48
#define OTP_RD_PERIOD             0xFF00
#define OTP_RD_PERIOD_SHIFT       8
#define OTP_READ                  0x04

#define OTP_STATUS                0x4C
#define OTP_READ_DONE             0x10

#define OTP_READ_ADDRESS          0x50
#define RD_OTP_ADDRESS            0x1F

struct otprx_sunplus {
	u32 sw_trim;
	u32 set_key;
	u32 otp_rsv;
	u32 otp_prog_ctl;
	u32 otp_prog_addr;
	u32 otp_prog_csb;
	u32 otp_prog_strobe;
	u32 otp_prog_load;
	u32 otp_prog_pgenb;
	u32 otp_prog_wr;
	u32 otp_prog_reg25;
	u32 otp_prog_state;
	u32 otp_usb_phy_trim;
	u32 otp_data2;
	u32 otp_pro_ps;
	u32 otp_rsv2;
	u32 key_srst;
	u32 otp_ctrl;
	u32 otp_cmd;
	u32 otp_cmd_status;
	u32 otp_addr;
	u32 otp_data;
};

struct sunplus_otp_priv {
    struct otprx2_sunplus *regs;
};

struct hbgpio_sunplus {
	u32 hb_gpio_rgst_bus32[13];
};

struct sunplus_hbgpio {
    struct hbgpio_sunplus *otp_data;
};

static volatile struct otprx_sunplus *regs = (volatile struct otprx_sunplus *)(OTPRX_BASE_ADR);
static volatile struct hbgpio_sunplus *otp_data = (volatile struct hbgpio_sunplus *)(HB_GPIO);

int readOTPData(int addr, char *value)
{        	
	unsigned int addr_data;
	unsigned int byte_shift;
	unsigned int data;
    u32 timeout = OTP_WAIT_MICRO_SECONDS;
	
	addr_data = (addr % 16) / 4;
	byte_shift = ((addr % 16) % 4);
		
	writel(0x0, &regs->otp_cmd_status);

	addr = (addr / 16) * 4 * 32;
	writel(addr, &regs->otp_addr);
	
	writel(0x1E04, &regs->otp_cmd);
	
	do
    {
        udelay(1000);
		if (timeout-- == 0)
		    return -1;

        data = readl(&regs->otp_cmd_status);
    } while((data & OTP_READ_DONE) != OTP_READ_DONE);

	*value = (otp_data->hb_gpio_rgst_bus32[8+addr_data] >> (8 * byte_shift)) & 0xFF;

	return 0;
}

static int do_read_otp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int addr;	
    char value;
	unsigned int data;
	int i, j;
	
	if (argc == 2)
	{
	    addr = simple_strtoul(argv[1], NULL, 0);

		if (addr >= 128)
			return CMD_RET_USAGE;
		
	    if (readOTPData(addr, &value) == -1)
			return CMD_RET_FAILURE;

		data = value;
        printf("OTP DATA (byte %u) = 0x%X\n", addr, data);
		
		return 0;
	}
	else if (argc == 1)
	{
	    printf(" (byte No.)   (data)\n");
	    j = 0;
		
		for (addr = 0 ; addr < 127; addr += 16)
		{
	        if (readOTPData(addr, &value) == -1)
			    return CMD_RET_FAILURE;
			
			for (i = 0; i < 4; i++, j++)
			{   					
                printf("  %03u~%03u : 0x%08X\n", 3+j*4, j*4, otp_data->hb_gpio_rgst_bus32[8+i]); 	
			}

			printf("\n");
		}
		
		return 0;
	}
	else
	{
	    return CMD_RET_USAGE;
	}	    
}

/*******************************************************/
U_BOOT_CMD(
	rotp,	2,	1,	do_read_otp,
	"read 1 byte data or all data of OTP", 
	"[OTP address (0, 1,..., 128 byte) | None]"
);
