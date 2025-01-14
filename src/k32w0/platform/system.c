/*
 *  Copyright (c) 2019, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes the platform-specific initializers.
 *
 */
#include "board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "platform-k32w.h"
#include "utils/uart.h"

#include "MemManager.h"

#include <stdbool.h>
#include <stdint.h>

#if ((defined(gClkUseFro32K) && (gClkUseFro32K == 1)) || (defined(gPWR_CpuClk_48MHz) && (gPWR_CpuClk_48MHz == 1))) && \
    (cPWR_FullPowerDownMode == 0)
#include "TimersManager.h"
#include <utils/code_utils.h>

#ifndef FRO32K_CALIBRATION_LOOPS
#define FRO32K_CALIBRATION_LOOPS 500
#endif

#ifndef FRO48M_CALIBRATION_LOOPS
#define FRO48M_CALIBRATION_LOOPS 500
#endif

typedef void (*pFroCalibrationStart)(void);
typedef uint32_t (*pFroCompleteCalibration)(void);

typedef struct
{
    pFroCalibrationStart    pfFroCalibrationStart;
    pFroCompleteCalibration pfFroCompleteCalibration;
    uint32_t                calibrationLoops;
} FroCalibrationFunctions_t;

const FroCalibrationFunctions_t mFroCalibFuncTable[] = {
#if (defined(gClkUseFro32K) && (gClkUseFro32K == 1))
    {FRO32K_StartCalibration, FRO32K_CompleteCalibration, FRO32K_CALIBRATION_LOOPS},
#endif
#if (defined(gPWR_CpuClk_48MHz) && (gPWR_CpuClk_48MHz == 1))
    {FRO48M_StartCalibration, FRO48M_CompleteCalibration, FRO48M_CALIBRATION_LOOPS},
#endif
};

const uint8_t sizeOfFroCalibrationTable = otARRAY_LENGTH(mFroCalibFuncTable);

#endif /* ((defined(gClkUseFro32K) && (gClkUseFro32K == 1)) || (defined(gPWR_CpuClk_48MHz) && \
          (gPWR_CpuClk_48MHz == 1))) && (cPWR_FullPowerDownMode == 0) */

otInstance           *sInstance;
OT_TOOL_WEAK uint32_t gInterruptDisableCount = 0;

void hardware_init(void);
#ifdef OT_PLAT_SPI_SUPPORT
extern void BOARD_InitSPI1Pins(void);
#endif
void K32WFroCalibration(void);

void otSysInit(int argc, char *argv[])
{
#ifdef OT_PLAT_SPI_SUPPORT
    BOARD_InitSPI1Pins();
#endif
#ifdef OT_PLAT_BOARD_INIT
    bool bHwInit = true;

    if ((argc == 1) && (!strcmp(argv[0], "app")))
    {
        bHwInit = false;
    }

    if (bHwInit)
    {
        hardware_init();
        BOARD_InitPins();

        K32WRandomInit();
        MEM_Init();
    }
#endif

    K32WAlarmInit();
    K32WRadioInit();

#if (OPENTHREAD_CONFIG_LOG_OUTPUT == OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED)
    K32WLogInit();
#endif
}

bool otSysPseudoResetWasRequested(void)
{
    /* TODO */
    return false;
}

void otSysDeinit(void)
{
    /* TODO */
}

void otSysProcessDrivers(otInstance *aInstance)
{
    K32WUartProcess();
    K32WRadioProcess(aInstance);
    K32WAlarmProcess(aInstance);
#ifdef OT_PLAT_SPI_SUPPORT
    K32WSpiSlaveProcess();
#endif
/* Do FRO (32k and/or 48M) calibration for non low power apps.
   K32W0 SDK will handle the calibration if low power is enabled */
#if ((defined(gClkUseFro32K) && (gClkUseFro32K == 1)) || (defined(gPWR_CpuClk_48MHz) && (gPWR_CpuClk_48MHz == 1))) && \
    (cPWR_FullPowerDownMode == 0)
    K32WFroCalibration();
#endif /* ((defined(gClkUseFro32K) && (gClkUseFro32K == 1)) || (defined(gPWR_CpuClk_48MHz) && \
          (gPWR_CpuClk_48MHz == 1))) && (cPWR_FullPowerDownMode == 0) */
}

WEAK void otSysEventSignalPending(void)
{
    /* Intentionally left empty */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptEnable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
OT_TOOL_WEAK void OSA_InterruptEnable(void)
{
    if (gInterruptDisableCount > 0)
    {
        gInterruptDisableCount--;

        if (gInterruptDisableCount == 0)
        {
            __enable_irq();
        }
        /* call core API to enable the global interrupt*/
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InterruptDisable
 * Description   : self explanatory.
 *
 *END**************************************************************************/
OT_TOOL_WEAK void OSA_InterruptDisable(void)
{
    /* call core API to disable the global interrupt*/
    __disable_irq();

    /* update counter*/
    gInterruptDisableCount++;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OSA_InstallIntHandler
 * Description   : This function is used to install interrupt handler.
 *
 *END**************************************************************************/
OT_TOOL_WEAK void OSA_InstallIntHandler(uint32_t IRQNumber, void (*handler)(void))
{
#ifdef ENABLE_RAM_VECTOR_TABLE
    InstallIRQHandler((IRQn_Type)IRQNumber, (uint32_t)handler);
#endif
}

#if ((defined(gClkUseFro32K) && (gClkUseFro32K == 1)) || (defined(gPWR_CpuClk_48MHz) && (gPWR_CpuClk_48MHz == 1))) && \
    (cPWR_FullPowerDownMode == 0)
/*FUNCTION**********************************************************************
 *
 * Function Name : K32WFroCalibration
 * Description   : This function is used to trigger a calibration of the enabled
 *                 FROs (FRO32k and/or FRO48M)
 *
 *END**************************************************************************/
void K32WFroCalibration(void)
{
    /* Variable to store if calibration started */
    static bool     bCalibStarted        = false;
    static uint32_t u32ProcessLoopCounts = 0;
    static uint8_t  indexOfCalibration   = 0;

    if (!bCalibStarted && (u32ProcessLoopCounts >= mFroCalibFuncTable[indexOfCalibration].calibrationLoops))
    {
        mFroCalibFuncTable[indexOfCalibration].pfFroCalibrationStart();
        /* Calibration started */
        bCalibStarted = true;
    }
    else
    {
        if (bCalibStarted)
        {
            uint32_t u32FreqComp;

            if ((u32FreqComp = mFroCalibFuncTable[indexOfCalibration].pfFroCompleteCalibration()) != 0)
            {
                /* Reset calibration state */
                bCalibStarted        = false;
                u32ProcessLoopCounts = 0;
                indexOfCalibration++;

                if (indexOfCalibration >= sizeOfFroCalibrationTable)
                {
                    indexOfCalibration = 0;
                }
            }
        }
        else
        {
            u32ProcessLoopCounts++;
        }
    }
}
#endif /* ((defined(gClkUseFro32K) && (gClkUseFro32K == 1)) || (defined(gPWR_CpuClk_48MHz) && \
          (gPWR_CpuClk_48MHz == 1))) && (cPWR_FullPowerDownMode == 0) */
