/********************************************************/
/* Author      : MAAM									*/
/* Version     : v03									*/
/* date        : 23/03/2023								*/
/********************************************************/

#ifndef LBTY_CFG_H
#define LBTY_CFG_H

#include <stdint.h>

/** Data Types New Definitions **/
typedef uint8_t     u8 ;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t  	u64;

typedef int8_t		s8 ;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t		s64;

typedef float       f32;
typedef double      f64;

/** Data Types Limitation **/
#define MAX_U8		0xFFU
#define MAX_S8		0x7F
#define MIN_S8		0x80

#define MAX_U16		0xFFFFU
#define MAX_S16		0x7FFF
#define MIN_S16		0x8000

#define MAX_U32		0xFFFFFFFFU
#define MAX_S32		0x7FFFFFFF
#define MIN_S32		0x80000000

#define MAX_U64		0xFFFFFFFFFFFFFFFFULL
#define MAX_S64		0x7FFFFFFFFFFFFFFFLL
#define MIN_S64		0x8000000000000000LL

/** Bitwise Operation **/
#define SET_BIT(REG, bit) 	((REG) |=  (1<<bit))
#define CLR_BIT(REG, bit) 	((REG) &= ~(1<<bit))
#define TOG_BIT(REG, bit) 	((REG) ^=  (1<<bit))

#define SET_REG(REG) 		((REG)  = ~(0u))
#define CLR_REG(REG) 		((REG)  =  (0u))
#define TOG_REG(REG) 		((REG) ^= ~(0u))

#define GET_BIT(REG, bit) 	(REG & (1<<bit))>>bit)


#endif // LBTY_CFG_H
