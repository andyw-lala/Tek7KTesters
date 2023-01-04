/*******************************************************************************
* File Name: PortExpanderInterrupt.h  
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

#if !defined(CY_PINS_PortExpanderInterrupt_H) /* Pins PortExpanderInterrupt_H */
#define CY_PINS_PortExpanderInterrupt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PortExpanderInterrupt_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PortExpanderInterrupt__PORT == 15 && ((PortExpanderInterrupt__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PortExpanderInterrupt_Write(uint8 value);
void    PortExpanderInterrupt_SetDriveMode(uint8 mode);
uint8   PortExpanderInterrupt_ReadDataReg(void);
uint8   PortExpanderInterrupt_Read(void);
void    PortExpanderInterrupt_SetInterruptMode(uint16 position, uint16 mode);
uint8   PortExpanderInterrupt_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PortExpanderInterrupt_SetDriveMode() function.
     *  @{
     */
        #define PortExpanderInterrupt_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PortExpanderInterrupt_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PortExpanderInterrupt_DM_RES_UP          PIN_DM_RES_UP
        #define PortExpanderInterrupt_DM_RES_DWN         PIN_DM_RES_DWN
        #define PortExpanderInterrupt_DM_OD_LO           PIN_DM_OD_LO
        #define PortExpanderInterrupt_DM_OD_HI           PIN_DM_OD_HI
        #define PortExpanderInterrupt_DM_STRONG          PIN_DM_STRONG
        #define PortExpanderInterrupt_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PortExpanderInterrupt_MASK               PortExpanderInterrupt__MASK
#define PortExpanderInterrupt_SHIFT              PortExpanderInterrupt__SHIFT
#define PortExpanderInterrupt_WIDTH              1u

/* Interrupt constants */
#if defined(PortExpanderInterrupt__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PortExpanderInterrupt_SetInterruptMode() function.
     *  @{
     */
        #define PortExpanderInterrupt_INTR_NONE      (uint16)(0x0000u)
        #define PortExpanderInterrupt_INTR_RISING    (uint16)(0x0001u)
        #define PortExpanderInterrupt_INTR_FALLING   (uint16)(0x0002u)
        #define PortExpanderInterrupt_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PortExpanderInterrupt_INTR_MASK      (0x01u) 
#endif /* (PortExpanderInterrupt__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PortExpanderInterrupt_PS                     (* (reg8 *) PortExpanderInterrupt__PS)
/* Data Register */
#define PortExpanderInterrupt_DR                     (* (reg8 *) PortExpanderInterrupt__DR)
/* Port Number */
#define PortExpanderInterrupt_PRT_NUM                (* (reg8 *) PortExpanderInterrupt__PRT) 
/* Connect to Analog Globals */                                                  
#define PortExpanderInterrupt_AG                     (* (reg8 *) PortExpanderInterrupt__AG)                       
/* Analog MUX bux enable */
#define PortExpanderInterrupt_AMUX                   (* (reg8 *) PortExpanderInterrupt__AMUX) 
/* Bidirectional Enable */                                                        
#define PortExpanderInterrupt_BIE                    (* (reg8 *) PortExpanderInterrupt__BIE)
/* Bit-mask for Aliased Register Access */
#define PortExpanderInterrupt_BIT_MASK               (* (reg8 *) PortExpanderInterrupt__BIT_MASK)
/* Bypass Enable */
#define PortExpanderInterrupt_BYP                    (* (reg8 *) PortExpanderInterrupt__BYP)
/* Port wide control signals */                                                   
#define PortExpanderInterrupt_CTL                    (* (reg8 *) PortExpanderInterrupt__CTL)
/* Drive Modes */
#define PortExpanderInterrupt_DM0                    (* (reg8 *) PortExpanderInterrupt__DM0) 
#define PortExpanderInterrupt_DM1                    (* (reg8 *) PortExpanderInterrupt__DM1)
#define PortExpanderInterrupt_DM2                    (* (reg8 *) PortExpanderInterrupt__DM2) 
/* Input Buffer Disable Override */
#define PortExpanderInterrupt_INP_DIS                (* (reg8 *) PortExpanderInterrupt__INP_DIS)
/* LCD Common or Segment Drive */
#define PortExpanderInterrupt_LCD_COM_SEG            (* (reg8 *) PortExpanderInterrupt__LCD_COM_SEG)
/* Enable Segment LCD */
#define PortExpanderInterrupt_LCD_EN                 (* (reg8 *) PortExpanderInterrupt__LCD_EN)
/* Slew Rate Control */
#define PortExpanderInterrupt_SLW                    (* (reg8 *) PortExpanderInterrupt__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PortExpanderInterrupt_PRTDSI__CAPS_SEL       (* (reg8 *) PortExpanderInterrupt__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PortExpanderInterrupt_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PortExpanderInterrupt__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PortExpanderInterrupt_PRTDSI__OE_SEL0        (* (reg8 *) PortExpanderInterrupt__PRTDSI__OE_SEL0) 
#define PortExpanderInterrupt_PRTDSI__OE_SEL1        (* (reg8 *) PortExpanderInterrupt__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PortExpanderInterrupt_PRTDSI__OUT_SEL0       (* (reg8 *) PortExpanderInterrupt__PRTDSI__OUT_SEL0) 
#define PortExpanderInterrupt_PRTDSI__OUT_SEL1       (* (reg8 *) PortExpanderInterrupt__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PortExpanderInterrupt_PRTDSI__SYNC_OUT       (* (reg8 *) PortExpanderInterrupt__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PortExpanderInterrupt__SIO_CFG)
    #define PortExpanderInterrupt_SIO_HYST_EN        (* (reg8 *) PortExpanderInterrupt__SIO_HYST_EN)
    #define PortExpanderInterrupt_SIO_REG_HIFREQ     (* (reg8 *) PortExpanderInterrupt__SIO_REG_HIFREQ)
    #define PortExpanderInterrupt_SIO_CFG            (* (reg8 *) PortExpanderInterrupt__SIO_CFG)
    #define PortExpanderInterrupt_SIO_DIFF           (* (reg8 *) PortExpanderInterrupt__SIO_DIFF)
#endif /* (PortExpanderInterrupt__SIO_CFG) */

/* Interrupt Registers */
#if defined(PortExpanderInterrupt__INTSTAT)
    #define PortExpanderInterrupt_INTSTAT            (* (reg8 *) PortExpanderInterrupt__INTSTAT)
    #define PortExpanderInterrupt_SNAP               (* (reg8 *) PortExpanderInterrupt__SNAP)
    
	#define PortExpanderInterrupt_0_INTTYPE_REG 		(* (reg8 *) PortExpanderInterrupt__0__INTTYPE)
#endif /* (PortExpanderInterrupt__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PortExpanderInterrupt_H */


/* [] END OF FILE */
