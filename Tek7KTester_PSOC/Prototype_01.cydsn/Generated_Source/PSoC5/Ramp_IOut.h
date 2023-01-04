/*******************************************************************************
* File Name: Ramp_IOut.h  
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

#if !defined(CY_PINS_Ramp_IOut_H) /* Pins Ramp_IOut_H */
#define CY_PINS_Ramp_IOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ramp_IOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ramp_IOut__PORT == 15 && ((Ramp_IOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ramp_IOut_Write(uint8 value);
void    Ramp_IOut_SetDriveMode(uint8 mode);
uint8   Ramp_IOut_ReadDataReg(void);
uint8   Ramp_IOut_Read(void);
void    Ramp_IOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ramp_IOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ramp_IOut_SetDriveMode() function.
     *  @{
     */
        #define Ramp_IOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ramp_IOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ramp_IOut_DM_RES_UP          PIN_DM_RES_UP
        #define Ramp_IOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ramp_IOut_DM_OD_LO           PIN_DM_OD_LO
        #define Ramp_IOut_DM_OD_HI           PIN_DM_OD_HI
        #define Ramp_IOut_DM_STRONG          PIN_DM_STRONG
        #define Ramp_IOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ramp_IOut_MASK               Ramp_IOut__MASK
#define Ramp_IOut_SHIFT              Ramp_IOut__SHIFT
#define Ramp_IOut_WIDTH              1u

/* Interrupt constants */
#if defined(Ramp_IOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ramp_IOut_SetInterruptMode() function.
     *  @{
     */
        #define Ramp_IOut_INTR_NONE      (uint16)(0x0000u)
        #define Ramp_IOut_INTR_RISING    (uint16)(0x0001u)
        #define Ramp_IOut_INTR_FALLING   (uint16)(0x0002u)
        #define Ramp_IOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ramp_IOut_INTR_MASK      (0x01u) 
#endif /* (Ramp_IOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ramp_IOut_PS                     (* (reg8 *) Ramp_IOut__PS)
/* Data Register */
#define Ramp_IOut_DR                     (* (reg8 *) Ramp_IOut__DR)
/* Port Number */
#define Ramp_IOut_PRT_NUM                (* (reg8 *) Ramp_IOut__PRT) 
/* Connect to Analog Globals */                                                  
#define Ramp_IOut_AG                     (* (reg8 *) Ramp_IOut__AG)                       
/* Analog MUX bux enable */
#define Ramp_IOut_AMUX                   (* (reg8 *) Ramp_IOut__AMUX) 
/* Bidirectional Enable */                                                        
#define Ramp_IOut_BIE                    (* (reg8 *) Ramp_IOut__BIE)
/* Bit-mask for Aliased Register Access */
#define Ramp_IOut_BIT_MASK               (* (reg8 *) Ramp_IOut__BIT_MASK)
/* Bypass Enable */
#define Ramp_IOut_BYP                    (* (reg8 *) Ramp_IOut__BYP)
/* Port wide control signals */                                                   
#define Ramp_IOut_CTL                    (* (reg8 *) Ramp_IOut__CTL)
/* Drive Modes */
#define Ramp_IOut_DM0                    (* (reg8 *) Ramp_IOut__DM0) 
#define Ramp_IOut_DM1                    (* (reg8 *) Ramp_IOut__DM1)
#define Ramp_IOut_DM2                    (* (reg8 *) Ramp_IOut__DM2) 
/* Input Buffer Disable Override */
#define Ramp_IOut_INP_DIS                (* (reg8 *) Ramp_IOut__INP_DIS)
/* LCD Common or Segment Drive */
#define Ramp_IOut_LCD_COM_SEG            (* (reg8 *) Ramp_IOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ramp_IOut_LCD_EN                 (* (reg8 *) Ramp_IOut__LCD_EN)
/* Slew Rate Control */
#define Ramp_IOut_SLW                    (* (reg8 *) Ramp_IOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ramp_IOut_PRTDSI__CAPS_SEL       (* (reg8 *) Ramp_IOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ramp_IOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ramp_IOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ramp_IOut_PRTDSI__OE_SEL0        (* (reg8 *) Ramp_IOut__PRTDSI__OE_SEL0) 
#define Ramp_IOut_PRTDSI__OE_SEL1        (* (reg8 *) Ramp_IOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ramp_IOut_PRTDSI__OUT_SEL0       (* (reg8 *) Ramp_IOut__PRTDSI__OUT_SEL0) 
#define Ramp_IOut_PRTDSI__OUT_SEL1       (* (reg8 *) Ramp_IOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ramp_IOut_PRTDSI__SYNC_OUT       (* (reg8 *) Ramp_IOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ramp_IOut__SIO_CFG)
    #define Ramp_IOut_SIO_HYST_EN        (* (reg8 *) Ramp_IOut__SIO_HYST_EN)
    #define Ramp_IOut_SIO_REG_HIFREQ     (* (reg8 *) Ramp_IOut__SIO_REG_HIFREQ)
    #define Ramp_IOut_SIO_CFG            (* (reg8 *) Ramp_IOut__SIO_CFG)
    #define Ramp_IOut_SIO_DIFF           (* (reg8 *) Ramp_IOut__SIO_DIFF)
#endif /* (Ramp_IOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ramp_IOut__INTSTAT)
    #define Ramp_IOut_INTSTAT            (* (reg8 *) Ramp_IOut__INTSTAT)
    #define Ramp_IOut_SNAP               (* (reg8 *) Ramp_IOut__SNAP)
    
	#define Ramp_IOut_0_INTTYPE_REG 		(* (reg8 *) Ramp_IOut__0__INTTYPE)
#endif /* (Ramp_IOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ramp_IOut_H */


/* [] END OF FILE */
