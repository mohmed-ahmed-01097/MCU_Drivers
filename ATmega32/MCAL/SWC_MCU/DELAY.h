/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : DELAY.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef DELAY_H_
#define DELAY_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define DELAY_MCU_FOCS_8MHZ			270.073f
#define DELAY_MCU_FOCS_16MHZ		540.146f
#define DELAY_MCU_FOCS_20MHZ		383.211f
#if(F_CPU == 8000000UL)
#define DELAY_FOR_LOOP				DELAY_MCU_FOCS_8MHZ
#elif(F_CPU == 16000000UL)
#define DELAY_FOR_LOOP				DELAY_MCU_FOCS_16MHZ
#elif(F_CPU == 20000000UL)
#define DELAY_FOR_LOOP				DELAY_MCU_FOCS_20MHZ
#endif

#define ERROR_RATIO					29.455f
#ifndef ERROR_RATIO
#define DELAY_US(x)			DELAY_LOOP_MS((F_CPU/4000000u)*x))
#define DELAY_MS(x)			DELAY_LOOP_US((F_CPU/4000u   )*x))
#else
#define DELAY_MS(x)					\
	for(volatile u32 u32Delay = (u32)((F_CPU/1000u)*x/ERROR_RATIO) ; u32Delay-- ; )	__asm__ __volatile__("NOP")
#endif

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

LCTY_INLINE void DelayU(u8 count){
	__asm__ __volatile__("1: dec %0"    "\n\t" "brne 1b" : "=r" (count) : "0" (count));
}
LCTY_INLINE void DelayM(u16 count){
	__asm__ __volatile__("1: sbiw %0,1" "\n\t" "brne 1b" : "=w" (count) : "0" (count));
}
LCTY_INLINE void DELAY_LOOP_US(u16 u16DelayNum){
	volatile u16 __tick = u16DelayNum / 2.8565f;
	while(--__tick){
		DelayU(F_CPU/3000000u);
	}
}
LCTY_INLINE void DELAY_LOOP_MS(u16 u16DelayNum){
	volatile u16 __tick = u16DelayNum;
	while(--__tick){
		DelayM(F_CPU/4000u);
	}
}

/* ************************************************************************** */
/* Description :    Delay function for milliseconde							  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LCTY_INLINE void vidMyDelay_ms(u16 u16DelayNum){
	for(volatile u32 i = (u32)(u16DelayNum * DELAY_FOR_LOOP) ; i-- ; );
}

#endif /* DELAY_H_ */
/*************************** E N D (DELAY.h) ******************************/
