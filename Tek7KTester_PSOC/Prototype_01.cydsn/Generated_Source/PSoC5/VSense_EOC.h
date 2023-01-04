/*******************************************************************************
* File Name: VSense_EOC.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_VSense_EOC_H)
#define CY_ISR_VSense_EOC_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void VSense_EOC_Start(void);
void VSense_EOC_StartEx(cyisraddress address);
void VSense_EOC_Stop(void);

CY_ISR_PROTO(VSense_EOC_Interrupt);

void VSense_EOC_SetVector(cyisraddress address);
cyisraddress VSense_EOC_GetVector(void);

void VSense_EOC_SetPriority(uint8 priority);
uint8 VSense_EOC_GetPriority(void);

void VSense_EOC_Enable(void);
uint8 VSense_EOC_GetState(void);
void VSense_EOC_Disable(void);

void VSense_EOC_SetPending(void);
void VSense_EOC_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the VSense_EOC ISR. */
#define VSense_EOC_INTC_VECTOR            ((reg32 *) VSense_EOC__INTC_VECT)

/* Address of the VSense_EOC ISR priority. */
#define VSense_EOC_INTC_PRIOR             ((reg8 *) VSense_EOC__INTC_PRIOR_REG)

/* Priority of the VSense_EOC interrupt. */
#define VSense_EOC_INTC_PRIOR_NUMBER      VSense_EOC__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable VSense_EOC interrupt. */
#define VSense_EOC_INTC_SET_EN            ((reg32 *) VSense_EOC__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the VSense_EOC interrupt. */
#define VSense_EOC_INTC_CLR_EN            ((reg32 *) VSense_EOC__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the VSense_EOC interrupt state to pending. */
#define VSense_EOC_INTC_SET_PD            ((reg32 *) VSense_EOC__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the VSense_EOC interrupt. */
#define VSense_EOC_INTC_CLR_PD            ((reg32 *) VSense_EOC__INTC_CLR_PD_REG)


#endif /* CY_ISR_VSense_EOC_H */


/* [] END OF FILE */
