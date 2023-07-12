/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef GPIO_PRIV_H_
#define GPIO_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of Union bit field of Single Byte"byte bits exchange"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_B0 : 1;			/*!< Bit 0 "LSB" */
    	__IO u8 m_B1 : 1;			/*!< Bit 1 */
    	__IO u8 m_B2 : 1;			/*!< Bit 2 */
    	__IO u8 m_B3 : 1;			/*!< Bit 3 */
    	__IO u8 m_B4 : 1;			/*!< Bit 4 */
    	__IO u8 m_B5 : 1;			/*!< Bit 5 */
    	__IO u8 m_B6 : 1;			/*!< Bit 6 */
    	__IO u8 m_B7 : 1;			/*!< Bit 7 "MSB" */
    }sBits;							/*!< All Bits of the Byte */
}BYTE_type;

/*************************************************************************/

/** @brief : General Purpose Input Output Registers                           */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
    __I  BYTE_type m_PIN;			/*!< Pins Input Register */
    __IO BYTE_type m_DDR;			/*!< Data Direction Register */
    __IO BYTE_type m_PORT;			/*!< Pins Output Register */
}GPIOx_type;

/*************************************************************************/

/** @brief : Special Function I/O Register                                    */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8        : 2;			/*!< Reversed */
    	__IO u8 m_PUD  : 1;			/*!< Pull-up disable */
    	__IO u8        : 5;			/*!< Reversed */
    }sBits;							/*!< All Bits of the Byte */
}SFIOR_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define PULL_UP_DISABLE			LBTY_RESET

#define GPIOA_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOA_PORT_INIT_DEF		PORT_Low

#define GPIOB_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOB_PORT_INIT_DEF		PORT_Low

#define GPIOC_DDR_INIT_DEF		PORT_OUTPUT
#define GPIOC_PORT_INIT_DEF		PORT_Low

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
