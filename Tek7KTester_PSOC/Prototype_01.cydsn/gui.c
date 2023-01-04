#include "lcd.h"
#include "string.h"
#include "font.h" 
#include "gui.h"

/*******************************************************************
 * @name       :void GUI_DrawPoint(uint16 x,uint16 y,uint16 color)
 * @date       :2018-08-09 
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
                y:the y coordinate of the point
		color:the color value of the point
 * @retvalue   :None
********************************************************************/
void GUI_DrawPoint(uint16 x,uint16 y,uint16 color)
{
	LCD_SetCursor(x,y);//ÉèÖÃ¹â±êÎ»ÖÃ 
	Lcd_WriteData_16Bit(color); 
}

/*******************************************************************
 * @name       :void LCD_Fill(uint16 sx,uint16 sy,uint16 ex,uint16 ey,uint16 color)
 * @date       :2018-08-09 
 * @function   :fill the specified area
 * @parameters :sx:the bebinning x coordinate of the specified area
                sy:the bebinning y coordinate of the specified area
		ex:the ending x coordinate of the specified area
		ey:the ending y coordinate of the specified area
		color:the filled color value
 * @retvalue   :None
********************************************************************/
void LCD_Fill(uint16 sx,uint16 sy,uint16 ex,uint16 ey,uint16 color)
{  	
	uint16 i,j;			
	uint16 width=ex-sx+1;
	uint16 height=ey-sy+1;
	LCD_SetWindows(sx,sy,ex,ey);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		Lcd_WriteData_16Bit(color);
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}

/*******************************************************************
 * @name       :void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
 * @date       :2018-08-09 
 * @function   :Draw a line between two points
 * @parameters :x1:the bebinning x coordinate of the line
                y1:the bebinning y coordinate of the line
		x2:the ending x coordinate of the line
		y2:the ending y coordinate of the line
 * @retvalue   :None
********************************************************************/
void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
	uint16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1;
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1;
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )
	{  
		LCD_DrawPoint(uRow,uCol);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

/*****************************************************************************
 * @name       :void LCD_DrawRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
 * @date       :2018-08-09 
 * @function   :Draw a rectangle
 * @parameters :x1:the bebinning x coordinate of the rectangle
                y1:the bebinning y coordinate of the rectangle
		        x2:the ending x coordinate of the rectangle
		        y2:the ending y coordinate of the rectangle
 * @retvalue   :None
******************************************************************************/
void LCD_DrawRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}  

/*****************************************************************************
 * @name       :void LCD_DrawFillRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
 * @date       :2018-08-09 
 * @function   :Filled a rectangle
 * @parameters :x1:the bebinning x coordinate of the filled rectangle
                y1:the bebinning y coordinate of the filled rectangle
		x2:the ending x coordinate of the filled rectangle
		y2:the ending y coordinate of the filled rectangle
 * @retvalue   :None
******************************************************************************/  
void LCD_DrawFillRectangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
	LCD_Fill(x1,y1,x2,y2,POINT_COLOR);
}
 
/*****************************************************************************
 * @name       :void _draw_circle_8(int xc, int yc, int x, int y, uint16 c)
 * @date       :2018-08-09 
 * @function   :8 symmetry circle drawing algorithm (internal call)
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
		x:the x coordinate relative to the Circular center 
		y:the y coordinate relative to the Circular center 
		c:the color value of the circle
 * @retvalue   :None
******************************************************************************/  
void _draw_circle_8(int xc, int yc, int x, int y, uint16 c)
{
	GUI_DrawPoint(xc + x, yc + y, c);

	GUI_DrawPoint(xc - x, yc + y, c);

	GUI_DrawPoint(xc + x, yc - y, c);

	GUI_DrawPoint(xc - x, yc - y, c);

	GUI_DrawPoint(xc + y, yc + x, c);

	GUI_DrawPoint(xc - y, yc + x, c);

	GUI_DrawPoint(xc + y, yc - x, c);

	GUI_DrawPoint(xc - y, yc - x, c);
}

/*****************************************************************************
 * @name       :void gui_circle(int xc, int yc,uint16 c,int r, int fill)
 * @date       :2018-08-09 
 * @function   :Draw a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center 
                yc:the y coordinate of the Circular center 
		r:Circular radius
		fill:1-filling,0-no filling
 * @retvalue   :None
******************************************************************************/  
void gui_circle(int xc, int yc,uint16 c,int r, int fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		while (x <= y) {
			_draw_circle_8(xc, yc, x, y, c);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

/*****************************************************************************
 * @name       :void Draw_Triangel(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 x2,uint16 y2)
 * @date       :2018-08-09 
 * @function   :Draw a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge 
                y0:the bebinning y coordinate of the triangular edge 
		x1:the vertex x coordinate of the triangular
		y1:the vertex y coordinate of the triangular
		x2:the ending x coordinate of the triangular edge 
		y2:the ending y coordinate of the triangular edge 
 * @retvalue   :None
******************************************************************************/ 
void Draw_Triangel(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 x2,uint16 y2)
{
	LCD_DrawLine(x0,y0,x1,y1);
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x2,y2,x0,y0);
}

static void _swap(uint16 *a, uint16 *b)
{
	uint16 tmp;

        tmp = *a;
	*a = *b;
	*b = tmp;
}

/*****************************************************************************
 * @name       :void Fill_Triangel(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 x2,uint16 y2)
 * @date       :2018-08-09 
 * @function   :filling a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge 
                y0:the bebinning y coordinate of the triangular edge 
		x1:the vertex x coordinate of the triangular
		y1:the vertex y coordinate of the triangular
		x2:the ending x coordinate of the triangular edge 
		y2:the ending y coordinate of the triangular edge 
 * @retvalue   :None
******************************************************************************/ 
void Fill_Triangel(uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 x2,uint16 y2)
{
	uint16 a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
 	if (y0 > y1) 
	{
            _swap(&y0,&y1); 
	    _swap(&x0,&x1);
 	}
 	if (y1 > y2) 
	{
            _swap(&y2,&y1); 
	    _swap(&x2,&x1);
 	}
        if (y0 > y1) 
	{
            _swap(&y0,&y1); 
	    _swap(&x0,&x1);
        }
	if(y0 == y2) 
	{ 
		a = b = x0;
		if(x1 < a)
    {
			a = x1;
    }
    else if(x1 > b)
    {
			b = x1;
    }
    if(x2 < a)
    {
			a = x2;
    }
		else if(x2 > b)
    {
			b = x2;
    }
		LCD_Fill(a,y0,b,y0,POINT_COLOR);
    return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;
	
	if(y1 == y2)
	{
		last = y1; 
	}
  else
	{
		last = y1-1; 
	}
	for(y=y0; y<=last; y++) 
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
    sb += dx02;
    if(a > b)
    {
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) 
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
}

/*****************************************************************************
 * @name       :void LCD_ShowChar(uint16 x,uint16 y,uint16 fc, uint16 bc, char c,uint8 size,uint8 mode)
 * @date       :2018-08-09 
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
                y:the bebinning y coordinate of the Character display position
		fc:the color value of display character
		bc:the background color of display character
		c:the ascii code of display character(0~94)
		size:the size of display character
		mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void LCD_ShowChar(uint16 x,uint16 y,uint16 fc, uint16 bc, char c,uint8 size,uint8 mode)
{  
    uint8 temp;
    uint8 pos,t;
    uint8 num;
	uint16 colortemp=POINT_COLOR;      
		   
	num=c-' ';
    if (num > 94) {
        return;
    }
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);
	if(!mode)
	{		
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];
			else temp=asc2_1608[num][pos];
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)Lcd_WriteData_16Bit(fc); 
				else Lcd_WriteData_16Bit(bc); 
				temp>>=1; 
				
		    }
			
		}	
	}else
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];
			else temp=asc2_1608[num][pos];
			for(t=0;t<size/2;t++)
		    {   
				POINT_COLOR=fc;              
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}

/*****************************************************************************
 * @name       :void LCD_ShowString(uint16 x,uint16 y,uint8 size,char *p,uint8 mode)
 * @date       :2018-08-09 
 * @function   :Display English string
 * @parameters :x:the bebinning x coordinate of the English string
                y:the bebinning y coordinate of the English string
		p:the start address of the English string
		size:the size of display character
		mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/   	  
void LCD_ShowString(uint16 x,uint16 y,uint8 size,char *p,uint8 mode)
{         
    while((*p<='~')&&(*p>=' '))
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
        x+=size/2;
        p++;
    }  
} 

/*****************************************************************************
 * @name       :uint32 mypow(uint8 m,uint8 n)
 * @date       :2018-08-09 
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
                n:the power
 * @retvalue   :the nth power of m
******************************************************************************/ 
uint32 mypow(uint8 m,uint8 n)
{
	uint32 result=1;	 
	while(n--)result*=m;    
	return result;
}

/*****************************************************************************
 * @name       :void LCD_ShowNum(uint16 x,uint16 y,uint32 num,uint8 len,uint8 size)
 * @date       :2018-08-09 
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
		num:the number(0~4294967295)
		len:the length of the display number
		size:the size of display number
 * @retvalue   :None
******************************************************************************/  			 
void LCD_ShowNum(uint16 x,uint16 y,uint32 num,uint8 len,uint8 size)
{         	
	uint8 t,temp;
	uint8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0); 
	}
} 

/*****************************************************************************
 * @name       :void Show_Str(uint16 x, uint16 y, uint16 fc, uint16 bc, uint8 *str,uint8 size,uint8 mode)
 * @date       :2018-08-09 
 * @function   :Display Chinese and English strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
		fc:the color value of Chinese and English strings
		bc:the background color of Chinese and English strings
		str:the start address of the Chinese and English strings
		size:the size of Chinese and English strings
		mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/	   		   
void Show_Str(uint16 x, uint16 y, uint16 fc, uint16 bc, char *str,uint8 size,uint8 mode)
{					
    uint16 x0=x;							  	  
    while(*str!=0) { 
        if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) {
            return; 
        }
        if(*str==0x0D) {         
            y+=size;
            x=x0;
            str++; 
        } else {
            if(size>16) {  
                LCD_ShowChar(x,y,fc,bc,*str,16,mode);
                x+=8;
            } else {
                LCD_ShowChar(x,y,fc,bc,*str,size,mode);
                x+=size/2;
            }
        } 
        str++; 
    }
}

/*****************************************************************************
 * @name       :void Gui_StrCenter(uint16 x, uint16 y, uint16 fc, uint16 bc, char *str,uint8 size,uint8 mode)
 * @date       :2018-08-09 
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
                y:the bebinning y coordinate of the Chinese and English strings
		fc:the color value of strings
		bc:the background color of strings
		str:the start address of the strings
		size:the size of strings
		mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void Gui_StrCenter(uint16 x, uint16 y, uint16 fc, uint16 bc, char *str,uint8 size,uint8 mode)
{
	uint16 len=strlen((const char *)str);
	uint16 x1=x -((len*(size/2))/2);
	Show_Str(x1,y,fc,bc,str,size,mode);
} 
 
/*****************************************************************************
 * @name       :void Gui_Drawbmp16(uint16 x,uint16 y,const unsigned char *p)
 * @date       :2018-08-09 
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
                y:the bebinning y coordinate of the BMP image
		p:the start address of image array
 * @retvalue   :None
******************************************************************************/ 
void Gui_Drawbmp16(uint16 x,uint16 y,const unsigned char *p)
{
  	int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+40-1,y+40-1);
        for(i=0;i<40*40;i++) {	
	 	picL=*(p+i*2);
		picH=*(p+i*2+1);				
		Lcd_WriteData_16Bit(picH<<8|picL);  						
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
}
