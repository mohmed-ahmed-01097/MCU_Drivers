/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LMD_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LMD_INT_H_
#define LMD_INT_H_

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
/* Description :    LED Matrix Display initialization						  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void LMD_vidInit(void);

/* ************************************************************************** */
/* Description :    LED Matrix Display Put char Output						  */
/* Input       :	pu8Display												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LMD_u8Display(u8* const pu8Display);

/* ************************************************************************** */
/* Description :    LED Matrix Display Put Show char						  */
/* Input       :	u8Char													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LMD_u8Char(u8 u8Char);

/* ************************************************************************** */
/* Description :    LED Matrix Display Show char							  */
/* Input       :	u8Char													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LMD_u8String(u8* pu8Str);

/* ************************************************************************** */
/* Description :    LED Matrix Display Show String							  */
/* Input       :	pu8Str													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LMD_u8String(u8* pu8Str);

/* ************************************************************************** */
/* Description :    LED Matrix Display Update shifting						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LMD_u8Update(void);


#endif /* LMD_INT_H_ */
/*************************** E N D (LMD_int.h) ******************************/
