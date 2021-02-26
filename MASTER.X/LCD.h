// Extraido de la calse de Pablo Mazariegos, modificado para 8 bits
// https://electrosome.com/lcd-pic-mplab-xc8/#google_vignette
#ifndef __LCD_H_
#define __LCD_H_
#include <xc.h>
#include <stdint.h>

//Puertos conectados
#ifndef RS
#define RS RE0
#endif
#ifndef EN
#define EN RE1
#endif
#ifndef D0
#define D0 RD0
#endif
#ifndef D1
#define D1 RD1
#endif
#ifndef D2
#define D2 RD2
#endif
#ifndef D3
#define D3 RD3
#endif
#ifndef D4
#define D4 RD4
#endif
#ifndef D5
#define D5 RD5
#endif
#ifndef D6
#define D6 RD6
#endif
#ifndef D7
#define D7 RD7
#endif

void Lcd_Init();
void LCD_CMD(char a);
void datosLCD(uint8_t x);
void Puerto(uint8_t x);
void LCD_Limpia(void);
void Lcd_Set_Cursor(uint8_t x, uint8_t y);
void Lcd_Write_String(char *a);
#endif