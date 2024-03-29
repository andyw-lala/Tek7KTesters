/*******************************************************************************
* File Name: Display_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Display_PWM.h"

static Display_PWM_backupStruct Display_PWM_backup;


/*******************************************************************************
* Function Name: Display_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Display_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Display_PWM_SaveConfig(void) 
{

    #if(!Display_PWM_UsingFixedFunction)
        #if(!Display_PWM_PWMModeIsCenterAligned)
            Display_PWM_backup.PWMPeriod = Display_PWM_ReadPeriod();
        #endif /* (!Display_PWM_PWMModeIsCenterAligned) */
        Display_PWM_backup.PWMUdb = Display_PWM_ReadCounter();
        #if (Display_PWM_UseStatus)
            Display_PWM_backup.InterruptMaskValue = Display_PWM_STATUS_MASK;
        #endif /* (Display_PWM_UseStatus) */

        #if(Display_PWM_DeadBandMode == Display_PWM__B_PWM__DBM_256_CLOCKS || \
            Display_PWM_DeadBandMode == Display_PWM__B_PWM__DBM_2_4_CLOCKS)
            Display_PWM_backup.PWMdeadBandValue = Display_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Display_PWM_KillModeMinTime)
             Display_PWM_backup.PWMKillCounterPeriod = Display_PWM_ReadKillTime();
        #endif /* (Display_PWM_KillModeMinTime) */

        #if(Display_PWM_UseControl)
            Display_PWM_backup.PWMControlRegister = Display_PWM_ReadControlRegister();
        #endif /* (Display_PWM_UseControl) */
    #endif  /* (!Display_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Display_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Display_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Display_PWM_RestoreConfig(void) 
{
        #if(!Display_PWM_UsingFixedFunction)
            #if(!Display_PWM_PWMModeIsCenterAligned)
                Display_PWM_WritePeriod(Display_PWM_backup.PWMPeriod);
            #endif /* (!Display_PWM_PWMModeIsCenterAligned) */

            Display_PWM_WriteCounter(Display_PWM_backup.PWMUdb);

            #if (Display_PWM_UseStatus)
                Display_PWM_STATUS_MASK = Display_PWM_backup.InterruptMaskValue;
            #endif /* (Display_PWM_UseStatus) */

            #if(Display_PWM_DeadBandMode == Display_PWM__B_PWM__DBM_256_CLOCKS || \
                Display_PWM_DeadBandMode == Display_PWM__B_PWM__DBM_2_4_CLOCKS)
                Display_PWM_WriteDeadTime(Display_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Display_PWM_KillModeMinTime)
                Display_PWM_WriteKillTime(Display_PWM_backup.PWMKillCounterPeriod);
            #endif /* (Display_PWM_KillModeMinTime) */

            #if(Display_PWM_UseControl)
                Display_PWM_WriteControlRegister(Display_PWM_backup.PWMControlRegister);
            #endif /* (Display_PWM_UseControl) */
        #endif  /* (!Display_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Display_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Display_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Display_PWM_Sleep(void) 
{
    #if(Display_PWM_UseControl)
        if(Display_PWM_CTRL_ENABLE == (Display_PWM_CONTROL & Display_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            Display_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Display_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (Display_PWM_UseControl) */

    /* Stop component */
    Display_PWM_Stop();

    /* Save registers configuration */
    Display_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Display_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Display_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Display_PWM_Wakeup(void) 
{
     /* Restore registers values */
    Display_PWM_RestoreConfig();

    if(Display_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Display_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
