/*******************************************************************************
* File Name: StepA_Buffer.h  
* Version 1.90
*
* Description:
*  This file contains the function prototypes and constants used in
*  the OpAmp (Analog Buffer) Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_StepA_Buffer_H) 
#define CY_OPAMP_StepA_Buffer_H 

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component OpAmp_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
}   StepA_Buffer_BACKUP_STRUCT;

/* Variable describes initial state of the component */
extern uint8 StepA_Buffer_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void StepA_Buffer_Start(void)               ;
void StepA_Buffer_Stop(void)                ;
void StepA_Buffer_SetPower(uint8 power)     ;
void StepA_Buffer_Sleep(void)               ;
void StepA_Buffer_Wakeup(void)              ;
void StepA_Buffer_SaveConfig(void)          ;
void StepA_Buffer_RestoreConfig(void)       ;
void StepA_Buffer_Init(void)                ;
void StepA_Buffer_Enable(void)              ;


/**************************************
*           API Constants
**************************************/

/* Power constants for SetPower() function */
#define StepA_Buffer_LPOCPOWER              (0x00u)
#define StepA_Buffer_LOWPOWER               (0x01u)
#define StepA_Buffer_MEDPOWER               (0x02u)
#define StepA_Buffer_HIGHPOWER              (0x03u)


/**************************************
*           Parameter Defaults        
**************************************/
#define StepA_Buffer_DEFAULT_POWER          (3u)
#define StepA_Buffer_DEFAULT_MODE           (0u)


/**************************************
*             Registers
**************************************/

#define StepA_Buffer_CR_REG                 (* (reg8 *) StepA_Buffer_ABuf__CR)
#define StepA_Buffer_CR_PTR                 (  (reg8 *) StepA_Buffer_ABuf__CR)

#define StepA_Buffer_MX_REG                 (* (reg8 *) StepA_Buffer_ABuf__MX)
#define StepA_Buffer_MX_PTR                 (  (reg8 *) StepA_Buffer_ABuf__MX)

#define StepA_Buffer_SW_REG                 (* (reg8 *) StepA_Buffer_ABuf__SW)
#define StepA_Buffer_SW_PTR                 (  (reg8 *) StepA_Buffer_ABuf__SW)

/* Active mode power manager register */
#define StepA_Buffer_PM_ACT_CFG_REG         (* (reg8 *) StepA_Buffer_ABuf__PM_ACT_CFG)
#define StepA_Buffer_PM_ACT_CFG_PTR         (  (reg8 *) StepA_Buffer_ABuf__PM_ACT_CFG)

/* Alternative mode power manager register */
#define StepA_Buffer_PM_STBY_CFG_REG        (* (reg8 *) StepA_Buffer_ABuf__PM_STBY_CFG)
#define StepA_Buffer_PM_STBY_CFG_PTR        (  (reg8 *) StepA_Buffer_ABuf__PM_STBY_CFG)

/* ANIF.PUMP.CR1 Pump Configuration Register 1 */
#define StepA_Buffer_PUMP_CR1_REG           (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define StepA_Buffer_PUMP_CR1_PTR           (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Trim register defines */
#define StepA_Buffer_TR0_REG                (* (reg8 *) StepA_Buffer_ABuf__TR0)
#define StepA_Buffer_TR0_PTR                (  (reg8 *) StepA_Buffer_ABuf__TR0)

#define StepA_Buffer_TR1_REG                (* (reg8 *) StepA_Buffer_ABuf__TR1)
#define StepA_Buffer_TR1_PTR                (  (reg8 *) StepA_Buffer_ABuf__TR1)


/**************************************
*       Register Constants
**************************************/

/* CX Analog Buffer Input Selection Register */

/* Power mode defines */

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define StepA_Buffer_ACT_PWR_EN             StepA_Buffer_ABuf__PM_ACT_MSK 
/* PM_STBY_CFG (Alternative Active Power Mode CFG Register) mask */ 
#define StepA_Buffer_STBY_PWR_EN            StepA_Buffer_ABuf__PM_STBY_MSK 
/* Power mask */
#define StepA_Buffer_PWR_MASK               (0x03u)

/* MX Analog Buffer Input Selection Register */

/* Bit Field  MX_VN */
#define StepA_Buffer_MX_VN_MASK             (0x30u)
#define StepA_Buffer_MX_VN_NC               (0x00u)
#define StepA_Buffer_MX_VN_AG4              (0x10u)
#define StepA_Buffer_MX_VN_AG6              (0x20u)

/* Bit Field  MX_VP */
#define StepA_Buffer_MX_VP_MASK             (0x0Fu)
#define StepA_Buffer_MX_VP_NC               (0x00u)
#define StepA_Buffer_MX_VP_VREF             (0x09u)
#define StepA_Buffer_MX_VP_AG4              (0x01u)
#define StepA_Buffer_MX_VP_AG5              (0x02u)
#define StepA_Buffer_MX_VP_AG6              (0x03u)
#define StepA_Buffer_MX_VP_AG7              (0x04u)
#define StepA_Buffer_MX_VP_ABUS0            (0x05u)
#define StepA_Buffer_MX_VP_ABUS1            (0x06u)
#define StepA_Buffer_MX_VP_ABUS2            (0x07u)
#define StepA_Buffer_MX_VP_ABUS3            (0x08u)

/* SW Analog Buffer Routing Switch Reg */

/* Bit Field  SW */
#define StepA_Buffer_SW_MASK                (0x07u) 
#define StepA_Buffer_SW_SWINP               (0x04u)  /* Enable positive input */
#define StepA_Buffer_SW_SWINN               (0x02u)  /* Enable negative input */

/* Pump configuration register masks */
#define StepA_Buffer_PUMP_CR1_CLKSEL        (0x40u)
#define StepA_Buffer_PUMP_CR1_FORCE         (0x20u)
#define StepA_Buffer_PUMP_CR1_AUTO          (0x10u)

#endif /* CY_OPAMP_StepA_Buffer_H */


/* [] END OF FILE */
