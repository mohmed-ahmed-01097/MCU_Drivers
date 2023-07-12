/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LCD_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 31, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "LCD_int.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** TODO: sprintf function **/
//#include <stdlib.h>
//#include <stdio.h>
//
//	sprintf (str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);

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
/* Description : 	Initialize the LCD configuration and pins				  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void LCD_vidInit(void){
	LCD_vidInitPins();
	LCD_vidInitMode();
	LCD_u8Home();
	LCD_u8FunctionSet();
	LCD_u8EntryMode(LCD_Entry_Inc);
	LCD_u8DisplayMode(LCD_Display_OFF);
	LCD_u8ClrDisplay();
	vidMyDelay_ms(LCD_DELAY_CMD_MAX);
	LCD_u8DisplayMode(LCD_Cursor_OFF);
}

/* ************************************************************************** */
/* Description :  	Set Page of LCD Column by Column						  */
/* Input/Output:	pu8String1, pu8String2									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetPage(const u8 pu8String1[],const u8 pu8String2[]){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	for(u8 i = 0, j = 0 ; i<LCD_COL_NUM && *pu8String1 && *pu8String2 ; i++){
		if(*pu8String1 == '@'){
			if((u8RetErrorState = LCD_u8SetSpecialCharIndex(j++, i, 0))){
				break;
			}
		}else{
			if((u8RetErrorState = LCD_u8SetChar(*pu8String1, i, 0))){
				break;
			}
		}
		if(*pu8String2 == '@'){
			if((u8RetErrorState = LCD_u8SetSpecialCharIndex(j++, i, 1))){
				break;
			}
		}else{
			if((u8RetErrorState = LCD_u8SetChar(*pu8String2, i, 1))){
				break;
			}
		}
#if (LCD_ROW_NUM >= LCD_ROW_NUM_4)
		if(*(pu8String1 + LCD_COL_NUM) == '@'){
			if((u8RetErrorState = LCD_u8SetSpecialCharIndex(j++, i, 2))){
				break;
			}
		}else{
			if((u8RetErrorState = LCD_u8SetChar(*(pu8String1 + LCD_COL_NUM), i, 2))){
				break;
			}
		}
		if(*(pu8String2 + LCD_COL_NUM) == '@'){
			if((u8RetErrorState = LCD_u8SetSpecialCharIndex(j++, i, 3))){
				break;
			}
		}else{
			if((u8RetErrorState = LCD_u8SetChar(*(pu8String2 + LCD_COL_NUM), i, 3))){
				break;
			}
		}
#endif
		vidMyDelay_ms(LCD_DELAY_WAIT);
		pu8String1++;
		pu8String2++;
	}
	vidMyDelay_ms(LCD_DELAY_PAGE);
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set String at X Column and Y Row						  */
/* Input       :	u8Col, u8Row											  */
/* Input/Output:	pu8String												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetString(const u8 pu8String[], u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LCD_u8GoTo_XY(u8Col, u8Row);
	while(*pu8String){
		if(u8RetErrorState)			break;
		u8RetErrorState = LCD_u8CHAR_W(*(pu8String++));
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Char at X Column and Y Row							  */
/* Input       :	u8Char, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetChar(u8 u8Char, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(LCD_u8GoTo_XY(u8Col, u8Row)){
		u8RetErrorState = LBTY_NOK;
	}else{
		u8RetErrorState = LCD_u8CHAR_W(u8Char);
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Get Num at X Column and Y Row							  */
/* Input       :	u8Col, u8Row											  */
/* Input/Output:	ps32Num													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8GetNum(s32* ps32Num, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u8 u8Char = LBTY_u8ZERO;
	u8 u8SignChar = LBTY_RESET;
	u8 u8FirstCharFlag = LBTY_SET;
	u32 u32NumRead = LBTY_u32ZERO;

	while(!u8RetErrorState){
		if(LCD_u8GoTo_XY(u8Col++, u8Row)){
			u8RetErrorState = LBTY_NULL_POINTER;
		}else{
			u8RetErrorState = LCD_u8CHAR_R(&u8Char);
			if(u8FirstCharFlag && (u8Char=='-' || u8Char=='+')){
				if(u8Char=='-')		{	u8SignChar = LBTY_SET; 	}
				else if(u8Char=='+'){	u8SignChar = LBTY_RESET;}
				u8FirstCharFlag = LBTY_RESET;
				continue;
			}else if(u8Char>='0' && u8Char<='9'){
				u32NumRead = (u32NumRead * 10) + (u8Char - '0');
				continue;
			}else if(u8Char == '.'){
			}
			break;
		}
	}
	*ps32Num = (u8SignChar? (s32)u32NumRead * -1 : (s32)u32NumRead);
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Num at X Column and Y Row							  */
/* Input       :	s32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetNum(s32 s32Num, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u8 u8Log = 1u;
	u32 u32Factor = 1u;
	u32 u32NumLoc = (u32)((s32Num >= (s32)LBTY_u32ZERO) ? s32Num : s32Num * -1);

	if(LCD_u8GoTo_XY(u8Col, u8Row)){
		u8RetErrorState = LBTY_NOK;
	}else{
		for(u32 i = u32NumLoc ; i/=10 ; u8Log++, u32Factor*=10);
		if(s32Num<0){
			u8RetErrorState = LCD_u8CHAR_W('-');
		}
		while(u8Log--){
			u8RetErrorState = LCD_u8CHAR_W((u8)((u32NumLoc/u32Factor)%10u) + '0');
			u32Factor/=10;
		}
		LCD_u8CHAR_W(' ');
		LCD_u8ShiftMode(LCD_Cursor_Shift_Left);
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Get Real float Num at X Column and Y Row				  */
/* Input       :	u8Col, u8Row											  */
/* Input/Output:	pf32Num													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8GetFloat(f32* pf32Num, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u8 u8Log = 1u;
	u32 u32Factor = 1u;
	u8 u8Char = LBTY_u8ZERO;
	s32 s32NumL = LBTY_u32ZERO;
	s32 s32NumR = LBTY_u32ZERO;

	u8RetErrorState = LCD_u8GetNum(&s32NumL, u8Col, u8Row);
	if(u8RetErrorState == LBTY_OK){

		for(u32 i = (u32)((s32NumL >= (s32)LBTY_u32ZERO) ? s32NumL : s32NumL * -1.0) ; i/=10 ; u8Log++);
		u8Col += u8Log + ((s32NumL >= (s32)LBTY_u32ZERO) ? 1u : 2u);

		while(!u8RetErrorState){
			if(LCD_u8GoTo_XY(u8Col++, u8Row)){
				u8RetErrorState = LBTY_NULL_POINTER;
			}else{
				u8RetErrorState = LCD_u8CHAR_R(&u8Char);
				if(u8Char>='0' && u8Char<='9'){
					s32NumR = (s32NumR * 10) + (u8Char - '0');
					u32Factor *= 10;
					continue;
				}else if(u8Char == '.'){
				}
				break;
			}
		}
	}
	if(s32NumL >= (s32)LBTY_u32ZERO){
		*pf32Num = s32NumL + (f32)s32NumR / u32Factor;
	}else{
		*pf32Num = s32NumL - (f32)s32NumR / u32Factor;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Real float Num at X Column and Y Row				  */
/* Input       :	f32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetFloat(f32 f32Num, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState =
			LCD_u8SetNum((s32)f32Num, u8Col, u8Row);
	if(u8RetErrorState == LBTY_OK){
		LCD_u8CHAR_W('.');

		if(f32Num < 0.0){
			f32Num *= -1.0;
			u8Col++;
		}

		u32 u32Lcd_R = (u32)((u32)(f32Num * LCD_FLOAT_MUL) % LCD_FLOAT_MUL);

		for(u32 u32Factor = LCD_FLOAT_MUL; u32Factor/=10 ; ){
			LCD_u8CHAR_W(((u32Lcd_R/u32Factor)%10u) + '0');
		}
		LCD_u8CHAR_W(' ');
		LCD_u8CHAR_W(' ');
		LCD_u8ShiftMode(LCD_Cursor_Shift_Left);
		LCD_u8ShiftMode(LCD_Cursor_Shift_Left);
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Num Rise at X Column and Y Row						  */
/* Input       :	s32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetNum_Rise(s32 s32Num, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u8 u8SignChar = LBTY_RESET;
	u32 u32NumNew = LBTY_u32ZERO;
	u32 u32NumRead = LBTY_u32ZERO;

	s32 s32LcdNum = (s32)LBTY_u32ZERO;
	u8RetErrorState = LCD_u8GetNum(&s32LcdNum, u8Col, u8Row);

	if(u8RetErrorState == LBTY_OK){
		if(s32Num >= (s32)LBTY_u32ZERO){
			u32NumNew = (u32)s32Num;
			u8SignChar = LBTY_RESET;
			if((s32LcdNum < (s32)LBTY_u32ZERO)){
				u32NumRead = (u32)(s32LcdNum * -1);
			}else{
				u32NumRead = (u32)s32LcdNum;
			}
		}else{
			u32NumNew = (u32)(s32Num * -1);
			u8SignChar = LBTY_SET;
			if((s32LcdNum < (s32)LBTY_u32ZERO)){
				u32NumRead = (u32)(s32LcdNum * -1);
			}else{
				u32NumRead = (u32)s32LcdNum;
				s32LcdNum *= -1;
			}
		}

		u32 u32Step = LCD_FLOAT_MUL;
		if(u32NumRead != u32NumNew){
			if(u32NumRead < u32NumNew){
				while(u32Step){
					if(u32NumNew >= (u32NumRead + u32Step)){
						u32NumRead += u32Step;
						break;
					}
					u32Step /= 10;
				}
			}else if(u32NumRead > u32NumNew){
				while(u32Step){
					if(u32NumNew <= (u32NumRead - u32Step)){
						while(u32Step){
							if(u32NumRead >= u32Step){
								u32NumRead -= u32Step;
								break;
							}
							u32Step /= 10;
						}
						break;
					}
					u32Step /= 10;
				}
			}
			s32LcdNum = u8SignChar ? (s32)u32NumRead * -1 : (s32)u32NumRead;
			LCD_u8SetNum(s32LcdNum, u8Col, u8Row);
			u8RetErrorState = LBTY_NOK;
		}

	}else{
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Real float Num Rise at X Column and Y Row			  */
/* Input       :	f32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetFloat_Rise(f32 f32Num, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u32 u32NumNew = LBTY_u32ZERO;
	u32 u32NumRead = LBTY_u32ZERO;

	f32 f32LcdRead = 0.0f;
	u8RetErrorState = LCD_u8GetFloat(&f32LcdRead, u8Col, u8Row);

	if(u8RetErrorState == LBTY_OK){

		/** TODO: Redesign this function with float work **/

		u8RetErrorState = LCD_u8SetNum_Rise((s32)f32Num, u8Col, u8Row);

		if(u8RetErrorState){
			LCD_u8CHAR_W('.');
		}

		if(f32Num >= (f32)LBTY_u32ZERO){
			u32NumNew = ((u32)( f32Num * LCD_FLOAT_MUL + 0.5f) % (u32)LCD_FLOAT_MUL);
		}else{
			u32NumNew = ((u32)(-f32Num * LCD_FLOAT_MUL + 0.5f) % (u32)LCD_FLOAT_MUL);
		}
		if(f32LcdRead >= (f32)LBTY_u32ZERO){
			u32NumRead = ((u32)( f32LcdRead * LCD_FLOAT_MUL + 0.5f) % (u32)LCD_FLOAT_MUL);
		}else{
			u32NumRead = ((u32)(-f32LcdRead * LCD_FLOAT_MUL + 0.5f) % (u32)LCD_FLOAT_MUL);
		}

		u32 u32Step = LCD_FLOAT_MUL;
		if(!u8RetErrorState && u32NumRead != u32NumNew){
			if(u32NumRead < u32NumNew){
				while(u32Step){
					if(u32NumNew >= (u32NumRead + u32Step)){
						u32NumRead += u32Step;
						u8RetErrorState = LBTY_NOK;
						break;
					}
					u32Step /= 10;
				}
			}else if(u32NumRead > u32NumNew){
				while(u32Step){
					if(u32NumNew <= (u32NumRead - u32Step)){
						while(u32Step){
							if(u32NumRead >= u32Step){
								u32NumRead -= u32Step;
								u8RetErrorState = LBTY_NOK;
								break;
							}
							u32Step /= 10;
						}
						break;
					}
					u32Step /= 10;
				}
			}else{
				u8RetErrorState = LBTY_OK;
			}
		}
		if(u8RetErrorState){
			for(u32 u32Factor = LCD_FLOAT_MUL; u32Factor/=10 ; ){
				LCD_u8CHAR_W(((u32NumRead/u32Factor)%10u) + '0');
			}
			LCD_u8CHAR_W(' ');
			LCD_u8CHAR_W(' ');
			LCD_u8ShiftMode(LCD_Cursor_Shift_Left);
			LCD_u8ShiftMode(LCD_Cursor_Shift_Left);
		}
	}else{
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Jump Cursor to X Column and Y Row						  */
/* Input       :	u8Col, u8Row											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8GoTo_XY(u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if((u8Col < LCD_COL_NUM)){
		switch(u8Row){
		case LCD_Line_1:	LCD_u8CMD_W(LCD_FIRST_LINE_POSITION_0  + u8Col);	break;
#if (LCD_ROW_NUM >= LCD_ROW_NUM_2)
		case LCD_Line_2:	LCD_u8CMD_W(LCD_SECOND_LINE_POSITION_0 + u8Col);	break;
#endif
#if (LCD_ROW_NUM >= LCD_ROW_NUM_4)
#if (LCD_COL_NUM == LCD_COL_NUM_16)
		case LCD_Line_3:	LCD_u8CMD_W(LCD_THIRD_LINE_POSITION_0  + u8Col);	break;
		case LCD_Line_4:	LCD_u8CMD_W(LCD_FOURTH_LINE_POSITION_0 + u8Col);	break;
#endif
#if (LCD_COL_NUM == LCD_COL_NUM_20)
		case LCD_Line_3:	LCD_u8CMD_W(LCD_THIRD_LINE_POSITION_0_20  + u8Col);	break;
		case LCD_Line_4:	LCD_u8CMD_W(LCD_FOURTH_LINE_POSITION_0_20 + u8Col);	break;
#endif
#if (LCD_COL_NUM == LCD_COL_NUM_32)
		case LCD_Line_3:	LCD_u8CMD_W(LCD_THIRD_LINE_POSITION_0_32  + u8Col);	break;
		case LCD_Line_4:	LCD_u8CMD_W(LCD_FOURTH_LINE_POSITION_0_32 + u8Col);	break;
#endif
#endif
		default:			u8RetErrorState = LBTY_NULL_POINTER;;				break;
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Clear Display (also clear DDRAM content)				  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8ClrDisplay(void){
	return LCD_u8CMD_W(LCD_CLEAR_DISPLAY);
}

/* ************************************************************************** */
/* Description :  	Initialize the LCD Mode									  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void LCD_vidInitMode(void){
#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
	LCD_u8CMD_W(LCD_INIT_4BIT);
	vidMyDelay_ms(LCD_DELAY_CMD_MAX);
	LCD_u8CMD_W(LCD_INIT_4BIT);
	LCD_u8CMD_W(LCD_INIT_4BIT);
#elif (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
	LCD_u8CMD_W(LCD_INIT_8BIT);
	vidMyDelay_ms(LCD_DELAY_CMD_MAX);
	LCD_u8CMD_W(LCD_INIT_8BIT);
	LCD_u8CMD_W(LCD_INIT_8BIT);
#endif
}

/* ************************************************************************** */
/* Description :  	Back the cursor to the home (0, 0)						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8Home(void){
	return LCD_u8CMD_W(LCD_CURSOR_HOME);
}

/* ************************************************************************** */
/* Description :  	Set Entry Mode 											  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8EntryMode(LCD_tenuEntryMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Mode){
	case LCD_Entry_Dec:
		u8RetErrorState = LCD_u8CMD_W(LCD_Entry_DEC);
		break;
	case LCD_Entry_Dec_Shift:
		u8RetErrorState = LCD_u8CMD_W(LCD_Entry_DEC_SHIFT);
		break;
	case LCD_Entry_Inc:
		u8RetErrorState = LCD_u8CMD_W(LCD_Entry_INC);
		break;
	case LCD_Entry_Inc_Shift:
		u8RetErrorState = LCD_u8CMD_W(LCD_Entry_INC_SHIFT);
		break;
	default:
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Display and Cursor Mode 										  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8DisplayMode(LCD_tenuDisplayCursorControl u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Mode){
	case LCD_Display_OFF:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_OFF_CURSOR_OFF);
		break;
	case LCD_Cursor_OFF:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_ON_CURSOR_OFF);
		break;
	case LCD_Cursor_OFF_Blink:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_ON_CURSOR_OFF_BLINK);
		break;
	case LCD_Cursor_UnderLine:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_ON_CURSOR_UNDERLINE);
		break;
	case LCD_Cursor_UnderLine_Blinking:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_ON_CURSOR_BLINK);
		break;
	default:
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Shifting Mode 										  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8ShiftMode(LCD_tenuDisplayCursorShift u8Shift){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Shift){
	case LCD_Cursor_Shift_Left:
		u8RetErrorState = LCD_u8CMD_W(LCD_CURSOR_SHIFT_LEFT);
		break;
	case LCD_Cursor_Shift_Right:
		u8RetErrorState = LCD_u8CMD_W(LCD_CURSOR_SHIFT_RIGHT);
		break;
	case LCD_Display_Shift_Left:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_SHIFT_LEFT);
		break;
	case LCD_Display_Shift_Right:
		u8RetErrorState = LCD_u8CMD_W(LCD_DISPLAY_SHIFT_RIGHT);
		break;
	default:
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Store Special Char 										  */
/* Input       :	u8Index													  */
/* Input/Output:	pu8char													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8StoreSpecialChar(u8* pu8char, u8 u8Index){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(u8Index < LCD_CGRAM_SECTIONS_NUM){
		u8RetErrorState = LCD_u8Set_CGRAM_Address(u8Index * LCD_CGRAM_LOCATIONS_NUM);
		for(u8 i = 0 ; i<LCD_CGRAM_LOCATIONS_NUM  && !u8RetErrorState ; i++){
			u8RetErrorState = LCD_u8CHAR_W(pu8char[i]);
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Special Char with index								  */
/* Input       :	u8Index, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetSpecialCharIndex(u8 u8Index, u8 u8Col, u8 u8Row){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(LCD_u8GoTo_XY(u8Col, u8Row)){
		u8RetErrorState = LBTY_NOK;
	}else{
		if(u8Index < LCD_CGRAM_SECTIONS_NUM){
			u8RetErrorState = LCD_u8CHAR_W(u8Index);
		}else{
			u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
		}
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Special Char with Array								  */
/* Input       :	u8Index, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetSpecialCharArray(u8* pu8char, u8 u8Col, u8 u8Row){
	static u8 u8Index = LBTY_u8ZERO;
	LBTY_tenuErrorStatus u8RetErrorState =
			LCD_u8StoreSpecialChar(pu8char,u8Index);

	if(u8RetErrorState ==  LBTY_OK){
		u8RetErrorState = LCD_u8SetSpecialCharIndex(u8Index++, u8Col, u8Row);
		u8Index = u8Index % LCD_CGRAM_SECTIONS_NUM;
	}
	return u8RetErrorState;
}

/*************************** E N D (LCD_prg.c) ******************************/
