/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : INT_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef INT_PRIV_H_
#define INT_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8        : 6;
    	__IO u8 m_ISC2 : 1;        // Interrupt 2 Sense Control
    	__IO u8        : 1;
    }sBits;
}MCUCSR_type;   // Control and Status Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_ISC0 : 2;        // Interrupt 0 Sense Control
    	__IO u8 m_ISC1 : 2;        // Interrupt 1 Sense Control
    	__IO u8        : 4;
    }sBits;
}MCUCR_type;   // MCU Control Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8        : 5;
    	__IO u8 m_INT2F: 1;        // External Interrupt Request Flag 2
    	__IO u8 m_INT0F: 1;        // External Interrupt Request Flag 0
    	__IO u8 m_INT1F: 1;        // External Interrupt Request Flag 1
    }sBits;
}GIFR_type;   // General Interrupt Flag Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8        : 5;
    	__IO u8 m_INT2E: 1;        // External Interrupt Request Enable 2
    	__IO u8 m_INT0E: 1;        // External Interrupt Request Enable 0
    	__IO u8 m_INT1E: 1;        // External Interrupt Request Enable 1
    }sBits;
}GICR_type;   // General Interrupt Control Register

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** MCU Control and Status Register **/
#define S_MCUCSR        ((MCUCSR_type* const)0x54U)
#define MCUCSR          (*(volatile u8* const)0x54U)

/** MCU Control Register **/
#define S_MCUCR         ((MCUCR_type* const)0x55U)
#define MCUCR           (*(volatile u8* const)0x55U)

/** General Interrupt Flag Register **/
#define S_GIFR          ((GIFR_type* const)0x5AU)
#define GIFR            (*(volatile u8* const)0x5AU)

/** General Interrupt Control Register **/
#define S_GICR          ((GICR_type* const)0x5BU)
#define GICR            (*(volatile u8* const)0x5BU)

/* ************************************************************************** */

#define INT0_PORT		D
#define INT0_PIN		GPIO_INT0
#define INT0_SC			INT_Rising_Edge

#define INT1_PORT		D
#define INT1_PIN		GPIO_INT1
#define INT1_SC			INT_Low_Level

#define INT2_PORT		B
#define INT2_PIN		GPIO_INT2
#define INT2_SC			INT2_Falling_Edge

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* INT_PRIV_H_ */
/*************************** E N D (INT_priv.h) ******************************/
