/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 13, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef I2C_PRIV_H_
#define I2C_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of TX/RX Status                                      */
/** <b>Type</b> : Enum <b>Unit</b> : None                                     */
typedef enum{
	I2C_IDLE = (u8)0u,
	I2C_START,
	I2C_ADDRESS,
//	I2C_RW,
//	I2C_ACK,
	I2C_DATA,
	I2C_STOP,
	I2C_ERROR
}I2C_tenuStatus;

/** @brief : I2C Address                                                      */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_OP  : 1;			/*!< Operation R/W */
        __IO u8 m_ADD : 7;			/*!< Slave Address */
    }sBits;
}I2C_tstrAddress;
/** @brief : I2C TX/RX Buffer                                                 */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
	I2C_tstrAddress  m_u8Add;		/*!< Slave Address */
	pu8 m_pu8Data;					/*!< Data Pointer */
	u8  m_u8Size;					/*!< Size of Data Bytes */
	u8  m_u8Idx;					/*!< Index of Data */
	u8  m_u8Status;					/*!< Current Status */
}I2C_tstrBuffer;

/*************************************************************************/

/** @brief : Type define of Union bit field of "TWI Control Register"         */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_TWIE : 1;			/*!< TWI Interrupt Enable */
    	__IO u8        : 1;			/*!< Reversed */
    	__IO u8 m_TWEN : 1;			/*!< TWI Enable Bit */
    	__I  u8 m_TWWC : 1;			/*!< TWI Write Collision Flag */
    	__IO u8 m_TWSTO: 1;			/*!< TWI STOP Condition Bit */
    	__IO u8 m_TWSTA: 1;			/*!< TWI START Condition Bit */
    	__IO u8 m_TWEA : 1;			/*!< TWI Enable Acknowledge Bit */
    	__IO u8 m_TWINT: 1;			/*!< TWI Interrupt Flag "0 -> set" "1 -> reset" */
    }sBits;
}TWCR_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "TWI Status Register"          */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_TWPS : 2;			/*!< TWI Prescaler Bits */
        __IO u8        : 1;			/*!< Reversed */
        __I  u8 m_TWS  : 5;			/*!< TWI Status */
    }sBits;
}TWSR_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "TWI Address Register"         */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_TWGCE : 1;		/*!< TWI General Call Recognition Enable Bit */
        __IO u8 m_TWA   : 7;		/*!< TWI Slave Address */
    }sBits;
}TWAR_type;

/*************************************************************************/

/** @brief : I2C "TWI" Registers                                              */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
    __IO u8         m_TWBR;			/*!< TWI Bit Rate Register */
    __IO TWSR_type  m_TWSR;			/*!< TWI Status Register */
    __IO TWAR_type  m_TWAR;			/*!< TWI Address Register */
    __IO u8         m_TWDR;			/*!< TWI Data Register */
    __I  u8         REVERSE[50];	/*!< Reversed */
    __IO TWCR_type  m_TWCR;			/*!< TWI Control Register */
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

#define TWIE						0
#define TWEN						2
#define TWWC						3
#define TWSTO						4
#define TWSTA						5
#define TWEA						6
#define TWINT						7

#define I2C_STATUS_MASK				0xF8u

#define I2C_PORT					C
#define I2C_SDA_PIN					GPIO_I2C_SDA
#define I2C_SCL_PIN					GPIO_I2C_SCL

#define I2C_START()			( S_TWI->m_TWCR.u_Reg = (_BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA)) )
#define I2C_ACK()			( S_TWI->m_TWCR.u_Reg = (_BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWEA) ) )
#define I2C_NACK()			( S_TWI->m_TWCR.u_Reg = (_BV(TWINT) | _BV(TWEN) | _BV(TWIE)             ) )
#define I2C_STOP()			( S_TWI->m_TWCR.u_Reg = (_BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTO)) )
#define I2C_DEF(value, bit)	( S_TWI->m_TWCR.u_Reg = (_BV(TWINT) | _BV(TWEN) | (value<<(bit))        ) )

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void _vidStart(void);
void _vidStop(void);
void _vidRelease(void);
void _vidError(void);
void _vidCMD(void);
void _vidReplay(void);
void _vidWR(void);
void _vidRD(void);

void _vidTX(u8 u8State);
void _vidRX(u8 u8State);

void I2C_vidStep(void);

#endif /* I2C_PRIV_H_ */
/*************************** E N D (I2C_priv.h) ******************************/
