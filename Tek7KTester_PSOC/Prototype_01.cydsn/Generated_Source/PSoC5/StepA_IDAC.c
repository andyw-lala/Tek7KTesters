/*******************************************************************************
* File Name: StepA_IDAC.c
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
#include "StepA_IDAC.h"   

#if (CY_PSOC5A)
    #include <CyLib.h>
#endif /* CY_PSOC5A */


uint8 StepA_IDAC_initVar = 0u;


#if (CY_PSOC5A)
    static StepA_IDAC_LOWPOWER_BACKUP_STRUCT  StepA_IDAC_lowPowerBackup;
#endif /* CY_PSOC5A */

/* Variable to decide whether or not to restore control register in Enable()
   API. This valid only for PSoC5A */
#if (CY_PSOC5A)
    static uint8 StepA_IDAC_restoreReg = 0u;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: StepA_IDAC_Init
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
void StepA_IDAC_Init(void) 
{
    StepA_IDAC_CR0 = (StepA_IDAC_MODE_I | StepA_IDAC_DEFAULT_RANGE );

    /* Set default data source */
    #if(StepA_IDAC_DEFAULT_DATA_SRC != 0u )    
        StepA_IDAC_CR1 = (StepA_IDAC_DEFAULT_CNTL | StepA_IDAC_DACBUS_ENABLE);
    #else
        StepA_IDAC_CR1 = (StepA_IDAC_DEFAULT_CNTL | StepA_IDAC_DACBUS_DISABLE);
    #endif /* (StepA_IDAC_DEFAULT_DATA_SRC != 0u ) */
    
    /*Controls polarity from UDB Control*/
    #if(StepA_IDAC_DEFAULT_POLARITY == StepA_IDAC_HARDWARE_CONTROLLED)
        StepA_IDAC_CR1 |= StepA_IDAC_IDIR_SRC_UDB;
    #else
        StepA_IDAC_CR1 |= StepA_IDAC_DEFAULT_POLARITY;
    #endif/* (StepA_IDAC_DEFAULT_POLARITY == StepA_IDAC_HARDWARE_CONTROLLED) */
    /*Controls Current Source from UDB Control*/
    #if(StepA_IDAC_HARDWARE_ENABLE != 0u ) 
        StepA_IDAC_CR1 |= StepA_IDAC_IDIR_CTL_UDB;
    #endif /* (StepA_IDAC_HARDWARE_ENABLE != 0u ) */ 
    
    /* Set default strobe mode */
    #if(StepA_IDAC_DEFAULT_STRB != 0u)
        StepA_IDAC_Strobe |= StepA_IDAC_STRB_EN;
    #endif /* (StepA_IDAC_DEFAULT_STRB != 0u) */
    
    /* Set default speed */
    StepA_IDAC_SetSpeed(StepA_IDAC_DEFAULT_SPEED);
    
    /* Set proper DAC trim */
    StepA_IDAC_DacTrim();
    
}


/*******************************************************************************
* Function Name: StepA_IDAC_Enable
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
void StepA_IDAC_Enable(void) 
{
    StepA_IDAC_PWRMGR |= StepA_IDAC_ACT_PWR_EN;
    StepA_IDAC_STBY_PWRMGR |= StepA_IDAC_STBY_PWR_EN;

    /* This is to restore the value of register CR0 which is saved 
      in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(StepA_IDAC_restoreReg == 1u)
        {
            StepA_IDAC_CR0 = StepA_IDAC_lowPowerBackup.DACCR0Reg;

            /* Clear the flag */
            StepA_IDAC_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: StepA_IDAC_Start
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
*  StepA_IDAC_initVar: Is modified when this function is called for 
*   the first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void StepA_IDAC_Start(void) 
{
    /* Hardware initiazation only needs to occur the first time */
    if ( StepA_IDAC_initVar == 0u)  
    {
        StepA_IDAC_Init();
        
        StepA_IDAC_initVar = 1u;
    }
   
    /* Enable power to DAC */
    StepA_IDAC_Enable();

    /* Set default value */
    StepA_IDAC_SetValue(StepA_IDAC_DEFAULT_DATA);

}


/*******************************************************************************
* Function Name: StepA_IDAC_Stop
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
void StepA_IDAC_Stop(void) 
{
    /* Disble power to DAC */
    StepA_IDAC_PWRMGR &= (uint8)(~StepA_IDAC_ACT_PWR_EN);
    StepA_IDAC_STBY_PWRMGR &= (uint8)(~StepA_IDAC_STBY_PWR_EN);
    
    #if (CY_PSOC5A)
    
        /* Set the global variable  */
        StepA_IDAC_restoreReg = 1u;

        /* Save the control register and then Clear it. */
        StepA_IDAC_lowPowerBackup.DACCR0Reg = StepA_IDAC_CR0;
        StepA_IDAC_CR0 = (StepA_IDAC_MODE_I | StepA_IDAC_RANGE_3 | StepA_IDAC_HS_HIGHSPEED);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: StepA_IDAC_SetSpeed
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
void StepA_IDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    StepA_IDAC_CR0 &= (uint8)(~StepA_IDAC_HS_MASK);
    StepA_IDAC_CR0 |=  ( speed & StepA_IDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: StepA_IDAC_SetPolarity
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
#if(StepA_IDAC_DEFAULT_POLARITY != StepA_IDAC_HARDWARE_CONTROLLED)
    void StepA_IDAC_SetPolarity(uint8 polarity) 
    {
        StepA_IDAC_CR1 &= (uint8)(~StepA_IDAC_IDIR_MASK);                /* clear polarity bit */
        StepA_IDAC_CR1 |= (polarity & StepA_IDAC_IDIR_MASK);             /* set new value */
    
        StepA_IDAC_DacTrim();
    }
#endif/*(StepA_IDAC_DEFAULT_POLARITY != StepA_IDAC_HARDWARE_CONTROLLED)*/


/*******************************************************************************
* Function Name: StepA_IDAC_SetRange
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
void StepA_IDAC_SetRange(uint8 range) 
{
    StepA_IDAC_CR0 &= (uint8)(~StepA_IDAC_RANGE_MASK);       /* Clear existing mode */
    StepA_IDAC_CR0 |= ( range & StepA_IDAC_RANGE_MASK );     /*  Set Range  */
    StepA_IDAC_DacTrim();
}


/*******************************************************************************
* Function Name: StepA_IDAC_SetValue
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
void StepA_IDAC_SetValue(uint8 value) 
{

    #if (CY_PSOC5A)
        uint8 StepA_IDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    StepA_IDAC_Data = value;         /*  Set Value  */
    
    /* PSOC5A silicons require a double write */
    #if (CY_PSOC5A)
        StepA_IDAC_Data = value;
        CyExitCriticalSection(StepA_IDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: StepA_IDAC_DacTrim
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
void StepA_IDAC_DacTrim(void) 
{
    uint8 mode;

    mode = ((StepA_IDAC_CR0 & StepA_IDAC_RANGE_MASK) >> 1u);
    
    if((StepA_IDAC_IDIR_MASK & StepA_IDAC_CR1) == StepA_IDAC_IDIR_SINK)
    {
        mode++;
    }

    StepA_IDAC_TR = CY_GET_XTND_REG8((uint8 *)(StepA_IDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
