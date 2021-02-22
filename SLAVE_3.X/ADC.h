#ifndef __ADC_H
#define	__ADC_H
#include <xc.h> 
#include <stdint.h>

//unsigned Canal_ADC(unsigned short x);
void conf_ADC(void);
void ADC_start(void);
void TAD(void);
void AD_cycle(void);
#endif