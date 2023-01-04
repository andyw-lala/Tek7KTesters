/*******************************************************************************
* File Name: Temp0.h  
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

#if !defined(CY_PINS_Temp0_H) /* Pins Temp0_H */
#define CY_PINS_Temp0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Temp0__PORT == 15 && ((Temp0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Temp0_Write(uint8 value);
void    Temp0_SetDriveMode(uint8 mode);
uint8   Temp0_ReadDataReg(void);
uint8   Temp0_Read(void);
void    Temp0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Temp0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Temp0_SetDriveMode() function.
     *  @{
     */
        #define Temp0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Temp0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Temp0_DM_RES_UP          PIN_DM_RES_UP
        #define Temp0_DM_RES_DWN         PIN_DM_RES_DWN
        #define Temp0_DM_OD_LO           PIN_DM_OD_LO
        #define Temp0_DM_OD_HI           PIN_DM_OD_HI
        #define Temp0_DM_STRONG          PIN_DM_STRONG
        #define Temp0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Temp0_MASK               Temp0__MASK
#define Temp0_SHIFT              Temp0__SHIFT
#define Temp0_WIDTH              1u

/* Interrupt constants */
#if defined(Temp0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Temp0_SetInterruptMode() function.
     *  @{
     */
        #define Temp0_INTR_NONE      (uint16)(0x0000u)
        #define Temp0_INTR_RISING    (uint16)(0x0001u)
        #define Temp0_INTR_FALLING   (uint16)(0x0002u)
        #define Temp0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Temp0_INTR_MASK      (0x01u) 
#endif /* (Temp0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp0_PS                     (* (reg8 *) Temp0__PS)
/* Data Register */
#define Temp0_DR                     (* (reg8 *) Temp0__DR)
/* Port Number */
#define Temp0_PRT_NUM                (* (reg8 *) Temp0__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp0_AG                     (* (reg8 *) Temp0__AG)                       
/* Analog MUX bux enable */
#define Temp0_AMUX                   (* (reg8 *) Temp0__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp0_BIE                    (* (reg8 *) Temp0__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp0_BIT_MASK               (* (reg8 *) Temp0__BIT_MASK)
/* Bypass Enable */
#define Temp0_BYP                    (* (reg8 *) Temp0__BYP)
/* Port wide control signals */                                                   
#define Temp0_CTL                    (* (reg8 *) Temp0__CTL)
/* Drive Modes */
#define Temp0_DM0                    (* (reg8 *) Temp0__DM0) 
#define Temp0_DM1                    (* (reg8 *) Temp0__DM1)
#define Temp0_DM2                    (* (reg8 *) Temp0__DM2) 
/* Input Buffer Disable Override */
#define Temp0_INP_DIS                (* (reg8 *) Temp0__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp0_LCD_COM_SEG            (* (reg8 *) Temp0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp0_LCD_EN                 (* (reg8 *) Temp0__LCD_EN)
/* Slew Rate Control */
#define Temp0_SLW                    (* (reg8 *) Temp0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp0_PRTDSI__CAPS_SEL       (* (reg8 *) Temp0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp0_PRTDSI__OE_SEL0        (* (reg8 *) Temp0__PRTDSI__OE_SEL0) 
#define Temp0_PRTDSI__OE_SEL1        (* (reg8 *) Temp0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp0_PRTDSI__OUT_SEL0       (* (reg8 *) Temp0__PRTDSI__OUT_SEL0) 
#define Temp0_PRTDSI__OUT_SEL1       (* (reg8 *) Temp0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp0_PRTDSI__SYNC_OUT       (* (reg8 *) Temp0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Temp0__SIO_CFG)
    #define Temp0_SIO_HYST_EN        (* (reg8 *) Temp0__SIO_HYST_EN)
    #define Temp0_SIO_REG_HIFREQ     (* (reg8 *) Temp0__SIO_REG_HIFREQ)
    #define Temp0_SIO_CFG            (* (reg8 *) Temp0__SIO_CFG)
    #define Temp0_SIO_DIFF           (* (reg8 *) Temp0__SIO_DIFF)
#endif /* (Temp0__SIO_CFG) */

/* Interrupt Registers */
#if defined(Temp0__INTSTAT)
    #define Temp0_INTSTAT            (* (reg8 *) Temp0__INTSTAT)
    #define Temp0_SNAP               (* (reg8 *) Temp0__SNAP)
    
	#define Temp0_0_INTTYPE_REG 		(* (reg8 *) Temp0__0__INTTYPE)
#endif /* (Temp0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Temp0_H */


/* [] END OF FILE */
