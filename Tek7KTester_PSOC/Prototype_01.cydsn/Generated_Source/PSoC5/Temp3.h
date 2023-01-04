/*******************************************************************************
* File Name: Temp3.h  
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

#if !defined(CY_PINS_Temp3_H) /* Pins Temp3_H */
#define CY_PINS_Temp3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Temp3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Temp3__PORT == 15 && ((Temp3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Temp3_Write(uint8 value);
void    Temp3_SetDriveMode(uint8 mode);
uint8   Temp3_ReadDataReg(void);
uint8   Temp3_Read(void);
void    Temp3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Temp3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Temp3_SetDriveMode() function.
     *  @{
     */
        #define Temp3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Temp3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Temp3_DM_RES_UP          PIN_DM_RES_UP
        #define Temp3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Temp3_DM_OD_LO           PIN_DM_OD_LO
        #define Temp3_DM_OD_HI           PIN_DM_OD_HI
        #define Temp3_DM_STRONG          PIN_DM_STRONG
        #define Temp3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Temp3_MASK               Temp3__MASK
#define Temp3_SHIFT              Temp3__SHIFT
#define Temp3_WIDTH              1u

/* Interrupt constants */
#if defined(Temp3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Temp3_SetInterruptMode() function.
     *  @{
     */
        #define Temp3_INTR_NONE      (uint16)(0x0000u)
        #define Temp3_INTR_RISING    (uint16)(0x0001u)
        #define Temp3_INTR_FALLING   (uint16)(0x0002u)
        #define Temp3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Temp3_INTR_MASK      (0x01u) 
#endif /* (Temp3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Temp3_PS                     (* (reg8 *) Temp3__PS)
/* Data Register */
#define Temp3_DR                     (* (reg8 *) Temp3__DR)
/* Port Number */
#define Temp3_PRT_NUM                (* (reg8 *) Temp3__PRT) 
/* Connect to Analog Globals */                                                  
#define Temp3_AG                     (* (reg8 *) Temp3__AG)                       
/* Analog MUX bux enable */
#define Temp3_AMUX                   (* (reg8 *) Temp3__AMUX) 
/* Bidirectional Enable */                                                        
#define Temp3_BIE                    (* (reg8 *) Temp3__BIE)
/* Bit-mask for Aliased Register Access */
#define Temp3_BIT_MASK               (* (reg8 *) Temp3__BIT_MASK)
/* Bypass Enable */
#define Temp3_BYP                    (* (reg8 *) Temp3__BYP)
/* Port wide control signals */                                                   
#define Temp3_CTL                    (* (reg8 *) Temp3__CTL)
/* Drive Modes */
#define Temp3_DM0                    (* (reg8 *) Temp3__DM0) 
#define Temp3_DM1                    (* (reg8 *) Temp3__DM1)
#define Temp3_DM2                    (* (reg8 *) Temp3__DM2) 
/* Input Buffer Disable Override */
#define Temp3_INP_DIS                (* (reg8 *) Temp3__INP_DIS)
/* LCD Common or Segment Drive */
#define Temp3_LCD_COM_SEG            (* (reg8 *) Temp3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Temp3_LCD_EN                 (* (reg8 *) Temp3__LCD_EN)
/* Slew Rate Control */
#define Temp3_SLW                    (* (reg8 *) Temp3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Temp3_PRTDSI__CAPS_SEL       (* (reg8 *) Temp3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Temp3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Temp3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Temp3_PRTDSI__OE_SEL0        (* (reg8 *) Temp3__PRTDSI__OE_SEL0) 
#define Temp3_PRTDSI__OE_SEL1        (* (reg8 *) Temp3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Temp3_PRTDSI__OUT_SEL0       (* (reg8 *) Temp3__PRTDSI__OUT_SEL0) 
#define Temp3_PRTDSI__OUT_SEL1       (* (reg8 *) Temp3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Temp3_PRTDSI__SYNC_OUT       (* (reg8 *) Temp3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Temp3__SIO_CFG)
    #define Temp3_SIO_HYST_EN        (* (reg8 *) Temp3__SIO_HYST_EN)
    #define Temp3_SIO_REG_HIFREQ     (* (reg8 *) Temp3__SIO_REG_HIFREQ)
    #define Temp3_SIO_CFG            (* (reg8 *) Temp3__SIO_CFG)
    #define Temp3_SIO_DIFF           (* (reg8 *) Temp3__SIO_DIFF)
#endif /* (Temp3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Temp3__INTSTAT)
    #define Temp3_INTSTAT            (* (reg8 *) Temp3__INTSTAT)
    #define Temp3_SNAP               (* (reg8 *) Temp3__SNAP)
    
	#define Temp3_0_INTTYPE_REG 		(* (reg8 *) Temp3__0__INTTYPE)
#endif /* (Temp3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Temp3_H */


/* [] END OF FILE */
