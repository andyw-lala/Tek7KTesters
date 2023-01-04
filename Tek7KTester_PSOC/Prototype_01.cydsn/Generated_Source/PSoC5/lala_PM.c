/*******************************************************************************
* File Name: lala_PM.c
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

#include "lala.h"

/* Check for removal by optimization */
#if !defined(lala_Sync_ctrl_reg__REMOVED)

static lala_BACKUP_STRUCT  lala_backup = {0u};

    
/*******************************************************************************
* Function Name: lala_SaveConfig
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
void lala_SaveConfig(void) 
{
    lala_backup.controlState = lala_Control;
}


/*******************************************************************************
* Function Name: lala_RestoreConfig
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
void lala_RestoreConfig(void) 
{
     lala_Control = lala_backup.controlState;
}


/*******************************************************************************
* Function Name: lala_Sleep
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
void lala_Sleep(void) 
{
    lala_SaveConfig();
}


/*******************************************************************************
* Function Name: lala_Wakeup
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
void lala_Wakeup(void)  
{
    lala_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
