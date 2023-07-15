/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PUSH_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef PUSH_PRIV_H_
#define PUSH_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
#ifdef PUSH0
	PUSH_0 = (u8)0u
#endif
#ifdef PUSH1
	,PUSH_1
#endif
#ifdef PUSH2
	,PUSH_2
#endif
#ifdef PUSH3
	,PUSH_3
#endif
#ifdef PUSH4
	,PUSH_4
#endif
#ifdef PUSH5
	,PUSH_5
#endif
#ifdef PUSH6
	,PUSH_6
#endif
#ifdef PUSH7
	,PUSH_7
#endif
	,PUSH_Num
}PUSH_tenuPushNum;

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


#endif /* PUSH_PRIV_H_ */
/*************************** E N D (PUSH_priv.h) ******************************/
