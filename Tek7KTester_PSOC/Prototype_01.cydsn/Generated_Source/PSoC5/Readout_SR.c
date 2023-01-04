/*******************************************************************************
* File Name: Readout_SR.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Readout_SR.h"

uint8 Readout_SR_initVar = 0u;


/*******************************************************************************
* Function Name: Readout_SR_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Readout_SR_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Readout_SR_Start(void) 
{
    if(0u == Readout_SR_initVar)
    {
        Readout_SR_Init();
        Readout_SR_initVar = 1u; /* Component initialized */
    }

    Readout_SR_Enable();
}


/*******************************************************************************
* Function Name: Readout_SR_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void Readout_SR_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    Readout_SR_SR_CONTROL |= Readout_SR_CLK_EN;

    Readout_SR_EnableInt();
}


/*******************************************************************************
* Function Name: Readout_SR_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void Readout_SR_Init(void) 
{
    Readout_SR_SetIntMode(Readout_SR_INT_SRC);
}


/*******************************************************************************
* Function Name: Readout_SR_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_SR_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    Readout_SR_SR_CONTROL &= ((uint8) ~Readout_SR_CLK_EN);
    Readout_SR_DisableInt();
}


/*******************************************************************************
* Function Name: Readout_SR_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_SR_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    Readout_SR_SR_AUX_CONTROL |= Readout_SR_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Readout_SR_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_SR_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    Readout_SR_SR_AUX_CONTROL &= ((uint8) ~Readout_SR_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Readout_SR_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 Readout_SR_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = Readout_SR_RET_FIFO_NOT_DEFINED;

    #if(0u != Readout_SR_USE_INPUT_FIFO)
        if(Readout_SR_IN_FIFO == fifoId)
        {
            switch(Readout_SR_GET_IN_FIFO_STS)
            {
                case Readout_SR_IN_FIFO_FULL :
                    result = Readout_SR_RET_FIFO_FULL;
                    break;

                case Readout_SR_IN_FIFO_EMPTY :
                    result = Readout_SR_RET_FIFO_EMPTY;
                    break;

                case Readout_SR_IN_FIFO_PARTIAL:
                    result = Readout_SR_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = Readout_SR_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != Readout_SR_USE_INPUT_FIFO) */

    if(Readout_SR_OUT_FIFO == fifoId)
    {
        switch(Readout_SR_GET_OUT_FIFO_STS)
        {
            case Readout_SR_OUT_FIFO_FULL :
                result = Readout_SR_RET_FIFO_FULL;
                break;

            case Readout_SR_OUT_FIFO_EMPTY :
                result = Readout_SR_RET_FIFO_EMPTY;
                break;

            case Readout_SR_OUT_FIFO_PARTIAL :
                result = Readout_SR_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = Readout_SR_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: Readout_SR_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_SR_SetIntMode(uint8 interruptSource) 
{
    Readout_SR_SR_STATUS_MASK &= ((uint8) ~Readout_SR_INTS_EN_MASK);          /* Clear existing int */
    Readout_SR_SR_STATUS_MASK |= (interruptSource & Readout_SR_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: Readout_SR_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 Readout_SR_GetIntStatus(void) 
{
    return(Readout_SR_SR_STATUS & Readout_SR_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Readout_SR_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void Readout_SR_WriteRegValue(uint16 shiftData)
                                                                     
{
    CY_SET_REG16(Readout_SR_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != Readout_SR_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: Readout_SR_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus Readout_SR_WriteData(uint16 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(Readout_SR_RET_FIFO_FULL != (Readout_SR_GetFIFOStatus(Readout_SR_IN_FIFO)))
        {
            CY_SET_REG16(Readout_SR_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != Readout_SR_USE_INPUT_FIFO) */


#if(0u != Readout_SR_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: Readout_SR_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 Readout_SR_ReadData(void) 
    {
        return(CY_GET_REG16(Readout_SR_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != Readout_SR_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: Readout_SR_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 Readout_SR_ReadRegValue(void) 
{
    uint16 result;

    /* Clear FIFO before software capture */
    while(Readout_SR_RET_FIFO_EMPTY != Readout_SR_GetFIFOStatus(Readout_SR_OUT_FIFO))
    {
        (void) CY_GET_REG16(Readout_SR_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(Readout_SR_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG16(Readout_SR_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (Readout_SR_SR_SIZE % 8u))
        result &= ((uint16) Readout_SR_SR_MASK);
    #endif /* (0u != (Readout_SR_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
