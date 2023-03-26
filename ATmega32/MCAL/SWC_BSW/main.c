/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include <stdio.h>
#include "LBTY_int.h"
#include "LBIT_int.h"

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

#ifdef	SWC_BSW
int main(void){

	printf("//////////////////////////////////////////////////////\n\r");
	printf("The size of u8  is %d bytes\n", sizeof(u8)) ;
	printf("The size of u16 is %d bytes\n", sizeof(u16));
	printf("The size of u32 is %d bytes\n", sizeof(u32));
	printf("The size of u64 is %d bytes\n", sizeof(u64));
	printf("//////////////////////////////////////////////////////\n\r");
	printf("The size of s8  is %d bytes\n", sizeof(s8)) ;
	printf("The size of s16 is %d bytes\n", sizeof(s16));
	printf("The size of s32 is %d bytes\n", sizeof(s32));
	printf("The size of s64 is %d bytes\n", sizeof(s64));
	printf("//////////////////////////////////////////////////////\n\r");
	printf("The size of f32 is %d bytes\n", sizeof(f32));
	printf("The size of f64 is %d bytes\n", sizeof(f64));
	printf("//////////////////////////////////////////////////////\n\r");

	/** Bitwise Operation **/
	u8 u8Reg0 = LBTY_u8ZERO;
	u8 u8Reg1 = LBTY_u8ZERO;
	u16 u16Reg = LBTY_u16ZERO;
	printf("\n\r\n\r");
	printf("######################################################\n\r");
	printf("A = %#04X\t", u8Reg0);
	SET_BIT(u8Reg0, 0);
	printf("SET_BIT(%02i)\tA = %#X\n", 0, u8Reg0);

	printf("A = %#04X\t", u8Reg0);
	CLR_BIT(u8Reg0, 0);
	printf("CLR_BIT(%02i)\tA = %#X\n", 0, u8Reg0);

	printf("B = %#04X\t", u8Reg1);
	TOG_BIT(u8Reg1, 10);
	printf("TOG_BIT(%02i)\tB = %#X\n", 10, u8Reg1);
	printf("B = %#04X\t", u8Reg1);
	TOG_BIT(u8Reg1, 10);
	printf("TOG_BIT(%02i)\tB = %#X\n", 10, u8Reg1);
	printf("//////////////////////////////////////////////////////\n\r");
	printf("C = %#04X\t", u16Reg);
	SET_BIT(u16Reg, 1);
	printf("SET_BIT(%02i)\tC = %#X\n", 1, u16Reg);

	printf("C = %#04X\t", u16Reg);
	CLR_BIT(u16Reg, 1);
	printf("CLR_BIT(%02i)\tC = %#X\n", 1, u16Reg);

	printf("C = %#04X\t", u16Reg);
	TOG_BIT(u16Reg, 15);
	printf("TOG_BIT(%02i)\tC = %#X\n", 15, u16Reg);
	printf("C = %#04X\t", u16Reg);
	TOG_BIT(u16Reg, 15);
	printf("TOG_BIT(%02i)\tC = %#X\n", 15, u16Reg);
	printf("######################################################\n\r");

	printf("######################################################\n\r");
	printf("A = %#04X\t", u8Reg0);
	SET_MASK(u8Reg0, 3);
	printf("SET_MASK(%02i)\tA = %#X\n", 3, u8Reg0);

	printf("A = %#04X\t", u8Reg0);
	CLR_MASK(u8Reg0, 3);
	printf("CLR_MASK(%02i)\tA = %#X\n", 3, u8Reg0);

	printf("B = %#04X\t", u8Reg1);
	TOG_MASK(u8Reg1, 48);
	printf("TOG_BIT(%02i)\tB = %#X\n", 48, u8Reg1);
	printf("B = %#04X\t", u8Reg1);
	TOG_MASK(u8Reg1, 48);
	printf("TOG_BIT(%02i)\tB = %#X\n", 48, u8Reg1);
	printf("//////////////////////////////////////////////////////\n\r");
	printf("C = %#04X\t", u16Reg);
	SET_MASK(u16Reg, 3);
	printf("SET_MASK(%02i)\tC = %#X\n", 3, u16Reg);

	printf("C = %#04X\t", u16Reg);
	CLR_MASK(u16Reg, 3);
	printf("CLR_MASK(%02i)\tC = %#X\n", 3, u16Reg);

	printf("C = %#04X\t", u16Reg);
	TOG_MASK(u16Reg, 55);
	printf("TOG_MASK(%02i)\tC = %#X\n", 55, u16Reg);
	printf("C = %#04X\t", u16Reg);
	TOG_MASK(u16Reg, 55);
	printf("TOG_MASK(%02i)\tC = %#X\n", 55, u16Reg);
	printf("######################################################\n\r");

	printf("######################################################\n\r");
	printf("A = %#04X\t", u8Reg0);
	SET_REG(u8Reg0, 0);
	printf("SET_REG(%02i)\tA = %#X\n", 0, u8Reg0);

	printf("A = %#04X\t", u8Reg0);
	CLR_REG(u8Reg0, 3);
	printf("CLR_REG(%02i)\tA = %#X\n", 3, u8Reg0);

	printf("B = %#04X\t", u8Reg1);
	TOG_REG(u8Reg1, 1);
	printf("TOG_REG(%02i)\tB = %#X\n", 1, u8Reg1);
	printf("B = %#04X\t", u8Reg1);
	TOG_REG(u8Reg1, 1);
	printf("TOG_REG(%02i)\tB = %#X\n", 1, u8Reg1);
	printf("//////////////////////////////////////////////////////\n\r");
	printf("C = %#04X\t", u16Reg);
	SET_REG(u16Reg, 3);
	printf("SET_REG(%02i)\tC = %#X\n", 3, u16Reg);

	printf("C = %#04X\t", u16Reg);
	CLR_REG(u16Reg, 7);
	printf("CLR_REG(%02i)\tC = %#X\n", 7, u16Reg);

	printf("C = %#04X\t", u16Reg);
	TOG_REG(u16Reg, 3);
	printf("TOG_REG(%02i)\tC = %#X\n", 3, u16Reg);
	printf("C = %#04X\t", u16Reg);
	TOG_REG(u16Reg, 7);
	printf("TOG_REG(%02i)\tC = %#X\n", 7, u16Reg);
	printf("######################################################\n\r");

	printf("######################################################\n\r");
	printf("A = %#04X\t", u8Reg0);
	ASSIGN_BIT(u8Reg0, 3, 3);
	printf("ASSIGN_NIB(%02i , %02i)\tA = %#X\n", 3, 3, u8Reg0);
	printf("C = %#04X\t", u16Reg);
	ASSIGN_BIT(u16Reg, 3, 3);
	printf("ASSIGN_NIB(%02i , %02i)\tC = %#X\n", 3, 3, u16Reg);

	printf("A = %#04X\t", u8Reg0);
	ASSIGN_BIT(u8Reg0, 11, 3);
	printf("ASSIGN_BIT(%02i , %02i)\tA = %#X\n", 11, 3, u8Reg0);
	printf("C = %#04X\t", u16Reg);
	ASSIGN_BIT(u16Reg, 11, 3);
	printf("ASSIGN_BIT(%02i , %02i)\tC = %#X\n", 11, 3, u16Reg);
	printf("//////////////////////////////////////////////////////\n\r");
	printf("B = %#04X\t", u8Reg1);
	ASSIGN_NIB(u8Reg1, 3, 3);
	printf("ASSIGN_NIB(%02i , %02i)\tB = %#X\n", 3, 3, u8Reg1);
	printf("C = %#04X\t", u16Reg);
	ASSIGN_NIB(u16Reg, 3, 3);
	printf("ASSIGN_NIB(%02i , %02i)\tC = %#X\n", 3, 3, u16Reg);

	printf("B = %#04X\t", u8Reg1);
	ASSIGN_NIB(u8Reg1, 11, 3);
	printf("ASSIGN_NIB(%02i , %02i)\tB = %#X\n", 11, 3, u8Reg1);
	printf("C = %#04X\t", u16Reg);
	ASSIGN_NIB(u16Reg, 11, 3);
	printf("ASSIGN_NIB(%02i , %02i)\tC = %#X\n", 11, 3, u16Reg);
	printf("//////////////////////////////////////////////////////\n\r");
	printf("C = %#04X\t", u16Reg);
	ASSIGN_BYTE(u16Reg, 7, 7);
	printf("ASSIGN_BYTE(%02i , %02i)\tC = %#X\n", 7, 7, u16Reg);
	printf("C = %#04X\t", u16Reg);
	ASSIGN_BYTE(u16Reg, 7, 8);
	printf("ASSIGN_BYTE(%02i , %02i)\tC = %#X\n", 7, 8, u16Reg);

	printf("C = %#04X\t", u16Reg);
	ASSIGN_BYTE(u16Reg, 11, 3);
	printf("ASSIGN_BYTE(%02i , %02i)\tC = %#X\n", 11, 3, u16Reg);
	printf("C = %#04X\t", u16Reg);
	ASSIGN_BYTE(u16Reg, 11, 12);
	printf("ASSIGN_BYTE(%02i , %02i)\tC = %#X\n", 11, 12, u16Reg);
	printf("######################################################\n\r");

	u8Reg0 = 0x3C;
	u8Reg1 = 0xA5;
	u16Reg = 0xDEAD;

	printf("######################################################\n\r");
	printf("A = %#04X\tGET_BIT(%02i)\tA = %#X\n", u8Reg0, 0, GET_BIT(u8Reg0, 0));
	printf("B = %#04X\tGET_BIT(%02i)\tB = %#X\n", u8Reg1, 0, GET_BIT(u8Reg1, 0));
	printf("C = %#04X\tGET_BIT(%02i)\tC = %#X\n", u16Reg, 0, GET_BIT(u16Reg, 0));

	printf("A = %#04X\tGET_BIT(%02i)\tA = %#X\n", u8Reg0, 10, GET_BIT(u8Reg0, 10));
	printf("B = %#04X\tGET_BIT(%02i)\tB = %#X\n", u8Reg1, 10, GET_BIT(u8Reg1, 10));
	printf("C = %#04X\tGET_BIT(%02i)\tC = %#X\n", u16Reg, 10, GET_BIT(u16Reg, 10));
	printf("//////////////////////////////////////////////////////\n\r");
	printf("A = %#04X\tGET_NIB(%02i)\tA = %#X\n", u8Reg0, 7, GET_NIB(u8Reg0, 7));
	printf("B = %#04X\tGET_NIB(%02i)\tB = %#X\n", u8Reg1, 7, GET_NIB(u8Reg1, 7));
	printf("C = %#04X\tGET_NIB(%02i)\tC = %#X\n", u16Reg, 7, GET_NIB(u16Reg, 7));

	printf("A = %#04X\tGET_NIB(%02i)\tA = %#X\n", u8Reg0, 10, GET_NIB(u8Reg0, 10));
	printf("B = %#04X\tGET_NIB(%02i)\tB = %#X\n", u8Reg1, 10, GET_NIB(u8Reg1, 10));
	printf("C = %#04X\tGET_NIB(%02i)\tC = %#X\n", u16Reg, 10, GET_NIB(u16Reg, 10));
	printf("//////////////////////////////////////////////////////\n\r");
	printf("A = %#04X\tGET_BYTE(%02i)\tA = %#X\n", u8Reg0, 4, GET_BYTE(u8Reg0, 4));
	printf("B = %#04X\tGET_BYTE(%02i)\tB = %#X\n", u8Reg1, 4, GET_BYTE(u8Reg1, 4));
	printf("C = %#04X\tGET_BYTE(%02i)\tC = %#X\n", u16Reg, 4, GET_BYTE(u16Reg, 4));

	printf("A = %#04X\tGET_BYTE(%02i)\tA = %#X\n", u8Reg0, 11, GET_BYTE(u8Reg0, 11));
	printf("B = %#04X\tGET_BYTE(%02i)\tB = %#X\n", u8Reg1, 11, GET_BYTE(u8Reg1, 11));
	printf("C = %#04X\tGET_BYTE(%02i)\tC = %#X\n", u16Reg, 11, (u8)GET_BYTE(u16Reg, 11));
	printf("######################################################\n\r");

	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
