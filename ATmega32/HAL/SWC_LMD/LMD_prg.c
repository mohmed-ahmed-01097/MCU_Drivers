/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LMD_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LMD_int.h"
#include "LMD_priv.h"
#include "LMD_cfg.h"

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

static u8 pu8Array_GLB[LMD_MAX_ARRAY_LEN];
static u8 u8TempChar_GLB;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :    LED Matrix Display initialization						  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void LMD_vidInit(void){
	GPIO_u8SetPortDirection(LMD_ROW_PORT, PORT_OUTPUT);
	GPIO_u8SetPortValue    (LMD_ROW_PORT, LMD_ROW_ACTIVE);
	GPIO_u8SetPortDirection(LMD_COL_PORT, PORT_OUTPUT);
	GPIO_u8SetPortValue    (LMD_COL_PORT, LMD_COL_ACTIVE);

	vidMyDelay_ms(500);

	GPIO_u8SetPortValue    (LMD_ROW_PORT, (u8)~LMD_ROW_ACTIVE);
	GPIO_u8SetPortValue    (LMD_COL_PORT, (u8)~LMD_COL_ACTIVE);
}

/* ************************************************************************** */
/* Description :    LED Matrix Display Put char Output						  */
/* Input       :	pu8Display												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LMD_u8Display(u8* const pu8Display){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	/** TODO: Update LDM with decoder **/

#if LMD_MUX_TYPE ==	LMD_COL_MUX
	for(u8 i = LMD_MAX_ROW_NUM ; i-- ; ){
		u8 u8ColChar = LBTY_u8ZERO;
		for(u8 j = LMD_MAX_ROW_NUM ; j-- ; ){
			u8ColChar |= GET_BIT(pu8Display[j], i)<<j;
		}

		GPIO_u8SetPortValue  (LMD_ROW_PORT, ~u8ColChar);
		GPIO_u8TogglePinValue(LMD_COL_PORT, i);
		vidMyDelay_ms(5);
		//GPIO_u8TogglePinValue(LMD_COL_PORT, i);
		u8RetErrorState = GPIO_u8SetPortValue    (LMD_COL_PORT, (u8)~LMD_COL_ACTIVE);
	}
#endif
#if LMD_MUX_TYPE ==	LMD_ROW_MUX
	for(u8 i = LMD_MAX_COL_NUM ; i-- ; ){
		GPIO_u8SetPortValue  (LMD_COL_PORT, pu8Display[i]);
		GPIO_u8TogglePinValue(LMD_ROW_PORT, i);
		vidMyDelay_ms(5);
		//GPIO_u8TogglePinValue(LMD_ROW_PORT, i);
		u8RetErrorState = GPIO_u8SetPortValue    (LMD_ROW_PORT, (u8)~LMD_ROW_ACTIVE);
	}
#endif
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    LED Matrix Display Show char							  */
/* Input       :	u8Char													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LMD_u8Char(u8 u8Char){
	return LMD_u8Display((u8*)IMAGES[u8Char]);
}

/* ************************************************************************** */
/* Description :    LED Matrix Display Show String							  */
/* Input       :	pu8Str													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LMD_u8String(u8* pu8Str){
	for(u8 i = 0 ; *pu8Str ; i++){
		pu8Array_GLB[i] = *pu8Str++;
	}
	return LMD_u8Display((u8*)IMAGES[0]);
}

/* ************************************************************************** */
/* Description :    LED Matrix Display Update shifting						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LMD_u8Update(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	static u8 u8Refresh = LBTY_u8ZERO;
	static u8 u8Shift   = LBTY_u8ZERO;
	static u8 u8index   = LBTY_u8ZERO;
	static u8 pu8Char[LMD_MAX_COL_NUM] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	if(u8Refresh++ > LMD_REFRESH_RATE){
		u8Refresh =  LBTY_u8ZERO;
		u8TempChar_GLB = pu8Array_GLB[u8index];
		for(u8 i = 0 ; i<LMD_MAX_COL_NUM ; i++){
			pu8Char[i] = pu8Char[i] >> 1 | (GET_BIT(IMAGES[u8TempChar_GLB][i], u8Shift)) << (LMD_MAX_COL_NUM - 1);
		}
		if(u8Shift<LMD_MAX_COL_NUM){
			u8Shift++;
		}else{
			u8Shift = LBTY_u8ZERO;
			u8index++;
			if(!pu8Array_GLB[u8index]){
				u8index = 0;
				u8RetErrorState = LBTY_NOK;
			}
		}
	}

	LMD_u8Display(pu8Char);
	return u8RetErrorState;
}

/*************************** E N D (LMD_prg.c) ******************************/
