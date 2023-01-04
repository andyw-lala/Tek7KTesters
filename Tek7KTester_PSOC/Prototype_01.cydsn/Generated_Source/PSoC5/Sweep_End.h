/*******************************************************************************
* File Name: Sweep_End.h
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
#if !defined(CY_ISR_Sweep_End_H)
#define CY_ISR_Sweep_End_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Sweep_End_Start(void);
void Sweep_End_StartEx(cyisraddress address);
void Sweep_End_Stop(void);

CY_ISR_PROTO(Sweep_End_Interrupt);

void Sweep_End_SetVector(cyisraddress address);
cyisraddress Sweep_End_GetVector(void);

void Sweep_End_SetPriority(uint8 priority);
uint8 Sweep_End_GetPriority(void);

void Sweep_End_Enable(void);
uint8 Sweep_End_GetState(void);
void Sweep_End_Disable(void);

void Sweep_End_SetPending(void);
void Sweep_End_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Sweep_End ISR. */
#define Sweep_End_INTC_VECTOR            ((reg32 *) Sweep_End__INTC_VECT)

/* Address of the Sweep_End ISR priority. */
#define Sweep_End_INTC_PRIOR             ((reg8 *) Sweep_End__INTC_PRIOR_REG)

/* Priority of the Sweep_End interrupt. */
#define Sweep_End_INTC_PRIOR_NUMBER      Sweep_End__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Sweep_End interrupt. */
#define Sweep_End_INTC_SET_EN            ((reg32 *) Sweep_End__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Sweep_End interrupt. */
#define Sweep_End_INTC_CLR_EN            ((reg32 *) Sweep_End__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Sweep_End interrupt state to pending. */
#define Sweep_End_INTC_SET_PD            ((reg32 *) Sweep_End__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Sweep_End interrupt. */
#define Sweep_End_INTC_CLR_PD            ((reg32 *) Sweep_End__INTC_CLR_PD_REG)


#endif /* CY_ISR_Sweep_End_H */


/* [] END OF FILE */
