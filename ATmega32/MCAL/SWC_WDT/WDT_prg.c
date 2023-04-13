/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : WDT_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
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

#define WDT_VCC				5u
#define WDT_TIME_OUT		WDT_TimeOut_1000ms

static inline void _WDR(void){__asm__ __volatile__ ("wdr");}
static inline void _cli(void){__asm__ __volatile__ ("cli");}

typedef enum{
#if WDT_VCC == 3u
	WDT_TimeOut_17_1ms = (u8)0u,
	WDT_TimeOut_34_3ms,
	WDT_TimeOut_68_5ms,
	WDT_TimeOut_140ms,
	WDT_TimeOut_270ms,
	WDT_TimeOut_550ms,
	WDT_TimeOut_1100ms,
	WDT_TimeOut_2200ms
#elif WDT_VCC == 5u
	WDT_TimeOut_16_3ms = (u8)0u,
	WDT_TimeOut_32_5ms,
	WDT_TimeOut_65ms,
	WDT_TimeOut_130ms,
	WDT_TimeOut_260ms,
	WDT_TimeOut_520ms,
	WDT_TimeOut_1000ms,
	WDT_TimeOut_2100ms
#endif
}WDT_tenumTimeOut;

void WDT_vidInit(void){
	S_WDTCR->sBits.m_WDTOE = LBTY_RESET;
	S_WDTCR->sBits.m_WDE   = LBTY_SET;
	S_WDTCR->sBits.m_WDP   = WDT_TIME_OUT;

	WDT_vidReset();
}

void WDT_vidReset(void){
	_WDR();	/* reset WDT */
	while(!S_MCUCSR->sBits.m_WDRF);
}

void WDT_vidEnable(void){
	S_WDTCR->sBits.m_WDTOE = LBTY_RESET;
}

void WDT_vidDisable(void){
	S_WDTCR->sBits.m_WDE   = LBTY_SET;
	S_WDTCR->sBits.m_WDTOE = LBTY_SET;
	S_WDTCR->sBits.m_WDE   = LBTY_RESET;
}
/*************************** E N D (WDT_prg.c) ******************************/
