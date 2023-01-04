/*******************************************************************************
* File Name: VSense_ADC_Bypass_P32.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VSense_ADC_Bypass_P32_ALIASES_H) /* Pins VSense_ADC_Bypass_P32_ALIASES_H */
#define CY_PINS_VSense_ADC_Bypass_P32_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define VSense_ADC_Bypass_P32_0			(VSense_ADC_Bypass_P32__0__PC)
#define VSense_ADC_Bypass_P32_0_INTR	((uint16)((uint16)0x0001u << VSense_ADC_Bypass_P32__0__SHIFT))

#define VSense_ADC_Bypass_P32_INTR_ALL	 ((uint16)(VSense_ADC_Bypass_P32_0_INTR))

#endif /* End Pins VSense_ADC_Bypass_P32_ALIASES_H */


/* [] END OF FILE */
