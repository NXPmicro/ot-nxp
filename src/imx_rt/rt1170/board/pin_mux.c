/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MIMXRT1176xxxxx
package_id: MIMXRT1176DVMAA
mcu_data: ksdk2_0
processor_version: 0.10.5
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "pin_mux.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
    BOARD_InitUSDHCPins();
    BOARD_InitSPIPins();

    /* Init the reset pin */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_10_GPIO_MUX3_IO09, /* GPIO_AD_10 is configured as GPIO_MUX3_IO09 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_GPR->GPR42 =
        ((IOMUXC_GPR->GPR42 &
          (~(IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW_MASK))) /* Mask bits to zero which are setting */
         | IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW(
               0x00U) /* GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function: 0x00U */
        );

#ifdef OT_PLAT_SPINEL_OVER_SPI
    BOARD_InitArduinoSPIPins();
#else
    BOARD_InitArduinoUARTPins();
#endif
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: M15, peripheral: LPUART1, signal: RXD, pin_signal: GPIO_AD_25, software_input_on: Disable,
pull_up_down_config: Pull_Down, pull_keeper_select: Keeper, open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: L13, peripheral: LPUART1, signal: TXD, pin_signal: GPIO_AD_24, software_input_on: Disable,
pull_up_down_config: Pull_Down, pull_keeper_select: Keeper, open_drain: Disable, drive_strength: High, slew_rate: Slow}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_24_LPUART1_TXD, /* GPIO_AD_24 is configured as LPUART1_TXD */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_25_LPUART1_RXD, /* GPIO_AD_25 is configured as LPUART1_RXD */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_24_LPUART1_TXD,   /* GPIO_AD_24 PAD functional properties : */
                        0x02U);                          /* Slew Rate Field: Slow Slew Rate
                                                            Drive Strength Field: high drive strength
                                                            Pull / Keep Select Field: Pull Disable, Highz
                                                            Pull Up / Down Config. Field: Weak pull down
                                                            Open Drain Field: Disabled
                                                            Domain write protection: Both cores are allowed
                                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_25_LPUART1_RXD,   /* GPIO_AD_25 PAD functional properties : */
                        0x02U);                          /* Slew Rate Field: Slow Slew Rate
                                                            Drive Strength Field: high drive strength
                                                            Pull / Keep Select Field: Pull Disable, Highz
                                                            Pull Up / Down Config. Field: Weak pull down
                                                            Open Drain Field: Disabled
                                                            Domain write protection: Both cores are allowed
                                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_10_LPUART2_TXD, /* GPIO_DISP_B2_10 is configured as LPUART2_TXD */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSDHCPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: A16, peripheral: USDHC1, signal: 'usdhc_data, 3', pin_signal: GPIO_SD_B1_05, software_input_on: Enable,
pull_down_pull_up_config: Pull_Up}
  - {pin_num: B15, peripheral: USDHC1, signal: 'usdhc_data, 2', pin_signal: GPIO_SD_B1_04, software_input_on: Enable,
pull_down_pull_up_config: Pull_Up}
  - {pin_num: B17, peripheral: USDHC1, signal: 'usdhc_data, 1', pin_signal: GPIO_SD_B1_03, software_input_on: Enable,
pull_down_pull_up_config: Pull_Up}
  - {pin_num: C15, peripheral: USDHC1, signal: 'usdhc_data, 0', pin_signal: GPIO_SD_B1_02, software_input_on: Enable,
pull_down_pull_up_config: Pull_Up}
  - {pin_num: B16, peripheral: USDHC1, signal: usdhc_cmd, pin_signal: GPIO_SD_B1_00, software_input_on: Enable,
pull_down_pull_up_config: Pull_Up}
  - {pin_num: D15, peripheral: USDHC1, signal: usdhc_clk, pin_signal: GPIO_SD_B1_01, software_input_on: Enable,
pull_down_pull_up_config: No_Pull}
  - {pin_num: J16, peripheral: USDHC1, signal: usdhc_vselect, pin_signal: GPIO_AD_34}
  - {pin_num: G17, peripheral: GPIO10, signal: 'gpio_io, 02', pin_signal: GPIO_AD_35}
  - {pin_num: K16, peripheral: CM7_GPIO3, signal: 'gpio_mux_io_cm7, 31', pin_signal: GPIO_AD_32}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitUSDHCPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitUSDHCPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_32_GPIO_MUX3_IO31, /* GPIO_AD_32 is configured as GPIO_MUX3_IO31 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_34_USDHC1_VSELECT, /* GPIO_AD_34 is configured as USDHC1_VSELECT */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_35_GPIO10_IO02, /* GPIO_AD_35 is configured as GPIO10_IO02 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_USDHC1_CMD, /* GPIO_SD_B1_00 is configured as USDHC1_CMD */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B1_00 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_USDHC1_CLK, /* GPIO_SD_B1_01 is configured as USDHC1_CLK */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B1_01 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_USDHC1_DATA0, /* GPIO_SD_B1_02 is configured as USDHC1_DATA0 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B1_02 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_USDHC1_DATA1, /* GPIO_SD_B1_03 is configured as USDHC1_DATA1 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B1_03 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_USDHC1_DATA2, /* GPIO_SD_B1_04 is configured as USDHC1_DATA2 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B1_04 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_05_USDHC1_DATA3, /* GPIO_SD_B1_05 is configured as USDHC1_DATA3 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B1_05 */
    IOMUXC_GPR->GPR43 =
        ((IOMUXC_GPR->GPR43 &
          (~(IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_MASK))) /* Mask bits to zero which are setting */
         |
         IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH(
             0x8000U) /* GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function: 0x8000U */
        );
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_USDHC1_CMD,   /* GPIO_SD_B1_00 PAD functional properties : */
                        0x04U);                            /* PDRV Field: high drive strength
                                                              Pull Down Pull Up Field: Internal pullup resistor enabled
                                                              Open Drain Field: Disabled
                                                              Domain write protection: Both cores are allowed
                                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_USDHC1_CLK,   /* GPIO_SD_B1_01 PAD functional properties : */
                        0x0CU);                            /* PDRV Field: high drive strength
                                                              Pull Down Pull Up Field: No Pull
                                                              Open Drain Field: Disabled
                                                              Domain write protection: Both cores are allowed
                                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_02_USDHC1_DATA0, /* GPIO_SD_B1_02 PAD functional properties : */
                        0x04U);                            /* PDRV Field: high drive strength
                                                              Pull Down Pull Up Field: Internal pullup resistor enabled
                                                              Open Drain Field: Disabled
                                                              Domain write protection: Both cores are allowed
                                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_03_USDHC1_DATA1, /* GPIO_SD_B1_03 PAD functional properties : */
                        0x04U);                            /* PDRV Field: high drive strength
                                                              Pull Down Pull Up Field: Internal pullup resistor enabled
                                                              Open Drain Field: Disabled
                                                              Domain write protection: Both cores are allowed
                                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_USDHC1_DATA2, /* GPIO_SD_B1_04 PAD functional properties : */
                        0x04U);                            /* PDRV Field: high drive strength
                                                              Pull Down Pull Up Field: Internal pullup resistor enabled
                                                              Open Drain Field: Disabled
                                                              Domain write protection: Both cores are allowed
                                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_05_USDHC1_DATA3, /* GPIO_SD_B1_05 PAD functional properties : */
                        0x04U);                            /* PDRV Field: high drive strength
                                                              Pull Down Pull Up Field: Internal pullup resistor enabled
                                                              Open Drain Field: Disabled
                                                              Domain write protection: Both cores are allowed
                                                              Domain write protection lock: Neither of DWP bits is locked */
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitArduinoUARTPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: R13, peripheral: LPUART7, signal: CTS_B, pin_signal: GPIO_AD_02, software_input_on: Disable,
pull_keeper_select: Keeper}
  - {pin_num: P15, peripheral: LPUART7, signal: RTS_B, pin_signal: GPIO_AD_03, software_input_on: Disable,
pull_keeper_select: Keeper}
  - {pin_num: N12, peripheral: LPUART7, signal: TXD, pin_signal: GPIO_AD_00, pull_up_down_config: Pull_Down,
pull_keeper_select: Keeper}
  - {pin_num: R14, peripheral: LPUART7, signal: RXD, pin_signal: GPIO_AD_01, pull_up_down_config: Pull_Down,
pull_keeper_select: Keeper}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitArduinoUARTPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitArduinoUARTPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_02_LPUART7_CTS_B, /* GPIO_AD_02 is configured as LPUART7_CTS_B */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_03_LPUART7_RTS_B, /* GPIO_AD_03 is configured as LPUART7_RTS_B */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_00_LPUART7_TXD, /* GPIO_AD_00 is configured as LPUART7_TXD */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_01_LPUART7_RXD, /* GPIO_AD_01 is configured as LPUART7_RXD */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_02_LPUART7_CTS_B, /* GPIO_AD_02 PAD functional properties : */
                        0x02U);                          /* Slew Rate Field: Slow Slew Rate
                                                            Drive Strength Field: high drive strength
                                                            Pull / Keep Select Field: Pull Disable, Highz
                                                            Pull Up / Down Config. Field: Weak pull down
                                                            Open Drain Field: Disabled
                                                            Domain write protection: Both cores are allowed
                                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_03_LPUART7_RTS_B, /* GPIO_AD_03 PAD functional properties : */
                        0x02U);                          /* Slew Rate Field: Slow Slew Rate
                                                            Drive Strength Field: high drive strength
                                                            Pull / Keep Select Field: Pull Disable, Highz
                                                            Pull Up / Down Config. Field: Weak pull down
                                                            Open Drain Field: Disabled
                                                            Domain write protection: Both cores are allowed
                                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_00_LPUART7_TXD,   /* GPIO_AD_00 PAD functional properties : */
                        0x02U);                          /* Slew Rate Field: Slow Slew Rate
                                                            Drive Strength Field: high drive strength
                                                            Pull / Keep Select Field: Pull Disable, Highz
                                                            Pull Up / Down Config. Field: Weak pull down
                                                            Open Drain Field: Disabled
                                                            Domain write protection: Both cores are allowed
                                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_01_LPUART7_RXD,   /* GPIO_AD_01 PAD functional properties : */
                        0x02U);                          /* Slew Rate Field: Slow Slew Rate
                                                            Drive Strength Field: high drive strength
                                                            Pull / Keep Select Field: Pull Disable, Highz
                                                            Pull Up / Down Config. Field: Weak pull down
                                                            Open Drain Field: Disabled
                                                            Domain write protection: Both cores are allowed
                                                            Domain write protection lock: Neither of DWP bits is locked */
}

void BOARD_InitArduinoSPIPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_11_GPIO_MUX3_IO10, /* GPIO_AD_11 is configured as GPIO_MUX3_IO10 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_28_LPSPI1_SCK, /* GPIO_AD_28 is configured as LPSPI1_SCK */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_29_LPSPI1_PCS0, /* GPIO_AD_29 is configured as LPSPI1_PCS0 */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_30_LPSPI1_SOUT, /* GPIO_AD_30 is configured as LPSPI1_SOUT */
                     0U); /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_31_LPSPI1_SIN, /* GPIO_AD_31 is configured as LPSPI1_SIN */
                     0U); /* Software Input On Field: Input Path is determined by functionality */

    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_28_LPSPI1_SCK,  /* GPIO_AD_28 PAD functional properties : */
                        0x02U);                        /* Slew Rate Field: Slow Slew Rate
                                                          Drive Strength Field: high drive strength
                                                          Pull / Keep Select Field: Pull Disable, Highz
                                                          Pull Up / Down Config. Field: Weak pull down
                                                          Open Drain Field: Disabled
                                                          Domain write protection: Both cores are allowed
                                                          Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_29_LPSPI1_PCS0, /* GPIO_AD_29 PAD functional properties : */
                        0x02U);                        /* Slew Rate Field: Slow Slew Rate
                                                          Drive Strength Field: high drive strength
                                                          Pull / Keep Select Field: Pull Disable, Highz
                                                          Pull Up / Down Config. Field: Weak pull down
                                                          Open Drain Field: Disabled
                                                          Domain write protection: Both cores are allowed
                                                          Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_30_LPSPI1_SOUT, /* GPIO_AD_30 PAD functional properties : */
                        0x02U);                        /* Slew Rate Field: Slow Slew Rate
                                                          Drive Strength Field: high drive strength
                                                          Pull / Keep Select Field: Pull Disable, Highz
                                                          Pull Up / Down Config. Field: Weak pull down
                                                          Open Drain Field: Disabled
                                                          Domain write protection: Both cores are allowed
                                                          Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_31_LPSPI1_SIN,  /* GPIO_AD_31 PAD functional properties : */
                        0x02U);                        /* Slew Rate Field: Slow Slew Rate
                                                          Drive Strength Field: high drive strength
                                                          Pull / Keep Select Field: Pull Disable, Highz
                                                          Pull Up / Down Config. Field: Weak pull down
                                                          Open Drain Field: Disabled
                                                          Domain write protection: Both cores are allowed
                                                          Domain write protection lock: Neither of DWP bits is locked */
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSPIPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: E14, peripheral: FLEXSPI1, signal: FLEXSPI_A_DQS, pin_signal: GPIO_SD_B2_05, software_input_on: Enable,
pull_down_pull_up_config: Pull_Down, pdrv_config: Normal_Driver}
  - {pin_num: F17, peripheral: FLEXSPI1, signal: FLEXSPI_A_SS0_B, pin_signal: GPIO_SD_B2_06, software_input_on: Enable,
pull_down_pull_up_config: Pull_Down, pdrv_config: Normal_Driver}
  - {pin_num: G14, peripheral: FLEXSPI1, signal: FLEXSPI_A_SCLK, pin_signal: GPIO_SD_B2_07, software_input_on: Enable,
pdrv_config: Normal_Driver}
  - {pin_num: F15, peripheral: FLEXSPI1, signal: FLEXSPI_A_DATA0, pin_signal: GPIO_SD_B2_08, software_input_on: Enable,
pdrv_config: Normal_Driver}
  - {pin_num: H15, peripheral: FLEXSPI1, signal: FLEXSPI_A_DATA1, pin_signal: GPIO_SD_B2_09, software_input_on: Enable,
pdrv_config: Normal_Driver}
  - {pin_num: H14, peripheral: FLEXSPI1, signal: FLEXSPI_A_DATA2, pin_signal: GPIO_SD_B2_10, software_input_on: Enable,
pdrv_config: Normal_Driver}
  - {pin_num: F16, peripheral: FLEXSPI1, signal: FLEXSPI_A_DATA3, pin_signal: GPIO_SD_B2_11, software_input_on: Enable,
pdrv_config: Normal_Driver}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSPIPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitSPIPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_05_FLEXSPI1_A_DQS, /* GPIO_SD_B2_05 is configured as FLEXSPI1_A_DQS */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_05 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_06_FLEXSPI1_A_SS0_B, /* GPIO_SD_B2_06 is configured as FLEXSPI1_A_SS0_B */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_06 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_07_FLEXSPI1_A_SCLK, /* GPIO_SD_B2_07 is configured as FLEXSPI1_A_SCLK */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_07 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_08_FLEXSPI1_A_DATA00, /* GPIO_SD_B2_08 is configured as FLEXSPI1_A_DATA00 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_08 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_09_FLEXSPI1_A_DATA01, /* GPIO_SD_B2_09 is configured as FLEXSPI1_A_DATA01 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_09 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_10_FLEXSPI1_A_DATA02, /* GPIO_SD_B2_10 is configured as FLEXSPI1_A_DATA02 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_10 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_11_FLEXSPI1_A_DATA03, /* GPIO_SD_B2_11 is configured as FLEXSPI1_A_DATA03 */
                     1U); /* Software Input On Field: Force input path of pad GPIO_SD_B2_11 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_05_FLEXSPI1_A_DQS,    /* GPIO_SD_B2_05 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_06_FLEXSPI1_A_SS0_B,  /* GPIO_SD_B2_06 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_07_FLEXSPI1_A_SCLK,   /* GPIO_SD_B2_07 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_08_FLEXSPI1_A_DATA00, /* GPIO_SD_B2_08 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_09_FLEXSPI1_A_DATA01, /* GPIO_SD_B2_09 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_10_FLEXSPI1_A_DATA02, /* GPIO_SD_B2_10 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_11_FLEXSPI1_A_DATA03, /* GPIO_SD_B2_11 PAD functional properties : */
                        0x0AU);                                 /* PDRV Field: normal drive strength
                                                                   Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                                   Open Drain Field: Disabled
                                                                   Domain write protection: Both cores are allowed
                                                                   Domain write protection lock: Neither of DWP bits is locked */
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/