/*******************************************************************************
* File Name: StepA_IOut.h  
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

#if !defined(CY_PINS_StepA_IOut_H) /* Pins StepA_IOut_H */
#define CY_PINS_StepA_IOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StepA_IOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 StepA_IOut__PORT == 15 && ((StepA_IOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    StepA_IOut_Write(uint8 value);
void    StepA_IOut_SetDriveMode(uint8 mode);
uint8   StepA_IOut_ReadDataReg(void);
uint8   StepA_IOut_Read(void);
void    StepA_IOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   StepA_IOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the StepA_IOut_SetDriveMode() function.
     *  @{
     */
        #define StepA_IOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define StepA_IOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define StepA_IOut_DM_RES_UP          PIN_DM_RES_UP
        #define StepA_IOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define StepA_IOut_DM_OD_LO           PIN_DM_OD_LO
        #define StepA_IOut_DM_OD_HI           PIN_DM_OD_HI
        #define StepA_IOut_DM_STRONG          PIN_DM_STRONG
        #define StepA_IOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define StepA_IOut_MASK               StepA_IOut__MASK
#define StepA_IOut_SHIFT              StepA_IOut__SHIFT
#define StepA_IOut_WIDTH              1u

/* Interrupt constants */
#if defined(StepA_IOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in StepA_IOut_SetInterruptMode() function.
     *  @{
     */
        #define StepA_IOut_INTR_NONE      (uint16)(0x0000u)
        #define StepA_IOut_INTR_RISING    (uint16)(0x0001u)
        #define StepA_IOut_INTR_FALLING   (uint16)(0x0002u)
        #define StepA_IOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define StepA_IOut_INTR_MASK      (0x01u) 
#endif /* (StepA_IOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StepA_IOut_PS                     (* (reg8 *) StepA_IOut__PS)
/* Data Register */
#define StepA_IOut_DR                     (* (reg8 *) StepA_IOut__DR)
/* Port Number */
#define StepA_IOut_PRT_NUM                (* (reg8 *) StepA_IOut__PRT) 
/* Connect to Analog Globals */                                                  
#define StepA_IOut_AG                     (* (reg8 *) StepA_IOut__AG)                       
/* Analog MUX bux enable */
#define StepA_IOut_AMUX                   (* (reg8 *) StepA_IOut__AMUX) 
/* Bidirectional Enable */                                                        
#define StepA_IOut_BIE                    (* (reg8 *) StepA_IOut__BIE)
/* Bit-mask for Aliased Register Access */
#define StepA_IOut_BIT_MASK               (* (reg8 *) StepA_IOut__BIT_MASK)
/* Bypass Enable */
#define StepA_IOut_BYP                    (* (reg8 *) StepA_IOut__BYP)
/* Port wide control signals */                                                   
#define StepA_IOut_CTL                    (* (reg8 *) StepA_IOut__CTL)
/* Drive Modes */
#define StepA_IOut_DM0                    (* (reg8 *) StepA_IOut__DM0) 
#define StepA_IOut_DM1                    (* (reg8 *) StepA_IOut__DM1)
#define StepA_IOut_DM2                    (* (reg8 *) StepA_IOut__DM2) 
/* Input Buffer Disable Override */
#define StepA_IOut_INP_DIS                (* (reg8 *) StepA_IOut__INP_DIS)
/* LCD Common or Segment Drive */
#define StepA_IOut_LCD_COM_SEG            (* (reg8 *) StepA_IOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define StepA_IOut_LCD_EN                 (* (reg8 *) StepA_IOut__LCD_EN)
/* Slew Rate Control */
#define StepA_IOut_SLW                    (* (reg8 *) StepA_IOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StepA_IOut_PRTDSI__CAPS_SEL       (* (reg8 *) StepA_IOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StepA_IOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StepA_IOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StepA_IOut_PRTDSI__OE_SEL0        (* (reg8 *) StepA_IOut__PRTDSI__OE_SEL0) 
#define StepA_IOut_PRTDSI__OE_SEL1        (* (reg8 *) StepA_IOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StepA_IOut_PRTDSI__OUT_SEL0       (* (reg8 *) StepA_IOut__PRTDSI__OUT_SEL0) 
#define StepA_IOut_PRTDSI__OUT_SEL1       (* (reg8 *) StepA_IOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StepA_IOut_PRTDSI__SYNC_OUT       (* (reg8 *) StepA_IOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(StepA_IOut__SIO_CFG)
    #define StepA_IOut_SIO_HYST_EN        (* (reg8 *) StepA_IOut__SIO_HYST_EN)
    #define StepA_IOut_SIO_REG_HIFREQ     (* (reg8 *) StepA_IOut__SIO_REG_HIFREQ)
    #define StepA_IOut_SIO_CFG            (* (reg8 *) StepA_IOut__SIO_CFG)
    #define StepA_IOut_SIO_DIFF           (* (reg8 *) StepA_IOut__SIO_DIFF)
#endif /* (StepA_IOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(StepA_IOut__INTSTAT)
    #define StepA_IOut_INTSTAT            (* (reg8 *) StepA_IOut__INTSTAT)
    #define StepA_IOut_SNAP               (* (reg8 *) StepA_IOut__SNAP)
    
	#define StepA_IOut_0_INTTYPE_REG 		(* (reg8 *) StepA_IOut__0__INTTYPE)
#endif /* (StepA_IOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_StepA_IOut_H */


/* [] END OF FILE */
