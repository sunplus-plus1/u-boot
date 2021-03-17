#include "pinctrl_sunplus.h"


static const unsigned pins_spif[] = { 6, 7, 8, 9, 10, 11 };
static const sppctlgrp_t q645grps_spif[] = {
	EGRP("SPI_FLASH", 1, pins_spif)
};

static const unsigned pins_emmc[] = { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };
static const sppctlgrp_t q645grps_emmc[] = {
	EGRP("CARD0_EMMC", 1, pins_emmc)
};

static const unsigned pins_snand[] = { 22, 23, 24, 25, 26, 27 };
static const sppctlgrp_t q645grps_snand[] = {
	EGRP("SPI_NAND", 1, pins_snand)
};

static const unsigned pins_sdc30[] = { 28, 29, 30, 31, 32, 33 };
static const sppctlgrp_t q645grps_sdc30[] = {
	EGRP("SD_CARD", 1, pins_sdc30)
};

static const unsigned pins_sdio30[] = { 34, 35, 36, 37, 38, 39 };
static const sppctlgrp_t q645grps_sdio30[] = {
	EGRP("SDIO", 1, pins_sdio30)
};

static const unsigned pins_uart0[] = { 40, 41 };
static const sppctlgrp_t q645grps_uart0[] = {
	EGRP("UART0", 1, pins_uart0)
};

static const unsigned pins_uart1[] = { 42, 43, 44, 45 };
static const sppctlgrp_t q645grps_uart1[] = {
	EGRP("UART1", 1, pins_uart1)
};

static const unsigned pins_uart2[] = { 46, 47, 48, 49 };
static const sppctlgrp_t q645grps_uart2[] = {
	EGRP("UART2", 1, pins_uart2)
};

static const unsigned pins_uart3[] = { 50, 51, 52, 53 };
static const sppctlgrp_t q645grps_uart3[] = {
	EGRP("UART3", 1, pins_uart3)
};

static const unsigned pins_spim0[] = { 56, 57, 58, 59, 60 };
static const sppctlgrp_t q645grps_spim0[] = {
	EGRP("SPI_MASTER0", 1, pins_spim0)
};

static const unsigned pins_spis0[] = { 56, 57, 58, 59, 60 };
static const sppctlgrp_t q645grps_spis0[] = {
	EGRP("SPI_SLAVE0", 1, pins_spis0)
};

static const unsigned pins_u2otg[] = { 61 };
static const sppctlgrp_t q645grps_u2otg[] = {
	EGRP("USB2_OTG", 1, pins_u2otg)
};

static const unsigned pins_i2cm0[] = { 64, 65 };
static const sppctlgrp_t q645grps_i2cm0[] = {
	EGRP("I2C_MASTER0", 1, pins_i2cm0)
};

static const unsigned pins_wakeup0[] = { 72 };
static const sppctlgrp_t q645grps_wakeup0[] = {
	EGRP("WAKEUP0", 1, pins_wakeup0)
};

static const unsigned pins_wakeup1[] = { 73 };
static const sppctlgrp_t q645grps_wakeup1[] = {
	EGRP("WAKEUP1", 1, pins_wakeup1)
};

static const unsigned pins_int_x1[] = { 77 };
static const unsigned pins_int_x2[] = { 78 };
static const unsigned pins_int_x3[] = { 52 };
static const unsigned pins_int_x4[] = { 53 };
static const unsigned pins_int_x5[] = { 49 };
static const unsigned pins_int_x6[] = { 59 };
static const unsigned pins_int_x7[] = { 60 };
static const sppctlgrp_t q645grps_int0[] = {
	EGRP("INT0_X1", 1, pins_int_x1),
	EGRP("INT0_X2", 1, pins_int_x2),
	EGRP("INT0_X3", 1, pins_int_x3),
	EGRP("INT0_X4", 1, pins_int_x4),
	EGRP("INT0_X5", 1, pins_int_x5),
	EGRP("INT0_X6", 1, pins_int_x6),
	EGRP("INT0_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int1[] = {
	EGRP("INT1_X1", 1, pins_int_x1),
	EGRP("INT1_X2", 1, pins_int_x2),
	EGRP("INT1_X3", 1, pins_int_x3),
	EGRP("INT1_X4", 1, pins_int_x4),
	EGRP("INT1_X5", 1, pins_int_x5),
	EGRP("INT1_X6", 1, pins_int_x6),
	EGRP("INT1_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int2[] = {
	EGRP("INT2_X1", 1, pins_int_x1),
	EGRP("INT2_X2", 1, pins_int_x2),
	EGRP("INT2_X3", 1, pins_int_x3),
	EGRP("INT2_X4", 1, pins_int_x4),
	EGRP("INT2_X5", 1, pins_int_x5),
	EGRP("INT2_X6", 1, pins_int_x6),
	EGRP("INT2_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int3[] = {
	EGRP("INT3_X1", 1, pins_int_x1),
	EGRP("INT3_X2", 1, pins_int_x2),
	EGRP("INT3_X3", 1, pins_int_x3),
	EGRP("INT3_X4", 1, pins_int_x4),
	EGRP("INT3_X5", 1, pins_int_x5),
	EGRP("INT3_X6", 1, pins_int_x6),
	EGRP("INT3_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int4[] = {
	EGRP("INT4_X1", 1, pins_int_x1),
	EGRP("INT4_X2", 1, pins_int_x2),
	EGRP("INT4_X3", 1, pins_int_x3),
	EGRP("INT4_X4", 1, pins_int_x4),
	EGRP("INT4_X5", 1, pins_int_x5),
	EGRP("INT4_X6", 1, pins_int_x6),
	EGRP("INT4_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int5[] = {
	EGRP("INT5_X1", 1, pins_int_x1),
	EGRP("INT5_X2", 1, pins_int_x2),
	EGRP("INT5_X3", 1, pins_int_x3),
	EGRP("INT5_X4", 1, pins_int_x4),
	EGRP("INT5_X5", 1, pins_int_x5),
	EGRP("INT5_X6", 1, pins_int_x6),
	EGRP("INT5_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int6[] = {
	EGRP("INT6_X1", 1, pins_int_x1),
	EGRP("INT6_X2", 1, pins_int_x2),
	EGRP("INT6_X3", 1, pins_int_x3),
	EGRP("INT6_X4", 1, pins_int_x4),
	EGRP("INT6_X5", 1, pins_int_x5),
	EGRP("INT6_X6", 1, pins_int_x6),
	EGRP("INT6_X7", 1, pins_int_x7)
};
static const sppctlgrp_t q645grps_int7[] = {
	EGRP("INT7_X1", 1, pins_int_x1),
	EGRP("INT7_X2", 1, pins_int_x2),
	EGRP("INT7_X3", 1, pins_int_x3),
	EGRP("INT7_X4", 1, pins_int_x4),
	EGRP("INT7_X5", 1, pins_int_x5),
	EGRP("INT7_X6", 1, pins_int_x6),
	EGRP("INT7_X7", 1, pins_int_x7)
};

func_t list_funcs[] = {
	FNCE("SPI_FLASH",       fOFF_G, 1, 0, 1, q645grps_spif),
	FNCE("CARD0_EMMC",      fOFF_G, 1, 1, 1, q645grps_emmc),
	FNCE("SPI_NAND",        fOFF_G, 1, 2, 1, q645grps_snand),
	FNCE("SD_CARD",         fOFF_G, 1, 3, 1, q645grps_sdc30),
	FNCE("SDIO",            fOFF_G, 1, 4, 1, q645grps_sdio30),
	FNCE("UART0",           fOFF_G, 1, 5, 1, q645grps_uart0),
	FNCE("UART1",           fOFF_G, 1, 6, 1, q645grps_uart1),
	FNCE("UART2",           fOFF_G, 1, 9, 1, q645grps_uart2),  // TO BE CONFIRMED
	FNCE("UART3",           fOFF_G, 1,10, 1, q645grps_uart3),  // TO BE CONFIRMED

	FNCE("INT0",            fOFF_G, 2, 0, 3, q645grps_int0),
	FNCE("INT1",            fOFF_G, 2, 3, 3, q645grps_int1),
	FNCE("INT2",            fOFF_G, 2, 6, 3, q645grps_int2),
	FNCE("INT3",            fOFF_G, 2, 9, 3, q645grps_int3),
	FNCE("INT4",            fOFF_G, 2,12, 3, q645grps_int4),
	FNCE("INT5",            fOFF_G, 3, 0, 3, q645grps_int5),
	FNCE("INT6",            fOFF_G, 3, 3, 3, q645grps_int6),
	FNCE("INT7",            fOFF_G, 3, 6, 3, q645grps_int7),

	FNCE("SPI_MASTER0",     fOFF_G, 2,15, 1, q645grps_spim0),  // TO BE CONFIRMED
	FNCE("SPI_SLAVE0",      fOFF_G, 2,15, 1, q645grps_spis0),  // TO BE CONFIRMED
	FNCE("USB2_OTG",        fOFF_G, 2,15, 1, q645grps_u2otg),  // TO BE CONFIRMED
	FNCE("I2C_MASTER0",     fOFF_G, 2,15, 1, q645grps_i2cm0),  // TO BE CONFIRMED
	FNCE("WAKEUP0",         fOFF_G, 2,15, 1, q645grps_wakeup0),  // TO BE CONFIRMED
	FNCE("WAKEUP1",         fOFF_G, 2,15, 1, q645grps_wakeup1)   // TO BE CONFIRMED
};

const int list_funcsSZ = ARRAY_SIZE(list_funcs);