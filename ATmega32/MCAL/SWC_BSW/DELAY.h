/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : DELAY.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
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

#define DELAY_MCU_FOCS_8MHZ			185
#define DELAY_MCU_FOCS_16MHZ		370
#define DELAY_MCU_FOCS_20MHZ		462 	// 462.5

#define DELAY_FOR_LOOP				DELAY_MCU_FOCS_8MHZ

#define ERROR_RATIO					43
#define DELAY_MS(x)					for(u32 u32Delay = ((F_CPU/1000u)*x/ERROR_RATIO) ; u32Delay-- ; )	__asm("NOP");

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* Description :    Delay function for milliseconde							  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void vidMyDelay_ms(u16 u16DelayNum);

#endif /* DELAY_H_ */
/*************************** E N D (DELAY.h) ******************************/
