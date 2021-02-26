#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include <pic16f887.h>
#include "SPI.h"

#define _XTAL_FREQ 8000000
// CONFIG1
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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

//******************************************************************************
// Variables
//******************************************************************************

float map;


//unsigned Canal_ADC (unsigned short x);
void setup(void);
void ADC(void);
char mapeo(void);


void __interrupt() isr(void){
   if(SSPIF == 1){
        PORTD = spiRead();
        spiWrite(map);
        SSPIF = 0;
    }
}
void main(void) {
    setup();
    while(1){
        ADC();
        map=mapeo();
       // PORTD=ADRESH;      
        }
    }
    
   

void setup(void){
    //TRISA = 0b00000001;
    ANSELbits.ANS0 = 0;
    TRISD= 0;
    
    PORTA=0;
    TRISAbits.TRISA0=1;
    ANSELbits.ANS0=1;
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    conf_ADC();   
    
}
void ADC(void){
    if(ADCON0bits.GO){
        return;
    }
    TAD();
    AD_cycle();
}
char mapeo(void){
    char volt;
    while (ADCON0bits.GO == 1){
        volt = ADRESH;//((ADRESH * 5.0)/255); //Conversion de 0V-5V
    }
    return volt;
}



























