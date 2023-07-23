/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : USART_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 10, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef USART_PRIV_H_
#define USART_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of TX/RX Status                                      */
/** <b>Type</b> : Enum <b>Unit</b> : None                                     */
typedef enum{
	TX_IDLE,
	TX_BUSY,
	RX_IDLE,
	RX_BUSY,
}USART_tstrStatus;

/** @brief : UART TX/RX Buffer                                                */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
	pu8 m_pu8Data;					/*!< Data Pointer */
	u8  m_u8Size;					/*!< Size of Data Bytes */
	u8  m_u8Idx;					/*!< Index of Data */
	u8  m_u8Status;					/*!< Current Status */
}USART_tstrBuffer;

/*************************************************************************/

/** @brief : Type define of UCSRC Register Selection                          */
/** <b>Type</b> : Enum <b>Unit</b> : None                                     */
typedef enum{
	USART_UBRRH_Reg = (u8)0u,
	USART_UCSRC_Reg,
}USART_tenumRegSelect;

/*************************************************************************/

/** @brief : Type define of Union bit field of "USART Control and Status RegC"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_UCPOL: 1;		/*!< Clock Polarity */
        __IO u8 m_UCSZ0: 1;		/*!< Character Size 0 */
        __IO u8 m_UCSZ1: 1;		/*!< Character Size 1 */
        __IO u8 m_USBS : 1;		/*!< Stop Bit Select */
        __IO u8 m_UPM  : 2;		/*!< Parity Mode */
        __IO u8 m_UMSEL: 1;		/*!< USART Mode Select */
        __IO u8 m_URSEL: 1;		/*!< Register Select */
    }sUCSRC;
    struct {
    	__IO u8 m_UBRR : 4;		/*!< USART Baud Rate High */
    	__IO u8        : 3;		/*!< Reversed */
    	__IO u8 m_URSEL: 1;		/*!< Register Select */
    }sUBRRH;
}UCSRC_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "USART Control and Status RegB"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_TXB8 : 1;		/*!< Transmit Data Bit 8 */
    	__I  u8 m_RXB8 : 1;		/*!< Receive Data Bit 8 */
    	__IO u8 m_UCSZ2: 1;		/*!< Character Size */
    	__IO u8 m_TXEN : 1;		/*!< Transmitter Enable */
    	__IO u8 m_RXEN : 1;		/*!< Receiver Enable */
    	__IO u8 m_UDRIE: 1;		/*!< USART Data Register Empty Interrupt Enable */
    	__IO u8 m_TXCIE: 1;		/*!< TX Complete Interrupt Enable */
    	__IO u8 m_RXCIE: 1;		/*!< RX Complete Interrupt Enable */
    }sBits;
}UCSRB_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "USART Control and Status RegA"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_MPCM: 1;		/*!< Multi-processor Communication Mode  */
        __IO u8 m_U2X : 1;		/*!< Double the USART Transmission Speed */
        __I  u8 m_PE  : 1;		/*!< Parity Error */
        __I  u8 m_DOR : 1;		/*!< Data OverRun */
        __I  u8 m_FE  : 1;		/*!< Frame Error */
        __I  u8 m_UDRE: 1;		/*!< USART Data Register Empty */
        __IO u8 m_TXC : 1;		/*!< USART Transmit Complete */
        __I  u8 m_RXC : 1;		/*!< USART Receive Complete */
    }sBits;
}UCSRA_type;

/*************************************************************************/

/** @brief : UART Registers                                                   */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
    __IO u8         m_UBRRL;		/*!< USART Baud Rate */
    __IO UCSRB_type m_UCSRB;		/*!< USART Control and Status Reg B */
    __IO UCSRA_type m_UCSRA;		/*!< USART Control and Status Reg A */
    __IO u8         m_UDR;			/*!< USART Data Reg */
    __I  u8         REVERSE[19];	/*!< Reversed */
    __IO u8         m_UCSRC;		/*!< USART Control and Status Reg C */
}USART_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** USART **/
#define S_USART         ((USART_type* const)0x29U)
#define UBRRL           (*(volatile u8* const)0x29U)
#define UCSRB           (*(volatile u8* const)0x2AU)
#define UCSRA           (*(volatile u8* const)0x2BU)
#define UDR             (*(volatile u8* const)0x2CU)

#define UCSRC           (*(volatile u8* const)0x40U)
#define UBRRH           (*(volatile u8* const)0x40U)

/* ************************************************************************** */

#define USART_UCSZ0_BIT				0u
#define USART_UCSZ1_BIT				1u
#define USART_UCSZ2_BIT				2u

#define USART_XCK_PORT				B
#define USART_XCK_PIN				GPIO_USART_XCK

#define USART_PORT					D
#define USART_RX_PIN				GPIO_UART_RX
#define USART_TX_PIN				GPIO_UART_TX

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

#endif /* USART_PRIV_H_ */
/*************************** E N D (USART_priv.h) ******************************/
