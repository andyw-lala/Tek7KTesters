/*******************************************************************************
* File Name: SRCLK.h  
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

#if !defined(CY_PINS_SRCLK_H) /* Pins SRCLK_H */
#define CY_PINS_SRCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SRCLK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SRCLK__PORT == 15 && ((SRCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SRCLK_Write(uint8 value);
void    SRCLK_SetDriveMode(uint8 mode);
uint8   SRCLK_ReadDataReg(void);
uint8   SRCLK_Read(void);
void    SRCLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   SRCLK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SRCLK_SetDriveMode() function.
     *  @{
     */
        #define SRCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SRCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SRCLK_DM_RES_UP          PIN_DM_RES_UP
        #define SRCLK_DM_RES_DWN         PIN_DM_RES_DWN
        #define SRCLK_DM_OD_LO           PIN_DM_OD_LO
        #define SRCLK_DM_OD_HI           PIN_DM_OD_HI
        #define SRCLK_DM_STRONG          PIN_DM_STRONG
        #define SRCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SRCLK_MASK               SRCLK__MASK
#define SRCLK_SHIFT              SRCLK__SHIFT
#define SRCLK_WIDTH              1u

/* Interrupt constants */
#if defined(SRCLK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SRCLK_SetInterruptMode() function.
     *  @{
     */
        #define SRCLK_INTR_NONE      (uint16)(0x0000u)
        #define SRCLK_INTR_RISING    (uint16)(0x0001u)
        #define SRCLK_INTR_FALLING   (uint16)(0x0002u)
        #define SRCLK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SRCLK_INTR_MASK      (0x01u) 
#endif /* (SRCLK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SRCLK_PS                     (* (reg8 *) SRCLK__PS)
/* Data Register */
#define SRCLK_DR                     (* (reg8 *) SRCLK__DR)
/* Port Number */
#define SRCLK_PRT_NUM                (* (reg8 *) SRCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define SRCLK_AG                     (* (reg8 *) SRCLK__AG)                       
/* Analog MUX bux enable */
#define SRCLK_AMUX                   (* (reg8 *) SRCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define SRCLK_BIE                    (* (reg8 *) SRCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define SRCLK_BIT_MASK               (* (reg8 *) SRCLK__BIT_MASK)
/* Bypass Enable */
#define SRCLK_BYP                    (* (reg8 *) SRCLK__BYP)
/* Port wide control signals */                                                   
#define SRCLK_CTL                    (* (reg8 *) SRCLK__CTL)
/* Drive Modes */
#define SRCLK_DM0                    (* (reg8 *) SRCLK__DM0) 
#define SRCLK_DM1                    (* (reg8 *) SRCLK__DM1)
#define SRCLK_DM2                    (* (reg8 *) SRCLK__DM2) 
/* Input Buffer Disable Override */
#define SRCLK_INP_DIS                (* (reg8 *) SRCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define SRCLK_LCD_COM_SEG            (* (reg8 *) SRCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define SRCLK_LCD_EN                 (* (reg8 *) SRCLK__LCD_EN)
/* Slew Rate Control */
#define SRCLK_SLW                    (* (reg8 *) SRCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SRCLK_PRTDSI__CAPS_SEL       (* (reg8 *) SRCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SRCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SRCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SRCLK_PRTDSI__OE_SEL0        (* (reg8 *) SRCLK__PRTDSI__OE_SEL0) 
#define SRCLK_PRTDSI__OE_SEL1        (* (reg8 *) SRCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SRCLK_PRTDSI__OUT_SEL0       (* (reg8 *) SRCLK__PRTDSI__OUT_SEL0) 
#define SRCLK_PRTDSI__OUT_SEL1       (* (reg8 *) SRCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SRCLK_PRTDSI__SYNC_OUT       (* (reg8 *) SRCLK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SRCLK__SIO_CFG)
    #define SRCLK_SIO_HYST_EN        (* (reg8 *) SRCLK__SIO_HYST_EN)
    #define SRCLK_SIO_REG_HIFREQ     (* (reg8 *) SRCLK__SIO_REG_HIFREQ)
    #define SRCLK_SIO_CFG            (* (reg8 *) SRCLK__SIO_CFG)
    #define SRCLK_SIO_DIFF           (* (reg8 *) SRCLK__SIO_DIFF)
#endif /* (SRCLK__SIO_CFG) */

/* Interrupt Registers */
#if defined(SRCLK__INTSTAT)
    #define SRCLK_INTSTAT            (* (reg8 *) SRCLK__INTSTAT)
    #define SRCLK_SNAP               (* (reg8 *) SRCLK__SNAP)
    
	#define SRCLK_0_INTTYPE_REG 		(* (reg8 *) SRCLK__0__INTTYPE)
#endif /* (SRCLK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SRCLK_H */


/* [] END OF FILE */
