// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#define _XTAL_FREQ 8000000
/**************************************************/
//*************VARIABLE*****************
/********************************************/
int contador=0;
/**************************************************/
/**************************************************/
//*******************Mencion de funciones******
/**************************************************/
/**************************************************/
void setup(void);
void SUMAR(void);
void RESTAR(void);
void CONTEO(void);

void __interrupt() isr(void){
   if(SSPIF == 1){
        PORTD = spiRead();
        spiWrite(contador);
        SSPIF = 0;
    }
}


void main(void){
    setup();
    while(1){
        CONTEO();
    }
/**************************************************/
/**************************************************/
//*******************FUNCIONES******
/**************************************************/
/**************************************************/
}
void setup(void){
TRISA = 1;
    TRISCbits.TRISC0=1;
    TRISCbits.TRISC1=1;
    TRISB = 0;
    //ANSEL = 0;
    ANSELH = 0;
    
     INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
       
}
void SUMAR(void){
    if (PORTCbits.RC0==1){
    __delay_ms(50);
    }
    else if (PORTCbits.RC0==0){
        contador++;
        PORTB= contador;
        __delay_ms(50);
    }
}
void RESTAR(void){
    if(PORTCbits.RC1==1){
    __delay_ms(50);
    }
    else if(PORTCbits.RC1==0){
        contador--;
        PORTB=contador;
    }
}
void CONTEO(void){
    SUMAR();
    RESTAR();
}
