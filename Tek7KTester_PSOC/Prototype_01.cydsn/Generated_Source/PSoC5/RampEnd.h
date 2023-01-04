/*******************************************************************************
* File Name: RampEnd.h  
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

#if !defined(CY_PINS_RampEnd_H) /* Pins RampEnd_H */
#define CY_PINS_RampEnd_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RampEnd_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RampEnd__PORT == 15 && ((RampEnd__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RampEnd_Write(uint8 value);
void    RampEnd_SetDriveMode(uint8 mode);
uint8   RampEnd_ReadDataReg(void);
uint8   RampEnd_Read(void);
void    RampEnd_SetInterruptMode(uint16 position, uint16 mode);
uint8   RampEnd_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RampEnd_SetDriveMode() function.
     *  @{
     */
        #define RampEnd_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RampEnd_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RampEnd_DM_RES_UP          PIN_DM_RES_UP
        #define RampEnd_DM_RES_DWN         PIN_DM_RES_DWN
        #define RampEnd_DM_OD_LO           PIN_DM_OD_LO
        #define RampEnd_DM_OD_HI           PIN_DM_OD_HI
        #define RampEnd_DM_STRONG          PIN_DM_STRONG
        #define RampEnd_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RampEnd_MASK               RampEnd__MASK
#define RampEnd_SHIFT              RampEnd__SHIFT
#define RampEnd_WIDTH              1u

/* Interrupt constants */
#if defined(RampEnd__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RampEnd_SetInterruptMode() function.
     *  @{
     */
        #define RampEnd_INTR_NONE      (uint16)(0x0000u)
        #define RampEnd_INTR_RISING    (uint16)(0x0001u)
        #define RampEnd_INTR_FALLING   (uint16)(0x0002u)
        #define RampEnd_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RampEnd_INTR_MASK      (0x01u) 
#endif /* (RampEnd__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RampEnd_PS                     (* (reg8 *) RampEnd__PS)
/* Data Register */
#define RampEnd_DR                     (* (reg8 *) RampEnd__DR)
/* Port Number */
#define RampEnd_PRT_NUM                (* (reg8 *) RampEnd__PRT) 
/* Connect to Analog Globals */                                                  
#define RampEnd_AG                     (* (reg8 *) RampEnd__AG)                       
/* Analog MUX bux enable */
#define RampEnd_AMUX                   (* (reg8 *) RampEnd__AMUX) 
/* Bidirectional Enable */                                                        
#define RampEnd_BIE                    (* (reg8 *) RampEnd__BIE)
/* Bit-mask for Aliased Register Access */
#define RampEnd_BIT_MASK               (* (reg8 *) RampEnd__BIT_MASK)
/* Bypass Enable */
#define RampEnd_BYP                    (* (reg8 *) RampEnd__BYP)
/* Port wide control signals */                                                   
#define RampEnd_CTL                    (* (reg8 *) RampEnd__CTL)
/* Drive Modes */
#define RampEnd_DM0                    (* (reg8 *) RampEnd__DM0) 
#define RampEnd_DM1                    (* (reg8 *) RampEnd__DM1)
#define RampEnd_DM2                    (* (reg8 *) RampEnd__DM2) 
/* Input Buffer Disable Override */
#define RampEnd_INP_DIS                (* (reg8 *) RampEnd__INP_DIS)
/* LCD Common or Segment Drive */
#define RampEnd_LCD_COM_SEG            (* (reg8 *) RampEnd__LCD_COM_SEG)
/* Enable Segment LCD */
#define RampEnd_LCD_EN                 (* (reg8 *) RampEnd__LCD_EN)
/* Slew Rate Control */
#define RampEnd_SLW                    (* (reg8 *) RampEnd__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RampEnd_PRTDSI__CAPS_SEL       (* (reg8 *) RampEnd__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RampEnd_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RampEnd__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RampEnd_PRTDSI__OE_SEL0        (* (reg8 *) RampEnd__PRTDSI__OE_SEL0) 
#define RampEnd_PRTDSI__OE_SEL1        (* (reg8 *) RampEnd__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RampEnd_PRTDSI__OUT_SEL0       (* (reg8 *) RampEnd__PRTDSI__OUT_SEL0) 
#define RampEnd_PRTDSI__OUT_SEL1       (* (reg8 *) RampEnd__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RampEnd_PRTDSI__SYNC_OUT       (* (reg8 *) RampEnd__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RampEnd__SIO_CFG)
    #define RampEnd_SIO_HYST_EN        (* (reg8 *) RampEnd__SIO_HYST_EN)
    #define RampEnd_SIO_REG_HIFREQ     (* (reg8 *) RampEnd__SIO_REG_HIFREQ)
    #define RampEnd_SIO_CFG            (* (reg8 *) RampEnd__SIO_CFG)
    #define RampEnd_SIO_DIFF           (* (reg8 *) RampEnd__SIO_DIFF)
#endif /* (RampEnd__SIO_CFG) */

/* Interrupt Registers */
#if defined(RampEnd__INTSTAT)
    #define RampEnd_INTSTAT            (* (reg8 *) RampEnd__INTSTAT)
    #define RampEnd_SNAP               (* (reg8 *) RampEnd__SNAP)
    
	#define RampEnd_0_INTTYPE_REG 		(* (reg8 *) RampEnd__0__INTTYPE)
#endif /* (RampEnd__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RampEnd_H */


/* [] END OF FILE */
