/*******************************************************************************
* File Name: Temp1.h  
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

#if !defined(CY_PINS_Temp1_H) /* Pins Temp1_H */
#define CY_PINS_Temp1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Temp1__PORT == 15 && ((Temp1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Temp1_Write(uint8 value);
void    Temp1_SetDriveMode(uint8 mode);
uint8   Temp1_ReadDataReg(void);
uint8   Temp1_Read(void);
void    Temp1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Temp1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Temp1_SetDriveMode() function.
     *  @{
     */
        #define Temp1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Temp1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Temp1_DM_RES_UP          PIN_DM_RES_UP
        #define Temp1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Temp1_DM_OD_LO           PIN_DM_OD_LO
        #define Temp1_DM_OD_HI           PIN_DM_OD_HI
        #define Temp1_DM_STRONG          PIN_DM_STRONG
        #define Temp1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Temp1_MASK               Temp1__MASK
#define Temp1_SHIFT              Temp1__SHIFT
#define Temp1_WIDTH              1u

/* Interrupt constants */
#if defined(Temp1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Temp1_SetInterruptMode() function.
     *  @{
     */
        #define Temp1_INTR_NONE      (uint16)(0x0000u)
        #define Temp1_INTR_RISING    (uint16)(0x0001u)
        #define Temp1_INTR_FALLING   (uint16)(0x0002u)
        #define Temp1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Temp1_INTR_MASK      (0x01u) 
#endif /* (Temp1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp1_PS                     (* (reg8 *) Temp1__PS)
/* Data Register */
#define Temp1_DR                     (* (reg8 *) Temp1__DR)
/* Port Number */
#define Temp1_PRT_NUM                (* (reg8 *) Temp1__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp1_AG                     (* (reg8 *) Temp1__AG)                       
/* Analog MUX bux enable */
#define Temp1_AMUX                   (* (reg8 *) Temp1__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp1_BIE                    (* (reg8 *) Temp1__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp1_BIT_MASK               (* (reg8 *) Temp1__BIT_MASK)
/* Bypass Enable */
#define Temp1_BYP                    (* (reg8 *) Temp1__BYP)
/* Port wide control signals */                                                   
#define Temp1_CTL                    (* (reg8 *) Temp1__CTL)
/* Drive Modes */
#define Temp1_DM0                    (* (reg8 *) Temp1__DM0) 
#define Temp1_DM1                    (* (reg8 *) Temp1__DM1)
#define Temp1_DM2                    (* (reg8 *) Temp1__DM2) 
/* Input Buffer Disable Override */
#define Temp1_INP_DIS                (* (reg8 *) Temp1__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp1_LCD_COM_SEG            (* (reg8 *) Temp1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp1_LCD_EN                 (* (reg8 *) Temp1__LCD_EN)
/* Slew Rate Control */
#define Temp1_SLW                    (* (reg8 *) Temp1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp1_PRTDSI__CAPS_SEL       (* (reg8 *) Temp1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp1_PRTDSI__OE_SEL0        (* (reg8 *) Temp1__PRTDSI__OE_SEL0) 
#define Temp1_PRTDSI__OE_SEL1        (* (reg8 *) Temp1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp1_PRTDSI__OUT_SEL0       (* (reg8 *) Temp1__PRTDSI__OUT_SEL0) 
#define Temp1_PRTDSI__OUT_SEL1       (* (reg8 *) Temp1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp1_PRTDSI__SYNC_OUT       (* (reg8 *) Temp1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Temp1__SIO_CFG)
    #define Temp1_SIO_HYST_EN        (* (reg8 *) Temp1__SIO_HYST_EN)
    #define Temp1_SIO_REG_HIFREQ     (* (reg8 *) Temp1__SIO_REG_HIFREQ)
    #define Temp1_SIO_CFG            (* (reg8 *) Temp1__SIO_CFG)
    #define Temp1_SIO_DIFF           (* (reg8 *) Temp1__SIO_DIFF)
#endif /* (Temp1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Temp1__INTSTAT)
    #define Temp1_INTSTAT            (* (reg8 *) Temp1__INTSTAT)
    #define Temp1_SNAP               (* (reg8 *) Temp1__SNAP)
    
	#define Temp1_0_INTTYPE_REG 		(* (reg8 *) Temp1__0__INTTYPE)
#endif /* (Temp1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Temp1_H */


/* [] END OF FILE */
