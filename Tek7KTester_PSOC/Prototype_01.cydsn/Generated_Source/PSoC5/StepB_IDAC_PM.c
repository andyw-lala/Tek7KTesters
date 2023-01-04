/*******************************************************************************
* File Name: StepB_IDAC.c
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


#include "StepB_IDAC.h"

static StepB_IDAC_backupStruct StepB_IDAC_backup;


/*******************************************************************************
* Function Name: StepB_IDAC_SaveConfig
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
void StepB_IDAC_SaveConfig(void) 
{
    if (!((StepB_IDAC_CR1 & StepB_IDAC_SRC_MASK) == StepB_IDAC_SRC_UDB))
    {
        StepB_IDAC_backup.data_value = StepB_IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: StepB_IDAC_RestoreConfig
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
void StepB_IDAC_RestoreConfig(void) 
{
    if (!((StepB_IDAC_CR1 & StepB_IDAC_SRC_MASK) == StepB_IDAC_SRC_UDB))
    {
        if((StepB_IDAC_Strobe & StepB_IDAC_STRB_MASK) == StepB_IDAC_STRB_EN)
        {
            StepB_IDAC_Strobe &= (uint8)(~StepB_IDAC_STRB_MASK);
            StepB_IDAC_Data = StepB_IDAC_backup.data_value;
            StepB_IDAC_Strobe |= StepB_IDAC_STRB_EN;
        }
        else
        {
            StepB_IDAC_Data = StepB_IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: StepB_IDAC_Sleep
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
*  StepB_IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void StepB_IDAC_Sleep(void) 
{
    if(StepB_IDAC_ACT_PWR_EN == (StepB_IDAC_PWRMGR & StepB_IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        StepB_IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        StepB_IDAC_backup.enableState = 0u;
    }

    StepB_IDAC_Stop();
    StepB_IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: StepB_IDAC_Wakeup
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
*  StepB_IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepB_IDAC_Wakeup(void) 
{
    StepB_IDAC_RestoreConfig();
    
    if(StepB_IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        StepB_IDAC_Enable();
        
        /* Set the data register */
        StepB_IDAC_SetValue(StepB_IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
