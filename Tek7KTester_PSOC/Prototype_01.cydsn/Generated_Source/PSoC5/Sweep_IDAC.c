/*******************************************************************************
* File Name: Sweep_IDAC.c
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
#include "Sweep_IDAC.h"   

#if (CY_PSOC5A)
    #include <CyLib.h>
#endif /* CY_PSOC5A */


uint8 Sweep_IDAC_initVar = 0u;


#if (CY_PSOC5A)
    static Sweep_IDAC_LOWPOWER_BACKUP_STRUCT  Sweep_IDAC_lowPowerBackup;
#endif /* CY_PSOC5A */

/* Variable to decide whether or not to restore control register in Enable()
   API. This valid only for PSoC5A */
#if (CY_PSOC5A)
    static uint8 Sweep_IDAC_restoreReg = 0u;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Sweep_IDAC_Init
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
void Sweep_IDAC_Init(void) 
{
    Sweep_IDAC_CR0 = (Sweep_IDAC_MODE_I | Sweep_IDAC_DEFAULT_RANGE );

    /* Set default data source */
    #if(Sweep_IDAC_DEFAULT_DATA_SRC != 0u )    
        Sweep_IDAC_CR1 = (Sweep_IDAC_DEFAULT_CNTL | Sweep_IDAC_DACBUS_ENABLE);
    #else
        Sweep_IDAC_CR1 = (Sweep_IDAC_DEFAULT_CNTL | Sweep_IDAC_DACBUS_DISABLE);
    #endif /* (Sweep_IDAC_DEFAULT_DATA_SRC != 0u ) */
    
    /*Controls polarity from UDB Control*/
    #if(Sweep_IDAC_DEFAULT_POLARITY == Sweep_IDAC_HARDWARE_CONTROLLED)
        Sweep_IDAC_CR1 |= Sweep_IDAC_IDIR_SRC_UDB;
    #else
        Sweep_IDAC_CR1 |= Sweep_IDAC_DEFAULT_POLARITY;
    #endif/* (Sweep_IDAC_DEFAULT_POLARITY == Sweep_IDAC_HARDWARE_CONTROLLED) */
    /*Controls Current Source from UDB Control*/
    #if(Sweep_IDAC_HARDWARE_ENABLE != 0u ) 
        Sweep_IDAC_CR1 |= Sweep_IDAC_IDIR_CTL_UDB;
    #endif /* (Sweep_IDAC_HARDWARE_ENABLE != 0u ) */ 
    
    /* Set default strobe mode */
    #if(Sweep_IDAC_DEFAULT_STRB != 0u)
        Sweep_IDAC_Strobe |= Sweep_IDAC_STRB_EN;
    #endif /* (Sweep_IDAC_DEFAULT_STRB != 0u) */
    
    /* Set default speed */
    Sweep_IDAC_SetSpeed(Sweep_IDAC_DEFAULT_SPEED);
    
    /* Set proper DAC trim */
    Sweep_IDAC_DacTrim();
    
}


/*******************************************************************************
* Function Name: Sweep_IDAC_Enable
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
void Sweep_IDAC_Enable(void) 
{
    Sweep_IDAC_PWRMGR |= Sweep_IDAC_ACT_PWR_EN;
    Sweep_IDAC_STBY_PWRMGR |= Sweep_IDAC_STBY_PWR_EN;

    /* This is to restore the value of register CR0 which is saved 
      in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(Sweep_IDAC_restoreReg == 1u)
        {
            Sweep_IDAC_CR0 = Sweep_IDAC_lowPowerBackup.DACCR0Reg;

            /* Clear the flag */
            Sweep_IDAC_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Sweep_IDAC_Start
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
*  Sweep_IDAC_initVar: Is modified when this function is called for 
*   the first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Sweep_IDAC_Start(void) 
{
    /* Hardware initiazation only needs to occur the first time */
    if ( Sweep_IDAC_initVar == 0u)  
    {
        Sweep_IDAC_Init();
        
        Sweep_IDAC_initVar = 1u;
    }
   
    /* Enable power to DAC */
    Sweep_IDAC_Enable();

    /* Set default value */
    Sweep_IDAC_SetValue(Sweep_IDAC_DEFAULT_DATA);

}


/*******************************************************************************
* Function Name: Sweep_IDAC_Stop
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
void Sweep_IDAC_Stop(void) 
{
    /* Disble power to DAC */
    Sweep_IDAC_PWRMGR &= (uint8)(~Sweep_IDAC_ACT_PWR_EN);
    Sweep_IDAC_STBY_PWRMGR &= (uint8)(~Sweep_IDAC_STBY_PWR_EN);
    
    #if (CY_PSOC5A)
    
        /* Set the global variable  */
        Sweep_IDAC_restoreReg = 1u;

        /* Save the control register and then Clear it. */
        Sweep_IDAC_lowPowerBackup.DACCR0Reg = Sweep_IDAC_CR0;
        Sweep_IDAC_CR0 = (Sweep_IDAC_MODE_I | Sweep_IDAC_RANGE_3 | Sweep_IDAC_HS_HIGHSPEED);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Sweep_IDAC_SetSpeed
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
void Sweep_IDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Sweep_IDAC_CR0 &= (uint8)(~Sweep_IDAC_HS_MASK);
    Sweep_IDAC_CR0 |=  ( speed & Sweep_IDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: Sweep_IDAC_SetPolarity
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
#if(Sweep_IDAC_DEFAULT_POLARITY != Sweep_IDAC_HARDWARE_CONTROLLED)
    void Sweep_IDAC_SetPolarity(uint8 polarity) 
    {
        Sweep_IDAC_CR1 &= (uint8)(~Sweep_IDAC_IDIR_MASK);                /* clear polarity bit */
        Sweep_IDAC_CR1 |= (polarity & Sweep_IDAC_IDIR_MASK);             /* set new value */
    
        Sweep_IDAC_DacTrim();
    }
#endif/*(Sweep_IDAC_DEFAULT_POLARITY != Sweep_IDAC_HARDWARE_CONTROLLED)*/


/*******************************************************************************
* Function Name: Sweep_IDAC_SetRange
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
void Sweep_IDAC_SetRange(uint8 range) 
{
    Sweep_IDAC_CR0 &= (uint8)(~Sweep_IDAC_RANGE_MASK);       /* Clear existing mode */
    Sweep_IDAC_CR0 |= ( range & Sweep_IDAC_RANGE_MASK );     /*  Set Range  */
    Sweep_IDAC_DacTrim();
}


/*******************************************************************************
* Function Name: Sweep_IDAC_SetValue
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
void Sweep_IDAC_SetValue(uint8 value) 
{

    #if (CY_PSOC5A)
        uint8 Sweep_IDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Sweep_IDAC_Data = value;         /*  Set Value  */
    
    /* PSOC5A silicons require a double write */
    #if (CY_PSOC5A)
        Sweep_IDAC_Data = value;
        CyExitCriticalSection(Sweep_IDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Sweep_IDAC_DacTrim
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
void Sweep_IDAC_DacTrim(void) 
{
    uint8 mode;

    mode = ((Sweep_IDAC_CR0 & Sweep_IDAC_RANGE_MASK) >> 1u);
    
    if((Sweep_IDAC_IDIR_MASK & Sweep_IDAC_CR1) == Sweep_IDAC_IDIR_SINK)
    {
        mode++;
    }

    Sweep_IDAC_TR = CY_GET_XTND_REG8((uint8 *)(Sweep_IDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
