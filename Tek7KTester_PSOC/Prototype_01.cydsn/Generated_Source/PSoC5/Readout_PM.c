/*******************************************************************************
* File Name: Readout_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Readout.h"

static Readout_BACKUP_STRUCT Readout_backup =
{
    Readout_DISABLED,

    ((uint16) Readout_DEFAULT_A0),
    ((uint16) Readout_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint16) Readout_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: Readout_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Readout_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    Readout_backup.saveSrA0Reg   = CY_GET_REG16(Readout_SHIFT_REG_LSB_PTR);
    Readout_backup.saveSrA1Reg   = CY_GET_REG16(Readout_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        Readout_backup.saveSrIntMask = Readout_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Readout_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG16(Readout_SHIFT_REG_LSB_PTR, Readout_backup.saveSrA0Reg);
    CY_SET_REG16(Readout_SHIFT_REG_VALUE_LSB_PTR, Readout_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        Readout_SR_STATUS_MASK = ((uint8) Readout_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Readout_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Readout_Sleep(void) 
{
    Readout_backup.enableState = ((uint8) Readout_IS_ENABLED);

    Readout_Stop();
    Readout_SaveConfig();
}


/*******************************************************************************
* Function Name: Readout_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_Wakeup(void) 
{
    Readout_RestoreConfig();

    if(0u != Readout_backup.enableState)
    {
        Readout_Enable();
    }
}


/* [] END OF FILE */
