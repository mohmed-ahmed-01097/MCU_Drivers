/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SEG_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SEG_PRIV_H_
#define SEG_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
#ifdef SEG_PIN_COM0
	SEG_COM0 = (u8)0u,
#endif
#ifdef SEG_PIN_COM1
	SEG_COM1,
#endif
#ifdef SEG_PIN_COM2
	SEG_COM2,
#endif
#ifdef SEG_PIN_COM3
	SEG_COM3,
#endif
#ifdef SEG_PIN_COM4
	SEG_COM4,
#endif
#ifdef SEG_PIN_COM5
	SEG_COM5,
#endif
	SEG_NUM
}SEG_tenuCom;

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

#endif /* SEG_PRIV_H_ */
/*************************** E N D (SEG_priv.h) ******************************/
