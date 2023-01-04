/*******************************************************************************
* File Name: Display_DIN.h  
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

#if !defined(CY_PINS_Display_DIN_H) /* Pins Display_DIN_H */
#define CY_PINS_Display_DIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Display_DIN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Display_DIN__PORT == 15 && ((Display_DIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Display_DIN_Write(uint8 value);
void    Display_DIN_SetDriveMode(uint8 mode);
uint8   Display_DIN_ReadDataReg(void);
uint8   Display_DIN_Read(void);
void    Display_DIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   Display_DIN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Display_DIN_SetDriveMode() function.
     *  @{
     */
        #define Display_DIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Display_DIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Display_DIN_DM_RES_UP          PIN_DM_RES_UP
        #define Display_DIN_DM_RES_DWN         PIN_DM_RES_DWN
        #define Display_DIN_DM_OD_LO           PIN_DM_OD_LO
        #define Display_DIN_DM_OD_HI           PIN_DM_OD_HI
        #define Display_DIN_DM_STRONG          PIN_DM_STRONG
        #define Display_DIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Display_DIN_MASK               Display_DIN__MASK
#define Display_DIN_SHIFT              Display_DIN__SHIFT
#define Display_DIN_WIDTH              1u

/* Interrupt constants */
#if defined(Display_DIN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Display_DIN_SetInterruptMode() function.
     *  @{
     */
        #define Display_DIN_INTR_NONE      (uint16)(0x0000u)
        #define Display_DIN_INTR_RISING    (uint16)(0x0001u)
        #define Display_DIN_INTR_FALLING   (uint16)(0x0002u)
        #define Display_DIN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Display_DIN_INTR_MASK      (0x01u) 
#endif /* (Display_DIN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Display_DIN_PS                     (* (reg8 *) Display_DIN__PS)
/* Data Register */
#define Display_DIN_DR                     (* (reg8 *) Display_DIN__DR)
/* Port Number */
#define Display_DIN_PRT_NUM                (* (reg8 *) Display_DIN__PRT) 
/* Connect to Analog Globals */                                                  
#define Display_DIN_AG                     (* (reg8 *) Display_DIN__AG)                       
/* Analog MUX bux enable */
#define Display_DIN_AMUX                   (* (reg8 *) Display_DIN__AMUX) 
/* Bidirectional Enable */                                                        
#define Display_DIN_BIE                    (* (reg8 *) Display_DIN__BIE)
/* Bit-mask for Aliased Register Access */
#define Display_DIN_BIT_MASK               (* (reg8 *) Display_DIN__BIT_MASK)
/* Bypass Enable */
#define Display_DIN_BYP                    (* (reg8 *) Display_DIN__BYP)
/* Port wide control signals */                                                   
#define Display_DIN_CTL                    (* (reg8 *) Display_DIN__CTL)
/* Drive Modes */
#define Display_DIN_DM0                    (* (reg8 *) Display_DIN__DM0) 
#define Display_DIN_DM1                    (* (reg8 *) Display_DIN__DM1)
#define Display_DIN_DM2                    (* (reg8 *) Display_DIN__DM2) 
/* Input Buffer Disable Override */
#define Display_DIN_INP_DIS                (* (reg8 *) Display_DIN__INP_DIS)
/* LCD Common or Segment Drive */
#define Display_DIN_LCD_COM_SEG            (* (reg8 *) Display_DIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define Display_DIN_LCD_EN                 (* (reg8 *) Display_DIN__LCD_EN)
/* Slew Rate Control */
#define Display_DIN_SLW                    (* (reg8 *) Display_DIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Display_DIN_PRTDSI__CAPS_SEL       (* (reg8 *) Display_DIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Display_DIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Display_DIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Display_DIN_PRTDSI__OE_SEL0        (* (reg8 *) Display_DIN__PRTDSI__OE_SEL0) 
#define Display_DIN_PRTDSI__OE_SEL1        (* (reg8 *) Display_DIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Display_DIN_PRTDSI__OUT_SEL0       (* (reg8 *) Display_DIN__PRTDSI__OUT_SEL0) 
#define Display_DIN_PRTDSI__OUT_SEL1       (* (reg8 *) Display_DIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Display_DIN_PRTDSI__SYNC_OUT       (* (reg8 *) Display_DIN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Display_DIN__SIO_CFG)
    #define Display_DIN_SIO_HYST_EN        (* (reg8 *) Display_DIN__SIO_HYST_EN)
    #define Display_DIN_SIO_REG_HIFREQ     (* (reg8 *) Display_DIN__SIO_REG_HIFREQ)
    #define Display_DIN_SIO_CFG            (* (reg8 *) Display_DIN__SIO_CFG)
    #define Display_DIN_SIO_DIFF           (* (reg8 *) Display_DIN__SIO_DIFF)
#endif /* (Display_DIN__SIO_CFG) */

/* Interrupt Registers */
#if defined(Display_DIN__INTSTAT)
    #define Display_DIN_INTSTAT            (* (reg8 *) Display_DIN__INTSTAT)
    #define Display_DIN_SNAP               (* (reg8 *) Display_DIN__SNAP)
    
	#define Display_DIN_0_INTTYPE_REG 		(* (reg8 *) Display_DIN__0__INTTYPE)
#endif /* (Display_DIN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Display_DIN_H */


/* [] END OF FILE */
