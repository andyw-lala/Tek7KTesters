/*******************************************************************************
* File Name: VSense_ADC_AMux.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "VSense_ADC_AMux.h"

static uint8 VSense_ADC_AMux_lastChannel = VSense_ADC_AMux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: VSense_ADC_AMux_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void VSense_ADC_AMux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < VSense_ADC_AMux_CHANNELS ; chan++)
    {
#if (VSense_ADC_AMux_MUXTYPE == VSense_ADC_AMux_MUX_SINGLE)
        VSense_ADC_AMux_Unset(chan);
#else
        VSense_ADC_AMux_CYAMUXSIDE_A_Unset(chan);
        VSense_ADC_AMux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    VSense_ADC_AMux_lastChannel = VSense_ADC_AMux_NULL_CHANNEL;
}


#if (!VSense_ADC_AMux_ATMOSTONE)
/*******************************************************************************
* Function Name: VSense_ADC_AMux_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void VSense_ADC_AMux_Select(uint8 channel) 
{
    VSense_ADC_AMux_DisconnectAll();        /* Disconnect all previous connections */
    VSense_ADC_AMux_Connect(channel);       /* Make the given selection */
    VSense_ADC_AMux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: VSense_ADC_AMux_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void VSense_ADC_AMux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( VSense_ADC_AMux_lastChannel != VSense_ADC_AMux_NULL_CHANNEL)
    {
        VSense_ADC_AMux_Disconnect(VSense_ADC_AMux_lastChannel);
    }

    /* Make the new channel connection */
#if (VSense_ADC_AMux_MUXTYPE == VSense_ADC_AMux_MUX_SINGLE)
    VSense_ADC_AMux_Set(channel);
#else
    VSense_ADC_AMux_CYAMUXSIDE_A_Set(channel);
    VSense_ADC_AMux_CYAMUXSIDE_B_Set(channel);
#endif


    VSense_ADC_AMux_lastChannel = channel;   /* Update last channel */
}


#if (VSense_ADC_AMux_MUXTYPE == VSense_ADC_AMux_MUX_DIFF)
#if (!VSense_ADC_AMux_ATMOSTONE)
/*******************************************************************************
* Function Name: VSense_ADC_AMux_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void VSense_ADC_AMux_Connect(uint8 channel) 
{
    VSense_ADC_AMux_CYAMUXSIDE_A_Set(channel);
    VSense_ADC_AMux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: VSense_ADC_AMux_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void VSense_ADC_AMux_Disconnect(uint8 channel) 
{
    VSense_ADC_AMux_CYAMUXSIDE_A_Unset(channel);
    VSense_ADC_AMux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (VSense_ADC_AMux_ATMOSTONE)
/*******************************************************************************
* Function Name: VSense_ADC_AMux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void VSense_ADC_AMux_DisconnectAll(void) 
{
    if(VSense_ADC_AMux_lastChannel != VSense_ADC_AMux_NULL_CHANNEL) 
    {
        VSense_ADC_AMux_Disconnect(VSense_ADC_AMux_lastChannel);
        VSense_ADC_AMux_lastChannel = VSense_ADC_AMux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
