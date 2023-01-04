/*******************************************************************************
* File Name: Sweep_IDAC.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
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


#include "Sweep_IDAC.h"

static Sweep_IDAC_backupStruct Sweep_IDAC_backup;


/*******************************************************************************
* Function Name: Sweep_IDAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Sweep_IDAC_SaveConfig(void) 
{
    if (!((Sweep_IDAC_CR1 & Sweep_IDAC_SRC_MASK) == Sweep_IDAC_SRC_UDB))
    {
        Sweep_IDAC_backup.data_value = Sweep_IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: Sweep_IDAC_RestoreConfig
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
*******************************************************************************/
void Sweep_IDAC_RestoreConfig(void) 
{
    if (!((Sweep_IDAC_CR1 & Sweep_IDAC_SRC_MASK) == Sweep_IDAC_SRC_UDB))
    {
        if((Sweep_IDAC_Strobe & Sweep_IDAC_STRB_MASK) == Sweep_IDAC_STRB_EN)
        {
            Sweep_IDAC_Strobe &= (uint8)(~Sweep_IDAC_STRB_MASK);
            Sweep_IDAC_Data = Sweep_IDAC_backup.data_value;
            Sweep_IDAC_Strobe |= Sweep_IDAC_STRB_EN;
        }
        else
        {
            Sweep_IDAC_Data = Sweep_IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Sweep_IDAC_Sleep
********************************************************************************
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
*  Sweep_IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Sweep_IDAC_Sleep(void) 
{
    if(Sweep_IDAC_ACT_PWR_EN == (Sweep_IDAC_PWRMGR & Sweep_IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        Sweep_IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        Sweep_IDAC_backup.enableState = 0u;
    }

    Sweep_IDAC_Stop();
    Sweep_IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: Sweep_IDAC_Wakeup
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
*  Sweep_IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Sweep_IDAC_Wakeup(void) 
{
    Sweep_IDAC_RestoreConfig();
    
    if(Sweep_IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        Sweep_IDAC_Enable();
        
        /* Set the data register */
        Sweep_IDAC_SetValue(Sweep_IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
