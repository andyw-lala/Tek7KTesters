/*******************************************************************************
* File Name: Sweep_Comp.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "Sweep_Comp.h"

static Sweep_Comp_backupStruct Sweep_Comp_backup;


/*******************************************************************************
* Function Name: Sweep_Comp_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Sweep_Comp_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Sweep_Comp_RestoreConfig
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
********************************************************************************/
void Sweep_Comp_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Sweep_Comp_Sleep
********************************************************************************
*
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
*  Sweep_Comp_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Sweep_Comp_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Sweep_Comp_ACT_PWR_EN == (Sweep_Comp_PWRMGR & Sweep_Comp_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Sweep_Comp_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Sweep_Comp_backup.enableState = 0u;
    }    
    
    Sweep_Comp_Stop();
    Sweep_Comp_SaveConfig();
}


/*******************************************************************************
* Function Name: Sweep_Comp_Wakeup
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
*  Sweep_Comp_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Sweep_Comp_Wakeup(void) 
{
    Sweep_Comp_RestoreConfig();
    
    if(Sweep_Comp_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Sweep_Comp_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
