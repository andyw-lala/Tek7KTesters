/*******************************************************************************
* File Name: VSense_ADC_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_VSense_ADC_AMux_H)
#define CY_AMUX_VSense_ADC_AMux_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void VSense_ADC_AMux_Start(void) ;
#define VSense_ADC_AMux_Init() VSense_ADC_AMux_Start()
void VSense_ADC_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void VSense_ADC_AMux_Stop(void); */
/* void VSense_ADC_AMux_Select(uint8 channel); */
/* void VSense_ADC_AMux_Connect(uint8 channel); */
/* void VSense_ADC_AMux_Disconnect(uint8 channel); */
/* void VSense_ADC_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define VSense_ADC_AMux_CHANNELS  2u
#define VSense_ADC_AMux_MUXTYPE   1
#define VSense_ADC_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define VSense_ADC_AMux_NULL_CHANNEL 0xFFu
#define VSense_ADC_AMux_MUX_SINGLE   1
#define VSense_ADC_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if VSense_ADC_AMux_MUXTYPE == VSense_ADC_AMux_MUX_SINGLE
# if !VSense_ADC_AMux_ATMOSTONE
#  define VSense_ADC_AMux_Connect(channel) VSense_ADC_AMux_Set(channel)
# endif
# define VSense_ADC_AMux_Disconnect(channel) VSense_ADC_AMux_Unset(channel)
#else
# if !VSense_ADC_AMux_ATMOSTONE
void VSense_ADC_AMux_Connect(uint8 channel) ;
# endif
void VSense_ADC_AMux_Disconnect(uint8 channel) ;
#endif

#if VSense_ADC_AMux_ATMOSTONE
# define VSense_ADC_AMux_Stop() VSense_ADC_AMux_DisconnectAll()
# define VSense_ADC_AMux_Select(channel) VSense_ADC_AMux_FastSelect(channel)
void VSense_ADC_AMux_DisconnectAll(void) ;
#else
# define VSense_ADC_AMux_Stop() VSense_ADC_AMux_Start()
void VSense_ADC_AMux_Select(uint8 channel) ;
# define VSense_ADC_AMux_DisconnectAll() VSense_ADC_AMux_Start()
#endif

#endif /* CY_AMUX_VSense_ADC_AMux_H */


/* [] END OF FILE */
