/*******************************************************************************
* File Name: Display_CLK.h  
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

#if !defined(CY_PINS_Display_CLK_H) /* Pins Display_CLK_H */
#define CY_PINS_Display_CLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Display_CLK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Display_CLK__PORT == 15 && ((Display_CLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Display_CLK_Write(uint8 value);
void    Display_CLK_SetDriveMode(uint8 mode);
uint8   Display_CLK_ReadDataReg(void);
uint8   Display_CLK_Read(void);
void    Display_CLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   Display_CLK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Display_CLK_SetDriveMode() function.
     *  @{
     */
        #define Display_CLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Display_CLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Display_CLK_DM_RES_UP          PIN_DM_RES_UP
        #define Display_CLK_DM_RES_DWN         PIN_DM_RES_DWN
        #define Display_CLK_DM_OD_LO           PIN_DM_OD_LO
        #define Display_CLK_DM_OD_HI           PIN_DM_OD_HI
        #define Display_CLK_DM_STRONG          PIN_DM_STRONG
        #define Display_CLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Display_CLK_MASK               Display_CLK__MASK
#define Display_CLK_SHIFT              Display_CLK__SHIFT
#define Display_CLK_WIDTH              1u

/* Interrupt constants */
#if defined(Display_CLK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Display_CLK_SetInterruptMode() function.
     *  @{
     */
        #define Display_CLK_INTR_NONE      (uint16)(0x0000u)
        #define Display_CLK_INTR_RISING    (uint16)(0x0001u)
        #define Display_CLK_INTR_FALLING   (uint16)(0x0002u)
        #define Display_CLK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Display_CLK_INTR_MASK      (0x01u) 
#endif /* (Display_CLK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Display_CLK_PS                     (* (reg8 *) Display_CLK__PS)
/* Data Register */
#define Display_CLK_DR                     (* (reg8 *) Display_CLK__DR)
/* Port Number */
#define Display_CLK_PRT_NUM                (* (reg8 *) Display_CLK__PRT) 
/* Connect to Analog Globals */                                                  
#define Display_CLK_AG                     (* (reg8 *) Display_CLK__AG)                       
/* Analog MUX bux enable */
#define Display_CLK_AMUX                   (* (reg8 *) Display_CLK__AMUX) 
/* Bidirectional Enable */                                                        
#define Display_CLK_BIE                    (* (reg8 *) Display_CLK__BIE)
/* Bit-mask for Aliased Register Access */
#define Display_CLK_BIT_MASK               (* (reg8 *) Display_CLK__BIT_MASK)
/* Bypass Enable */
#define Display_CLK_BYP                    (* (reg8 *) Display_CLK__BYP)
/* Port wide control signals */                                                   
#define Display_CLK_CTL                    (* (reg8 *) Display_CLK__CTL)
/* Drive Modes */
#define Display_CLK_DM0                    (* (reg8 *) Display_CLK__DM0) 
#define Display_CLK_DM1                    (* (reg8 *) Display_CLK__DM1)
#define Display_CLK_DM2                    (* (reg8 *) Display_CLK__DM2) 
/* Input Buffer Disable Override */
#define Display_CLK_INP_DIS                (* (reg8 *) Display_CLK__INP_DIS)
/* LCD Common or Segment Drive */
#define Display_CLK_LCD_COM_SEG            (* (reg8 *) Display_CLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define Display_CLK_LCD_EN                 (* (reg8 *) Display_CLK__LCD_EN)
/* Slew Rate Control */
#define Display_CLK_SLW                    (* (reg8 *) Display_CLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Display_CLK_PRTDSI__CAPS_SEL       (* (reg8 *) Display_CLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Display_CLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Display_CLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Display_CLK_PRTDSI__OE_SEL0        (* (reg8 *) Display_CLK__PRTDSI__OE_SEL0) 
#define Display_CLK_PRTDSI__OE_SEL1        (* (reg8 *) Display_CLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Display_CLK_PRTDSI__OUT_SEL0       (* (reg8 *) Display_CLK__PRTDSI__OUT_SEL0) 
#define Display_CLK_PRTDSI__OUT_SEL1       (* (reg8 *) Display_CLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Display_CLK_PRTDSI__SYNC_OUT       (* (reg8 *) Display_CLK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Display_CLK__SIO_CFG)
    #define Display_CLK_SIO_HYST_EN        (* (reg8 *) Display_CLK__SIO_HYST_EN)
    #define Display_CLK_SIO_REG_HIFREQ     (* (reg8 *) Display_CLK__SIO_REG_HIFREQ)
    #define Display_CLK_SIO_CFG            (* (reg8 *) Display_CLK__SIO_CFG)
    #define Display_CLK_SIO_DIFF           (* (reg8 *) Display_CLK__SIO_DIFF)
#endif /* (Display_CLK__SIO_CFG) */

/* Interrupt Registers */
#if defined(Display_CLK__INTSTAT)
    #define Display_CLK_INTSTAT            (* (reg8 *) Display_CLK__INTSTAT)
    #define Display_CLK_SNAP               (* (reg8 *) Display_CLK__SNAP)
    
	#define Display_CLK_0_INTTYPE_REG 		(* (reg8 *) Display_CLK__0__INTTYPE)
#endif /* (Display_CLK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Display_CLK_H */


/* [] END OF FILE */
