#ifndef __GUI_H__
#define __GUI_H__

#include "lcd.h"
    
void GUI_DrawPoint(uint16 x,uint16 y,uint16 color);
void LCD_Fill(uint16 sx,uint16 sy,uint16 ex,uint16 ey,uint16 color);
void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2);
void LCD_DrawRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2);
void Draw_Circle(uint16 x0,uint16 y0,uint16 fc,uint8 r);
void Draw_Triangel(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void Fill_Triangel(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void LCD_ShowChar(uint16 x,uint16 y,uint16 fc, uint16 bc, char num,uint8 size,uint8 mode);
void LCD_ShowNum(uint16 x,uint16 y,uint32 num,uint8 len,uint8 size);
void LCD_Show2Num(uint16 x,uint16 y,uint16 num,uint8 len,uint8 size,uint8 mode);
void LCD_ShowString(uint16 x,uint16 y,uint8 size,char *p,uint8 mode);
void Show_Str(uint16 x, uint16 y, uint16 fc, uint16 bc, char *str,uint8 size,uint8 mode);
void Gui_Drawbmp16(uint16 x,uint16 y,const unsigned char *p);
void gui_circle(int xc, int yc,uint16 c,int r, int fill);
void Gui_StrCenter(uint16 x, uint16 y, uint16 fc, uint16 bc, char *str,uint8 size,uint8 mode);
void LCD_DrawFillRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2);
#endif

