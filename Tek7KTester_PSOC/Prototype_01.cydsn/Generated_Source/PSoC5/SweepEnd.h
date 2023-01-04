/*******************************************************************************
* File Name: SweepEnd.h  
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

#if !defined(CY_PINS_SweepEnd_H) /* Pins SweepEnd_H */
#define CY_PINS_SweepEnd_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SweepEnd_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SweepEnd__PORT == 15 && ((SweepEnd__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SweepEnd_Write(uint8 value);
void    SweepEnd_SetDriveMode(uint8 mode);
uint8   SweepEnd_ReadDataReg(void);
uint8   SweepEnd_Read(void);
void    SweepEnd_SetInterruptMode(uint16 position, uint16 mode);
uint8   SweepEnd_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SweepEnd_SetDriveMode() function.
     *  @{
     */
        #define SweepEnd_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SweepEnd_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SweepEnd_DM_RES_UP          PIN_DM_RES_UP
        #define SweepEnd_DM_RES_DWN         PIN_DM_RES_DWN
        #define SweepEnd_DM_OD_LO           PIN_DM_OD_LO
        #define SweepEnd_DM_OD_HI           PIN_DM_OD_HI
        #define SweepEnd_DM_STRONG          PIN_DM_STRONG
        #define SweepEnd_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SweepEnd_MASK               SweepEnd__MASK
#define SweepEnd_SHIFT              SweepEnd__SHIFT
#define SweepEnd_WIDTH              1u

/* Interrupt constants */
#if defined(SweepEnd__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SweepEnd_SetInterruptMode() function.
     *  @{
     */
        #define SweepEnd_INTR_NONE      (uint16)(0x0000u)
        #define SweepEnd_INTR_RISING    (uint16)(0x0001u)
        #define SweepEnd_INTR_FALLING   (uint16)(0x0002u)
        #define SweepEnd_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SweepEnd_INTR_MASK      (0x01u) 
#endif /* (SweepEnd__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SweepEnd_PS                     (* (reg8 *) SweepEnd__PS)
/* Data Register */
#define SweepEnd_DR                     (* (reg8 *) SweepEnd__DR)
/* Port Number */
#define SweepEnd_PRT_NUM                (* (reg8 *) SweepEnd__PRT) 
/* Connect to Analog Globals */                                                  
#define SweepEnd_AG                     (* (reg8 *) SweepEnd__AG)                       
/* Analog MUX bux enable */
#define SweepEnd_AMUX                   (* (reg8 *) SweepEnd__AMUX) 
/* Bidirectional Enable */                                                        
#define SweepEnd_BIE                    (* (reg8 *) SweepEnd__BIE)
/* Bit-mask for Aliased Register Access */
#define SweepEnd_BIT_MASK               (* (reg8 *) SweepEnd__BIT_MASK)
/* Bypass Enable */
#define SweepEnd_BYP                    (* (reg8 *) SweepEnd__BYP)
/* Port wide control signals */                                                   
#define SweepEnd_CTL                    (* (reg8 *) SweepEnd__CTL)
/* Drive Modes */
#define SweepEnd_DM0                    (* (reg8 *) SweepEnd__DM0) 
#define SweepEnd_DM1                    (* (reg8 *) SweepEnd__DM1)
#define SweepEnd_DM2                    (* (reg8 *) SweepEnd__DM2) 
/* Input Buffer Disable Override */
#define SweepEnd_INP_DIS                (* (reg8 *) SweepEnd__INP_DIS)
/* LCD Common or Segment Drive */
#define SweepEnd_LCD_COM_SEG            (* (reg8 *) SweepEnd__LCD_COM_SEG)
/* Enable Segment LCD */
#define SweepEnd_LCD_EN                 (* (reg8 *) SweepEnd__LCD_EN)
/* Slew Rate Control */
#define SweepEnd_SLW                    (* (reg8 *) SweepEnd__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SweepEnd_PRTDSI__CAPS_SEL       (* (reg8 *) SweepEnd__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SweepEnd_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SweepEnd__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SweepEnd_PRTDSI__OE_SEL0        (* (reg8 *) SweepEnd__PRTDSI__OE_SEL0) 
#define SweepEnd_PRTDSI__OE_SEL1        (* (reg8 *) SweepEnd__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SweepEnd_PRTDSI__OUT_SEL0       (* (reg8 *) SweepEnd__PRTDSI__OUT_SEL0) 
#define SweepEnd_PRTDSI__OUT_SEL1       (* (reg8 *) SweepEnd__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SweepEnd_PRTDSI__SYNC_OUT       (* (reg8 *) SweepEnd__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SweepEnd__SIO_CFG)
    #define SweepEnd_SIO_HYST_EN        (* (reg8 *) SweepEnd__SIO_HYST_EN)
    #define SweepEnd_SIO_REG_HIFREQ     (* (reg8 *) SweepEnd__SIO_REG_HIFREQ)
    #define SweepEnd_SIO_CFG            (* (reg8 *) SweepEnd__SIO_CFG)
    #define SweepEnd_SIO_DIFF           (* (reg8 *) SweepEnd__SIO_DIFF)
#endif /* (SweepEnd__SIO_CFG) */

/* Interrupt Registers */
#if defined(SweepEnd__INTSTAT)
    #define SweepEnd_INTSTAT            (* (reg8 *) SweepEnd__INTSTAT)
    #define SweepEnd_SNAP               (* (reg8 *) SweepEnd__SNAP)
    
	#define SweepEnd_0_INTTYPE_REG 		(* (reg8 *) SweepEnd__0__INTTYPE)
#endif /* (SweepEnd__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SweepEnd_H */


/* [] END OF FILE */
