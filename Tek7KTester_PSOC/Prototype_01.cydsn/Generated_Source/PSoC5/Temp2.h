/*******************************************************************************
* File Name: Temp2.h  
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

#if !defined(CY_PINS_Temp2_H) /* Pins Temp2_H */
#define CY_PINS_Temp2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Temp2__PORT == 15 && ((Temp2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Temp2_Write(uint8 value);
void    Temp2_SetDriveMode(uint8 mode);
uint8   Temp2_ReadDataReg(void);
uint8   Temp2_Read(void);
void    Temp2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Temp2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Temp2_SetDriveMode() function.
     *  @{
     */
        #define Temp2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Temp2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Temp2_DM_RES_UP          PIN_DM_RES_UP
        #define Temp2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Temp2_DM_OD_LO           PIN_DM_OD_LO
        #define Temp2_DM_OD_HI           PIN_DM_OD_HI
        #define Temp2_DM_STRONG          PIN_DM_STRONG
        #define Temp2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Temp2_MASK               Temp2__MASK
#define Temp2_SHIFT              Temp2__SHIFT
#define Temp2_WIDTH              1u

/* Interrupt constants */
#if defined(Temp2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Temp2_SetInterruptMode() function.
     *  @{
     */
        #define Temp2_INTR_NONE      (uint16)(0x0000u)
        #define Temp2_INTR_RISING    (uint16)(0x0001u)
        #define Temp2_INTR_FALLING   (uint16)(0x0002u)
        #define Temp2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Temp2_INTR_MASK      (0x01u) 
#endif /* (Temp2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp2_PS                     (* (reg8 *) Temp2__PS)
/* Data Register */
#define Temp2_DR                     (* (reg8 *) Temp2__DR)
/* Port Number */
#define Temp2_PRT_NUM                (* (reg8 *) Temp2__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp2_AG                     (* (reg8 *) Temp2__AG)                       
/* Analog MUX bux enable */
#define Temp2_AMUX                   (* (reg8 *) Temp2__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp2_BIE                    (* (reg8 *) Temp2__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp2_BIT_MASK               (* (reg8 *) Temp2__BIT_MASK)
/* Bypass Enable */
#define Temp2_BYP                    (* (reg8 *) Temp2__BYP)
/* Port wide control signals */                                                   
#define Temp2_CTL                    (* (reg8 *) Temp2__CTL)
/* Drive Modes */
#define Temp2_DM0                    (* (reg8 *) Temp2__DM0) 
#define Temp2_DM1                    (* (reg8 *) Temp2__DM1)
#define Temp2_DM2                    (* (reg8 *) Temp2__DM2) 
/* Input Buffer Disable Override */
#define Temp2_INP_DIS                (* (reg8 *) Temp2__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp2_LCD_COM_SEG            (* (reg8 *) Temp2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp2_LCD_EN                 (* (reg8 *) Temp2__LCD_EN)
/* Slew Rate Control */
#define Temp2_SLW                    (* (reg8 *) Temp2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp2_PRTDSI__CAPS_SEL       (* (reg8 *) Temp2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp2_PRTDSI__OE_SEL0        (* (reg8 *) Temp2__PRTDSI__OE_SEL0) 
#define Temp2_PRTDSI__OE_SEL1        (* (reg8 *) Temp2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp2_PRTDSI__OUT_SEL0       (* (reg8 *) Temp2__PRTDSI__OUT_SEL0) 
#define Temp2_PRTDSI__OUT_SEL1       (* (reg8 *) Temp2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp2_PRTDSI__SYNC_OUT       (* (reg8 *) Temp2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Temp2__SIO_CFG)
    #define Temp2_SIO_HYST_EN        (* (reg8 *) Temp2__SIO_HYST_EN)
    #define Temp2_SIO_REG_HIFREQ     (* (reg8 *) Temp2__SIO_REG_HIFREQ)
    #define Temp2_SIO_CFG            (* (reg8 *) Temp2__SIO_CFG)
    #define Temp2_SIO_DIFF           (* (reg8 *) Temp2__SIO_DIFF)
#endif /* (Temp2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Temp2__INTSTAT)
    #define Temp2_INTSTAT            (* (reg8 *) Temp2__INTSTAT)
    #define Temp2_SNAP               (* (reg8 *) Temp2__SNAP)
    
	#define Temp2_0_INTTYPE_REG 		(* (reg8 *) Temp2__0__INTTYPE)
#endif /* (Temp2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Temp2_H */


/* [] END OF FILE */
