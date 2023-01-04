/*******************************************************************************
* File Name: StepY_VOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_StepY_VOut_H) /* Pins StepY_VOut_H */
#define CY_PINS_StepY_VOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StepY_VOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 StepY_VOut__PORT == 15 && ((StepY_VOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    StepY_VOut_Write(uint8 value);
void    StepY_VOut_SetDriveMode(uint8 mode);
uint8   StepY_VOut_ReadDataReg(void);
uint8   StepY_VOut_Read(void);
void    StepY_VOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   StepY_VOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the StepY_VOut_SetDriveMode() function.
     *  @{
     */
        #define StepY_VOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define StepY_VOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define StepY_VOut_DM_RES_UP          PIN_DM_RES_UP
        #define StepY_VOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define StepY_VOut_DM_OD_LO           PIN_DM_OD_LO
        #define StepY_VOut_DM_OD_HI           PIN_DM_OD_HI
        #define StepY_VOut_DM_STRONG          PIN_DM_STRONG
        #define StepY_VOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define StepY_VOut_MASK               StepY_VOut__MASK
#define StepY_VOut_SHIFT              StepY_VOut__SHIFT
#define StepY_VOut_WIDTH              1u

/* Interrupt constants */
#if defined(StepY_VOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in StepY_VOut_SetInterruptMode() function.
     *  @{
     */
        #define StepY_VOut_INTR_NONE      (uint16)(0x0000u)
        #define StepY_VOut_INTR_RISING    (uint16)(0x0001u)
        #define StepY_VOut_INTR_FALLING   (uint16)(0x0002u)
        #define StepY_VOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define StepY_VOut_INTR_MASK      (0x01u) 
#endif /* (StepY_VOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StepY_VOut_PS                     (* (reg8 *) StepY_VOut__PS)
/* Data Register */
#define StepY_VOut_DR                     (* (reg8 *) StepY_VOut__DR)
/* Port Number */
#define StepY_VOut_PRT_NUM                (* (reg8 *) StepY_VOut__PRT) 
/* Connect to Analog Globals */                                                  
#define StepY_VOut_AG                     (* (reg8 *) StepY_VOut__AG)                       
/* Analog MUX bux enable */
#define StepY_VOut_AMUX                   (* (reg8 *) StepY_VOut__AMUX) 
/* Bidirectional Enable */                                                        
#define StepY_VOut_BIE                    (* (reg8 *) StepY_VOut__BIE)
/* Bit-mask for Aliased Register Access */
#define StepY_VOut_BIT_MASK               (* (reg8 *) StepY_VOut__BIT_MASK)
/* Bypass Enable */
#define StepY_VOut_BYP                    (* (reg8 *) StepY_VOut__BYP)
/* Port wide control signals */                                                   
#define StepY_VOut_CTL                    (* (reg8 *) StepY_VOut__CTL)
/* Drive Modes */
#define StepY_VOut_DM0                    (* (reg8 *) StepY_VOut__DM0) 
#define StepY_VOut_DM1                    (* (reg8 *) StepY_VOut__DM1)
#define StepY_VOut_DM2                    (* (reg8 *) StepY_VOut__DM2) 
/* Input Buffer Disable Override */
#define StepY_VOut_INP_DIS                (* (reg8 *) StepY_VOut__INP_DIS)
/* LCD Common or Segment Drive */
#define StepY_VOut_LCD_COM_SEG            (* (reg8 *) StepY_VOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define StepY_VOut_LCD_EN                 (* (reg8 *) StepY_VOut__LCD_EN)
/* Slew Rate Control */
#define StepY_VOut_SLW                    (* (reg8 *) StepY_VOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StepY_VOut_PRTDSI__CAPS_SEL       (* (reg8 *) StepY_VOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StepY_VOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StepY_VOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StepY_VOut_PRTDSI__OE_SEL0        (* (reg8 *) StepY_VOut__PRTDSI__OE_SEL0) 
#define StepY_VOut_PRTDSI__OE_SEL1        (* (reg8 *) StepY_VOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StepY_VOut_PRTDSI__OUT_SEL0       (* (reg8 *) StepY_VOut__PRTDSI__OUT_SEL0) 
#define StepY_VOut_PRTDSI__OUT_SEL1       (* (reg8 *) StepY_VOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StepY_VOut_PRTDSI__SYNC_OUT       (* (reg8 *) StepY_VOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(StepY_VOut__SIO_CFG)
    #define StepY_VOut_SIO_HYST_EN        (* (reg8 *) StepY_VOut__SIO_HYST_EN)
    #define StepY_VOut_SIO_REG_HIFREQ     (* (reg8 *) StepY_VOut__SIO_REG_HIFREQ)
    #define StepY_VOut_SIO_CFG            (* (reg8 *) StepY_VOut__SIO_CFG)
    #define StepY_VOut_SIO_DIFF           (* (reg8 *) StepY_VOut__SIO_DIFF)
#endif /* (StepY_VOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(StepY_VOut__INTSTAT)
    #define StepY_VOut_INTSTAT            (* (reg8 *) StepY_VOut__INTSTAT)
    #define StepY_VOut_SNAP               (* (reg8 *) StepY_VOut__SNAP)
    
	#define StepY_VOut_0_INTTYPE_REG 		(* (reg8 *) StepY_VOut__0__INTTYPE)
#endif /* (StepY_VOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_StepY_VOut_H */


/* [] END OF FILE */
