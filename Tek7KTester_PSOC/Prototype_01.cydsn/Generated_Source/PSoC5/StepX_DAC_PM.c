/*******************************************************************************
* File Name: StepX_DAC_PM.c  
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

#include "StepX_DAC.h"

static StepX_DAC_backupStruct StepX_DAC_backup;


/*******************************************************************************
* Function Name: StepX_DAC_SaveConfig
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
void StepX_DAC_SaveConfig(void) 
{
    if (!((StepX_DAC_CR1 & StepX_DAC_SRC_MASK) == StepX_DAC_SRC_UDB))
    {
        StepX_DAC_backup.data_value = StepX_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: StepX_DAC_RestoreConfig
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
void StepX_DAC_RestoreConfig(void) 
{
    if (!((StepX_DAC_CR1 & StepX_DAC_SRC_MASK) == StepX_DAC_SRC_UDB))
    {
        if((StepX_DAC_Strobe & StepX_DAC_STRB_MASK) == StepX_DAC_STRB_EN)
        {
            StepX_DAC_Strobe &= (uint8)(~StepX_DAC_STRB_MASK);
            StepX_DAC_Data = StepX_DAC_backup.data_value;
            StepX_DAC_Strobe |= StepX_DAC_STRB_EN;
        }
        else
        {
            StepX_DAC_Data = StepX_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: StepX_DAC_Sleep
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
*  StepX_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void StepX_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(StepX_DAC_ACT_PWR_EN == (StepX_DAC_PWRMGR & StepX_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        StepX_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        StepX_DAC_backup.enableState = 0u;
    }
    
    StepX_DAC_Stop();
    StepX_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: StepX_DAC_Wakeup
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
*  StepX_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepX_DAC_Wakeup(void) 
{
    StepX_DAC_RestoreConfig();
    
    if(StepX_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        StepX_DAC_Enable();

        /* Restore the data register */
        StepX_DAC_SetValue(StepX_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
