/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : INT_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef INT_INT_H_
#define INT_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum {
	INT0 = (u8)0u,
	INT1,
	INT2
}INT_tenuPin;

typedef enum{
    INT_Low_Level = (u8)0u,
	INT_Logic_Change,
	INT_Falling_Edge,
	INT_Rising_Edge,

	INT2_Falling_Edge = (u8)0u,
	INT2_Rising_Edge
}INT_tenuSenseControl;      // Interrupt Sense Control

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
/* Description : 	Initialize the INT pins direction and SenseControl		  */
/* Input       :	u8INT_Num												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidInit(u8 u8INT_Num);

/* ************************************************************************** */
/* Description :  	Set the SenseControl 									  */
/* Input       :	u8INT_Num, u8INT_SC										  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidSetSenseControl(u8 u8INT_Num, INT_tenuSenseControl u8INT_SC);

/* ************************************************************************** */
/* Description :  	Enable the INT		 									  */
/* Input       :	u8INT_Num												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidEnable(u8 u8INT_Num);

/* ************************************************************************** */
/* Description :  	Disable the INT		 									  */
/* Input       :	u8INT_Num												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidDisable(u8 u8INT_Num);

/* ************************************************************************** */
/* Description :  	Set the INT Flag	 									  */
/* Input       :	u8INT_Num												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidSetFlag(u8 u8INT_Num);

/* ************************************************************************** */
/* Description :  	Reset the INT Flag	 									  */
/* Input       :	u8INT_Num												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidResetFlag(u8 u8INT_Num);

/* ************************************************************************** */
/* Description :  	Interrupt Callback	 									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void INT_vidSetCallBack(u8 u8INT_Num, void (*pvidCallback)(void));

#endif /* INT_INT_H_ */
/*************************** E N D (INT_int.h) ******************************/
