/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"
#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

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
const GPIO_tstrPinConfig kau8I2C_PinConfig_GLB[] = {
		{.m_Port = I2C_PORT, .m_Pin = I2C_SDA_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_UP},
		{.m_Port = I2C_PORT, .m_Pin = I2C_SCL_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_UP}
};
//https://www.electronicwings.com/avr-atmega/atmega1632-i2c
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

static volatile u8 I2C_u8Flag_GLB;

static void (*pFuncCallBack_I2C)(void) = INTP_vidCallBack;

volatile I2C_tstrBuffer strBuffer_GLB = {
	.m_u8Add.u_Reg = LBTY_u8ZERO,
	.m_pu8Data     = LBTY_NULL,
	.m_u8Size      = LBTY_u8ZERO,
	.m_u8Idx       = LBTY_u8ZERO,
	.m_u8Status	   = I2C_IDLE
};

static volatile I2C_tstrConfiguration strI2C_Config_GLB = {
	.m_Mode			= I2C_MODE,
	.m_Address		= I2C_SLAVE_ADDRESS,
	.m_Prescaler 	= I2C_CLOCK_PRESCALER,
	.m_I2CEN 		= I2C_INIT_STATE,
	.m_I2CIE 		= I2C_INT_STATE,
};

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void I2C_vidSetConfig(I2C_tstrConfiguration const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strI2C_Config_GLB = *pstrConfig;
	}
	I2C_vidInit();
}

void I2C_vidResetConfig(I2C_tstrConfiguration* const pstrConfig){
	strI2C_Config_GLB.m_Mode		= I2C_MODE;
	strI2C_Config_GLB.m_Address		= I2C_SLAVE_ADDRESS;
	strI2C_Config_GLB.m_Prescaler 	= I2C_CLOCK_PRESCALER;
	strI2C_Config_GLB.m_I2CEN 		= I2C_INIT_STATE;
	strI2C_Config_GLB.m_I2CIE 		= I2C_INT_STATE;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strI2C_Config_GLB;
	}
	I2C_vidInit();
}

void I2C_vidInit(void){

	if(strI2C_Config_GLB.m_Mode == I2C_Master){
		/*SCL frequency =  F_CPU / (16 + 2 * TWBR * pow(4,TWPS))*/
		volatile u32 u32TWBR = 1u;
		for(u8 i = strI2C_Config_GLB.m_Prescaler ; i-- ; )	u32TWBR *= 4;
		S_TWI->m_TWBR = (u8)(((f32)F_CPU / I2C_SCL_FREQ - 16) / 2 * u32TWBR);

		S_TWI->m_TWSR.sBits.m_TWPS  = strI2C_Config_GLB.m_Prescaler;

		I2C_DEF(0u, 0);
	}else if(strI2C_Config_GLB.m_Mode == I2C_Slave){
		S_TWI->m_TWBR = LBTY_u8ZERO;
		I2C_DEF(1u, TWEA);
	}

	GPIO_u8PinInit(kau8I2C_PinConfig_GLB[0]);
	GPIO_u8PinInit(kau8I2C_PinConfig_GLB[1]);

	S_TWI->m_TWAR.sBits.m_TWGCE = LBTY_RESET;
	S_TWI->m_TWAR.sBits.m_TWA   = strI2C_Config_GLB.m_Address;

//	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_RESET;
//	S_TWI->m_TWCR.sBits.m_TWSTO = LBTY_RESET;
//	S_TWI->m_TWCR.sBits.m_TWEA  = LBTY_RESET;

	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN;
	S_TWI->m_TWCR.sBits.m_TWIE  = strI2C_Config_GLB.m_I2CIE;
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;		// The TWINT Flag must be cleared by software by writing a logic one to it

}

void I2C_vidEnable(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
}
void I2C_vidDisable(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_RESET;
}

u8 I2C_u8GetStatus(void){
	return (u8)GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK);
}
u8 I2C_u8GetINTF(void){
	return (u8)S_TWI->m_TWCR.sBits.m_TWIE;
}

/********************************************************************************************************************/

void I2C_vidWait(void){
//	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;// The TWINT Flag must be cleared by software by writing a logic one to it
	I2C_u8Flag_GLB = LBTY_RESET;
	while((!S_TWI->m_TWCR.sBits.m_TWINT) && (!I2C_u8Flag_GLB));
//	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;// The TWINT Flag must be cleared by software by writing a logic one to it
}

LBTY_tenuErrorStatus I2C_u8SetSTART(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	I2C_DEF(1u, TWSTA);
	I2C_vidWait();

	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) != I2C_Start){
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetRepeatSTART(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	I2C_DEF(1u, TWSTA);
	I2C_vidWait();

	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) != I2C_RepeatStart){
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetAddress(u8 u8Address, u8 Operation){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if((Operation == I2C_WRITE) || (Operation == I2C_READ)){
		S_TWI->m_TWDR = (u8Address<<1) | (Operation & 0x01);
		I2C_DEF(0u, 0);
		I2C_vidWait();

		switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
			case I2C_MT_SLA_ACK:
			case I2C_MR_SLA_ACK:
				break;
			case I2C_MT_SLA_NACK:
			case I2C_MR_SLA_NACK:
			default:
				u8RetErrorState = LBTY_NOK;
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	if(u8RetErrorState)		I2C_u8SetSTOP();
	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8GetRequest(u8* Operation){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	I2C_DEF(1u, TWEA);
	I2C_vidWait();

	switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
		case I2C_ST_SLA_ACK:
		case I2C_ST_ARB_LOST:
			*Operation = I2C_WRITE;
			break;
		case I2C_SR_SLA_ACK:
		case I2C_SR_SLA_ARB_LOST:
			*Operation = I2C_READ;
			break;
		case I2C_SR_GCALL_ACK:
		case I2C_SR_GCALL_ARB_LOST:
			*Operation = I2C_READ;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetData(u8 u8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	S_TWI->m_TWDR = u8Data;

	if(S_TWI->m_TWCR.sBits.m_TWWC){
		u8RetErrorState = LBTY_WRITE_ERROR;
	}else{

   		if(I2C_MODE == I2C_Master){
   			I2C_DEF(0u, 0);
   			I2C_vidWait();

   			switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
   				case I2C_MT_DATA_ACK:
   				case I2C_MT_DATA_NACK:
   					break;
   				default:
   					u8RetErrorState = LBTY_NOK;
   			}
   		}
   		if(I2C_MODE == I2C_Slave){
   			I2C_DEF(1u, TWEA);
   			I2C_vidWait();

   			switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
   				case I2C_ST_DATA_ACK:
   					break;
   				case I2C_ST_DATA_NACK:
   				case I2C_Stop:
   					S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;		// The TWINT Flag must be cleared by software by writing a logic one to it
   					u8RetErrorState = LBTY_NOK;
   					break;
   				case I2C_ST_LAST_Data:
   				default:
   					u8RetErrorState = LBTY_NOK;
   			}
   		}
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8GetData(u8* pu8Data, u8 u8ACK){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	I2C_DEF(u8ACK, TWEA);
	I2C_vidWait();

	if(I2C_MODE == I2C_Master){
		switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
			case I2C_MR_DATA_ACK:
			case I2C_MR_DATA_NACK:
				*pu8Data = S_TWI->m_TWDR;
				break;
			default:
				u8RetErrorState = LBTY_NOK;
		}

	}
	if(I2C_MODE == I2C_Slave){
		switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
			case I2C_SR_DATA_ACK:
			case I2C_SR_DATA_NACK:
			case I2C_SR_GCALL_Data_ACK:
			case I2C_SR_GCALL_Data_NACK:
				*pu8Data = S_TWI->m_TWDR;
				break;
			case I2C_Stop:
				S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;		// The TWINT Flag must be cleared by software by writing a logic one to it
				u8RetErrorState = LBTY_NOK;
				break;
			default:
				u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetSTOP(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	I2C_DEF(1u, TWSTO);
//	I2C_vidWait();
	while(S_TWI->m_TWCR.sBits.m_TWSTO);

	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) != I2C_Stop){
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

void I2C_u8SetChar(u8 u8char, u8 u8Address){
	while(S_TWI->m_TWCR.sBits.m_TWIE == LBTY_SET);
	while(1){
		if(I2C_u8SetSTART())						continue;
		if(I2C_u8SetAddress(u8Address, I2C_WRITE))	continue;
		break;
	}vidMyDelay_ms(I2C_SLAVE_WAIT);
	I2C_u8SetData(u8char);
	I2C_u8SetSTOP();
}
void I2C_u8GetChar(u8* pu8char, u8 u8Address){
	while(S_TWI->m_TWCR.sBits.m_TWIE == LBTY_SET);
	while(1){
		if(I2C_u8SetSTART())						continue;
		if(I2C_u8SetAddress(u8Address, I2C_READ))	continue;
		break;
	}vidMyDelay_ms(I2C_SLAVE_WAIT);
	I2C_u8GetData(pu8char, LBTY_SET);
	I2C_u8SetSTOP();
}

void I2C_SlaveListen(u8* pu8char, u8 u8Size){
	u8 u8Operation;
	while(I2C_u8GetRequest(&u8Operation));
	if(u8Operation == I2C_WRITE){
		for(u8 i = u8Size ; i-- ; ){
			if(I2C_u8SetData(*pu8char++))						break;
		}
	}else if(u8Operation == I2C_READ){
		for(u8 i = u8Size ; i-- ; ){
			if(I2C_u8GetData( pu8char, i?LBTY_SET:LBTY_RESET)) 	break;
		}
	}
}
/********************************************************************************************************************/

LBTY_tenuErrorStatus I2C_u8SendBuffer(u8* pu8Data, u8 u8Size, u8 u8Address){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu8Data == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(S_TWI->m_TWCR.sBits.m_TWIE == LBTY_RESET && strBuffer_GLB.m_u8Status == I2C_IDLE){
			strBuffer_GLB.m_u8Add.sBits.m_ADD = u8Address;
			strBuffer_GLB.m_u8Add.sBits.m_OP  = I2C_WRITE;
			strBuffer_GLB.m_pu8Data  = pu8Data;
			strBuffer_GLB.m_u8Size   = u8Size;
			strBuffer_GLB.m_u8Idx    = LBTY_u8ZERO;
			strBuffer_GLB.m_u8Status = I2C_IDLE;

			I2C_vidInit();
			_vidStart();
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8ReceiveBuffer(u8* pu8Data, u8 u8Size, u8 u8Address){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu8Data == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(S_TWI->m_TWCR.sBits.m_TWIE == LBTY_RESET && strBuffer_GLB.m_u8Status == I2C_IDLE){
			strBuffer_GLB.m_u8Add.sBits.m_ADD = u8Address;
			strBuffer_GLB.m_u8Add.sBits.m_OP  = I2C_READ;
			strBuffer_GLB.m_pu8Data  = pu8Data;
			strBuffer_GLB.m_u8Size   = u8Size;
			strBuffer_GLB.m_u8Idx    = LBTY_u8ZERO;
			strBuffer_GLB.m_u8Status = I2C_IDLE;

			I2C_vidInit();
			_vidStart();
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

void I2C_vidEnableINT(void) {S_TWI->m_TWCR.sBits.m_TWIE = strI2C_Config_GLB.m_I2CIE = LBTY_SET;}
void I2C_vidDisableINT(void){S_TWI->m_TWCR.sBits.m_TWIE = strI2C_Config_GLB.m_I2CIE = LBTY_RESET;}

void I2C_vidResetINT_Flag(void){
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;// The TWINT Flag must be cleared by software by writing a logic one to it
}

void I2C_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	pFuncCallBack_I2C = pCallBack;
}

ISR(TWI_vect){
	switch(strBuffer_GLB.m_u8Status){
		case I2C_IDLE:
			break;
		case I2C_START:
		case I2C_ADDRESS:
		case I2C_DATA:
		case I2C_STOP:
			I2C_vidStep();
			if(strBuffer_GLB.m_u8Status == I2C_IDLE)
				pFuncCallBack_I2C();
			break;
		case I2C_ERROR:
			break;
		default:
			I2C_vidInit();
			break;
	}

	I2C_u8Flag_GLB = LBTY_SET;
}

/*************************** E N D (I2C_prg.c) ******************************/
