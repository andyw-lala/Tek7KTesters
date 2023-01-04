/*******************************************************************************
* File Name: Readout_SR_PM.c
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

#include "Readout_SR.h"

static Readout_SR_BACKUP_STRUCT Readout_SR_backup =
{
    Readout_SR_DISABLED,

    ((uint16) Readout_SR_DEFAULT_A0),
    ((uint16) Readout_SR_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint16) Readout_SR_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: Readout_SR_SaveConfig
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
void Readout_SR_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    Readout_SR_backup.saveSrA0Reg   = CY_GET_REG16(Readout_SR_SHIFT_REG_LSB_PTR);
    Readout_SR_backup.saveSrA1Reg   = CY_GET_REG16(Readout_SR_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        Readout_SR_backup.saveSrIntMask = Readout_SR_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Readout_SR_RestoreConfig
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
void Readout_SR_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG16(Readout_SR_SHIFT_REG_LSB_PTR, Readout_SR_backup.saveSrA0Reg);
    CY_SET_REG16(Readout_SR_SHIFT_REG_VALUE_LSB_PTR, Readout_SR_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        Readout_SR_SR_STATUS_MASK = ((uint8) Readout_SR_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Readout_SR_Sleep
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
void Readout_SR_Sleep(void) 
{
    Readout_SR_backup.enableState = ((uint8) Readout_SR_IS_ENABLED);

    Readout_SR_Stop();
    Readout_SR_SaveConfig();
}


/*******************************************************************************
* Function Name: Readout_SR_Wakeup
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
void Readout_SR_Wakeup(void) 
{
    Readout_SR_RestoreConfig();

    if(0u != Readout_SR_backup.enableState)
    {
        Readout_SR_Enable();
    }
}


/* [] END OF FILE */
