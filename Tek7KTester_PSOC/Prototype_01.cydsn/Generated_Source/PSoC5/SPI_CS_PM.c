/*******************************************************************************
* File Name: SPI_CS_PM.c
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

#include "SPI_CS.h"

/* Check for removal by optimization */
#if !defined(SPI_CS_Sync_ctrl_reg__REMOVED)

static SPI_CS_BACKUP_STRUCT  SPI_CS_backup = {0u};

    
/*******************************************************************************
* Function Name: SPI_CS_SaveConfig
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
void SPI_CS_SaveConfig(void) 
{
    SPI_CS_backup.controlState = SPI_CS_Control;
}


/*******************************************************************************
* Function Name: SPI_CS_RestoreConfig
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
void SPI_CS_RestoreConfig(void) 
{
     SPI_CS_Control = SPI_CS_backup.controlState;
}


/*******************************************************************************
* Function Name: SPI_CS_Sleep
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
void SPI_CS_Sleep(void) 
{
    SPI_CS_SaveConfig();
}


/*******************************************************************************
* Function Name: SPI_CS_Wakeup
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
void SPI_CS_Wakeup(void)  
{
    SPI_CS_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
