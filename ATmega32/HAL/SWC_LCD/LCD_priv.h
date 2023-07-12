/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LCD_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 31, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** Clear and Return Home **/
#define LCD_CLEAR_DISPLAY 				0x01u	// Clear Display (also clear DDRAM content)
#define LCD_CURSOR_HOME					0x02u	// Cursor Home

#define LCD_INIT_4BIT					0x03u	// LCD Initialize Command
#define LCD_INIT_8BIT					0x30u	// LCD Initialize Command

/** Entry Mode Set **/
#define LCD_Entry_DEC					0x04u	// Entry Decrement Cursor
#define LCD_Entry_DEC_SHIFT				0x05u	// Entry Decrement Cursor with Display Shift
#define LCD_Entry_INC					0x06u	// Entry Increment Cursor
#define LCD_Entry_INC_SHIFT				0x07u	// Entry Increment Cursor with Display Shift

/** Display & Cursor Control **/
#define LCD_DISPLAY_OFF_CURSOR_OFF		0x08u	// Display off Cursor off(clearing display without clearing DDRAM content)
/** ... **/										// Not Used
#define LCD_DISPLAY_ON_CURSOR_OFF		0x0Cu	// Display on Cursor off
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK	0x0Du	// Display on Cursor off 	Blinking
#define LCD_DISPLAY_ON_CURSOR_UNDERLINE	0x0Eu	// Display on Cursor on 	Under Line
#define LCD_DISPLAY_ON_CURSOR_BLINK		0x0Fu	// Display on Cursor on 	blinking

/** Display & Cursor Shifting **/
#define LCD_CURSOR_SHIFT_LEFT			0x10u	// Move cursor left by one character
/** ... **/
#define LCD_CURSOR_SHIFT_RIGHT			0x14u	// Move cursor right by one character
/** ... **/
#define LCD_DISPLAY_SHIFT_LEFT			0x18u	// Shift entire display left
/** ... **/
#define LCD_DISPLAY_SHIFT_RIGHT			0x1Cu	// Shift entire display right
/** ... **/

/********************************************************************************************************************/
// MxN
// N = 1, 2, 4
// M = 8, 16, 20

/** Function Set **/
/** DB7-DB4 --> 4-Bits **/
#define LCD_CONFIG_1LINE_4BIT_5ROW		0x20u	// Function Set: 4-bit, 1 Line, 5x7 Dots
#define LCD_CONFIG_1LINE_4BIT_10ROW		0x24u	// Function Set: 4-bit, 1 Line, 5x10 Dots
#define LCD_CONFIG_2LINE_4BIT_5ROW		0x28u	// Function Set: 4-bit, 2 Line, 5x7 Dots
#define LCD_CONFIG_2LINE_4BIT_10ROW		0x2Cu	// Function Set: 4-bit, 2 Line, 5x10 Dots
/** ... **/
/** DB7-DB0 --> 8-Bits **/
#define LCD_CONFIG_1LINE_8BIT_5ROW		0x30u	// Function Set: 8-bit, 1 Line, 5x7 Dots
#define LCD_CONFIG_1LINE_8BIT_10ROW		0x34u	// Function Set: 8-bit, 1 Line, 5x10 Dots
#define LCD_CONFIG_2LINE_8BIT_5ROW		0x38u	// Function Set: 8-bit, 2 Line, 5x7 Dots
//#define LCD_CONFIG_2LINE_8BIT_10ROW		0x3Cu	// Function Set: 8-bit, 2 Line, 5x10 Dots (Can't Used)
/** ... **/

// LCD_XXXX_LINE_POSITION_0 + x = Jump Cursor to XXXX line position x
#define LCD_FIRST_LINE_POSITION_0 		0x80u	// Force cursor to beginning of first line
/** ... **/
#define LCD_SECOND_LINE_POSITION_0 		0xC0u	// Force cursor to beginning of second line
/** ... **/
#define LCD_THIRD_LINE_POSITION_0 		0x90u	// Force cursor to beginning of third line
#define LCD_THIRD_LINE_POSITION_0_20	0x94u	// Force cursor to beginning of third line
#define LCD_THIRD_LINE_POSITION_0_32	0xA0u	// Force cursor to beginning of third line
/** ... **/
#define LCD_FOURTH_LINE_POSITION_0 		0xD0u	// Force cursor to beginning of fourth line
#define LCD_FOURTH_LINE_POSITION_0_20	0xD4u	// Force cursor to beginning of fourth line
#define LCD_FOURTH_LINE_POSITION_0_32	0xE0u	// Force cursor to beginning of fourth line

/********************************************************************************************************************/
// LCD_REGISTER_SELECT_PIN
#define LCD_RS_CMD						0u
#define LCD_RS_DATA						1u

//LCD_READ_WRITE_PIN
#define LCD_RW_WRITE					0u
#define LCD_RW_READ						1u

#define BUSY_FLAG_BIT					7u

/** 1-RS - 0-RW bits **/				// 40usec
#define LCD_WRITE_INSTRUCTION_CMD		0u
#define LCD_READ_INSTRUCTION_CMD		1u
#define LCD_WRITE_DATA_CMD				2u
#define LCD_READ_DATA_CMD				3u

#define LCD_SEND_CGRAM_ADDRESS			0x40u	// Character Generator RAM
/** ... **/
#define LCD_SEND_DDRAM_ADDRESS			0x80u	// Display Data RAM
/** ... **/

#define LCD_CGRAM_ADDRESS_MASK			0x3Fu
#define LCD_DDRAM_ADDRESS_MASK			0x7Fu

#define LCD_CGRAM_SECTIONS_NUM 			8u
#define LCD_CGRAM_LOCATIONS_NUM  		8u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

extern const u8 ETA32[][LCD_CGRAM_LOCATIONS_NUM];

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

extern LBTY_tenuErrorStatus LCD_u8FunctionSet(void);
extern void LCD_vidInitPins(void);

extern void LCD_vidDirection(u8 u8PinDir);
extern void LCD_vidTriger(void);

extern LBTY_tenuErrorStatus LCD_u8Write(u8 u8Byte);
extern LBTY_tenuErrorStatus LCD_u8Read(u8* pu8Byte);

extern LBTY_tenuErrorStatus LCD_u8CMD_W(u8 u8CMD);
extern LBTY_tenuErrorStatus LCD_u8CMD_R(u8* pu8CMD);

extern LBTY_tenuErrorStatus LCD_u8CHAR_W(u8 u8Char);
extern LBTY_tenuErrorStatus LCD_u8CHAR_R(u8* pu8Char);

extern LBTY_tenuErrorStatus LCD_u8Set_CGRAM_Address(u8 u8Address);
extern LBTY_tenuErrorStatus LCD_u8Set_DDRAM_Address(u8 u8Address);

extern LBTY_tenuErrorStatus LCD_u8Get_DDRAM_Address(u8* pu8Address);
extern u8 LCD_u8GetBusyFlag(void);

#endif /* LCD_PRIV_H_ */
/*************************** E N D (LCD_priv.h) ******************************/
