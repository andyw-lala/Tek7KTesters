/*******************************************************************************
* File Name: Readout.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_Readout_H)
#define CY_SHIFTREG_Readout_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Readout_FIFO_SIZE          (4u)
#define Readout_USE_INPUT_FIFO     (0u)
#define Readout_USE_OUTPUT_FIFO    (0u)
#define Readout_SR_SIZE            (16u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint16 saveSrA0Reg;
    uint16 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint16 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} Readout_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Readout_Start(void)                              ;
void  Readout_Stop(void)                               ;
void  Readout_Init(void)                               ;
void  Readout_Enable(void)                             ;
void  Readout_RestoreConfig(void)                      ;
void  Readout_SaveConfig(void)                         ;
void  Readout_Sleep(void)                              ;
void  Readout_Wakeup(void)                             ;
void  Readout_EnableInt(void)                          ;
void  Readout_DisableInt(void)                         ;
void  Readout_SetIntMode(uint8 interruptSource)        ;
uint8 Readout_GetIntStatus(void)                       ;
void  Readout_WriteRegValue(uint16 shiftData) \
                                                                ;
uint16 Readout_ReadRegValue(void) ;
uint8    Readout_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != Readout_USE_INPUT_FIFO)
    cystatus Readout_WriteData(uint16 shiftData) \
                                                                ;
#endif /* (0u != Readout_USE_INPUT_FIFO) */

#if(0u != Readout_USE_OUTPUT_FIFO)
    uint16 Readout_ReadData(void) ;
#endif /* (0u != Readout_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 Readout_initVar;


/***************************************
*           API Constants
***************************************/

#define Readout_LOAD                   (0x01u)
#define Readout_STORE                  (0x02u)
#define Readout_RESET                  (0x04u)

#define Readout_IN_FIFO                (0x01u)
#define Readout_OUT_FIFO               (0x02u)

#define Readout_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define Readout_RET_FIFO_NOT_EMPTY     (0x01u)

#define Readout_RET_FIFO_PARTIAL       (0x01u)
#define Readout_RET_FIFO_EMPTY         (0x02u)
#define Readout_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Readout__LEFT 0
#define Readout__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define Readout_SR_MASK    (0xFFFFu) /* Unsigned is added to parameter */
#define Readout_INT_SRC    (0u)
#define Readout_DIRECTION  (0u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define Readout_SR_CONTROL_REG (* (reg8 *) \
                                           Readout_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define Readout_SR_CONTROL_PTR (  (reg8 *) \
                                           Readout_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define Readout_SR_STATUS_REG      (* (reg8 *) Readout_bSR_StsReg__STATUS_REG)
#define Readout_SR_STATUS_PTR      (  (reg8 *) Readout_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define Readout_SR_STATUS_MASK_REG (* (reg8 *) Readout_bSR_StsReg__MASK_REG)
#define Readout_SR_STATUS_MASK_PTR (  (reg8 *) Readout_bSR_StsReg__MASK_REG)

/* Aux control register */
#define Readout_SR_AUX_CONTROL_REG (* (reg8 *) Readout_bSR_StsReg__STATUS_AUX_CTL_REG)
#define Readout_SR_AUX_CONTROL_PTR (  (reg8 *) Readout_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define Readout_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define Readout_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__F0_REG )

    #define Readout_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A0_REG )

    #define Readout_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A1_REG )

    #define Readout_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__F1_REG )

#else
    #if(Readout_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define Readout_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define Readout_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define Readout_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define Readout_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #elif(Readout_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define Readout_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__16BIT_F0_REG )

        #define Readout_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__16BIT_A0_REG )

        #define Readout_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__16BIT_A1_REG )

        #define Readout_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(Readout_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define Readout_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define Readout_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define Readout_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define Readout_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        Readout_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define Readout_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__32BIT_F0_REG )

        #define Readout_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__32BIT_A0_REG )

        #define Readout_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__32BIT_A1_REG )

        #define Readout_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  Readout_bSR_sC16_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (Readout_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define Readout_INTERRUPTS_ENABLE      (0x10u)
#define Readout_LOAD_INT_EN            (0x01u)
#define Readout_STORE_INT_EN           (0x02u)
#define Readout_RESET_INT_EN           (0x04u)
#define Readout_CLK_EN                 (0x01u)

#define Readout_RESET_INT_EN_MASK      (0xFBu)
#define Readout_LOAD_INT_EN_MASK       (0xFEu)
#define Readout_STORE_INT_EN_MASK      (0xFDu)
#define Readout_INTS_EN_MASK           (0x07u)

#define Readout_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != Readout_USE_INPUT_FIFO)

    #define Readout_IN_FIFO_MASK       (0x18u)

    #define Readout_IN_FIFO_FULL       (0x00u)
    #define Readout_IN_FIFO_EMPTY      (0x01u)
    #define Readout_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define Readout_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != Readout_USE_INPUT_FIFO) */

#define Readout_OUT_FIFO_MASK          (0x60u)

#define Readout_OUT_FIFO_EMPTY         (0x00u)
#define Readout_OUT_FIFO_FULL          (0x01u)
#define Readout_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define Readout_OUT_FIFO_NOT_EMPTY     (0x02u)

#define Readout_IN_FIFO_SHIFT_MASK     (0x03u)
#define Readout_OUT_FIFO_SHIFT_MASK    (0x05u)

#define Readout_DISABLED               (0u)
#define Readout_DEFAULT_A0             (0u)
#define Readout_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define Readout_IS_ENABLED         (0u != (Readout_SR_CONTROL & Readout_CLK_EN))

#define Readout_GET_OUT_FIFO_STS   ((Readout_SR_STATUS & Readout_OUT_FIFO_MASK) >> \
                                              Readout_OUT_FIFO_SHIFT_MASK)

#define Readout_GET_IN_FIFO_STS    ((Readout_SR_STATUS & Readout_IN_FIFO_MASK)  >> \
                                              Readout_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define Readout_SR_CONTROL     (Readout_SR_CONTROL_REG)
#define Readout_SR_STATUS      (Readout_SR_STATUS_REG)
#define Readout_SR_STATUS_MASK (Readout_SR_STATUS_MASK_REG)
#define Readout_SR_AUX_CONTROL (Readout_SR_AUX_CONTROL_REG)

#define Readout_IN_FIFO_SHFT_MASK  (Readout_IN_FIFO_SHIFT_MASK)
#define Readout_OUT_FIFO_SHFT_MASK (Readout_OUT_FIFO_SHFIT_MASK)

#define Readout_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_Readout_H) */


/* [] END OF FILE */
