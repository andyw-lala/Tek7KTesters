/*******************************************************************************
* File Name: StepY_IDAC.c
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
#include "StepY_IDAC.h"   

#if (CY_PSOC5A)
    #include <CyLib.h>
#endif /* CY_PSOC5A */


uint8 StepY_IDAC_initVar = 0u;


#if (CY_PSOC5A)
    static StepY_IDAC_LOWPOWER_BACKUP_STRUCT  StepY_IDAC_lowPowerBackup;
#endif /* CY_PSOC5A */

/* Variable to decide whether or not to restore control register in Enable()
   API. This valid only for PSoC5A */
#if (CY_PSOC5A)
    static uint8 StepY_IDAC_restoreReg = 0u;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: StepY_IDAC_Init
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
void StepY_IDAC_Init(void) 
{
    StepY_IDAC_CR0 = (StepY_IDAC_MODE_I | StepY_IDAC_DEFAULT_RANGE );

    /* Set default data source */
    #if(StepY_IDAC_DEFAULT_DATA_SRC != 0u )    
        StepY_IDAC_CR1 = (StepY_IDAC_DEFAULT_CNTL | StepY_IDAC_DACBUS_ENABLE);
    #else
        StepY_IDAC_CR1 = (StepY_IDAC_DEFAULT_CNTL | StepY_IDAC_DACBUS_DISABLE);
    #endif /* (StepY_IDAC_DEFAULT_DATA_SRC != 0u ) */
    
    /*Controls polarity from UDB Control*/
    #if(StepY_IDAC_DEFAULT_POLARITY == StepY_IDAC_HARDWARE_CONTROLLED)
        StepY_IDAC_CR1 |= StepY_IDAC_IDIR_SRC_UDB;
    #else
        StepY_IDAC_CR1 |= StepY_IDAC_DEFAULT_POLARITY;
    #endif/* (StepY_IDAC_DEFAULT_POLARITY == StepY_IDAC_HARDWARE_CONTROLLED) */
    /*Controls Current Source from UDB Control*/
    #if(StepY_IDAC_HARDWARE_ENABLE != 0u ) 
        StepY_IDAC_CR1 |= StepY_IDAC_IDIR_CTL_UDB;
    #endif /* (StepY_IDAC_HARDWARE_ENABLE != 0u ) */ 
    
    /* Set default strobe mode */
    #if(StepY_IDAC_DEFAULT_STRB != 0u)
        StepY_IDAC_Strobe |= StepY_IDAC_STRB_EN;
    #endif /* (StepY_IDAC_DEFAULT_STRB != 0u) */
    
    /* Set default speed */
    StepY_IDAC_SetSpeed(StepY_IDAC_DEFAULT_SPEED);
    
    /* Set proper DAC trim */
    StepY_IDAC_DacTrim();
    
}


/*******************************************************************************
* Function Name: StepY_IDAC_Enable
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
void StepY_IDAC_Enable(void) 
{
    StepY_IDAC_PWRMGR |= StepY_IDAC_ACT_PWR_EN;
    StepY_IDAC_STBY_PWRMGR |= StepY_IDAC_STBY_PWR_EN;

    /* This is to restore the value of register CR0 which is saved 
      in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(StepY_IDAC_restoreReg == 1u)
        {
            StepY_IDAC_CR0 = StepY_IDAC_lowPowerBackup.DACCR0Reg;

            /* Clear the flag */
            StepY_IDAC_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: StepY_IDAC_Start
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
*  StepY_IDAC_initVar: Is modified when this function is called for 
*   the first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void StepY_IDAC_Start(void) 
{
    /* Hardware initiazation only needs to occur the first time */
    if ( StepY_IDAC_initVar == 0u)  
    {
        StepY_IDAC_Init();
        
        StepY_IDAC_initVar = 1u;
    }
   
    /* Enable power to DAC */
    StepY_IDAC_Enable();

    /* Set default value */
    StepY_IDAC_SetValue(StepY_IDAC_DEFAULT_DATA);

}


/*******************************************************************************
* Function Name: StepY_IDAC_Stop
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
void StepY_IDAC_Stop(void) 
{
    /* Disble power to DAC */
    StepY_IDAC_PWRMGR &= (uint8)(~StepY_IDAC_ACT_PWR_EN);
    StepY_IDAC_STBY_PWRMGR &= (uint8)(~StepY_IDAC_STBY_PWR_EN);
    
    #if (CY_PSOC5A)
    
        /* Set the global variable  */
        StepY_IDAC_restoreReg = 1u;

        /* Save the control register and then Clear it. */
        StepY_IDAC_lowPowerBackup.DACCR0Reg = StepY_IDAC_CR0;
        StepY_IDAC_CR0 = (StepY_IDAC_MODE_I | StepY_IDAC_RANGE_3 | StepY_IDAC_HS_HIGHSPEED);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: StepY_IDAC_SetSpeed
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
void StepY_IDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    StepY_IDAC_CR0 &= (uint8)(~StepY_IDAC_HS_MASK);
    StepY_IDAC_CR0 |=  ( speed & StepY_IDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: StepY_IDAC_SetPolarity
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
#if(StepY_IDAC_DEFAULT_POLARITY != StepY_IDAC_HARDWARE_CONTROLLED)
    void StepY_IDAC_SetPolarity(uint8 polarity) 
    {
        StepY_IDAC_CR1 &= (uint8)(~StepY_IDAC_IDIR_MASK);                /* clear polarity bit */
        StepY_IDAC_CR1 |= (polarity & StepY_IDAC_IDIR_MASK);             /* set new value */
    
        StepY_IDAC_DacTrim();
    }
#endif/*(StepY_IDAC_DEFAULT_POLARITY != StepY_IDAC_HARDWARE_CONTROLLED)*/


/*******************************************************************************
* Function Name: StepY_IDAC_SetRange
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
void StepY_IDAC_SetRange(uint8 range) 
{
    StepY_IDAC_CR0 &= (uint8)(~StepY_IDAC_RANGE_MASK);       /* Clear existing mode */
    StepY_IDAC_CR0 |= ( range & StepY_IDAC_RANGE_MASK );     /*  Set Range  */
    StepY_IDAC_DacTrim();
}


/*******************************************************************************
* Function Name: StepY_IDAC_SetValue
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
void StepY_IDAC_SetValue(uint8 value) 
{

    #if (CY_PSOC5A)
        uint8 StepY_IDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    StepY_IDAC_Data = value;         /*  Set Value  */
    
    /* PSOC5A silicons require a double write */
    #if (CY_PSOC5A)
        StepY_IDAC_Data = value;
        CyExitCriticalSection(StepY_IDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: StepY_IDAC_DacTrim
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
void StepY_IDAC_DacTrim(void) 
{
    uint8 mode;

    mode = ((StepY_IDAC_CR0 & StepY_IDAC_RANGE_MASK) >> 1u);
    
    if((StepY_IDAC_IDIR_MASK & StepY_IDAC_CR1) == StepY_IDAC_IDIR_SINK)
    {
        mode++;
    }

    StepY_IDAC_TR = CY_GET_XTND_REG8((uint8 *)(StepY_IDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
