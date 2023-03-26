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
    u8 m_u8b0 :1;		// LSB
    u8 m_u8b1 :1;
    u8 m_u8b2 :1;
    u8 m_u8b3 :1;
    u8 m_u8b4 :1;
    u8 m_u8b5 :1;
    u8 m_u8b6 :1;
    u8 m_u8b7 :1;		// MSB
  } sBits;
  u8 u_u8Byte;
} LBTY_tuniPort8;

typedef union {
  struct  {
    u8 m_u8b0  :1;		// LSB
    u8 m_u8b1  :1;
    u8 m_u8b2  :1;
    u8 m_u8b3  :1;
    u8 m_u8b4  :1;
    u8 m_u8b5  :1;
    u8 m_u8b6  :1;
    u8 m_u8b7  :1;
    u8 m_u8b8  :1;
    u8 m_u8b9  :1;
    u8 m_u8b10 :1;
    u8 m_u8b11 :1;
    u8 m_u8b12 :1;
    u8 m_u8b13 :1;
    u8 m_u8b14 :1;
    u8 m_u8b15 :1;		// MSB
  } sBits;
  struct {
    u8 m_u8low;
    u8 m_u8high;
  } sBytes;
  u16 u_u16Word;
} LBTY_tuniPort16;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* _LBTY_INT_H_ */
/*************************** E N D (LBTY_int.h) ******************************/
