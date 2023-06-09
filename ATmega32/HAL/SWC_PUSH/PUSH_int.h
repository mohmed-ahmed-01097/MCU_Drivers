/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PUSH_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Mar 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef PUSH_INT_H_
#define PUSH_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	PUSH_PULL_UP = (u8)0u,
	PUSH_PULL_DOWN
}PUSH_tenuConnection;

typedef enum{
	PUSH_RELEASED = (u8)0u,
	PUSH_PRESSED
}PUSH_tenuStatus;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if 	AMIT_KIT
#define PUSH_NUM		3u
#elif	ETA32_KIT
#define PUSH_NUM		4u
#else
#define PUSH_NUM		3u
#endif

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
/* Description : Initialize the Push Button direction						  */
/* Input       :	u8PushNum												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void PUSH_vidInit(u8 u8PushNum);

/* ************************************************************************** */
/* Description :    Get the Push Button value								  */
/* Input       :	u8PushNum												  */
/* Input/Output:    pu8State												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus PUSH_u8GetPushState(u8 u8PushNum, u8* pu8State);

#endif /* PUSH_INT_H_ */
/*************************** E N D (PUSH_int.h) ******************************/
