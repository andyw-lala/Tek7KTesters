/*******************************************************************************
* File Name: Step_IDAC.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the 8-bit Current 
*  DAC (IDAC8) User Module.
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

#include "cytypes.h"
#include "Step_IDAC.h"   

#if (CY_PSOC5A)
    #include <CyLib.h>
#endif /* CY_PSOC5A */


uint8 Step_IDAC_initVar = 0u;


#if (CY_PSOC5A)
    static Step_IDAC_LOWPOWER_BACKUP_STRUCT  Step_IDAC_lowPowerBackup;
#endif /* CY_PSOC5A */

/* Variable to decide whether or not to restore control register in Enable()
   API. This valid only for PSoC5A */
#if (CY_PSOC5A)
    static uint8 Step_IDAC_restoreReg = 0u;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Step_IDAC_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_Init(void) 
{
    Step_IDAC_CR0 = (Step_IDAC_MODE_I | Step_IDAC_DEFAULT_RANGE );

    /* Set default data source */
    #if(Step_IDAC_DEFAULT_DATA_SRC != 0u )    
        Step_IDAC_CR1 = (Step_IDAC_DEFAULT_CNTL | Step_IDAC_DACBUS_ENABLE);
    #else
        Step_IDAC_CR1 = (Step_IDAC_DEFAULT_CNTL | Step_IDAC_DACBUS_DISABLE);
    #endif /* (Step_IDAC_DEFAULT_DATA_SRC != 0u ) */
    
    /*Controls polarity from UDB Control*/
    #if(Step_IDAC_DEFAULT_POLARITY == Step_IDAC_HARDWARE_CONTROLLED)
        Step_IDAC_CR1 |= Step_IDAC_IDIR_SRC_UDB;
    #else
        Step_IDAC_CR1 |= Step_IDAC_DEFAULT_POLARITY;
    #endif/* (Step_IDAC_DEFAULT_POLARITY == Step_IDAC_HARDWARE_CONTROLLED) */
    /*Controls Current Source from UDB Control*/
    #if(Step_IDAC_HARDWARE_ENABLE != 0u ) 
        Step_IDAC_CR1 |= Step_IDAC_IDIR_CTL_UDB;
    #endif /* (Step_IDAC_HARDWARE_ENABLE != 0u ) */ 
    
    /* Set default strobe mode */
    #if(Step_IDAC_DEFAULT_STRB != 0u)
        Step_IDAC_Strobe |= Step_IDAC_STRB_EN;
    #endif /* (Step_IDAC_DEFAULT_STRB != 0u) */
    
    /* Set default speed */
    Step_IDAC_SetSpeed(Step_IDAC_DEFAULT_SPEED);
    
    /* Set proper DAC trim */
    Step_IDAC_DacTrim();
    
}


/*******************************************************************************
* Function Name: Step_IDAC_Enable
********************************************************************************
* Summary:
*  Enable the IDAC8
* 
* Parameters:
*  void:
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_Enable(void) 
{
    Step_IDAC_PWRMGR |= Step_IDAC_ACT_PWR_EN;
    Step_IDAC_STBY_PWRMGR |= Step_IDAC_STBY_PWR_EN;

    /* This is to restore the value of register CR0 which is saved 
      in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(Step_IDAC_restoreReg == 1u)
        {
            Step_IDAC_CR0 = Step_IDAC_lowPowerBackup.DACCR0Reg;

            /* Clear the flag */
            Step_IDAC_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Step_IDAC_Start
********************************************************************************
* Summary:
*  Set power level then turn on IDAC8.
*
* Parameters:  
*  power: Sets power level between off (0) and (3) high power
*
* Return:
*  (void)
*
* Global variables:
*  Step_IDAC_initVar: Is modified when this function is called for 
*   the first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Step_IDAC_Start(void) 
{
    /* Hardware initiazation only needs to occur the first time */
    if ( Step_IDAC_initVar == 0u)  
    {
        Step_IDAC_Init();
        
        Step_IDAC_initVar = 1u;
    }
   
    /* Enable power to DAC */
    Step_IDAC_Enable();

    /* Set default value */
    Step_IDAC_SetValue(Step_IDAC_DEFAULT_DATA);

}


/*******************************************************************************
* Function Name: Step_IDAC_Stop
********************************************************************************
* Summary:
*  Powers down IDAC8 to lowest power state.
*
* Parameters:
*  (void)
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_Stop(void) 
{
    /* Disble power to DAC */
    Step_IDAC_PWRMGR &= (uint8)(~Step_IDAC_ACT_PWR_EN);
    Step_IDAC_STBY_PWRMGR &= (uint8)(~Step_IDAC_STBY_PWR_EN);
    
    #if (CY_PSOC5A)
    
        /* Set the global variable  */
        Step_IDAC_restoreReg = 1u;

        /* Save the control register and then Clear it. */
        Step_IDAC_lowPowerBackup.DACCR0Reg = Step_IDAC_CR0;
        Step_IDAC_CR0 = (Step_IDAC_MODE_I | Step_IDAC_RANGE_3 | Step_IDAC_HS_HIGHSPEED);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Step_IDAC_SetSpeed
********************************************************************************
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Step_IDAC_CR0 &= (uint8)(~Step_IDAC_HS_MASK);
    Step_IDAC_CR0 |=  ( speed & Step_IDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: Step_IDAC_SetPolarity
********************************************************************************
* Summary:
*  Sets IDAC to Sink or Source current.
*  
* Parameters:
*  Polarity: Sets the IDAC to Sink or Source 
*  0x00 - Source
*  0x04 - Sink
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
#if(Step_IDAC_DEFAULT_POLARITY != Step_IDAC_HARDWARE_CONTROLLED)
    void Step_IDAC_SetPolarity(uint8 polarity) 
    {
        Step_IDAC_CR1 &= (uint8)(~Step_IDAC_IDIR_MASK);                /* clear polarity bit */
        Step_IDAC_CR1 |= (polarity & Step_IDAC_IDIR_MASK);             /* set new value */
    
        Step_IDAC_DacTrim();
    }
#endif/*(Step_IDAC_DEFAULT_POLARITY != Step_IDAC_HARDWARE_CONTROLLED)*/


/*******************************************************************************
* Function Name: Step_IDAC_SetRange
********************************************************************************
* Summary:
*  Set current range
*
* Parameters:
*  Range: Sets on of four valid ranges.
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_SetRange(uint8 range) 
{
    Step_IDAC_CR0 &= (uint8)(~Step_IDAC_RANGE_MASK);       /* Clear existing mode */
    Step_IDAC_CR0 |= ( range & Step_IDAC_RANGE_MASK );     /*  Set Range  */
    Step_IDAC_DacTrim();
}


/*******************************************************************************
* Function Name: Step_IDAC_SetValue
********************************************************************************
* Summary:
*  Set DAC value
*
* Parameters:
*  value: Sets DAC value between 0 and 255.
*
* Return:
*  (void)
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_SetValue(uint8 value) 
{

    #if (CY_PSOC5A)
        uint8 Step_IDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Step_IDAC_Data = value;         /*  Set Value  */
    
    /* PSOC5A silicons require a double write */
    #if (CY_PSOC5A)
        Step_IDAC_Data = value;
        CyExitCriticalSection(Step_IDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Step_IDAC_DacTrim
********************************************************************************
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  None
*
* Return:
*  (void) 
*
* Theory:
*  Trim values for the IDAC blocks are stored in the "Customer Table" area in 
*  Row 1 of the Hidden Flash.  There are 8 bytes of trim data for each 
*  IDAC block.
*  The values are:
*       I Gain offset, min range, Sourcing
*       I Gain offset, min range, Sinking
*       I Gain offset, med range, Sourcing
*       I Gain offset, med range, Sinking
*       I Gain offset, max range, Sourcing
*       I Gain offset, max range, Sinking
*       V Gain offset, 1V range
*       V Gain offset, 4V range
*
* Side Effects:
*
*******************************************************************************/
void Step_IDAC_DacTrim(void) 
{
    uint8 mode;

    mode = ((Step_IDAC_CR0 & Step_IDAC_RANGE_MASK) >> 1u);
    
    if((Step_IDAC_IDIR_MASK & Step_IDAC_CR1) == Step_IDAC_IDIR_SINK)
    {
        mode++;
    }

    Step_IDAC_TR = CY_GET_XTND_REG8((uint8 *)(Step_IDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
