/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 13, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef I2C_PRIV_H_
#define I2C_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	TX_IDLE,
	TX_BUSY,
	RX_IDLE,
	RX_BUSY,
}USART_tstrStatus;

typedef struct{
	pu8 m_pu8Data;
	u8  m_u8Size;
	u8  m_u8Idx;
	u8  m_u8Status;
}I2C_tstrBuffer;

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_TWIE : 1;   // TWI Interrupt Enable
    	__IO u8        : 1;
    	__IO u8 m_TWEN : 1;   // TWI Enable Bit
    	__I  u8 m_TWWC : 1;   // TWI Write Collision Flag
    	__IO u8 m_TWSTO: 1;   // TWI STOP Condition Bit
    	__IO u8 m_TWSTA: 1;   // TWI START Condition Bit
    	__IO u8 m_TWEA : 1;   // TWI Enable Acknowledge Bit
    	__IO u8 m_TWINT: 1;   // TWI Interrupt Flag "0 -> set" "1 -> reset"
    }sBits;
}TWCR_type; // TWI Control Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_TWPS : 2;   // TWI Prescaler Bits
        __IO u8        : 1;
        __I  u8 m_TWS  : 5;   // TWI Status
    }sBits;
}TWSR_type; // TWI Status Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_TWGCE : 1;   // TWI General Call Recognition Enable Bit
        __IO u8 m_TWA   : 7;   // TWI Slave Address
    }sBits;
}TWAR_type; // TWI Address Register

/*************************************************************************/

typedef struct{
    __IO u8         m_TWBR;
    __IO TWSR_type  m_TWSR;
    __IO TWAR_type  m_TWAR;
    __IO u8         m_TWDR;
    __I  u8         REVERSE[50];
    __IO TWCR_type  m_TWCR;
}TWI_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** Two-Wire Serial Interface **/
#define S_TWI           ((TWI_type* const)0x20U)
#define TWBR            (*(volatile u8* const)0x20U)
#define TWSR            (*(volatile u8* const)0x21U)
#define TWAR            (*(volatile u8* const)0x22U)
#define TWDR            (*(volatile u8* const)0x23U)

#define TWCR            (*(volatile u8* const)0x56U)

/* ************************************************************************** */

#define I2C_SLAVE					0u
#define I2C_MASTER					1u

#define I2C_STATUS_MASK				0xF8u

#define I2C_PORT					C
#define I2C_SDA_PIN					GPIO_I2C_SDA
#define I2C_SCL_PIN					GPIO_I2C_SCL

#if (I2C_MODE == I2C_MASTER)

#define I2C_SDA_CONFIG				PIN_OUTPUT
#define I2C_SCL_CONFIG				PIN_INPUT

#elif(I2C_MODE == I2C_SLAVE)

#define I2C_SDA_CONFIG				PIN_INPUT
#define I2C_SCL_CONFIG				PIN_OUTPUT

#endif
/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void I2C_vidIDLE(void);
void I2C_vidSTART(void);
void I2C_vidAddress(void);
void I2C_vidRW(void);
void I2C_vidACK(void);
void I2C_vidData(u8* pu8Data);
void I2C_vidSTOP(void);
void I2C_vidERROR(void);

#endif /* I2C_PRIV_H_ */
/*************************** E N D (I2C_priv.h) ******************************/
