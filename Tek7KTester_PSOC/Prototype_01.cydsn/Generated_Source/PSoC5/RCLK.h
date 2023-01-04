/*******************************************************************************
* File Name: RCLK.h  
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

#if !defined(CY_PINS_RCLK_H) /* Pins RCLK_H */
#define CY_PINS_RCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RCLK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RCLK__PORT == 15 && ((RCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RCLK_Write(uint8 value);
void    RCLK_SetDriveMode(uint8 mode);
uint8   RCLK_ReadDataReg(void);
uint8   RCLK_Read(void);
void    RCLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   RCLK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RCLK_SetDriveMode() function.
     *  @{
     */
        #define RCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RCLK_DM_RES_UP          PIN_DM_RES_UP
        #define RCLK_DM_RES_DWN         PIN_DM_RES_DWN
        #define RCLK_DM_OD_LO           PIN_DM_OD_LO
        #define RCLK_DM_OD_HI           PIN_DM_OD_HI
        #define RCLK_DM_STRONG          PIN_DM_STRONG
        #define RCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RCLK_MASK               RCLK__MASK
#define RCLK_SHIFT              RCLK__SHIFT
#define RCLK_WIDTH              1u

/* Interrupt constants */
#if defined(RCLK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RCLK_SetInterruptMode() function.
     *  @{
     */
        #define RCLK_INTR_NONE      (uint16)(0x0000u)
        #define RCLK_INTR_RISING    (uint16)(0x0001u)
        #define RCLK_INTR_FALLING   (uint16)(0x0002u)
        #define RCLK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RCLK_INTR_MASK      (0x01u) 
#endif /* (RCLK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RCLK_PS                     (* (reg8 *) RCLK__PS)
/* Data Register */
#define RCLK_DR                     (* (reg8 *) RCLK__DR)
/* Port Number */
#define RCLK_PRT_NUM                (* (reg8 *) RCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define RCLK_AG                     (* (reg8 *) RCLK__AG)                       
/* Analog MUX bux enable */
#define RCLK_AMUX                   (* (reg8 *) RCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define RCLK_BIE                    (* (reg8 *) RCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define RCLK_BIT_MASK               (* (reg8 *) RCLK__BIT_MASK)
/* Bypass Enable */
#define RCLK_BYP                    (* (reg8 *) RCLK__BYP)
/* Port wide control signals */                                                   
#define RCLK_CTL                    (* (reg8 *) RCLK__CTL)
/* Drive Modes */
#define RCLK_DM0                    (* (reg8 *) RCLK__DM0) 
#define RCLK_DM1                    (* (reg8 *) RCLK__DM1)
#define RCLK_DM2                    (* (reg8 *) RCLK__DM2) 
/* Input Buffer Disable Override */
#define RCLK_INP_DIS                (* (reg8 *) RCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define RCLK_LCD_COM_SEG            (* (reg8 *) RCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define RCLK_LCD_EN                 (* (reg8 *) RCLK__LCD_EN)
/* Slew Rate Control */
#define RCLK_SLW                    (* (reg8 *) RCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RCLK_PRTDSI__CAPS_SEL       (* (reg8 *) RCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RCLK_PRTDSI__OE_SEL0        (* (reg8 *) RCLK__PRTDSI__OE_SEL0) 
#define RCLK_PRTDSI__OE_SEL1        (* (reg8 *) RCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RCLK_PRTDSI__OUT_SEL0       (* (reg8 *) RCLK__PRTDSI__OUT_SEL0) 
#define RCLK_PRTDSI__OUT_SEL1       (* (reg8 *) RCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RCLK_PRTDSI__SYNC_OUT       (* (reg8 *) RCLK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RCLK__SIO_CFG)
    #define RCLK_SIO_HYST_EN        (* (reg8 *) RCLK__SIO_HYST_EN)
    #define RCLK_SIO_REG_HIFREQ     (* (reg8 *) RCLK__SIO_REG_HIFREQ)
    #define RCLK_SIO_CFG            (* (reg8 *) RCLK__SIO_CFG)
    #define RCLK_SIO_DIFF           (* (reg8 *) RCLK__SIO_DIFF)
#endif /* (RCLK__SIO_CFG) */

/* Interrupt Registers */
#if defined(RCLK__INTSTAT)
    #define RCLK_INTSTAT            (* (reg8 *) RCLK__INTSTAT)
    #define RCLK_SNAP               (* (reg8 *) RCLK__SNAP)
    
	#define RCLK_0_INTTYPE_REG 		(* (reg8 *) RCLK__0__INTTYPE)
#endif /* (RCLK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RCLK_H */


/* [] END OF FILE */
