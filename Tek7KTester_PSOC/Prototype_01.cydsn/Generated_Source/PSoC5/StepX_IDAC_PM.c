/*******************************************************************************
* File Name: StepX_IDAC.c
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


#include "StepX_IDAC.h"

static StepX_IDAC_backupStruct StepX_IDAC_backup;


/*******************************************************************************
* Function Name: StepX_IDAC_SaveConfig
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
void StepX_IDAC_SaveConfig(void) 
{
    if (!((StepX_IDAC_CR1 & StepX_IDAC_SRC_MASK) == StepX_IDAC_SRC_UDB))
    {
        StepX_IDAC_backup.data_value = StepX_IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: StepX_IDAC_RestoreConfig
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
void StepX_IDAC_RestoreConfig(void) 
{
    if (!((StepX_IDAC_CR1 & StepX_IDAC_SRC_MASK) == StepX_IDAC_SRC_UDB))
    {
        if((StepX_IDAC_Strobe & StepX_IDAC_STRB_MASK) == StepX_IDAC_STRB_EN)
        {
            StepX_IDAC_Strobe &= (uint8)(~StepX_IDAC_STRB_MASK);
            StepX_IDAC_Data = StepX_IDAC_backup.data_value;
            StepX_IDAC_Strobe |= StepX_IDAC_STRB_EN;
        }
        else
        {
            StepX_IDAC_Data = StepX_IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: StepX_IDAC_Sleep
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
*  StepX_IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void StepX_IDAC_Sleep(void) 
{
    if(StepX_IDAC_ACT_PWR_EN == (StepX_IDAC_PWRMGR & StepX_IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        StepX_IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        StepX_IDAC_backup.enableState = 0u;
    }

    StepX_IDAC_Stop();
    StepX_IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: StepX_IDAC_Wakeup
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
*  StepX_IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepX_IDAC_Wakeup(void) 
{
    StepX_IDAC_RestoreConfig();
    
    if(StepX_IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        StepX_IDAC_Enable();
        
        /* Set the data register */
        StepX_IDAC_SetValue(StepX_IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
