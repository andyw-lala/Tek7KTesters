/* ========================================
 *
 * ========================================
*/
#ifndef __LCD_H
#define __LCD_H

#include "cytypes.h"
    
// TODO - PSoC I/O includes here.

typedef struct  
{										    
	uint16 width;
	uint16 height;
	uint16 id;
	uint8  dir;
	uint16	 wramcmd;
	uint16  setxcmd;
	uint16  setycmd;
}_lcd_dev; 	

extern _lcd_dev lcddev;

#define USE_HORIZONTAL  	 0

#define LCD_W 240
#define LCD_H 320

extern uint16  POINT_COLOR;
extern uint16  BACK_COLOR;

//-----------------LCD Connections

#define LCD_CS   (0)
#define LCD_RS   (1)
#define LCD_RST  (2)


// Access macros TBD
#define	LCD_CS_SET  (Display_Control_Write(Display_Control_Read() | (1 << LCD_CS)))
#define	LCD_RS_SET  (Display_Control_Write(Display_Control_Read() | (1 << LCD_RS)))
#define	LCD_RST_SET (Display_Control_Write(Display_Control_Read() | (1 << LCD_RST)))

#define	LCD_CS_CLR  (Display_Control_Write(Display_Control_Read() & ~(1 << LCD_CS)))
#define	LCD_RS_CLR  (Display_Control_Write(Display_Control_Read() & ~(1 << LCD_RS)))
#define	LCD_RST_CLR (Display_Control_Write(Display_Control_Read() & ~(1 << LCD_RST)))

#define WHITE       0xFFFF
#define BLACK       0x0000	  
#define BLUE        0x001F  
#define BRED        0xF81F
#define GRED 	    0xFFE0
#define GBLUE	    0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 	    0xBC40
#define BRRED 	    0xFC07
#define GRAY  	    0x8430
#define DARKBLUE      	 0x01CF
#define LIGHTBLUE      	 0x7D7C
#define GRAYBLUE       	 0x5458
#define LIGHTGREEN     	 0x841F
#define LIGHTGRAY        0xEF5B
#define LGRAY 		 0xC618
#define LGRAYBLUE      	 0xA651
#define LBBLUE           0x2B12
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16 Color);	 
void LCD_SetCursor(uint16 Xpos, uint16 Ypos);
void LCD_DrawPoint(uint16 x,uint16 y);
uint16  LCD_ReadPoint(uint16 x,uint16 y);
void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2);
void LCD_DrawRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2);		   
void LCD_SetWindows(uint16 xStar, uint16 yStar,uint16 xEnd,uint16 yEnd);

uint16 LCD_RD_DATA(void);
void LCD_WriteReg(uint8 LCD_Reg, uint16 LCD_RegValue);
void LCD_WR_DATA(uint8 data);
uint16 LCD_ReadReg(uint8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16 RGB_Code);
uint16 LCD_ReadRAM(void);		   
uint16 LCD_BGR2RGB(uint16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(uint16 Data);
void LCD_direction(uint8 direction );

#endif