/*******************************************************************************
* File Name: StepA_InvInput.h  
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

#if !defined(CY_PINS_StepA_InvInput_H) /* Pins StepA_InvInput_H */
#define CY_PINS_StepA_InvInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StepA_InvInput_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 StepA_InvInput__PORT == 15 && ((StepA_InvInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    StepA_InvInput_Write(uint8 value);
void    StepA_InvInput_SetDriveMode(uint8 mode);
uint8   StepA_InvInput_ReadDataReg(void);
uint8   StepA_InvInput_Read(void);
void    StepA_InvInput_SetInterruptMode(uint16 position, uint16 mode);
uint8   StepA_InvInput_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the StepA_InvInput_SetDriveMode() function.
     *  @{
     */
        #define StepA_InvInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define StepA_InvInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define StepA_InvInput_DM_RES_UP          PIN_DM_RES_UP
        #define StepA_InvInput_DM_RES_DWN         PIN_DM_RES_DWN
        #define StepA_InvInput_DM_OD_LO           PIN_DM_OD_LO
        #define StepA_InvInput_DM_OD_HI           PIN_DM_OD_HI
        #define StepA_InvInput_DM_STRONG          PIN_DM_STRONG
        #define StepA_InvInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define StepA_InvInput_MASK               StepA_InvInput__MASK
#define StepA_InvInput_SHIFT              StepA_InvInput__SHIFT
#define StepA_InvInput_WIDTH              1u

/* Interrupt constants */
#if defined(StepA_InvInput__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in StepA_InvInput_SetInterruptMode() function.
     *  @{
     */
        #define StepA_InvInput_INTR_NONE      (uint16)(0x0000u)
        #define StepA_InvInput_INTR_RISING    (uint16)(0x0001u)
        #define StepA_InvInput_INTR_FALLING   (uint16)(0x0002u)
        #define StepA_InvInput_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define StepA_InvInput_INTR_MASK      (0x01u) 
#endif /* (StepA_InvInput__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StepA_InvInput_PS                     (* (reg8 *) StepA_InvInput__PS)
/* Data Register */
#define StepA_InvInput_DR                     (* (reg8 *) StepA_InvInput__DR)
/* Port Number */
#define StepA_InvInput_PRT_NUM                (* (reg8 *) StepA_InvInput__PRT) 
/* Connect to Analog Globals */                                                  
#define StepA_InvInput_AG                     (* (reg8 *) StepA_InvInput__AG)                       
/* Analog MUX bux enable */
#define StepA_InvInput_AMUX                   (* (reg8 *) StepA_InvInput__AMUX) 
/* Bidirectional Enable */                                                        
#define StepA_InvInput_BIE                    (* (reg8 *) StepA_InvInput__BIE)
/* Bit-mask for Aliased Register Access */
#define StepA_InvInput_BIT_MASK               (* (reg8 *) StepA_InvInput__BIT_MASK)
/* Bypass Enable */
#define StepA_InvInput_BYP                    (* (reg8 *) StepA_InvInput__BYP)
/* Port wide control signals */                                                   
#define StepA_InvInput_CTL                    (* (reg8 *) StepA_InvInput__CTL)
/* Drive Modes */
#define StepA_InvInput_DM0                    (* (reg8 *) StepA_InvInput__DM0) 
#define StepA_InvInput_DM1                    (* (reg8 *) StepA_InvInput__DM1)
#define StepA_InvInput_DM2                    (* (reg8 *) StepA_InvInput__DM2) 
/* Input Buffer Disable Override */
#define StepA_InvInput_INP_DIS                (* (reg8 *) StepA_InvInput__INP_DIS)
/* LCD Common or Segment Drive */
#define StepA_InvInput_LCD_COM_SEG            (* (reg8 *) StepA_InvInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define StepA_InvInput_LCD_EN                 (* (reg8 *) StepA_InvInput__LCD_EN)
/* Slew Rate Control */
#define StepA_InvInput_SLW                    (* (reg8 *) StepA_InvInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StepA_InvInput_PRTDSI__CAPS_SEL       (* (reg8 *) StepA_InvInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StepA_InvInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StepA_InvInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StepA_InvInput_PRTDSI__OE_SEL0        (* (reg8 *) StepA_InvInput__PRTDSI__OE_SEL0) 
#define StepA_InvInput_PRTDSI__OE_SEL1        (* (reg8 *) StepA_InvInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StepA_InvInput_PRTDSI__OUT_SEL0       (* (reg8 *) StepA_InvInput__PRTDSI__OUT_SEL0) 
#define StepA_InvInput_PRTDSI__OUT_SEL1       (* (reg8 *) StepA_InvInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StepA_InvInput_PRTDSI__SYNC_OUT       (* (reg8 *) StepA_InvInput__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(StepA_InvInput__SIO_CFG)
    #define StepA_InvInput_SIO_HYST_EN        (* (reg8 *) StepA_InvInput__SIO_HYST_EN)
    #define StepA_InvInput_SIO_REG_HIFREQ     (* (reg8 *) StepA_InvInput__SIO_REG_HIFREQ)
    #define StepA_InvInput_SIO_CFG            (* (reg8 *) StepA_InvInput__SIO_CFG)
    #define StepA_InvInput_SIO_DIFF           (* (reg8 *) StepA_InvInput__SIO_DIFF)
#endif /* (StepA_InvInput__SIO_CFG) */

/* Interrupt Registers */
#if defined(StepA_InvInput__INTSTAT)
    #define StepA_InvInput_INTSTAT            (* (reg8 *) StepA_InvInput__INTSTAT)
    #define StepA_InvInput_SNAP               (* (reg8 *) StepA_InvInput__SNAP)
    
	#define StepA_InvInput_0_INTTYPE_REG 		(* (reg8 *) StepA_InvInput__0__INTTYPE)
#endif /* (StepA_InvInput__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_StepA_InvInput_H */


/* [] END OF FILE */
