/*******************************************************************************
* File: main.c
*
* Version: 1.2
*
* Description: 
*   This is a source code for basic functionality of IDAC8.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include "lcd.h"
#include "gui.h"
#include "test.h"   // DWD

enum    DisplayMode {OFF, HORIZ, VERT, XHATCH_HORIZ, XHATCH_VERT, DOTS, HORIZ_FINE, VERT_FINE, XHATCH_HORIZ_FINE, XHATCH_VERT_FINE};

enum DisplayMode display_mode = XHATCH_HORIZ_FINE;

uint8 lines_horiz[] = {68, 88, 108, 128, 148, 148, 148, 168, 188, 208, 228 } ;
uint8 lines_vert[] = {48, 68, 88, 108, 128, 148, 148, 148, 168, 188, 208, 228, 248 } ;
uint8 lines_horiz_fine[] = {68, 68, 72, 76, 80, 84, 88, 88, 92, 96, 100, 104, 108, 108,
                      112, 116, 120, 124, 128, 128, 132, 136, 140, 144, 148, 148, 148, 148,
                      152, 156, 160, 164, 168, 168, 172, 176, 180, 184, 188, 188,
                      192, 196, 200, 204, 208, 208, 212, 216, 220, 224, 228, 228};
uint8 lines_vert_fine[] = {48, 48, 52, 56, 60, 64, 68, 68, 72, 76, 80, 84, 88, 88, 92, 96, 100, 104, 108, 108,
                      112, 116, 120, 124, 128, 128, 132, 136, 140, 144, 148, 148, 148, 148,
                      152, 156, 160, 164, 168, 168, 172, 176, 180, 184, 188, 188,
                      192, 196, 200, 204, 208, 208, 212, 216, 220, 224, 228, 228, 232, 236, 240, 244, 248, 248};

CY_ISR (Sweep_End_ISR)
{
    static uint8 step = 0;
    // TODO: Bounds check step on mode change
    switch (display_mode) {
        case HORIZ:
        case XHATCH_HORIZ:
            StepY_IDAC_SetValue(lines_horiz[step]);
            if (++step >= (sizeof(lines_horiz)/sizeof(lines_horiz[0]))) {
                step = 0;
                if (display_mode == XHATCH_HORIZ) {
                    display_mode = XHATCH_VERT;
                    ModeReg_Write(1);
                }
            }
            break;
        
        case VERT:
        case XHATCH_VERT:
            StepX_IDAC_SetValue(lines_vert[step]);
            if (++step >= (sizeof(lines_vert)/sizeof(lines_vert[0]))) {
                step = 0;
                if (display_mode == XHATCH_VERT) {
                    display_mode = XHATCH_HORIZ;
                    ModeReg_Write(0);
                }
            }
            break;
            
        case HORIZ_FINE:
        case XHATCH_HORIZ_FINE:
            StepY_IDAC_SetValue(lines_horiz_fine[step]);
            if (++step >= (sizeof(lines_horiz_fine)/sizeof(lines_horiz_fine[0]))) {
                step = 0;
                if (display_mode == XHATCH_HORIZ_FINE) {
                    display_mode = XHATCH_VERT_FINE;
                    ModeReg_Write(1);
                }
            }
            break;
        
        case VERT_FINE:
        case XHATCH_VERT_FINE:
            StepX_IDAC_SetValue(lines_vert_fine[step]);
            if (++step >= (sizeof(lines_vert_fine)/sizeof(lines_vert_fine[0]))) {
                step = 0;
                if (display_mode == XHATCH_VERT_FINE) {
                    display_mode = XHATCH_HORIZ_FINE;
                    ModeReg_Write(0);
                }
            }
            break;
            
        case DOTS:
            StepY_IDAC_SetValue(lines_horiz[step % (sizeof(lines_horiz)/sizeof(lines_horiz[0]))]);
            StepX_IDAC_SetValue(lines_vert[step / (sizeof(lines_horiz)/sizeof(lines_horiz[0]))]);
            
            if (++step >= ((sizeof(lines_horiz)/sizeof(lines_horiz[0])) * (sizeof(lines_vert)/sizeof(lines_vert[0])))) {
                step = 0;
            }
            break;
    }
}

uint8 foo;

void
Readout_Init(void)
{
    Readout_Control_Write(0x01); 
    Readout_Counter_Start();
    Readout_SR_Start();
}

void
Readout_Write(uint8 ch1, uint8 ch2)
{
    uint16 readout = ch1 | (ch2 << 8);
    
    Readout_SR_WriteRegValue(~readout);
    Readout_Control_Write(0x01);
}

CY_ISR (TS_ISR)
{
    uint8 ts;
    
    lala_Write(0x01);
    
    ts = Timeslot_Read();

    Readout_Write((ts & 0x0f) | ((ts << 4) & 0xf0), (ts & 0x0f) | ((ts << 4) & 0xf0));
    
    
    lala_Write(0x00);
}
void draw_horiz_fine(void)
{
    int i;

    POINT_COLOR = 0x0500;
    for (i = 64; i < 256; i += 24) { 
        LCD_DrawLine(0, i + 5, 239, i + 5);
        LCD_DrawLine(0, i + 10, 239, i + 10);
        LCD_DrawLine(0, i + 14, 239, i + 14);
        LCD_DrawLine(0, i + 19, 239, i + 19);
    }
}

void draw_vert_fine(void)
{
    int i;
    
    POINT_COLOR = 0x0500;
    for (i = 0; i < 240; i += 24) {     
        LCD_DrawLine(i + 5, 64, i + 5, 255);
        LCD_DrawLine(i + 10, 64, i + 10, 255);
        LCD_DrawLine(i + 14, 64, i + 14, 255);
        LCD_DrawLine(i + 19, 64, i + 19, 255);
    }
}

void draw_vert(void)
{
    int i;
    
    POINT_COLOR = GREEN;
    for (i = 0; i <= 240; i += 24) {
        if (i == 240) {
            i = 239;
        }
        LCD_DrawLine(i, 64, i, 255);
    }  
    
    LCD_DrawLine(119, 64, 119, 255);
}

void draw_horiz(void)
{
    int i;
    
    POINT_COLOR = GREEN;
    for (i = 64; i <= 256; i += 24) {
        if (i == 256) {
            i = 255;
        }
        LCD_DrawLine(0, i, 239, i);
    }
    LCD_DrawLine(0, 159, 239, 159);
}

void draw_dots(void)
{
    int x, y;

    POINT_COLOR = GREEN;
    for (x = 0; x <= 240; x += 24) {
        if (x == 240) {
            x = 239;
        }
        for (y = 64; y <= 256; y += 24) {
            if (y == 256) {
                y = 255;
            }
            LCD_DrawPoint(x, y);
            if (x == 120) {
                LCD_DrawPoint(x - 1, y);
                LCD_DrawPoint(x + 1, y);
            }
            
            if (y == 160) {
                LCD_DrawPoint(x, y - 1);
                LCD_DrawPoint(x, y + 1);
            }                
        }
    }
}
    
void foo_test(int lala)
{
    int i;
    
    LCD_Fill(0,0,239,47,WHITE);
    POINT_COLOR = BLACK;
    LCD_DrawLine(0, 47, 239, 47);
    LCD_DrawLine(60, 0, 60, 47);
    LCD_DrawLine(120, 0, 120, 47);
    LCD_DrawLine(180, 0, 180, 47);
    
    Gui_StrCenter(30, 8, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(30, 24, BLACK, WHITE, "4", 16, 0);
    Gui_StrCenter(90, 8, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(90, 24, BLACK, WHITE, "5", 16, 0);
    Gui_StrCenter(150, 8, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(150, 24, BLACK, WHITE, "6", 16, 0);
    Gui_StrCenter(210, 8, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(210, 24, BLACK, WHITE, "7", 16, 0);
    
    LCD_Fill(0,48,239,63,0x39e7);
    Gui_StrCenter(120, 48, GREEN, 0x39e7, "0123456789", 16, 0);
    
    LCD_Fill(0, 64, 239, 255, 0x4208);
    
    switch (lala) {
        case 0:
            draw_horiz();
            break;
        case 1:
            draw_vert();
            break;
        case 2:
            draw_horiz();
            draw_vert();
            break;
        case 3:
            draw_dots();
            break;
        case 4:
            draw_horiz_fine();
            draw_horiz();
            break;
        case 5:
            draw_vert_fine();
            draw_vert();
            break;
        case 6:
            draw_horiz_fine();
            draw_vert_fine();
            draw_horiz();
            draw_vert();
            break;
        case 7:
            LCD_Fill(0,64,239, 255, /*0x6e1a*/0x001f);
            break;
    }
    
    LCD_Fill(0,256,239,271,0x39e7);
    Gui_StrCenter(120, 256, GREEN, 0x39e7, "ABCDEFGHIJ", 16, 0);
    LCD_Fill(0,272,239,319,WHITE);
    POINT_COLOR = BLACK;
    LCD_DrawLine(0, 272, 239, 272);
    LCD_DrawLine(60, 272, 60, 319);
    LCD_DrawLine(120, 272, 120, 319);
    LCD_DrawLine(180, 272, 180, 319);
    
    Gui_StrCenter(30, 280, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(30, 296, BLACK, WHITE, "0", 16, 0);
    Gui_StrCenter(90, 280, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(90, 296, BLACK, WHITE, "1", 16, 0);
    Gui_StrCenter(150, 280, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(150, 296, BLACK, WHITE, "2", 16, 0);
    Gui_StrCenter(210, 280, BLACK, WHITE, "Button", 16, 0);
    Gui_StrCenter(210, 296, BLACK, WHITE, "3", 16, 0);
    
    
    CyDelay(1000u);
}
/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1: Initializes the LCD and clears the display
*   2: Start the IDAC
*   3: IDAC range is set to 255uA and value to 100
*   4: Prints test name on LCD
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    uint8_t foo = 10u;
    
    /* Start the LCD component */
    //LCD_Char_1_Start();           

    /* Clear LCD Display */
    //LCD_Char_1_ClearDisplay();    
    
    switch (display_mode) {
        case HORIZ:
        case XHATCH_HORIZ:
        case HORIZ_FINE:
        case XHATCH_HORIZ_FINE:
            ModeReg_Write(0);
            break;
            
        case VERT:
        case XHATCH_VERT:
        case VERT_FINE:
        case XHATCH_VERT_FINE:
            ModeReg_Write(1);
            break;
            
        case DOTS:
            ModeReg_Write(2);
            break;
    }

    Sweep_Comp_Start();
    //StepX_Buffer_Start();
    //StepY_Buffer_Start();
    
    TS1_Comp_Start();
    TSn_Comp_Start();
       
    /* Start the IDAC component */
    Sweep_IDAC_Start();
    StepX_IDAC_Start();
    StepY_IDAC_Start();
    
    Sweep_Tick_Start();
    
    Readout_Init();
    
    CyGlobalIntEnable;
    
    Sweep_Tick_WritePeriod(100);
    
    Sweep_End_StartEx(Sweep_End_ISR);
    
    Readout_Write(0, 0);
    
    TS_Int_StartEx(TS_ISR);
  
    /* Sets the IDAC full scale range to 255uA */
    Sweep_IDAC_SetRange(Sweep_IDAC_RANGE_255uA);    
    /* Init the sweep IDAC value */
    Sweep_IDAC_SetValue(132); 
    
    LCD_Init();
    
    while(1) {
        int i;
                
        for (i = 0; i <= 7; i++) {
            //main_test();
            //Test_Color();
            //Test_FillRec();
            //Test_Circle();
            //Test_Triangle();
            //English_Font_test();
            foo_test(i);
            //Rotate_Test();
            //CyDelay(10000u);
        }
    }
    
}


/* [] END OF FILE */

