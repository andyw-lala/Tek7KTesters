/*******************************************************************************
* File Name: Step_IDAC.c
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


#include "Step_IDAC.h"

static Step_IDAC_backupStruct Step_IDAC_backup;


/*******************************************************************************
* Function Name: Step_IDAC_SaveConfig
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
void Step_IDAC_SaveConfig(void) 
{
    if (!((Step_IDAC_CR1 & Step_IDAC_SRC_MASK) == Step_IDAC_SRC_UDB))
    {
        Step_IDAC_backup.data_value = Step_IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: Step_IDAC_RestoreConfig
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
void Step_IDAC_RestoreConfig(void) 
{
    if (!((Step_IDAC_CR1 & Step_IDAC_SRC_MASK) == Step_IDAC_SRC_UDB))
    {
        if((Step_IDAC_Strobe & Step_IDAC_STRB_MASK) == Step_IDAC_STRB_EN)
        {
            Step_IDAC_Strobe &= (uint8)(~Step_IDAC_STRB_MASK);
            Step_IDAC_Data = Step_IDAC_backup.data_value;
            Step_IDAC_Strobe |= Step_IDAC_STRB_EN;
        }
        else
        {
            Step_IDAC_Data = Step_IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Step_IDAC_Sleep
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
*  Step_IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Step_IDAC_Sleep(void) 
{
    if(Step_IDAC_ACT_PWR_EN == (Step_IDAC_PWRMGR & Step_IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        Step_IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        Step_IDAC_backup.enableState = 0u;
    }

    Step_IDAC_Stop();
    Step_IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: Step_IDAC_Wakeup
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
*  Step_IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Step_IDAC_Wakeup(void) 
{
    Step_IDAC_RestoreConfig();
    
    if(Step_IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        Step_IDAC_Enable();
        
        /* Set the data register */
        Step_IDAC_SetValue(Step_IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
