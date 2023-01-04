/*******************************************************************************
* File Name: Step_Buffer_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Step_Buffer.h"

static Step_Buffer_BACKUP_STRUCT  Step_Buffer_backup;


/*******************************************************************************  
* Function Name: Step_Buffer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void Step_Buffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Step_Buffer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Step_Buffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Step_Buffer_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Step_Buffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Step_Buffer_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((Step_Buffer_PM_ACT_CFG_REG & Step_Buffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Step_Buffer_backup.enableState = 1u;
         /* Stops the component */
         Step_Buffer_Stop();
    }
    else
    {
        /* Component is disabled */
        Step_Buffer_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Step_Buffer_SaveConfig();
}


/*******************************************************************************  
* Function Name: Step_Buffer_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Step_Buffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Step_Buffer_Wakeup(void) 
{
    /* Restore the user configuration */
    Step_Buffer_RestoreConfig();

    /* Enables the component operation */
    if(Step_Buffer_backup.enableState == 1u)
    {
        Step_Buffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
