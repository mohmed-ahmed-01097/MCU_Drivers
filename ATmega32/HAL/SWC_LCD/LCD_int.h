/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LCD_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Mar 31, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LCD_INT_H_
#define LCD_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	LCD_Function_Set_8Bits = (u8)0u,
	LCD_Function_Set_4Bits
}LCD_tenuFunctionSet;

typedef enum{
	LCD_Entry_Dec = (u8)0u,
	LCD_Entry_Dec_Shift,
	LCD_Entry_Inc,
	LCD_Entry_Inc_Shift
}LCD_tenuEntryMode;


typedef enum{
	LCD_Display_OFF = (u8)0u,
	LCD_Cursor_OFF,
	LCD_Cursor_OFF_Blink,
	LCD_Cursor_UnderLine,
	LCD_Cursor_UnderLine_Blinking
}LCD_tenuDisplayCursorControl;

typedef enum{
	LCD_Cursor_Shift_Left = (u8)0u,
	LCD_Cursor_Shift_Right,
	LCD_Display_Shift_Left,
	LCD_Display_Shift_Right
}LCD_tenuDisplayCursorShift;

typedef enum{
	LCD_Line_1 = (u8)0u,
	LCD_Line_2,
	LCD_Line_3,
	LCD_Line_4
}LCD_tenuLinePosition;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define LCD_FUNCTION_SET_8Bits			0u
#define LCD_FUNCTION_SET_4Bits			1u

#define LCD_COL_NUM_8					8u
#define LCD_COL_NUM_16					16u
#define LCD_COL_NUM_20					20u
#define LCD_COL_NUM_32					32u

#define LCD_ROW_NUM_1					1u
#define LCD_ROW_NUM_2					2u
#define LCD_ROW_NUM_4					4u

#define LCD_FLOAT_MUL					100

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
void LCD_vidInit(void);

/* ************************************************************************** */
/* Description :  	Set String at X Column and Y Row						  */
/* Input       :	u8Col, u8Row											  */
/* Input/Output:	pu8String												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetString(u8 pu8String[], u8 u8Row, u8 u8Col);

/* ************************************************************************** */
/* Description :  	Set Char at X Column and Y Row 							  */
/* Input       :	u8Char, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetChar(u8 u8Char, u8 u8Row, u8 u8Col);

/* ************************************************************************** */
/* Description :  	Get Num at X Column and Y Row							  */
/* Input       :	u8Col, u8Row											  */
/* Input/Output:	ps32Num													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8GetNum(s32* ps32Num, u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Set Num at X Column and Y Row							  */
/* Input       :	s32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetNum(s32 s32Num, u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Get Real float Num at X Column and Y Row				  */
/* Input       :	u8Col, u8Row											  */
/* Input/Output:	pf32Num													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8GetFloat(f32* pf32Num, u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Set Real float Num at X Column and Y Row				  */
/* Input       :	f32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetFloat(f32 f32Num, u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Set Num Rise at X Column and Y Row						  */
/* Input       :	s32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetNum_Rise(s32 s32Num, u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Set Real float Num Rise at X Column and Y Row			  */
/* Input       :	f32Num, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetFloat_Rise(f32 f32Num, u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Jump Cursor to X Column and Y Row						  */
/* Input       :	u8Col, u8Row											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8GoTo_XY(u8 u8Col, u8 u8Row);

/* ************************************************************************** */
/* Description :  	Clear Display (also clear DDRAM content)				  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8ClrDisplay(void);

/* ************************************************************************** */
/* Description :  	Back the cursor to the home (0, 0)						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8Home(void);

/* ************************************************************************** */
/* Description :  	Set Entry Mode 											  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8EntryMode(LCD_tenuEntryMode u8Mode);

/* ************************************************************************** */
/* Description :  	Set Display and Cursor Mode 										  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8DisplayMode(LCD_tenuDisplayCursorControl u8Mode);

/* ************************************************************************** */
/* Description :  	Set Shifting Mode 										  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8ShiftMode(LCD_tenuDisplayCursorShift u8Shift);

/* ************************************************************************** */
/* Description :  	Store Special Char 										  */
/* Input       :	u8Index													  */
/* Input/Output:	pu8char													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8StoreSpecialChar(u8* pu8char, u8 u8Index);
/* ************************************************************************** */
/* Description :  	Set Special Char 										  */
/* Input       :	u8Index, u8Col, u8Row									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LCD_u8SetSpecialChar(u8 u8Index, u8 u8Col, u8 u8Row);
#endif /* LCD_INT_H_ */
/*************************** E N D (LCD_int.h) ******************************/
