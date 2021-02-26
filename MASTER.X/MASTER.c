/*//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"

//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
char variabe_basura=0;
char V_POT;
char CONT;
char TEMP;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
char slave_1 (void);
char slave_2 (void);
char slave_3 (void);


//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        V_POT=slave_1();
       __delay_ms(25);
        CONT=slave_2();
       __delay_ms(25);
        TEMP=slave_3();
       __delay_ms(25);
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}
char slave_1 (void){
   char v_pot=0;
    //slave_1
       PORTCbits.RC0 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(variabe_basura);
       v_pot= spiRead();
       
       
       __delay_ms(1);
       PORTCbits.RC0 = 1;       //Slave Deselect 
       return v_pot;
       
}
char slave_2 (void){
    char cont=0;
    //slave_1
       PORTCbits.RC0 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(variabe_basura);
       cont= spiRead();
       
       
       __delay_ms(1);
       PORTCbits.RC0 = 1;       //Slave Deselect 
       return cont;
       
}
char slave_3 (void){
        //slave_3
    char temp;
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(variabe_basura);
       temp = spiRead();
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       return temp;
}*/
//*********
// Palabra de configuración
//*********
// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*********
// Definición e importación de librerías
//*********
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <pic16f887.h>
#include "LCD.h"
#include "SPI.h"
#include "UART.h"
#define _XTAL_FREQ 8000000

//*********
// Definición de variables
//*********
char lcd[20];
char variable_basura=1;
char v_pot=0;
char temp=0;
int cont=0;
int pot=0;
//*********
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*********
void setup(void);
char slave_1 (void);
char slave_2 (void);
char slave_3 (void);



//*********
// Código Principal
//*********
void main(void) {
    setup();
    wilder();
    conf_tx();
    //conf_rc();
    Lcd_Init();
    LCD_Limpia();
    
    //*********
    // Loop infinito
    //*********
    while(1){
            v_pot=slave_1();
       __delay_ms(25);
            cont=slave_2();
       __delay_ms(25);
            temp = slave_3();
       __delay_ms(25);
           pot=v_pot;
        escribir_UART(pot);
        LCD_Limpia();//Limpiamos la lcd
        Lcd_Set_Cursor(1,1);//Se mostrar en la primera fila de la lcd
        Lcd_Write_String("S1   S2   S3");
       sprintf (lcd, "%d   %d    %d", v_pot, cont, temp); 
       // sprintf(lcd,"esto es una prueba");
        Lcd_Set_Cursor(2,1);//Se mostrar en la primera fila de la lcd
        Lcd_Write_String(lcd);
        __delay_ms(15);
        //W_USART_S("S1   S2   S3");
        //Mensaje que se muestra en la terminal en la segunda linea
       /* escribir_UART(13);
        escribir_UART(10);*/
        //Saltar lineas
      /*  W_USART_S(lcd);//Muestra en la terminal los valores
        escribir_UART(13);
        escribir_UART(10);*/
        //Saltar lineas
        __delay_ms(500);
    }
    return;
}
//*********
// Función de Inicialización
//*********
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC6=0;
    TRISC7=0;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;
    PORTE = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW,
            SPI_IDLE_2_ACTIVE);

}
char slave_1 (void){
   char V_POT;
    //slave_1
       PORTCbits.RC0 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(1);
       V_POT= spiRead();
       
       
       __delay_ms(10);
       PORTCbits.RC0 = 1;       //Slave Deselect 
       //return V_POT;
       return V_POT;
}
char slave_2 (void){
    char CONT=0;
    //slave_1
       PORTCbits.RC1 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(variable_basura);
       CONT= spiRead();
       
       
       __delay_ms(1);
       PORTCbits.RC1 = 1;       //Slave Deselect 
      return CONT;
       
}
char slave_3 (void){
        //slave_3
    char TEMP;
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(variable_basura);
       TEMP = spiRead();
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       return TEMP;
}

