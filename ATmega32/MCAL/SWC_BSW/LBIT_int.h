/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LBIT_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
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

#define _BV(bit)										(1u<<(bit))

/** Bitwise Operation **/
#define SET_BIT(REG, bit) 							((REG) |=  (1u<<(bit)))
#define CLR_BIT(REG, bit) 							((REG) &= ~(1u<<(bit)))
#define TOG_BIT(REG, bit) 							((REG) ^=  (1u<<(bit)))

#define SET_BYTE(REG, bit) 							((REG) |=  (0xFFu<<(bit)))
#define CLR_BYTE(REG, bit) 							((REG) &= ~(0xFFu<<(bit)))
#define TOG_BYTE(REG, bit) 							((REG) ^=  (0xFFu<<(bit)))

#define SET_MASK(REG, MASK) 						((REG) |=  (MASK))
#define CLR_MASK(REG, MASK) 						((REG) &= ~(MASK))
#define TOG_MASK(REG, MASK) 						((REG) ^=  (MASK))
#define GET_MASK(REG, MASK) 						((REG) &   (MASK))

#define SET_REG(REG) 								((REG)  = ~(0u))
#define CLR_REG(REG) 								((REG)  =  (0u))
#define TOG_REG(REG) 								((REG) ^= ~(0u))

#define GET_BIT(REG, bit) 							(((REG)>>(bit)) & 0x01u)
#define GET_NIB(REG, bit) 							(((REG)>>(bit)) & 0x0Fu)
#define GET_BYTE(REG, bit) 							(((REG)>>(bit)) & 0xFFu)

#define ASSIGN_BIT(REG, bit, value) 				((REG) = ((REG) & ~(0x01u<<(bit)))	| (((value) & 0x01u)<<(bit)))
#define ASSIGN_NIB(REG, bit, value) 				((REG) = ((REG) & ~(0x0Fu<<(bit))) 	| (((value) & 0x0Fu)<<(bit)))
#define ASSIGN_BYTE(REG, bit, value) 				((REG) = ((REG) & ~(0xFFu<<(bit))) 	| (((value) & 0xFFu)<<(bit)))

/*
#define ASSIGN_BIT(REG,bit,value)					do{										\
                                             	 	 REG &= ~(0x01u<<bit);					\
                                             	 	 REG |=  ((value & 0x01u)<<bit);		\
                                            		}while(0)
*/

/*           bits together in an u8 register          */
#define CON_u8Bits(b7, b6, b5, b4, b3, b2, b1, b0)											\
													(0b##b7##b6##b5##b4##b3##b2##b1##b0)

/*           bits together in an u16 register         */
#define CON_u16Bits(b15, b14, b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0)	\
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
