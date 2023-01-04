/*******************************************************************************
* File Name: Sweep_Tick_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Sweep_Tick.h"

static Sweep_Tick_backupStruct Sweep_Tick_backup;


/*******************************************************************************
* Function Name: Sweep_Tick_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Sweep_Tick_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Sweep_Tick_SaveConfig(void) 
{
    #if (!Sweep_Tick_UsingFixedFunction)
        Sweep_Tick_backup.TimerUdb = Sweep_Tick_ReadCounter();
        Sweep_Tick_backup.InterruptMaskValue = Sweep_Tick_STATUS_MASK;
        #if (Sweep_Tick_UsingHWCaptureCounter)
            Sweep_Tick_backup.TimerCaptureCounter = Sweep_Tick_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Sweep_Tick_UDB_CONTROL_REG_REMOVED)
            Sweep_Tick_backup.TimerControlRegister = Sweep_Tick_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Sweep_Tick_RestoreConfig
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
* Global variables:
*  Sweep_Tick_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Sweep_Tick_RestoreConfig(void) 
{   
    #if (!Sweep_Tick_UsingFixedFunction)

        Sweep_Tick_WriteCounter(Sweep_Tick_backup.TimerUdb);
        Sweep_Tick_STATUS_MASK =Sweep_Tick_backup.InterruptMaskValue;
        #if (Sweep_Tick_UsingHWCaptureCounter)
            Sweep_Tick_SetCaptureCount(Sweep_Tick_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Sweep_Tick_UDB_CONTROL_REG_REMOVED)
            Sweep_Tick_WriteControlRegister(Sweep_Tick_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Sweep_Tick_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Sweep_Tick_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Sweep_Tick_Sleep(void) 
{
    #if(!Sweep_Tick_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Sweep_Tick_CTRL_ENABLE == (Sweep_Tick_CONTROL & Sweep_Tick_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Sweep_Tick_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Sweep_Tick_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Sweep_Tick_Stop();
    Sweep_Tick_SaveConfig();
}


/*******************************************************************************
* Function Name: Sweep_Tick_Wakeup
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
*  Sweep_Tick_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Sweep_Tick_Wakeup(void) 
{
    Sweep_Tick_RestoreConfig();
    #if(!Sweep_Tick_UDB_CONTROL_REG_REMOVED)
        if(Sweep_Tick_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Sweep_Tick_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
