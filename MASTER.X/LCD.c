//Obtenido y modificado de la clase de Pablo Mazariegos
#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#define _XTAL_FREQ 8000000

//Funcion para indicar el caracter segun sea el tamaño del mismo. 
void Puerto(uint8_t x){
	if(x & 1){D0 = 1;}else{D0 = 0;}
    if(x & 2){D1 = 1;}else{D1 = 0;}
    if(x & 4){D2 = 1;}else{D2 = 0;}
    if(x & 8){D3 = 1;}else{D3 = 0;}
    if(x & 16){D4 = 1;}else{D4 = 0;}
    if(x & 32){D5 = 1;}else{D5 = 0;}
    if(x & 64){D6 = 1;}else{D6 = 0;}
    if(x & 128){D7 = 1;}else{D7 = 0;}
}

//Funcion para imprimir el caracter
void LCD_CMD(char a){
    RS = 1;//Las direcciones a los caracteres
    Puerto(a);
    EN = 1;//Mandar el valor
    __delay_us(5);
    EN = 0;//Verificar si el valor de carac llego
    __delay_us(5);
    __delay_us(50);
}
//Funcion para mandar los datos a la LCD
void datosLCD(uint8_t x){
    RS = 0;//Modifica el contraste de la patalla
    Puerto(x);
    EN = 1;//Mandar el valor
    __delay_us(5);
    EN = 0;//Verificar si el valor de carac llego
    __delay_us(5);
    __delay_ms(2);   
}
//Funcion para limpiar la LCD
void LCD_Limpia(void){
    datosLCD(0);
    datosLCD(1);
}
//Funcion para iniciar la LCD
//En base de la presentacion de clase. 
void Lcd_Init(){
    __delay_ms(20);
    datosLCD (0x30);
    __delay_ms(5);
    datosLCD (0x30);
    __delay_us(100);
    datosLCD (0x30);
    __delay_us(100);
    datosLCD (0x38);
    __delay_us(60);
    datosLCD (0x08);
    __delay_us(60);
    datosLCD (0x01);
    __delay_ms(5);
    datosLCD (0x06);
    __delay_us(60);
    datosLCD (0x0C);     
    __delay_us(60);
}
//Funcion para configurar el cursor
void Lcd_Set_Cursor(uint8_t x, uint8_t y){
	uint8_t a;
	if(x == 1){//Linea que se coloca arriba
	  a = 0x80 + y;//direccion(hexadecimal) y posicion para colocarlo en la fila 
                       //adecuada para ire leyendo adecuadamente
		datosLCD(a);
    }
	else if(x == 2){//Linea que se coloca abajo
	  a = 0xC0 + y;//direccion(hexadecimal) y posicion para colocarlo en la fila 
                       //adecuada para ire leyendo adecuadamente
		datosLCD(a);
    }
}
//Funcion para mandar un string
void Lcd_Write_String(char *a){
    //funcion para poder imprimir texto usando el puntero 
    //para guardar la direccion del registro o valor de a
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_CMD(a[i]);
}