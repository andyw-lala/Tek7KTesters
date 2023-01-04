/*******************************************************************************
* File Name: StepX_Buffer_PM.c
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

#include "StepX_Buffer.h"

static StepX_Buffer_BACKUP_STRUCT  StepX_Buffer_backup;


/*******************************************************************************  
* Function Name: StepX_Buffer_SaveConfig
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
void StepX_Buffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: StepX_Buffer_RestoreConfig
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
void StepX_Buffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: StepX_Buffer_Sleep
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
*  StepX_Buffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void StepX_Buffer_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((StepX_Buffer_PM_ACT_CFG_REG & StepX_Buffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        StepX_Buffer_backup.enableState = 1u;
         /* Stops the component */
         StepX_Buffer_Stop();
    }
    else
    {
        /* Component is disabled */
        StepX_Buffer_backup.enableState = 0u;
    }
    /* Saves the configuration */
    StepX_Buffer_SaveConfig();
}


/*******************************************************************************  
* Function Name: StepX_Buffer_Wakeup
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
*  StepX_Buffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void StepX_Buffer_Wakeup(void) 
{
    /* Restore the user configuration */
    StepX_Buffer_RestoreConfig();

    /* Enables the component operation */
    if(StepX_Buffer_backup.enableState == 1u)
    {
        StepX_Buffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
