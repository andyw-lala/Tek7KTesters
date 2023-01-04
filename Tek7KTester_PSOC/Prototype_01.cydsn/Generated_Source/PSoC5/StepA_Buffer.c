/*******************************************************************************
* File Name: StepA_Buffer.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "StepA_Buffer.h"

uint8 StepA_Buffer_initVar = 0u;


/*******************************************************************************   
* Function Name: StepA_Buffer_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  StepA_Buffer_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void StepA_Buffer_Init(void) 
{
    StepA_Buffer_SetPower(StepA_Buffer_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: StepA_Buffer_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void StepA_Buffer_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    StepA_Buffer_PUMP_CR1_REG  |= (StepA_Buffer_PUMP_CR1_CLKSEL | StepA_Buffer_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    StepA_Buffer_PM_ACT_CFG_REG |= StepA_Buffer_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    StepA_Buffer_PM_STBY_CFG_REG |= StepA_Buffer_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   StepA_Buffer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  StepA_Buffer_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void StepA_Buffer_Start(void) 
{
    if(StepA_Buffer_initVar == 0u)
    {
        StepA_Buffer_initVar = 1u;
        StepA_Buffer_Init();
    }

    StepA_Buffer_Enable();
}


/*******************************************************************************
* Function Name: StepA_Buffer_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void StepA_Buffer_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    StepA_Buffer_PM_ACT_CFG_REG &= (uint8)(~StepA_Buffer_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    StepA_Buffer_PM_STBY_CFG_REG &= (uint8)(~StepA_Buffer_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(StepA_Buffer_PM_ACT_CFG_REG == 0u)
    {
        StepA_Buffer_PUMP_CR1_REG &= (uint8)(~(StepA_Buffer_PUMP_CR1_CLKSEL | StepA_Buffer_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: StepA_Buffer_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void StepA_Buffer_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        StepA_Buffer_CR_REG &= (uint8)(~StepA_Buffer_PWR_MASK);
        StepA_Buffer_CR_REG |= power & StepA_Buffer_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(StepA_Buffer_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
