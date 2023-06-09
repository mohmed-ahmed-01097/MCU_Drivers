/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "LMD_cfg.h"
#include "LMD_int.h"

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

#ifdef	SWC_LMD
int main(void){
	LMD_vidInit();
	u8 u8char = '0', i=5, u8Arr[150], index;
	while(1){
		LMD_u8String((u8*)"Hello_MAAM! ");
		while(!LMD_u8Update());
		LMD_u8String((u8*)"https://xantorohara.github.io/led-matrix-editor/");
		while(!LMD_u8Update());
		while(u8char != 127){
			LMD_u8Char(u8char);
			if(!i--){
				u8Arr[index++] = ++u8char;
				i = LMD_REFRESH_RATE;
			}
		}
		u8Arr[index++] = '\0';
		LMD_u8String(u8Arr);
		while(!LMD_u8Update());
	}
	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
