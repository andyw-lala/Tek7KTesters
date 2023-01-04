/*******************************************************************************
* File Name: StepA_IDAC.c
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


#include "StepA_IDAC.h"

static StepA_IDAC_backupStruct StepA_IDAC_backup;


/*******************************************************************************
* Function Name: StepA_IDAC_SaveConfig
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
void StepA_IDAC_SaveConfig(void) 
{
    if (!((StepA_IDAC_CR1 & StepA_IDAC_SRC_MASK) == StepA_IDAC_SRC_UDB))
    {
        StepA_IDAC_backup.data_value = StepA_IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: StepA_IDAC_RestoreConfig
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
void StepA_IDAC_RestoreConfig(void) 
{
    if (!((StepA_IDAC_CR1 & StepA_IDAC_SRC_MASK) == StepA_IDAC_SRC_UDB))
    {
        if((StepA_IDAC_Strobe & StepA_IDAC_STRB_MASK) == StepA_IDAC_STRB_EN)
        {
            StepA_IDAC_Strobe &= (uint8)(~StepA_IDAC_STRB_MASK);
            StepA_IDAC_Data = StepA_IDAC_backup.data_value;
            StepA_IDAC_Strobe |= StepA_IDAC_STRB_EN;
        }
        else
        {
            StepA_IDAC_Data = StepA_IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: StepA_IDAC_Sleep
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
*  StepA_IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void StepA_IDAC_Sleep(void) 
{
    if(StepA_IDAC_ACT_PWR_EN == (StepA_IDAC_PWRMGR & StepA_IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        StepA_IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        StepA_IDAC_backup.enableState = 0u;
    }

    StepA_IDAC_Stop();
    StepA_IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: StepA_IDAC_Wakeup
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
*  StepA_IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepA_IDAC_Wakeup(void) 
{
    StepA_IDAC_RestoreConfig();
    
    if(StepA_IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        StepA_IDAC_Enable();
        
        /* Set the data register */
        StepA_IDAC_SetValue(StepA_IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
