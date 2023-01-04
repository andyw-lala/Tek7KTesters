/*******************************************************************************
* File Name: Readout_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Readout_Counter.h"

static Readout_Counter_backupStruct Readout_Counter_backup;


/*******************************************************************************
* Function Name: Readout_Counter_SaveConfig
********************************************************************************
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
*  Readout_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Readout_Counter_SaveConfig(void) 
{
    #if (!Readout_Counter_UsingFixedFunction)

        Readout_Counter_backup.CounterUdb = Readout_Counter_ReadCounter();

        #if(!Readout_Counter_ControlRegRemoved)
            Readout_Counter_backup.CounterControlRegister = Readout_Counter_ReadControlRegister();
        #endif /* (!Readout_Counter_ControlRegRemoved) */

    #endif /* (!Readout_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Readout_Counter_RestoreConfig
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
*  Readout_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Readout_Counter_RestoreConfig(void) 
{      
    #if (!Readout_Counter_UsingFixedFunction)

       Readout_Counter_WriteCounter(Readout_Counter_backup.CounterUdb);

        #if(!Readout_Counter_ControlRegRemoved)
            Readout_Counter_WriteControlRegister(Readout_Counter_backup.CounterControlRegister);
        #endif /* (!Readout_Counter_ControlRegRemoved) */

    #endif /* (!Readout_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Readout_Counter_Sleep
********************************************************************************
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
*  Readout_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Readout_Counter_Sleep(void) 
{
    #if(!Readout_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Readout_Counter_CTRL_ENABLE == (Readout_Counter_CONTROL & Readout_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Readout_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Readout_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Readout_Counter_backup.CounterEnableState = 1u;
        if(Readout_Counter_backup.CounterEnableState != 0u)
        {
            Readout_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Readout_Counter_ControlRegRemoved) */
    
    Readout_Counter_Stop();
    Readout_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Readout_Counter_Wakeup
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
*  Readout_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Readout_Counter_Wakeup(void) 
{
    Readout_Counter_RestoreConfig();
    #if(!Readout_Counter_ControlRegRemoved)
        if(Readout_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Readout_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Readout_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
