/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : DELAY.c												 	  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "DELAY.h"

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

/* ************************************************************************** */
/* Description :    Delay function for milliseconde							  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void vidMyDelay_ms(u16 u16DelayNum){
	while(--u16DelayNum){
        for(u32 i = 235 ; --i ; );
	}
    //for(u32 i = 235294 ; --i ; );
}


/*************************** E N D (DELAY.c) ******************************/