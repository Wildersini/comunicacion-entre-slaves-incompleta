#ifndef _UART_H_
#define _UART_H_
#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

void wilder (void);
void conf_tx (void);
void conf_rc (void);
uint8_t R_UART ();
void W_USART_S (char *a);
void escribir_UART (int a);
#endif	

