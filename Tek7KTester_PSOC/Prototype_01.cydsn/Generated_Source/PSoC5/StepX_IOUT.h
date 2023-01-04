/*******************************************************************************
* File Name: StepX_IOUT.h  
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

#if !defined(CY_PINS_StepX_IOUT_H) /* Pins StepX_IOUT_H */
#define CY_PINS_StepX_IOUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StepX_IOUT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 StepX_IOUT__PORT == 15 && ((StepX_IOUT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    StepX_IOUT_Write(uint8 value);
void    StepX_IOUT_SetDriveMode(uint8 mode);
uint8   StepX_IOUT_ReadDataReg(void);
uint8   StepX_IOUT_Read(void);
void    StepX_IOUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   StepX_IOUT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the StepX_IOUT_SetDriveMode() function.
     *  @{
     */
        #define StepX_IOUT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define StepX_IOUT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define StepX_IOUT_DM_RES_UP          PIN_DM_RES_UP
        #define StepX_IOUT_DM_RES_DWN         PIN_DM_RES_DWN
        #define StepX_IOUT_DM_OD_LO           PIN_DM_OD_LO
        #define StepX_IOUT_DM_OD_HI           PIN_DM_OD_HI
        #define StepX_IOUT_DM_STRONG          PIN_DM_STRONG
        #define StepX_IOUT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define StepX_IOUT_MASK               StepX_IOUT__MASK
#define StepX_IOUT_SHIFT              StepX_IOUT__SHIFT
#define StepX_IOUT_WIDTH              1u

/* Interrupt constants */
#if defined(StepX_IOUT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in StepX_IOUT_SetInterruptMode() function.
     *  @{
     */
        #define StepX_IOUT_INTR_NONE      (uint16)(0x0000u)
        #define StepX_IOUT_INTR_RISING    (uint16)(0x0001u)
        #define StepX_IOUT_INTR_FALLING   (uint16)(0x0002u)
        #define StepX_IOUT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define StepX_IOUT_INTR_MASK      (0x01u) 
#endif /* (StepX_IOUT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StepX_IOUT_PS                     (* (reg8 *) StepX_IOUT__PS)
/* Data Register */
#define StepX_IOUT_DR                     (* (reg8 *) StepX_IOUT__DR)
/* Port Number */
#define StepX_IOUT_PRT_NUM                (* (reg8 *) StepX_IOUT__PRT) 
/* Connect to Analog Globals */                                                  
#define StepX_IOUT_AG                     (* (reg8 *) StepX_IOUT__AG)                       
/* Analog MUX bux enable */
#define StepX_IOUT_AMUX                   (* (reg8 *) StepX_IOUT__AMUX) 
/* Bidirectional Enable */                                                        
#define StepX_IOUT_BIE                    (* (reg8 *) StepX_IOUT__BIE)
/* Bit-mask for Aliased Register Access */
#define StepX_IOUT_BIT_MASK               (* (reg8 *) StepX_IOUT__BIT_MASK)
/* Bypass Enable */
#define StepX_IOUT_BYP                    (* (reg8 *) StepX_IOUT__BYP)
/* Port wide control signals */                                                   
#define StepX_IOUT_CTL                    (* (reg8 *) StepX_IOUT__CTL)
/* Drive Modes */
#define StepX_IOUT_DM0                    (* (reg8 *) StepX_IOUT__DM0) 
#define StepX_IOUT_DM1                    (* (reg8 *) StepX_IOUT__DM1)
#define StepX_IOUT_DM2                    (* (reg8 *) StepX_IOUT__DM2) 
/* Input Buffer Disable Override */
#define StepX_IOUT_INP_DIS                (* (reg8 *) StepX_IOUT__INP_DIS)
/* LCD Common or Segment Drive */
#define StepX_IOUT_LCD_COM_SEG            (* (reg8 *) StepX_IOUT__LCD_COM_SEG)
/* Enable Segment LCD */
#define StepX_IOUT_LCD_EN                 (* (reg8 *) StepX_IOUT__LCD_EN)
/* Slew Rate Control */
#define StepX_IOUT_SLW                    (* (reg8 *) StepX_IOUT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StepX_IOUT_PRTDSI__CAPS_SEL       (* (reg8 *) StepX_IOUT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StepX_IOUT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StepX_IOUT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StepX_IOUT_PRTDSI__OE_SEL0        (* (reg8 *) StepX_IOUT__PRTDSI__OE_SEL0) 
#define StepX_IOUT_PRTDSI__OE_SEL1        (* (reg8 *) StepX_IOUT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StepX_IOUT_PRTDSI__OUT_SEL0       (* (reg8 *) StepX_IOUT__PRTDSI__OUT_SEL0) 
#define StepX_IOUT_PRTDSI__OUT_SEL1       (* (reg8 *) StepX_IOUT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StepX_IOUT_PRTDSI__SYNC_OUT       (* (reg8 *) StepX_IOUT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(StepX_IOUT__SIO_CFG)
    #define StepX_IOUT_SIO_HYST_EN        (* (reg8 *) StepX_IOUT__SIO_HYST_EN)
    #define StepX_IOUT_SIO_REG_HIFREQ     (* (reg8 *) StepX_IOUT__SIO_REG_HIFREQ)
    #define StepX_IOUT_SIO_CFG            (* (reg8 *) StepX_IOUT__SIO_CFG)
    #define StepX_IOUT_SIO_DIFF           (* (reg8 *) StepX_IOUT__SIO_DIFF)
#endif /* (StepX_IOUT__SIO_CFG) */

/* Interrupt Registers */
#if defined(StepX_IOUT__INTSTAT)
    #define StepX_IOUT_INTSTAT            (* (reg8 *) StepX_IOUT__INTSTAT)
    #define StepX_IOUT_SNAP               (* (reg8 *) StepX_IOUT__SNAP)
    
	#define StepX_IOUT_0_INTTYPE_REG 		(* (reg8 *) StepX_IOUT__0__INTTYPE)
#endif /* (StepX_IOUT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_StepX_IOUT_H */


/* [] END OF FILE */
