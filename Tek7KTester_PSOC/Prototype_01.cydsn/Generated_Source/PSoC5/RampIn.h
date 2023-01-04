/*******************************************************************************
* File Name: RampIn.h  
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

#if !defined(CY_PINS_RampIn_H) /* Pins RampIn_H */
#define CY_PINS_RampIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RampIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RampIn__PORT == 15 && ((RampIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RampIn_Write(uint8 value);
void    RampIn_SetDriveMode(uint8 mode);
uint8   RampIn_ReadDataReg(void);
uint8   RampIn_Read(void);
void    RampIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   RampIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RampIn_SetDriveMode() function.
     *  @{
     */
        #define RampIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RampIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RampIn_DM_RES_UP          PIN_DM_RES_UP
        #define RampIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define RampIn_DM_OD_LO           PIN_DM_OD_LO
        #define RampIn_DM_OD_HI           PIN_DM_OD_HI
        #define RampIn_DM_STRONG          PIN_DM_STRONG
        #define RampIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RampIn_MASK               RampIn__MASK
#define RampIn_SHIFT              RampIn__SHIFT
#define RampIn_WIDTH              1u

/* Interrupt constants */
#if defined(RampIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RampIn_SetInterruptMode() function.
     *  @{
     */
        #define RampIn_INTR_NONE      (uint16)(0x0000u)
        #define RampIn_INTR_RISING    (uint16)(0x0001u)
        #define RampIn_INTR_FALLING   (uint16)(0x0002u)
        #define RampIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RampIn_INTR_MASK      (0x01u) 
#endif /* (RampIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RampIn_PS                     (* (reg8 *) RampIn__PS)
/* Data Register */
#define RampIn_DR                     (* (reg8 *) RampIn__DR)
/* Port Number */
#define RampIn_PRT_NUM                (* (reg8 *) RampIn__PRT) 
/* Connect to Analog Globals */                                                  
#define RampIn_AG                     (* (reg8 *) RampIn__AG)                       
/* Analog MUX bux enable */
#define RampIn_AMUX                   (* (reg8 *) RampIn__AMUX) 
/* Bidirectional Enable */                                                        
#define RampIn_BIE                    (* (reg8 *) RampIn__BIE)
/* Bit-mask for Aliased Register Access */
#define RampIn_BIT_MASK               (* (reg8 *) RampIn__BIT_MASK)
/* Bypass Enable */
#define RampIn_BYP                    (* (reg8 *) RampIn__BYP)
/* Port wide control signals */                                                   
#define RampIn_CTL                    (* (reg8 *) RampIn__CTL)
/* Drive Modes */
#define RampIn_DM0                    (* (reg8 *) RampIn__DM0) 
#define RampIn_DM1                    (* (reg8 *) RampIn__DM1)
#define RampIn_DM2                    (* (reg8 *) RampIn__DM2) 
/* Input Buffer Disable Override */
#define RampIn_INP_DIS                (* (reg8 *) RampIn__INP_DIS)
/* LCD Common or Segment Drive */
#define RampIn_LCD_COM_SEG            (* (reg8 *) RampIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define RampIn_LCD_EN                 (* (reg8 *) RampIn__LCD_EN)
/* Slew Rate Control */
#define RampIn_SLW                    (* (reg8 *) RampIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RampIn_PRTDSI__CAPS_SEL       (* (reg8 *) RampIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RampIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RampIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RampIn_PRTDSI__OE_SEL0        (* (reg8 *) RampIn__PRTDSI__OE_SEL0) 
#define RampIn_PRTDSI__OE_SEL1        (* (reg8 *) RampIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RampIn_PRTDSI__OUT_SEL0       (* (reg8 *) RampIn__PRTDSI__OUT_SEL0) 
#define RampIn_PRTDSI__OUT_SEL1       (* (reg8 *) RampIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RampIn_PRTDSI__SYNC_OUT       (* (reg8 *) RampIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RampIn__SIO_CFG)
    #define RampIn_SIO_HYST_EN        (* (reg8 *) RampIn__SIO_HYST_EN)
    #define RampIn_SIO_REG_HIFREQ     (* (reg8 *) RampIn__SIO_REG_HIFREQ)
    #define RampIn_SIO_CFG            (* (reg8 *) RampIn__SIO_CFG)
    #define RampIn_SIO_DIFF           (* (reg8 *) RampIn__SIO_DIFF)
#endif /* (RampIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(RampIn__INTSTAT)
    #define RampIn_INTSTAT            (* (reg8 *) RampIn__INTSTAT)
    #define RampIn_SNAP               (* (reg8 *) RampIn__SNAP)
    
	#define RampIn_0_INTTYPE_REG 		(* (reg8 *) RampIn__0__INTTYPE)
#endif /* (RampIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RampIn_H */


/* [] END OF FILE */
