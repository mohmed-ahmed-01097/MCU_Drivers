/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "SEG_int.h"
#include "SEG_cfg.h"

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

#ifdef	SWC_SEG
int main(void){

	GPIO_voidInit();

    SEG_vidInit();

	for(u16 i = 50 ; i-- ; ){
		SEG_vidDisplayNum(1234);
	}
	for(u16 i = 50 ; i-- ; ){
		SEG_vidDisplayNum(5678);
	}
	for(u16 i = 50 ; i-- ; ){
		SEG_vidDisplayNum(9012);
	}
	for(u16 i = 50 ; i-- ; ){
		SEG_vidDisplayNum(3456);
	}
	for(u16 i = 50 ; i-- ; ){
		SEG_vidDisplayNum(7890);
	}

    GPIO_u8SetPinDirection(B, Eta32_LED_R, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (B, Eta32_LED_R, PIN_Low);

   	u8 u8Value = 0;

   	while(1){

    	for(u16 i = 50 ; i-- ; ){
    		SEG_vidDisplayNum(u8Value);
    	}
    	u8Value++;
    	GPIO_u8TogglePinValue(B, Eta32_LED_R);

    }
   	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
