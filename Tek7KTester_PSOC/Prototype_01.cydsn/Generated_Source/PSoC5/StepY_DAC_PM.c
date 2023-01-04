/*******************************************************************************
* File Name: StepY_DAC_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "StepY_DAC.h"

static StepY_DAC_backupStruct StepY_DAC_backup;


/*******************************************************************************
* Function Name: StepY_DAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void StepY_DAC_SaveConfig(void) 
{
    if (!((StepY_DAC_CR1 & StepY_DAC_SRC_MASK) == StepY_DAC_SRC_UDB))
    {
        StepY_DAC_backup.data_value = StepY_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: StepY_DAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void StepY_DAC_RestoreConfig(void) 
{
    if (!((StepY_DAC_CR1 & StepY_DAC_SRC_MASK) == StepY_DAC_SRC_UDB))
    {
        if((StepY_DAC_Strobe & StepY_DAC_STRB_MASK) == StepY_DAC_STRB_EN)
        {
            StepY_DAC_Strobe &= (uint8)(~StepY_DAC_STRB_MASK);
            StepY_DAC_Data = StepY_DAC_backup.data_value;
            StepY_DAC_Strobe |= StepY_DAC_STRB_EN;
        }
        else
        {
            StepY_DAC_Data = StepY_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: StepY_DAC_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  StepY_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void StepY_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(StepY_DAC_ACT_PWR_EN == (StepY_DAC_PWRMGR & StepY_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        StepY_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        StepY_DAC_backup.enableState = 0u;
    }
    
    StepY_DAC_Stop();
    StepY_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: StepY_DAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  StepY_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepY_DAC_Wakeup(void) 
{
    StepY_DAC_RestoreConfig();
    
    if(StepY_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        StepY_DAC_Enable();

        /* Restore the data register */
        StepY_DAC_SetValue(StepY_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
