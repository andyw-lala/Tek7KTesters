/*******************************************************************************
* File Name: StepY_IDAC.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
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


#include "StepY_IDAC.h"

static StepY_IDAC_backupStruct StepY_IDAC_backup;


/*******************************************************************************
* Function Name: StepY_IDAC_SaveConfig
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
void StepY_IDAC_SaveConfig(void) 
{
    if (!((StepY_IDAC_CR1 & StepY_IDAC_SRC_MASK) == StepY_IDAC_SRC_UDB))
    {
        StepY_IDAC_backup.data_value = StepY_IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: StepY_IDAC_RestoreConfig
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
void StepY_IDAC_RestoreConfig(void) 
{
    if (!((StepY_IDAC_CR1 & StepY_IDAC_SRC_MASK) == StepY_IDAC_SRC_UDB))
    {
        if((StepY_IDAC_Strobe & StepY_IDAC_STRB_MASK) == StepY_IDAC_STRB_EN)
        {
            StepY_IDAC_Strobe &= (uint8)(~StepY_IDAC_STRB_MASK);
            StepY_IDAC_Data = StepY_IDAC_backup.data_value;
            StepY_IDAC_Strobe |= StepY_IDAC_STRB_EN;
        }
        else
        {
            StepY_IDAC_Data = StepY_IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: StepY_IDAC_Sleep
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
*  StepY_IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void StepY_IDAC_Sleep(void) 
{
    if(StepY_IDAC_ACT_PWR_EN == (StepY_IDAC_PWRMGR & StepY_IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        StepY_IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        StepY_IDAC_backup.enableState = 0u;
    }

    StepY_IDAC_Stop();
    StepY_IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: StepY_IDAC_Wakeup
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
*  StepY_IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepY_IDAC_Wakeup(void) 
{
    StepY_IDAC_RestoreConfig();
    
    if(StepY_IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        StepY_IDAC_Enable();
        
        /* Set the data register */
        StepY_IDAC_SetValue(StepY_IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
