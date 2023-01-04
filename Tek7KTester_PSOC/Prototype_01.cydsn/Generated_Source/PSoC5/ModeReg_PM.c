/*******************************************************************************
* File Name: ModeReg_PM.c
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

#include "ModeReg.h"

/* Check for removal by optimization */
#if !defined(ModeReg_Sync_ctrl_reg__REMOVED)

static ModeReg_BACKUP_STRUCT  ModeReg_backup = {0u};

    
/*******************************************************************************
* Function Name: ModeReg_SaveConfig
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
void ModeReg_SaveConfig(void) 
{
    ModeReg_backup.controlState = ModeReg_Control;
}


/*******************************************************************************
* Function Name: ModeReg_RestoreConfig
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
void ModeReg_RestoreConfig(void) 
{
     ModeReg_Control = ModeReg_backup.controlState;
}


/*******************************************************************************
* Function Name: ModeReg_Sleep
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
void ModeReg_Sleep(void) 
{
    ModeReg_SaveConfig();
}


/*******************************************************************************
* Function Name: ModeReg_Wakeup
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
void ModeReg_Wakeup(void)  
{
    ModeReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
