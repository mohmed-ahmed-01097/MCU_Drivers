#include "ATMega32.h"
#include "GPIO.h"

void GPIO_Init(GPIOx_type * GPIOx){
    GPIOx->m_DDR.sBits.m_B0 = OUTPUT;
    GPIOx->m_PORT.sBits.m_B0 = High;
}

void main(void){
    S_GPIOA->m_DDR.u_Reg = 0xffu;
    S_GPIOA->m_PORT.sBits.m_B0 = High;
}
