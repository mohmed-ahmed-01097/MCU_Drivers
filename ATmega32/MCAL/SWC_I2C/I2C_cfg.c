/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : May 19, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "I2C_int.h"
#include "I2C_cfg.h"
#include "I2C_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

extern volatile I2C_tstrBuffer strBuffer_GLB;
//https://github.com/MayaPosch/Nodate/blob/e68c252b858cb9dbe812eb617688b2752fe16664/arch/avr/arduino/libraries/Wire/src/utility/twi.c#L441
//https://github.com/scttnlsn/avr-twi/blob/master/twi.c#L64
/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void _vidStart(void){
	if(I2C_MODE == I2C_Master){
		I2C_START();
	}else if(I2C_MODE == I2C_Slave){
		I2C_ACK();
	}

	strBuffer_GLB.m_u8Status = I2C_START;
}
void _vidStop(void){
	I2C_STOP();
	while(S_TWI->m_TWCR.sBits.m_TWSTO);
	S_TWI->m_TWCR.sBits.m_TWSTO = LBTY_SET;
	strBuffer_GLB.m_u8Status = I2C_STOP;

//	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) == I2C_Stop){
		_vidRelease();
//	}
}
void _vidRelease(void){
	I2C_DEF(LBTY_SET, TWEA);
	strBuffer_GLB.m_u8Status = I2C_IDLE;
}
void _vidError(void){
	I2C_STOP();
	//S_TWI->m_TWCR.sBits.m_TWEN = LBTY_RESET;
	strBuffer_GLB.m_u8Status   = I2C_ERROR;
	_vidRelease();
}
void _vidCMD(void){
	S_TWI->m_TWDR = strBuffer_GLB.m_u8Add.u_Reg;
	if(I2C_MODE == I2C_Master){
		I2C_NACK();
	}else if(I2C_MODE == I2C_Slave){
		I2C_ACK();
	}
	strBuffer_GLB.m_u8Status = I2C_ADDRESS;
}
void _vidReplay(void){
	if(strBuffer_GLB.m_u8Idx < (strBuffer_GLB.m_u8Size /*- 1*/)){
		I2C_ACK();
	}else{
		I2C_NACK();
	}
}
void _vidWR(void){
	if(strBuffer_GLB.m_u8Idx < strBuffer_GLB.m_u8Size){
		S_TWI->m_TWDR = strBuffer_GLB.m_pu8Data[strBuffer_GLB.m_u8Idx++];
		if(I2C_MODE == I2C_Master){
			I2C_NACK();
		}else if(I2C_MODE == I2C_Slave){
			I2C_ACK();
		}
		strBuffer_GLB.m_u8Status = I2C_DATA;
	}else{
		_vidStop();
	}
}
void _vidRD(void){
	if(strBuffer_GLB.m_u8Idx < strBuffer_GLB.m_u8Size){
		strBuffer_GLB.m_pu8Data[strBuffer_GLB.m_u8Idx++] = S_TWI->m_TWDR;
		_vidReplay();
		strBuffer_GLB.m_u8Status = I2C_DATA;
	}else{
		_vidStop();
	}
}
void _vidTX(u8 u8State){
	switch(u8State){
		case I2C_MT_SLA_ACK:
		case I2C_MT_DATA_ACK:
		case I2C_ST_SLA_ACK:
		case I2C_ST_DATA_ACK:
		case I2C_MT_SLA_NACK:
			_vidWR();
			break;
		case I2C_MT_DATA_NACK:
		case I2C_ST_DATA_NACK:
		case I2C_ST_LAST_Data:
			_vidStop();
			break;
		default:
			_vidError();
	}
}
void _vidRX(u8 u8State){
	switch(u8State){
		case I2C_MR_SLA_ACK:
		case I2C_SR_SLA_ACK:
		case I2C_SR_GCALL_ACK:
			_vidReplay();
			break;
		case I2C_MR_DATA_ACK:
		case I2C_SR_DATA_ACK:
		case I2C_SR_GCALL_Data_ACK:
			_vidRD();
			break;
		case I2C_MR_DATA_NACK:
		case I2C_SR_DATA_NACK:
		case I2C_SR_GCALL_Data_NACK:
		case I2C_ST_LAST_Data:
			_vidRD();
			_vidStop();
			break;
		case I2C_MR_SLA_NACK:
		default:
			_vidError();
	}
}

void I2C_vidStep(void){
	volatile u8 u8State = GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK);
	switch(u8State) {
		case I2C_Start:					// Start condition transmitted
		case I2C_RepeatStart:			// Repeated start condition transmitted

			_vidCMD();
			break;
/* ************************************************************************** */
		case I2C_MT_SLA_ACK:			// SLA+W transmitted, ACK received = Slave receiver ACKed address
		case I2C_MT_DATA_ACK:			// Data transmitted, ACK received = Slave receiver ACKed data
		case I2C_ST_SLA_ACK:			// SLA+R received, ACK returned = Addressed, returned ACK
		case I2C_ST_DATA_ACK:			// Data transmitted, ACK received

		case I2C_MT_SLA_NACK:			// SLA+W transmitted, NACK received = Slave receiver with transmitted address doesn't exists?
		case I2C_MT_DATA_NACK:			// Data transmitted, NACK received
		case I2C_ST_DATA_NACK:			// Data transmitted, NACK received = Received NACK, so we are done

			_vidTX(u8State);
			break;
/* ************************************************************************** */
		case I2C_MR_SLA_ACK:			// SLA+R transmitted, ACK received = Slave transmitter ACKed address
		case I2C_MR_DATA_ACK:			// Data received, ACK returned
		case I2C_SR_SLA_ACK:			// SLA+W received, ACK returned = Addressed, returned ACK
		case I2C_SR_DATA_ACK:			// Data received, ACK returned
		case I2C_SR_GCALL_ACK:			// General call received, ACK returned = Addressed generally, returned ACK
		case I2C_SR_GCALL_Data_ACK:		// General call data received, ACK returned

		case I2C_MR_SLA_NACK:			// SLA+R transmitted, NACK received = Slave transmitter with transmitted address doesn't exists?
		case I2C_MR_DATA_NACK:			// Data received, NACK returned
		case I2C_SR_DATA_NACK:			// Data received, NACK returned
		case I2C_SR_GCALL_Data_NACK:	// General call data received, NACK returned

		case I2C_ST_LAST_Data:			// Last data byte transmitted, ACK received = Received ACK, but we are done already!

			_vidRX(u8State);
			break;
/* ************************************************************************** */
		case I2C_MT_ARB_LOST:			// Arbitration lost in SLA+W or data
//		case I2C_MR_ARB_LOST:			// Arbitration lost in SLA+R or NACK
		case I2C_ST_ARB_LOST:			// Arbitration lost in SLA+RW, SLA+R received, ACK returned
		case I2C_SR_SLA_ARB_LOST:		// Arbitration lost in SLA+RW, SLA+W received, ACK returned
		case I2C_SR_GCALL_ARB_LOST:		// Arbitration lost in SLA+RW, general call received, ACK returned

			_vidStart();
			break;
/* ************************************************************************** */
		case I2C_Stop:					// Stop or repeated start condition received while selected

			_vidRelease();
			break;
/* ************************************************************************** */
		case I2C_NoInfo:				// No state information available
		case I2C_Bus_Error:				// Bus error; Illegal START or STOP condition
		default:

			_vidError();
	}
}

/*************************** E N D (I2C_cfg.c) ******************************/
