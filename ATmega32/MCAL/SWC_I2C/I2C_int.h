/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 13, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef I2C_INT_H_
#define I2C_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	I2C_WRITE = (u8)0u,
	I2C_READ,
}USART_tstrRW;

typedef enum{
	I2C_Master_IDLE,
	I2C_Master_Transmit,
	I2C_Master_Receive,
	I2C_Slave_IDLE,
	I2C_Slave_Transmit,
	I2C_Slave_Receive,
}I2C_tenuMode;

typedef enum{
	I2C_IDLE = (u8)0u,
	I2C_START,
	I2C_ADDRESS,
	I2C_RW,
	I2C_ACK,
	I2C_DATA,
	I2C_STOP,
	I2C_ERROR
}I2C_tenuStatus;

typedef enum{
	I2C_Prescaler_1 = (u8)0u,
	I2C_Prescaler_4,
	I2C_Prescaler_16,
	I2C_Prescaler_64
}I2C_tenuPrescaler;

typedef enum{
	I2C_Bus_Error    			= (u8)0x00,	// illegal start or stop condition
	I2C_Start        			= (u8)0x08,	// start condition transmitted
	I2C_RepeatStart  			= (u8)0x10,	// repeated start condition transmitted

	I2C_MT_SLA_ACK   			= (u8)0x18,	// SLA+W transmitted, ACK received
	I2C_MT_SLA_NACK  			= (u8)0x20,	// SLA+W transmitted, NACK received
	I2C_MT_DATA_ACK  			= (u8)0x28,	// data transmitted, ACK received
	I2C_MT_DATA_NACK 			= (u8)0x30,	// data transmitted, NACK received

	I2C_MT_ARB_LOST 		 	= (u8)0x38,	// arbitration lost in SLA+W or data
	I2C_MR_ARB_LOST  			= (u8)0x38,	// arbitration lost in SLA+W or data

	I2C_MR_SLA_ACK   			= (u8)0x40,	// SLA+R transmitted, ACK received
	I2C_MR_SLA_NACK  			= (u8)0x48,	// SLA+R transmitted, NACK received
	I2C_MR_DATA_ACK  			= (u8)0x50,	// data received, ACK returned
	I2C_MR_DATA_NACK 			= (u8)0x58,	// data received, NACK returned

	I2C_SR_SLA_ACK       		= (u8)0x60,	// SLA+W received, ACK returned
	I2C_SR_SLA_ARB_LOST 		= (u8)0x68,	// arbitration lost in SLA+RW, SLA+W received, ACK returned
	I2C_SR_GCALL_ACK   			= (u8)0x70,	// general call received, ACK returned
	I2C_SR_GCALL_ARB_LOST		= (u8)0x78,	// arbitration lost in SLA+RW, general call received, ACK returned
	I2C_SR_DATA_ACK    		  	= (u8)0x80,	// data received, ACK returned
	I2C_SR_DATA_NACK     		= (u8)0x88,	// data received, NACK returned
	I2C_SR_GCALL_Data_ACK		= (u8)0x90,	// general call data received, ACK returned
	I2C_SR_GCALL_Data_ARB_LOST	= (u8)0x98,	// general call data received, NACK returned

	I2C_Stop         			= (u8)0xA0,	// stop or repeated start condition received while selected

	I2C_ST_SLA_ACK  			= (u8)0xA8,	// SLA+R received, ACK returned
	I2C_ST_ARB_LOST  			= (u8)0xB0,	// arbitration lost in SLA+RW, SLA+R received, ACK returned
	I2C_ST_DATA_ACK  			= (u8)0xB8,	// data transmitted, ACK received
	I2C_ST_DATA_NACK 			= (u8)0xC0,	// data transmitted, NACK received

	I2C_ST_LAST_Data 			= (u8)0xC8,	// last data byte transmitted, ACK received

	I2C_NoInfo       			= (u8)0xF8,	// no state information available

}I2C_tenuStatusCode;

typedef struct{
	I2C_tenuMode			m_Mode;
	I2C_tenuStatus			m_Status;
	I2C_tenuPrescaler		m_Prescaler;
//	LBTY_tenuFlagStatus		m_Start;
//	LBTY_tenuFlagStatus		m_Stop;
//	LBTY_tenuFlagStatus		m_ACK;

	u8						m_Address;

	LBTY_tenuFlagStatus		m_I2CEN;
	LBTY_tenuFlagStatus		m_I2CIE;
}I2C_tstrConfiguration;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void I2C_vidSetConfig(I2C_tstrConfiguration const* const pstrConfig);
void I2C_vidResetConfig(I2C_tstrConfiguration* const pstrConfig);

void I2C_vidInit(void);

void I2C_vidEnable(void);
void I2C_vidDisable(void);

u8 I2C_u8GetStatus(void);

/********************************************************************************************************************/

LBTY_tenuErrorStatus I2C_u8SetSTART(void);
LBTY_tenuErrorStatus I2C_u8SetRepeatSTART(void);
LBTY_tenuErrorStatus I2C_u8SetAddress(u8 u8Address, u8 Operation);
LBTY_tenuErrorStatus I2C_u8SetData(u8 u8Data);
LBTY_tenuErrorStatus I2C_u8GetDataNACK(u8* pu8Data);
LBTY_tenuErrorStatus I2C_u8GetDataACK(u8* pu8Data);
LBTY_tenuErrorStatus I2C_u8SetSTOP(void);

LBTY_tenuErrorStatus I2C_u8SendBuffer(u8* pu8Data, u8 u8Size);
LBTY_tenuErrorStatus I2C_u8ReceiveBuffer(u8* pu8Data, u8 u8Size);

/********************************************************************************************************************/

void I2C_vidEnableINT(void);
void I2C_vidDisableINT(void);

void I2C_vidResetINT_Flag(void);

void I2C_vidSetCallBack_OverFlow(void (*pCallBack)(void));

void I2C_vidTX_Step(void);
void I2C_vidRX_Step(void);

#endif /* I2C_INT_H_ */
/*************************** E N D (I2C_int.h) ******************************/
