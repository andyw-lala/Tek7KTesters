/*******************************************************************************
* File Name: Tick_PM.c
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

#include "Tick.h"

static Tick_backupStruct Tick_backup;


/*******************************************************************************
* Function Name: Tick_SaveConfig
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
*  Tick_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Tick_SaveConfig(void) 
{
    #if (!Tick_UsingFixedFunction)
        Tick_backup.TimerUdb = Tick_ReadCounter();
        Tick_backup.InterruptMaskValue = Tick_STATUS_MASK;
        #if (Tick_UsingHWCaptureCounter)
            Tick_backup.TimerCaptureCounter = Tick_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Tick_UDB_CONTROL_REG_REMOVED)
            Tick_backup.TimerControlRegister = Tick_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Tick_RestoreConfig
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
*  Tick_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Tick_RestoreConfig(void) 
{   
    #if (!Tick_UsingFixedFunction)

        Tick_WriteCounter(Tick_backup.TimerUdb);
        Tick_STATUS_MASK =Tick_backup.InterruptMaskValue;
        #if (Tick_UsingHWCaptureCounter)
            Tick_SetCaptureCount(Tick_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Tick_UDB_CONTROL_REG_REMOVED)
            Tick_WriteControlRegister(Tick_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Tick_Sleep
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
*  Tick_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Tick_Sleep(void) 
{
    #if(!Tick_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Tick_CTRL_ENABLE == (Tick_CONTROL & Tick_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Tick_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Tick_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Tick_Stop();
    Tick_SaveConfig();
}


/*******************************************************************************
* Function Name: Tick_Wakeup
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
*  Tick_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Tick_Wakeup(void) 
{
    Tick_RestoreConfig();
    #if(!Tick_UDB_CONTROL_REG_REMOVED)
        if(Tick_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Tick_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
