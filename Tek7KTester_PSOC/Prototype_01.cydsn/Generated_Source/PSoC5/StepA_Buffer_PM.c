/*******************************************************************************
* File Name: StepA_Buffer_PM.c
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

#include "StepA_Buffer.h"

static StepA_Buffer_BACKUP_STRUCT  StepA_Buffer_backup;


/*******************************************************************************  
* Function Name: StepA_Buffer_SaveConfig
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
void StepA_Buffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: StepA_Buffer_RestoreConfig
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
void StepA_Buffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: StepA_Buffer_Sleep
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
*  StepA_Buffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void StepA_Buffer_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((StepA_Buffer_PM_ACT_CFG_REG & StepA_Buffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        StepA_Buffer_backup.enableState = 1u;
         /* Stops the component */
         StepA_Buffer_Stop();
    }
    else
    {
        /* Component is disabled */
        StepA_Buffer_backup.enableState = 0u;
    }
    /* Saves the configuration */
    StepA_Buffer_SaveConfig();
}


/*******************************************************************************  
* Function Name: StepA_Buffer_Wakeup
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
*  StepA_Buffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void StepA_Buffer_Wakeup(void) 
{
    /* Restore the user configuration */
    StepA_Buffer_RestoreConfig();

    /* Enables the component operation */
    if(StepA_Buffer_backup.enableState == 1u)
    {
        StepA_Buffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
