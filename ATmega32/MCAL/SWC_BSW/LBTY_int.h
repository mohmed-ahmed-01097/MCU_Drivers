/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LBTY_int.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 23, 2023												  */
/* description : Basic Library												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef _LBTY_INT_H_
#define _LBTY_INT_H_

#include <stdint.h>

/* ************************************************************************** */
/* ******************************* TYPE_DEF SECTION ************************* */
/* ************************************************************************** */

/** Data Types New Definitions **/
/** Standard Unsigned Byte/Word/Long_Word **/
typedef uint8_t     u8 ;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t  	u64;

/** Standard Signed Byte/Word/Long_Word **/
typedef int8_t		s8 ;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t		s64;

typedef float       f32;
typedef double      f64;

/** Standard Pointer to Unsigned Byte/Word/Long_Word **/
typedef u8*			pu8 ;
typedef u16*		pu16;
typedef u32*		pu32;
typedef u64*		pu64;

/** Standard Pointer to Signed Byte/Word/Long_Word **/
typedef s8*			ps8 ;
typedef s16*		ps16;
typedef s32*		ps32;
typedef s64*		ps64;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define LBTY_u8vidNOP()
#define LBTY_NULL		((void *) 0U)

/** Data Types Limitation **/
#define LBTY_u8ZERO		((u8)0x00U)
#define LBTY_u8MAX		((u8)0xFFU)
#define LBTY_s8MAX		((s8)0x7F )
#define LBTY_s8MIN		((s8)0x80 )

#define LBTY_u16ZERO	((u16)0x0000U)
#define LBTY_u16MAX		((u16)0xFFFFU)
#define LBTY_s16MAX		((u16)0x7FFF )
#define LBTY_s16MIN		((u16)0x8000 )

#define LBTY_u32ZERO	((u32)0x00000000U)
#define LBTY_u32MAX		((u32)0xFFFFFFFFU)
#define LBTY_s32MAX		((u32)0x7FFFFFFF )
#define LBTY_s32MIN		((u32)0x80000000 )

#define LBTY_u64ZERO	((u64)0x0000000000000000ULL)
#define LBTY_u64MAX		((u64)0xFFFFFFFFFFFFFFFFULL)
#define LBTY_s64MAX		((u64)0x7FFFFFFFFFFFFFFFLL )
#define LBTY_s64MIN		((u64)0x8000000000000000LL )

/* ************************************************************************** */
/* ****************************** ENUM SECTION ****************************** */
/* ************************************************************************** */

/** Flag Status type **/
typedef enum {
	LBTY_RESET = 0,
	LBTY_SET = !LBTY_RESET
} LBTY_tenuFlagStatus;

/** Boolean type **/
typedef enum {
  LBTY_TRUE = 0x55,
  LBTY_FALSE = 0xAA
} LBTY_tenuBoolean;

/** Error Return type **/
typedef enum {
  LBTY_OK = (u16)0,
  LBTY_NOK,
  LBTY_NULL_POINTER,
  LBTY_INDEX_OUT_OF_RANGE,
  LBTY_NO_MASTER_CHANNEL,
  LBTY_READ_ERROR,
  LBTY_WRITE_ERROR,
  LBTY_UNDEFINED_ERROR,
  LBTY_IN_PROGRESS        /* Error is not available, wait for availability */
} LBTY_tenuErrorStatus;

/* ************************************************************************** */
/* ****************************** STRUCT SECTION **************************** */
/* ************************************************************************** */

/** Union Byte bit by bit **/
typedef union {
  struct {
    u8 u8b0 :1; 	// lsb (least significant bit)
    u8 u8b1 :1;
    u8 u8b2 :1;
    u8 u8b3 :1;
    u8 u8b4 :1;
    u8 u8b5 :1;
    u8 u8b6 :1;
    u8 u8b7 :1;
  } strBit;
  u8 u8Byte;
} LBTY_tuniPort8;

typedef union {
  struct  {
    u8 u8b0  :1; /* !comment : lsb (least significant bit)*/
    u8 u8b1  :1; /* !comment : BIT 1*/
    u8 u8b2  :1; /* !comment : BIT 2*/
    u8 u8b3  :1; /* !comment : BIT 3*/
    u8 u8b4  :1; /* !comment : BIT 4*/
    u8 u8b5  :1; /* !comment : BIT 5*/
    u8 u8b6  :1; /* !comment : BIT 6*/
    u8 u8b7  :1; /* !comment : BIT 7*/
    u8 u8b8  :1; /* !comment : BIT 8*/
    u8 u8b9  :1; /* !comment : BIT 9*/
    u8 u8b10 :1; /* !comment : BIT 10*/
    u8 u8b11 :1; /* !comment : BIT 11*/
    u8 u8b12 :1; /* !comment : BIT 12*/
    u8 u8b13 :1; /* !comment : BIT 13*/
    u8 u8b14 :1; /* !comment : BIT 14*/
    u8 u8b15 :1; /* !comment : msb (most significant bit)*/
  } strBit; /* !comment : for bit  access*/
  struct {
    u8 u8low; /* !comment : Least significant byte*/
    u8 u8high; /* !comment : Most significant byte*/
  } strByte; /* !comment : for byte access*/
  u16 u16Word; /* !comment : for word access*/
} LBTY_tuniPort16;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* _LBTY_INT_H_ */
/*************************** E N D (LBTY_int.h) ******************************/
