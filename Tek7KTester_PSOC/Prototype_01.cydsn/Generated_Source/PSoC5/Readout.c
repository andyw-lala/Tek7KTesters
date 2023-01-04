/*******************************************************************************
* File Name: Readout.c
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

#include "Readout.h"

uint8 Readout_initVar = 0u;


/*******************************************************************************
* Function Name: Readout_Start
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
*  Readout_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Readout_Start(void) 
{
    if(0u == Readout_initVar)
    {
        Readout_Init();
        Readout_initVar = 1u; /* Component initialized */
    }

    Readout_Enable();
}


/*******************************************************************************
* Function Name: Readout_Enable
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
void Readout_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    Readout_SR_CONTROL |= Readout_CLK_EN;

    Readout_EnableInt();
}


/*******************************************************************************
* Function Name: Readout_Init
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
void Readout_Init(void) 
{
    Readout_SetIntMode(Readout_INT_SRC);
}


/*******************************************************************************
* Function Name: Readout_Stop
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
void Readout_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    Readout_SR_CONTROL &= ((uint8) ~Readout_CLK_EN);
    Readout_DisableInt();
}


/*******************************************************************************
* Function Name: Readout_EnableInt
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
void Readout_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    Readout_SR_AUX_CONTROL |= Readout_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Readout_DisableInt
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
void Readout_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    Readout_SR_AUX_CONTROL &= ((uint8) ~Readout_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Readout_GetFIFOStatus
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
uint8 Readout_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = Readout_RET_FIFO_NOT_DEFINED;

    #if(0u != Readout_USE_INPUT_FIFO)
        if(Readout_IN_FIFO == fifoId)
        {
            switch(Readout_GET_IN_FIFO_STS)
            {
                case Readout_IN_FIFO_FULL :
                    result = Readout_RET_FIFO_FULL;
                    break;

                case Readout_IN_FIFO_EMPTY :
                    result = Readout_RET_FIFO_EMPTY;
                    break;

                case Readout_IN_FIFO_PARTIAL:
                    result = Readout_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = Readout_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != Readout_USE_INPUT_FIFO) */

    if(Readout_OUT_FIFO == fifoId)
    {
        switch(Readout_GET_OUT_FIFO_STS)
        {
            case Readout_OUT_FIFO_FULL :
                result = Readout_RET_FIFO_FULL;
                break;

            case Readout_OUT_FIFO_EMPTY :
                result = Readout_RET_FIFO_EMPTY;
                break;

            case Readout_OUT_FIFO_PARTIAL :
                result = Readout_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = Readout_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: Readout_SetIntMode
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
void Readout_SetIntMode(uint8 interruptSource) 
{
    Readout_SR_STATUS_MASK &= ((uint8) ~Readout_INTS_EN_MASK);          /* Clear existing int */
    Readout_SR_STATUS_MASK |= (interruptSource & Readout_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: Readout_GetIntStatus
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
uint8 Readout_GetIntStatus(void) 
{
    return(Readout_SR_STATUS & Readout_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Readout_WriteRegValue
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
void Readout_WriteRegValue(uint16 shiftData)
                                                                     
{
    CY_SET_REG16(Readout_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != Readout_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: Readout_WriteData
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
    cystatus Readout_WriteData(uint16 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(Readout_RET_FIFO_FULL != (Readout_GetFIFOStatus(Readout_IN_FIFO)))
        {
            CY_SET_REG16(Readout_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != Readout_USE_INPUT_FIFO) */


#if(0u != Readout_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: Readout_ReadData
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
    uint16 Readout_ReadData(void) 
    {
        return(CY_GET_REG16(Readout_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != Readout_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: Readout_ReadRegValue
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
uint16 Readout_ReadRegValue(void) 
{
    uint16 result;

    /* Clear FIFO before software capture */
    while(Readout_RET_FIFO_EMPTY != Readout_GetFIFOStatus(Readout_OUT_FIFO))
    {
        (void) CY_GET_REG16(Readout_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(Readout_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG16(Readout_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (Readout_SR_SIZE % 8u))
        result &= ((uint16) Readout_SR_MASK);
    #endif /* (0u != (Readout_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
