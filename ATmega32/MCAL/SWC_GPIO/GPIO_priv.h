/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef GPIO_PRIV_H_
#define GPIO_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_B0 : 1;
    	__IO u8 m_B1 : 1;
    	__IO u8 m_B2 : 1;
    	__IO u8 m_B3 : 1;
    	__IO u8 m_B4 : 1;
    	__IO u8 m_B5 : 1;
    	__IO u8 m_B6 : 1;
    	__IO u8 m_B7 : 1;
    }sBits;
}BYTE_type; // byte bit exchange

/*************************************************************************/

typedef struct{
    __I  BYTE_type m_PIN;
    __IO BYTE_type m_DDR;
    __IO BYTE_type m_PORT;
}GPIOx_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8        : 2;
    	__IO u8 m_PUD  : 1;        // Pull-up disable
    	__IO u8        : 5;
    }sBits;
}SFIOR_type;   // Special Function I/O Register

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define PULL_UP_DISABLE			LBTY_RESET

#define GPIOA_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOA_PORT_INIT_DEF		PORT_Low

#define GPIOB_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOB_PORT_INIT_DEF		PORT_Low

#define GPIOC_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOC_PORT_INIT_DEF		PORT_High

#define GPIOD_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOD_PORT_INIT_DEF		PORT_Low

/* ************************************************************************** */

/** GPIOD **/
#define S_GPIOD         ((GPIOx_type* const)0x30U)
#define PIND            (*(volatile u8* const)0x30U)
#define DDRD            (*(volatile u8* const)0x31U)
#define PORTD           (*(volatile u8* const)0x32U)

/** GPIOC **/
#define S_GPIOC         ((GPIOx_type* const)0x33U)
#define PINC            (*(volatile u8* const)0x33U)
#define DDRC            (*(volatile u8* const)0x34U)
#define PORTC           (*(volatile u8* const)0x35U)

/** GPIOB **/
#define S_GPIOB         ((GPIOx_type* const)0x36U)
#define PINB            (*(volatile u8* const)0x36U)
#define DDRB            (*(volatile u8* const)0x37U)
#define PORTB           (*(volatile u8* const)0x38U)

/** GPIOA **/
#define S_GPIOA         ((GPIOx_type* const)0x39U)
#define PINA            (*(volatile u8* const)0x39U)
#define DDRA            (*(volatile u8* const)0x3AU)
#define PORTA           (*(volatile u8* const)0x3BU)

/** Special Function I/O Register **/
#define S_SFIOR         ((SFIOR_type* const)0x50U)
#define SFIOR           (*(volatile u8* const)0x50U)

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* GPIO_PRIV_H_ */
/*************************** E N D (GPIO_priv.h) ******************************/
