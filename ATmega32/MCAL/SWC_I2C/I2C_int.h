/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_int.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
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
	I2C_Prescaler_1 = (u8)0u,
	I2C_Prescaler_4,
	I2C_Prescaler_16,
	I2C_Prescaler_64
}I2C_tenuPrescaler;

typedef enum{
	I2C_Start        = (u8)0x08,			// start condition transmitted
	I2C_RepeatStart  = (u8)0x10,			// repeated start condition transmitted

	I2C_MT_SLA_ACK   = (u8)0x18,			// SLA+W transmitted, ACK received
	I2C_MT_SLA_NACK  = (u8)0x20,			// SLA+W transmitted, NACK received
	I2C_MT_DATA_ACK  = (u8)0x28,			// data transmitted, ACK received
	I2C_MT_DATA_NACK = (u8)0x30,			// data transmitted, NACK received

	I2C_MT_ARB_LOST  = (u8)0x38,			// arbitration lost in SLA+W or data
	I2C_MR_ARB_LOST  = (u8)0x38,			// arbitration lost in SLA+W or data

	I2C_MR_SLA_ACK   = (u8)0x40,			// SLA+R transmitted, ACK received
	I2C_MR_SLA_NACK  = (u8)0x48,			// SLA+R transmitted, NACK received
	I2C_MR_DATA_ACK  = (u8)0x50,			// data received, ACK returned
	I2C_MR_DATA_NACK = (u8)0x58,			// data received, NACK returned

	I2C_SR_SLA_ACK       = (u8)0x60,		// SLA+W received, ACK returned
	I2C_SR_SLA_ARB_LOST  = (u8)0x68,		// arbitration lost in SLA+RW, SLA+W received, ACK returned
	I2C_SR_GCALL_ACK     = (u8)0x70,		// general call received, ACK returned
	I2C_SR_GCALL_ARB_LOST= (u8)0x78,		// arbitration lost in SLA+RW, general call received, ACK returned
	I2C_SR_DATA_ACK      = (u8)0x80,		// data received, ACK returned
	I2C_SR_DATA_NACK     = (u8)0x88,		// data received, NACK returned
	I2C_SR_GCALL_Data_ACK= (u8)0x90,		// general call data received, ACK returned
	I2C_SR_GCALL_Data_ARB_LOST= (u8)0x98,	// general call data received, NACK returned

	I2C_Stop         = (u8)0xA0,			// stop or repeated start condition received while selected

	I2C_ST_SLA_ACK   = (u8)0xA8,			// SLA+R received, ACK returned
	I2C_ST_ARB_LOST  = (u8)0xB0,			// arbitration lost in SLA+RW, SLA+R received, ACK returned
	I2C_ST_DATA_ACK  = (u8)0xB8,			// data transmitted, ACK received
	I2C_ST_DATA_NACK = (u8)0xC0,			// data transmitted, NACK received

	I2C_ST_LAST_Data = (u8)0xC8,			// last data byte transmitted, ACK received

	I2C_NoInfo       = (u8)0xF8,			// no state information available
	I2C_Bus_Error    = (u8)0x00,			// illegal start or stop condition
}I2C_tenuStatusCode;

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

void I2C_vidSlaveInit(u8 u8Address);

void I2C_vidWrite(u8 u8Char);
void I2C_vidRead_ACK(u8* pu8Char);
void I2C_vidRead_NACK(u8* pu8Char);

void I2C_vidSTART(void);
void I2C_vidAddress(u8 u8Address);
void I2C_vidSTOP(void);
u8 I2C_u8GetStatus(void);

u8 I2C_u8SlaveAvailable(void);

#endif /* I2C_INT_H_ */
/*************************** E N D (I2C_int.h) ******************************/
