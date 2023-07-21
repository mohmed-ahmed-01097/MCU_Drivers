/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

#ifdef	SWC_TMR

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "INTP.h"

#include "TMR_int.h"
#include "TMR_cfg.h"

#if defined(AMIT_KIT)

#define PORT_BUZZER			D
#define PIN_BUZZER			AMIT_BUZZER

#define PORT_LED0			D
#define PIN_LED0			AMIT_LED0

#define PORT_LED1			D
#define PIN_LED1			AMIT_LED1

#define PORT_LED2			D
#define PIN_LED2			AMIT_LED2

#elif defined(ETA32_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_BUZZER

#define PORT_LED0			B
#define PIN_LED0			Eta32_LED_R

#define PORT_LED1			A
#define PIN_LED1			Eta32_LED_G

#define PORT_LED2			A
#define PIN_LED2			Eta32_LED_B

#elif defined(ETA32_MINI_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_mini_BUZZER

#define PORT_LED0			C
#define PIN_LED0			Eta32_mini_LED_R

#define PORT_LED1			C
#define PIN_LED1			Eta32_mini_LED_G

#define PORT_LED2			C
#define PIN_LED2			Eta32_mini_LED_B

#endif

#if defined(TMR0)
TMR0_tstrConfig strTMR0_CFG = {
		.m_TMR_Compare   = 0xC7,	// 25 uSec
		.m_TMR_Prescalar = TMRx_Fosc_Prescaler_1,
		.m_TMR_Mode      = TMRx_u8_CTC_Mode_Mode,
		.m_TMR_OutputMode= TMRx_u8_COM_Disconnected,
		.m_TMR_FOC       = LBTY_RESET,
		.m_TMR_OVIE      = LBTY_RESET,
		.m_TMR_OCIE      = LBTY_SET
};
#elif defined(PWM0)
TMR0_tstrConfig strTMR0_CFG = {
		.m_TMR_Freq      = 40000u,
		.m_TMR_Duty      = 50u,
		.m_TMR_Compare   = 0xC7,	// 25 uSec
		.m_TMR_Prescalar = TMR0_Fosc_Prescaler_1,
		.m_TMR_Mode      = TMRx_u8_PWM_Fase_Mode,
		.m_TMR_OutputMode= TMRx_u8_FastPWM_Clear_on_Match,
		.m_TMR_FOC       = LBTY_RESET,
		.m_TMR_OVIE      = LBTY_SET,
		.m_TMR_OCIE      = LBTY_RESET
};
#endif
#if defined(TMR2)
TMR2_tstrConfig strTMR2_CFG = {
		.m_TMR_Compare   = 0x9F,	// 20 uSec
		.m_TMR_Prescalar = TMR2_Fosc_Prescaler_1,
		.m_TMR_Mode      = TMRx_u8_Normal_Mode,
		.m_TMR_OutputMode= TMRx_u8_COM_Toggle_on_Match,
		.m_TMR_FOC       = LBTY_RESET,
		.m_TMR_OVIE      = LBTY_SET,
		.m_TMR_OCIE      = LBTY_RESET,
		.m_TMR_AsyClock  = TMR2_IO_Clock
};
#elif defined(PWM2)
TMR2_tstrConfig strTMR2_CFG = {
		.m_TMR_Freq      = 10000,
		.m_TMR_Duty      = 10,
		.m_TMR_Compare   = 0x00, 	//0x9F,	// 20 uSec
		.m_TMR_Prescalar = TMR2_Fosc_Prescaler_8,
		.m_TMR_Mode      = TMRx_u8_PWM_Fase_Mode,
		.m_TMR_OutputMode= TMRx_u8_FastPWM_Set_on_Match,
		.m_TMR_FOC       = LBTY_RESET,
		.m_TMR_OVIE      = LBTY_SET,
		.m_TMR_OCIE      = LBTY_RESET,
		.m_TMR_AsyClock  = TMR2_IO_Clock
};
#endif
void TMR0_ISR(void);
void TMR2_ISR(void);
void TMR1_ISR(void);

volatile u8 u8INT0_Flag = LBTY_RESET;
volatile u8 u8INT2_Flag = LBTY_RESET;
volatile u8 u8INT1_Flag = LBTY_RESET;

int main(void){

	GPIO_u8SetPinDirection(PORT_LED0, PIN_LED0, PIN_OUTPUT);
	GPIO_u8SetPinValue	  (PORT_LED0, PIN_LED0, PIN_Low);
	GPIO_u8SetPinDirection(PORT_LED1, PIN_LED1, PIN_OUTPUT);
	GPIO_u8SetPinValue	  (PORT_LED1, PIN_LED1, PIN_Low);
	GPIO_u8SetPinDirection(PORT_LED2, PIN_LED2, PIN_OUTPUT);
	GPIO_u8SetPinValue	  (PORT_LED2, PIN_LED2, PIN_Low);

	INTP_vidDisable();

#if defined(TMR0)
	TMR0_vidSetConfig((TMR0_tstrConfig* const)&strTMR0_CFG);
	TMR0_vidSetCallBack_CompareMatch(TMR0_ISR);
#elif defined(PWM0)
	TMR0_vidSetConfig((TMR0_tstrConfig* const)&strTMR0_CFG);
	TMR0_vidSetCallBack_OverFlow(TMR0_ISR);
	PWM_vidEnable_OC0();
#endif
#if defined(TMR2)
	TMR2_vidSetConfig((TMR2_tstrConfig* const)&strTMR2_CFG);
	TMR2_vidSetCallBack_OverFlow(TMR2_ISR);
#elif defined(PWM2)
	TMR2_vidSetConfig((TMR2_tstrConfig* const)&strTMR2_CFG);
	TMR2_vidSetCallBack_OverFlow(TMR2_ISR);
	PWM_vidEnable_OC2();
#endif
#if defined(TMR1)
	    TMR1_vidInit();
	    TMR1_vidSetCallBack_OverFlow(TMR1_ISR);
#elif defined(PWM1)
	    TMR1_vidInit();
	    TMR1_vidSetCallBack_OverFlow(TMR1_ISR);
	    PWM_vidEnable_OC1x();
#endif

	INTP_vidEnable();

	while(1){

		if(u8INT0_Flag){
#if defined(TMR0)
			static u8 count;
			if(count++ == 50){
				if(++strTMR0_CFG.m_TMR_Prescalar > TMRx_Fosc_Prescaler_1024) strTMR0_CFG.m_TMR_Prescalar = TMRx_Fosc_Prescaler_1;
				TMR0_vidSetConfig((TMR0_tstrConfig* const)&strTMR0_CFG);
				count = 0;
			}
#elif defined(PWM0)
			static u8 u8Duty0;
			PWM_u8SetDuty_OC0(u8Duty0++);
			GPIO_u8SetPinValue(PORT_LED0, PIN_LED0, PIN_Low);
			if(u8Duty0 >= 100)	u8Duty0 = 0;
#endif
			u8INT0_Flag = LBTY_RESET;
		}
		if(u8INT2_Flag){
#if defined(TMR2)
			static u8 count;
			if(count++ == 50){
				++strTMR2_CFG.m_TMR_Compare;
				TMR2_vidSetConfig((TMR2_tstrConfig* const)&strTMR2_CFG);
				count = 0;
			}
#elif defined(PWM2)
			static u8 u8Duty2;
			PWM_u8SetDuty_OC2(u8Duty2++);
			GPIO_u8SetPinValue(PORT_LED1, PIN_LED1, PIN_Low);
			if(u8Duty2 >= 100)	u8Duty2 = 0;
#endif
			u8INT2_Flag = LBTY_RESET;
		}
		if(u8INT1_Flag){
#if defined(PWM1)
			static u8 u8Duty1A;
			static u8 u8Duty1B;
			PWM_u8SetDuty_OC1A(u8Duty1A++);
			PWM_u8SetDuty_OC1B(u8Duty1B++);
			GPIO_u8SetPinValue(PORT_LED2, PIN_LED2, PIN_Low);
			if(u8Duty1A > 100)	u8Duty1A = 0;
			if(u8Duty1B > 100)	u8Duty1B = 0;
#endif
			u8INT1_Flag = LBTY_RESET;
		}
	}


#if defined(TMR0)
#elif defined(PWM0)
#endif

	return 0;
}

void TMR0_ISR(void){
	static u8 count;
	if(++count == 4){
		u8INT0_Flag = LBTY_SET;
//		GPIO_u8TogglePinValue(PORT_LED0, PIN_LED0);
		count = 0;
	}
}
void TMR2_ISR(void){
	u8INT2_Flag = LBTY_SET;
//	GPIO_u8TogglePinValue(PORT_LED1, PIN_LED1);
}
void TMR1_ISR(void){
	u8INT1_Flag = LBTY_SET;
//	GPIO_u8TogglePinValue(PORT_LED2, PIN_LED2);
}

#endif

/*************************** E N D (main.c) ******************************/
