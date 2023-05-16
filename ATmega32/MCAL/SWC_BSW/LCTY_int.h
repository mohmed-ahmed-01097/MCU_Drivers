/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LCTY_int.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 26, 2023												  */
/* description : Compiler Library											  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LCTY_INT_H_
#define LCTY_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* prog memory attribute */
#define LCTY_PROGMEM 				__attribute__((__progmem__))

/* pure attribute */
#define LCTY_PURE 					__attribute__((__pure__))

/* Abstraction for inlining */
//#define LCTY_INLINE  				static inline
#define LCTY_INLINE  				__attribute__((always_inline)) static inline

/* define function as interrupt handler */
#define LCTY_INTERRUPT 				__attribute__((interrupt))

/* Memory packed to pass Memory padding */
#define CTY_PACKED 					__attribute__((__packed__))

/* Const attribute */
#define LCTY_CONST 					__attribute__((__const__))

/* place variable in direct page */
#define LCTY_DPAGE 					__attribute__((dp))

/* do not place variable in direct page */
#define LCTY_NODPAGE 				__attribute__((nodp))

/* Sections */
#define LCTY_SECTION(section)		__attribute__((section( # section)))

/* Abstraction for assembly command */
# define LCTY_ASM(cmd)  			__asm__ __volatile__ ( # cmd ::)

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* LCTY_INT_H_ */
/*************************** E N D (LCTY_int.h) ******************************/
