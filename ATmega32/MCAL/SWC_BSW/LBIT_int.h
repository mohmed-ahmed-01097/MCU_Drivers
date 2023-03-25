/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LBIT_int.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 24, 2023												  */
/* description : Bitwise Library											  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LBIT_INT_H_
#define LBIT_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** Bitwise Operation **/
#define SET_BIT(REG, bit) 							((REG) |=  (1u<<bit))
#define CLR_BIT(REG, bit) 							((REG) &= ~(1u<<bit))
#define TOG_BIT(REG, bit) 							((REG) ^=  (1u<<bit))

#define SET_MASK(REG, MASK) 						((REG) |=  (MASK))
#define CLR_MASK(REG, MASK) 						((REG) &= ~(MASK))
#define TOG_MASK(REG, MASK) 						((REG) ^=  (MASK))

#define SET_REG(REG) 								((REG) |= ~(0u))
#define CLR_REG(REG) 								((REG) &=  (0u))
#define TOG_REG(REG) 								((REG) ^= ~(0u))

#define GET_BIT(REG, bit) 							(((REG) & (0x01u<<(bit)))>>(bit))
#define GET_NIB(REG, bit) 							(((REG) & (0x0Fu<<(bit)))>>(bit))
#define GET_BYTE(REG, bit) 							(((REG) & (0xFFu<<(bit)))>>(bit))

#define ASSIGN_BIT(REG, bit, value) 				((REG) = ((REG) & ~(0x01u<<(bit)))	| (((value) & 0x01u)<<(bit)))
#define ASSIGN_NIB(REG, bit, value) 				((REG) = ((REG) & ~(0x0Fu<<(bit))) 	| (((value) & 0x0Fu)<<(bit)))
#define ASSIGN_BYTE(REG, value) 					((REG) = ((REG) &  (0x00u       )) 	|  ((value) & 0xFFu)		)

#define CON_u8Bits(b0, b1, b2, b3, b4, b5, b6, b7)											\
													(0b##b7##b6##b5##b4##b3##b2##b1##b0)

#define CON_u16Bits(b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15)	\
													(0b##b15##b14##b13##b12##b11##b10##b9##b8##b7##b6##b5##b4##b3##b2##b1##b0)

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* LBIT_INT_H_ */
/*************************** E N D (LBIT_int.h) ******************************/