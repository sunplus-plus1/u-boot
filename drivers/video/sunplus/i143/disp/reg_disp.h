/********************************************************
 * Copyright (c) 2019 by Sunplus Technology Co., Ltd.
 *    ____               __
 *   / __/_ _____  ___  / /_ _____
 *  _\ \/ // / _ \/ _ \/ / // (_-<
 * /___/\_,_/_//_/ .__/_/\_,_/___/
 *              /_/
 * Sunplus Technology Co., Ltd.19, Innovation First Road,
 * Science-Based Industrial Park, Hsin-Chu, Taiwan, R.O.C.
 * ------------------------------------------------------
 *
 * Description :  dispplay register header for sp7021
 * ------------------------------------------------------
 * Rev  Date          Author(s)      Status & Comments
 * ======================================================
 * 0.1  2020/09/02    hammer.hsieh   initial version
 */
#ifndef __DISP_REG_H__
#define __DISP_REG_H__

#include <common.h>
#include "display2.h"

#define DISP_REG_BASE           0x9c000000
#define DISP_RF_GRP(_grp, _reg) ((((_grp) * 32 + (_reg)) * 4) + DISP_REG_BASE)
#define DISP_RF_MASK_V(_mask, _val)       (((_mask) << 16) | (_val))
#define DISP_RF_MASK_V_SET(_mask)         (((_mask) << 16) | (_mask))
#define DISP_RF_MASK_V_CLR(_mask)         (((_mask) << 16) | 0)

struct DISP_moon0_regs{
	unsigned int stamp;
	unsigned int clken[10];
	unsigned int gclken[10];
	unsigned int reset[10];
	unsigned int hw_cfg;
};
#define DISP_MOON0_REG ((volatile struct DISP_moon0_regs *)DISP_RF_GRP(0,0))

struct DISP_moon1_regs{
	unsigned int sft_cfg[32];
};
#define DISP_MOON1_REG ((volatile struct DISP_moon1_regs *)DISP_RF_GRP(1,0))

struct DISP_moon4_regs {
	unsigned int reserved1[15];		// 4.0-14
	unsigned int plltv_ctl[4];		// 4.15-18
	unsigned int reserved2[13];		// 4.19-31
};
#define DISP_MOON4_REG ((volatile struct DISP_moon4_regs *)DISP_RF_GRP(4, 0))

struct DISP_moon5_regs {
	unsigned int cfg[7];           // 5.0
};
#define DISP_MOON5_REG ((volatile struct DISP_moon5_regs *) DISP_RF_GRP(5, 0))
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 struct define                                                            //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef volatile struct _DISP_DDFCH_REG_ {
	u32 ddfch_latch_en					; // 00
	u32 ddfch_mode_option				; // 01
	u32 ddfch_enable					; // 02
	u32 ddfch_urgent_thd				; // 03
	u32 ddfch_cmdq_thd					; // 04
	u32 g185_reserved0					; // 05
	u32 ddfch_luma_base_addr_0			; // 06
	u32 ddfch_luma_base_addr_1			; // 07
	u32 ddfch_luma_base_addr_2			; // 08
	u32 ddfch_crma_base_addr_0			; // 09
	u32 ddfch_crma_base_addr_1			; // 10
	u32 ddfch_crma_base_addr_2			; // 11
	u32 g185_reserved1[3]				; // 12-14
	u32 ddfch_frame_id					; // 15
	u32 ddfch_free_run_control			; // 16
	u32 g185_reserved2[3]				; // 17-19
	u32 ddfch_vdo_frame_size			; // 20
	u32 ddfch_vdo_crop_size				; // 21
	u32 ddfch_vdo_crop_offset			; // 22
	u32 ddfch_config_0					; // 23
	u32 ddfch_config_1					; // 24
	u32 g185_reserved3					; // 25
	u32 ddfch_checksum_info				; // 26
	u32 ddfch_error_flag_info			; // 27
	u32 ddfch_bist						; // 28
	u32 ddfch_axi_ipbj_info				; // 29
	u32 g185_reserved4					; // 30
	u32 ddfch_others_info				; // 31
} DISP_DDFCH_REG_t;

typedef volatile struct _DISP_VPPDMA_REG_ {
	u32 vdma_ver						; // 00
	u32 vdma_gc							; // 01
	u32 vdma_cfg						; // 02
	u32 vdma_frame_size					; // 03
	u32 vdma_crop_st					; // 04
	u32 vdma_lstd_size					; // 05
	u32 vdma_data_addr1					; // 06
	u32 vdma_data_addr2					; // 07
	u32 g186_reserved[24]				; // 08-31
} DISP_VPPDMA_REG_t;

typedef volatile struct _DISP_VSCL1_REG_ {
	u32 vscl0_config1					; // 00
	u32 vscl0_config2					; // 01
	u32 g187_reserved0					; // 02
	u32 vscl0_actrl_i_xlen				; // 03
	u32 vscl0_actrl_i_ylen				; // 04
	u32 vscl0_actrl_s_xstart			; // 05
	u32 vscl0_actrl_s_ystart			; // 06
	u32 vscl0_actrl_s_xlen				; // 07
	u32 vscl0_actrl_s_ylen				; // 08
	u32 vscl0_dctrl_o_xlen				; // 09
	u32 vscl0_dctrl_o_ylen				; // 10	
	u32 vscl0_dctrl_d_xstart			; // 11
	u32 vscl0_dctrl_d_ystart			; // 12
	u32 vscl0_dctrl_d_xlen				; // 13
	u32 vscl0_dctrl_d_ylen				; // 14
	u32 vscl0_dctrl_bgc_c				; // 15
	u32 vscl0_dctrl_bgc_y				; // 16
	u32 g187_reserved1					; // 17
	u32 vscl0_hint_ctrl					; // 18
	u32 vscl0_hint_hfactor_low			; // 19
	u32 vscl0_hint_hfactor_high			; // 20
	u32 vscl0_hint_initf_low			; // 21
	u32 vscl0_hint_initf_high			; // 22
	u32 g187_reserved2[5]				; // 23-27
	u32 vscl0_sram_ctrl					; // 28
	u32 vscl0_sram_addr					; // 29
	u32 vscl0_sram_write_data			; // 30
	u32 vscl0_sram_read_data			; // 31
} DISP_VSCL_1_REG_t;

typedef volatile struct _DISP_VSCL2_REG_ {
	u32 vscl0_vint_ctrl					; // 00
	u32 vscl0_vint_vfactor_low			; // 01
	u32 vscl0_vint_vfactor_high			; // 02	
	u32 vscl0_vint_initf_low			; // 03
	u32 vscl0_vint_initf_high			; // 04	
	u32 g188_reserved0[17]				; // 05-21
	u32 vscl0_checksum_result			; // 22
	u32 vscl0_Version_ID				; // 23
	u32 g188_reserved1[8]				; // 24-31
} DISP_VSCL_2_REG_t;

typedef volatile struct _DISP_VPOST_REG_ {
	u32 vpost_config					; // 00
	u32 vpost_adj_config				; // 01
	u32 vpost_adj_src					; // 02
	u32 vpost_adj_des					; // 03
	u32 vpost_adj_slope0				; // 04
	u32 vpost_adj_slope1				; // 05
	u32 vpost_adj_slope2				; // 06
	u32 vpost_adj_bound					; // 07
	u32 vpost_cspace_config				; // 08
	u32 vpost_opif_config				; // 09
	u32 vpost_opif_bgy					; // 10
	u32 vpost_opif_bgyu					; // 11
	u32 vpost_opif_alpha				; // 12
	u32 vpost_opif_msktop				; // 13
	u32 vpost_opif_mskbot				; // 14
	u32 vpost_opif_mskleft				; // 15
	u32 vpost_opif_mskright				; // 16
	u32 vpost0_checksum_ans				; // 17
	u32 vpp_xstart						; // 18
	u32 vpp_ystart						; // 19
	u32 vpost_reserved0[11]				; // 20~30
	u32 VPOST_Version_ID				; // 31
} DISP_VPOST_REG_t;

typedef volatile struct _DISP_OSD_REG_ {
	u32 osd_ctrl						; // 00
	u32 osd_en							; // 01
	u32 osd_base_addr					; // 02
	u32 osd_reserved0[3]				; // 03-05
	u32 osd_bus_monitor_l				; // 06
	u32 osd_bus_monitor_h				; // 07
	u32 osd_req_ctrl					; // 08
	u32 osd_debug_cmd_lock				; // 09
	u32 osd_debug_burst_lock			; // 10
	u32 osd_debug_xlen_lock				; // 11
	u32 osd_debug_ylen_lock				; // 12
	u32 osd_debug_queue_lock			; // 13
	u32 osd_crc_chksum					; // 14
	u32 osd_reserved1					; // 15
	u32 osd_hvld_offset					; // 16
	u32 osd_hvld_width					; // 17
	u32 osd_vvld_offset					; // 18
	u32 osd_vvld_height					; // 19
	u32 osd_data_fetch_ctrl				; // 20
	u32 osd_bist_ctrl					; // 21
	u32 osd_non_fetch_0					; // 22
	u32 osd_non_fetch_1					; // 23
	u32 osd_non_fetch_2					; // 24
	u32 osd_non_fetch_3					; // 25
	u32 osd_bus_status					; // 26
	u32 osd_3d_h_offset					; // 27
	u32 osd_reserved3					; // 28
	u32 osd_src_decimation_sel			; // 29
	u32 osd_bus_time_0					; // 30
	u32 osd_bus_time_1					; // 31
} DISP_OSD_REG_t;

typedef volatile struct _DISP_OSD1_REG_ {
	u32 osd_ctrl						; // 00
	u32 osd_en							; // 01
	u32 osd_base_addr					; // 02
	u32 osd_reserved0[3]				; // 03-05
	u32 osd_bus_monitor_l				; // 06
	u32 osd_bus_monitor_h				; // 07
	u32 osd_req_ctrl					; // 08
	u32 osd_debug_cmd_lock				; // 09
	u32 osd_debug_burst_lock			; // 10
	u32 osd_debug_xlen_lock				; // 11
	u32 osd_debug_ylen_lock				; // 12
	u32 osd_debug_queue_lock			; // 13
	u32 osd_crc_chksum					; // 14
	u32 osd_reserved1					; // 15
	u32 osd_hvld_offset					; // 16
	u32 osd_hvld_width					; // 17
	u32 osd_vvld_offset					; // 18
	u32 osd_vvld_height					; // 19
	u32 osd_data_fetch_ctrl				; // 20
	u32 osd_bist_ctrl					; // 21
	u32 osd_non_fetch_0					; // 22
	u32 osd_non_fetch_1					; // 23
	u32 osd_non_fetch_2					; // 24
	u32 osd_non_fetch_3					; // 25
	u32 osd_bus_status					; // 26
	u32 osd_3d_h_offset					; // 27
	u32 osd_reserved3					; // 28
	u32 osd_src_decimation_sel			; // 29
	u32 osd_bus_time_0					; // 30
	u32 osd_bus_time_1					; // 31
} DISP_OSD1_REG_t;

typedef volatile struct _DISP_GPOST_REG_ {
	u32 gpost0_config					; // 00
	u32 gpost0_mskl						; // 01
	u32 gpost0_mskr						; // 02
	u32 gpost0_mskt						; // 03
	u32 gpost0_mskb						; // 04
	u32 gpost0_bg1						; // 05
	u32 gpost0_bg2						; // 06
	u32 gpost0_contrast_config			; // 07
	u32 gpost0_adj_src					; // 08
	u32 gpost0_adj_des					; // 09
	u32 gpost0_adj_slope0				; // 10
	u32 gpost0_adj_slope1				; // 11
	u32 gpost0_adj_slope2				; // 12
	u32 gpost0_adj_bound				; // 13
	u32 gpost0_bri_value				; // 14
	u32 gpost0_hue_sat_en				; // 15
	u32 gpost0_chroma_satsin			; // 16
	u32 gpost0_chroma_satcos			; // 17
	u32 gpost0_master_en				; // 18
	u32 gpost0_master_horizontal		; // 19
	u32 gpost0_master_vertical			; // 20
	u32 gpost0_reserved0[11]			; // 21-31
} DISP_GPOST_REG_t;

typedef volatile struct _DISP_GPOST1_REG_ {
	u32 gpost1_config					; // 00
	u32 gpost1_mskl						; // 01
	u32 gpost1_mskr						; // 02
	u32 gpost1_mskt						; // 03
	u32 gpost1_mskb						; // 04
	u32 gpost1_bg1						; // 05
	u32 gpost1_bg2						; // 06
	u32 gpost1_contrast_config			; // 07
	u32 gpost1_adj_src					; // 08
	u32 gpost1_adj_des					; // 09
	u32 gpost1_adj_slope0				; // 10
	u32 gpost1_adj_slope1				; // 11
	u32 gpost1_adj_slope2				; // 12
	u32 gpost1_adj_bound				; // 13
	u32 gpost1_bri_value				; // 14
	u32 gpost1_hue_sat_en				; // 15
	u32 gpost1_chroma_satsin			; // 16
	u32 gpost1_chroma_satcos			; // 17
	u32 gpost1_master_en				; // 18
	u32 gpost1_master_horizontal		; // 19
	u32 gpost1_master_vertical			; // 20
	u32 gpost1_reserved0[11]			; // 21-31
} DISP_GPOST1_REG_t;

typedef volatile struct _DISP_TGEN_REG_ {
	u32 tgen_config						; // 00
	u32 tgen_reset						; // 01
	u32 tgen_user_int1_config			; // 02
	u32 tgen_user_int2_config			; // 03
	u32 tgen_dtg_config					; // 04
	u32 g213_reserved_1[2]				; // 05-06
	u32 tgen_dtg_venc_line_rst_cnt		; // 07
	u32 tgen_dtg_total_pixel			; // 08
	u32 tgen_dtg_ds_line_start_cd_point	; // 09
	u32 tgen_dtg_total_line				; // 10
	u32 tgen_dtg_field_end_line			; // 11
	u32 tgen_dtg_start_line				; // 12
	u32 tgen_dtg_status1				; // 13
	u32 tgen_dtg_status2				; // 14
	u32 tgen_dtg_status3				; // 15
	u32 tgen_dtg_status4				; // 16
	u32 tgen_dtg_clk_ratio_low			; // 17
	u32 tgen_dtg_clk_ratio_high			; // 18
	u32 g213_reserved_2[4]				; // 19-22
	u32 tgen_dtg_adjust1				; // 23
	u32 tgen_dtg_adjust2				; // 24
	u32 tgen_dtg_adjust3				; // 25
	u32 tgen_dtg_adjust4				; // 26
	u32 tgen_dtg_adjust5				; // 27
	u32 g213_reserved_3					; // 28
	u32 tgen_source_sel					; // 29
	u32 tgen_dtg_field_start_adj_lcnt	; // 30
	u32 g213_reserved_4					; // 31
} DISP_TGEN_REG_t;

typedef volatile struct _DISP_DMIX_REG_ {
	u32 dmix_layer_config_0				; // 00
	u32 dmix_layer_config_1				; // 01
	u32 dmix_plane_alpha_config_0		; // 02
	u32 dmix_plane_alpha_config_1		; // 03
	u32 dmix_adjust_config_0			; // 04
	u32 dmix_adjust_config_1			; // 05
	u32 dmix_adjust_config_2			; // 06
	u32 dmix_adjust_config_3			; // 07
	u32 dmix_adjust_config_4			; // 08
	u32 dmix_ptg_config_0				; // 09
	u32 dmix_ptg_config_1				; // 10	
	u32 dmix_ptg_config_2				; // 11
	u32 dmix_ptg_config_3				; // 12
	u32 dmix_ptg_config_4				; // 13
	u32 dmix_dtg_config_0				; // 14
	u32 dmix_dtg_config_1				; // 15
	u32 dmix_dtg_config_2				; // 16
	u32 dmix_dtg_config_3				; // 17
	u32 dmix_exp_config_0				; // 18
	u32 dmix_exp_config_1				; // 19
	u32 dmix_source_select				; // 20
	u32 dmix_chksum						; // 21
	u32 dmix_version					; // 22
	u32 dmix_time_detect_0				; // 23
	u32 dmix_time_detect_1				; // 24
	u32 dmix_time_detect_2				; // 25
	u32 g217_reserved2[6]				; // 26~31
} DISP_DMIX_REG_t;

typedef volatile struct _DISP_DVE_1_REG_ {
	u32 dve_vsync_start_top				; // 00
	u32 dve_vsync_start_bot				; // 01
	u32 dve_vsync_h_point				; // 02
	u32 dve_vsync_pd_cnt				; // 03
	u32 dve_hsync_start					; // 04
	u32 dve_hsync_pd_cnt				; // 05
	u32 dve_hdmi_mode_1					; // 06
	u32 dve_v_vld_top_start				; // 07
	u32 dve_v_vld_top_end				; // 08
	u32 dve_v_vld_bot_start				; // 09
	u32 dve_v_vld_bot_end				; // 10
	u32 dve_de_h_start					; // 11
	u32 dve_de_h_end					; // 12
	u32 dve_mp_tg_line_0_length			; // 13
	u32 dve_mp_tg_frame_0_line			; // 14
	u32 dve_mp_tg_act_0_pix				; // 15
	u32 dve_hdmi_mode_0					; // 16
	u32 g234_reserved[15]				; // 17-31
} DISP_DVE_1_REG_t;

typedef volatile struct _DISP_DVE_2_REG_ {
	u32 color_bar_mode					; // 00
	u32 color_bar_v_total				; // 01
	u32 color_bar_v_active				; // 02
	u32 color_bar_v_active_start		; // 03
	u32 color_bar_h_total				; // 04
	u32 color_bar_h_active				; // 05
	u32 g235_reserved[26]				; // 06-31
} DISP_DVE_2_REG_t;

typedef volatile struct _DISP_HDMITX_0_REG_ {
	u32 g380_reserved[32]				; // 00-31
} DISP_HDMITX_0_REG_t;

typedef volatile struct _DISP_HDMITX_1_REG_ {
	u32 g381_reserved[32]				; // 00-31
} DISP_HDMITX_1_REG_t;

typedef volatile struct _DISP_HDMITX_2_REG_ {
	u32 g382_reserved[32]				; // 00-31
} DISP_HDMITX_2_REG_t;

typedef volatile struct _DISP_HDMITX_3_REG_ {
	u32 g383_reserved[32]				; // 00-31
} DISP_HDMITX_3_REG_t;

typedef volatile struct _DISP_HDMITX_4_REG_ {
	u32 g384_reserved[32]				; // 00-31
} DISP_HDMITX_4_REG_t;

typedef volatile struct _DISP_HDMITX_5_REG_ {
	u32 g385_reserved[32]				; // 00-31
} DISP_HDMITX_5_REG_t;

typedef volatile struct _DISP_HDMITX_6_REG_ {
	u32 g386_reserved[32]				; // 00-31
} DISP_HDMITX_6_REG_t;

typedef volatile struct _DISP_HDMITX_7_REG_ {
	u32 g387_reserved[32]				; // 00-31
} DISP_HDMITX_7_REG_t;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 display engine                                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define G185_DDFCH_REG			((volatile DISP_DDFCH_REG_t *)(DISP_RF_GRP(185, 0)))
#define G186_VPPDMA_REG			((volatile DISP_VPPDMA_REG_t *)(DISP_RF_GRP(186, 0)))
#define G187_VSCL_REG			((volatile DISP_VSCL_1_REG_t *)(DISP_RF_GRP(187, 0)))
#define G188_VSCL_REG			((volatile DISP_VSCL_2_REG_t *)(DISP_RF_GRP(188, 0)))
#define G199_VPOST_REG			((volatile DISP_VPOST_REG_t *)(DISP_RF_GRP(199, 0)))
#define G196_OSD0_REG			((volatile DISP_OSD_REG_t *)(DISP_RF_GRP(196, 0)))
#define G197_OSD1_REG			((volatile DISP_OSD1_REG_t *)(DISP_RF_GRP(197, 0)))
#define G206_GPOST_REG			((volatile DISP_GPOST_REG_t *)(DISP_RF_GRP(206, 0)))
#define G207_GPOST_REG			((volatile DISP_GPOST1_REG_t *)(DISP_RF_GRP(207, 0)))
#define G213_TGEN_REG			((volatile DISP_TGEN_REG_t *)(DISP_RF_GRP(213, 0)))
#define G217_DMIX_REG			((volatile DISP_DMIX_REG_t *)(DISP_RF_GRP(217, 0)))
#define G234_DVE_REG			((volatile DISP_DVE_1_REG_t *)(DISP_RF_GRP(234, 0)))
#define G235_DVE_REG			((volatile DISP_DVE_2_REG_t *)(DISP_RF_GRP(235, 0)))

#define G380_HDMITX_REG			((volatile DISP_HDMITX_0_REG_t *)(DISP_RF_GRP(380, 0)))
#define G381_HDMITX_REG			((volatile DISP_HDMITX_1_REG_t *)(DISP_RF_GRP(381, 0)))
#define G382_HDMITX_REG			((volatile DISP_HDMITX_2_REG_t *)(DISP_RF_GRP(382, 0)))
#define G383_HDMITX_REG			((volatile DISP_HDMITX_3_REG_t *)(DISP_RF_GRP(383, 0)))
#define G384_HDMITX_REG			((volatile DISP_HDMITX_4_REG_t *)(DISP_RF_GRP(384, 0)))
#define G385_HDMITX_REG			((volatile DISP_HDMITX_5_REG_t *)(DISP_RF_GRP(385, 0)))
#define G386_HDMITX_REG			((volatile DISP_HDMITX_6_REG_t *)(DISP_RF_GRP(386, 0)))
#define G387_HDMITX_REG			((volatile DISP_HDMITX_7_REG_t *)(DISP_RF_GRP(387, 0)))
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 display address base enumerate                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum DRV_Status_t {
	/* common status values */
	DRV_SUCCESS,				/*!< successful outcome					*/
	DRV_ERR_FAILURE,			/*!< operation failed					*/
	DRV_ERR_INVALID_HANDLE,		/*!< invalid handle						*/
	DRV_ERR_INVALID_ID,			/*!< invalid identifier					*/
	DRV_ERR_INVALID_PARAM,		/*!< invalid parameter					*/
	DRV_ERR_INVALID_OP,			/*!< requested operation is invalid		*/
	DRV_ERR_MEMORY_ALLOC,		/*!< problem allocating memory			*/
	DRV_ERR_MEMORY_SIZE,		/*!< problem with the size of memory	*/
	/* < supplied							*/
	DRV_ERR_RESOURCE_UNAVAILABLE,
	DRV_ERR_TIMEOUT,			/*!< timeout							*/
	DRV_WARN_NO_ACTION,			/* < the function completed successfully,*/
	/* < but no action was taken            */
	DRV_WARN_PARAM_CLIPPED,		/*!< the function has completed			*/
	/*!< successfully, though a parameter was	*/
	/*!< clipped to within a valid range.		*/
	DRV_WARN_BUFFER_EMPTY,
	DRV_WARN_BUFFER_FULL,
	DRV_WARN_UNINITED,			/*!< driver has not been initialized yet */
	DRV_WARN_INITED,			/*!< driver has been initialized already */
	DRV_ERR_MODE_MISMATCH,		/*!< deinterlacer off*/
	DRV_ERR_MAX					/*!< Max error number*/
} DRV_Status_e;

#endif // #ifndef __DISP_REG_H__
