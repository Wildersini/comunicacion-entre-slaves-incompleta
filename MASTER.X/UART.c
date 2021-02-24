#include <xc.h>
#include <pic16f887.h>
#include "UART.h"

void wilder (void) {
    SPBRG = 12;
}

void conf_tx (void) {
    TXSTAbits.CSRC = 0;
    TXSTAbits.TX9  = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 0;
    TXSTAbits.TRMT = 0;
    TXSTAbits.TX9D = 0;
}

void conf_rc (void) {
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9  = 0;
    RCSTAbits.SREN = 0;
    RCSTAbits.CREN = 1;
    RCREG = 0;
}

void escribir_UART (uint8_t a) {
    while (!TRMT);
    TXREG = a;
}

void W_USART_S (char* a) {
    uint8_t i;
    for (i = 0; a[i]!='\0'; i++) {
        escribir_UART (a[i]);
    }
}

uint8_t R_UART () {
    while (!RCIF);
    return RCREG;
}