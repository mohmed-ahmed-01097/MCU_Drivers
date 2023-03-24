/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SEV_SEG.c													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBIT_int.h"
#include "LBTY_int.h"
#include "GPIO_int.h"
#include "GPIO_cfg.h"

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

void SEG_vidInit(void){

    GPIO_u8SetPinDirection(C, AMIT_7Seg_COM0, PIN_OUTPUT);
    GPIO_u8SetPinValue(C, AMIT_7Seg_COM0, PIN_Low);
    GPIO_u8SetPinDirection(C, AMIT_7Seg_COM1, PIN_OUTPUT);
    GPIO_u8SetPinValue(C, AMIT_7Seg_COM1, PIN_Low);

    GPIO_u8SetPinDirection(C, AMIT_7Seg_A, PIN_OUTPUT);
    GPIO_u8SetPinValue(C, AMIT_7Seg_A, PIN_Low);
    GPIO_u8SetPinDirection(C, AMIT_7Seg_B, PIN_OUTPUT);
    GPIO_u8SetPinValue(C, AMIT_7Seg_B, PIN_Low);
    GPIO_u8SetPinDirection(C, AMIT_7Seg_C, PIN_OUTPUT);
    GPIO_u8SetPinValue(C, AMIT_7Seg_C, PIN_Low);
    GPIO_u8SetPinDirection(C, AMIT_7Seg_D, PIN_OUTPUT);
    GPIO_u8SetPinValue(C, AMIT_7Seg_D, PIN_Low);
}

void SEG_vidSetValue(u8 u8SegValue){
	u8 u8PortValue_LOC = 0;

	GPIO_u8GetPortValue(C, &u8PortValue_LOC);
	u8PortValue_LOC =  (((u8SegValue%10u) << AMIT_7Seg_A) | (1u<<AMIT_7Seg_COM0) | (u8PortValue_LOC & 0x02u));
	GPIO_u8SetPortValue(C, u8PortValue_LOC);
	vidMyDelay_ms(11);
    GPIO_u8SetPinValue(C, AMIT_7Seg_COM0, PIN_Low);

	GPIO_u8GetPortValue(C, &u8PortValue_LOC);
	u8PortValue_LOC =  (((u8SegValue/10u) << AMIT_7Seg_A) | (1u<<AMIT_7Seg_COM1) | (u8PortValue_LOC & 0x02u));
	GPIO_u8SetPortValue(C, u8PortValue_LOC);
	vidMyDelay_ms(11);
    GPIO_u8SetPinValue(C, AMIT_7Seg_COM1, PIN_Low);
}
void SEG_vidSetDigit(u8 u8SegValue){
	GPIO_u8SetPortValue(C, (((u8SegValue%10u) & 0xFu) << AMIT_7Seg_A) | (1u<<AMIT_7Seg_COM0));
	vidMyDelay_ms(11);
    GPIO_u8SetPinValue(C, AMIT_7Seg_COM0, PIN_Low);

	GPIO_u8SetPortValue(C, ((u8SegValue/10u) << AMIT_7Seg_A) | (1u<<AMIT_7Seg_COM1));
	vidMyDelay_ms(11);
    GPIO_u8SetPinValue(C, AMIT_7Seg_COM1, PIN_Low);

}
/*************************** E N D (SEV_SEG.c) ******************************/
