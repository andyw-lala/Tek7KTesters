/*******************************************************************************
* File Name: Test_Current_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Test_Current.h"

/* Check for removal by optimization */
#if !defined(Test_Current_Sync_ctrl_reg__REMOVED)

static Test_Current_BACKUP_STRUCT  Test_Current_backup = {0u};

    
/*******************************************************************************
* Function Name: Test_Current_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Test_Current_SaveConfig(void) 
{
    Test_Current_backup.controlState = Test_Current_Control;
}


/*******************************************************************************
* Function Name: Test_Current_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Test_Current_RestoreConfig(void) 
{
     Test_Current_Control = Test_Current_backup.controlState;
}


/*******************************************************************************
* Function Name: Test_Current_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Test_Current_Sleep(void) 
{
    Test_Current_SaveConfig();
}


/*******************************************************************************
* Function Name: Test_Current_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Test_Current_Wakeup(void)  
{
    Test_Current_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
