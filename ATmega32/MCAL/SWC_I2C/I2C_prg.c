/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

//#include "GPIO_int.h"
//#include "GPIO_cfg.h"

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

static void (*pFuncCallBack_I2C)(void);

static I2C_tstrBuffer strTX_GLB = {
	.m_pu8Data 	= LBTY_NULL,
	.m_u8Size	= LBTY_u8ZERO,
	.m_u8Idx 	= LBTY_u8ZERO,
	.m_u8Status	= TX_IDLE,
};
static I2C_tstrBuffer strRX_GLB = {
	.m_pu8Data 	= LBTY_NULL,
	.m_u8Size	= LBTY_u8ZERO,
	.m_u8Idx 	= LBTY_u8ZERO,
	.m_u8Status	= RX_IDLE,
};

volatile I2C_tstrConfiguration strI2C_Config_GLB = {
	.m_Mode			= I2C_MODE_INIT,
	.m_Status		= I2C_STATE_INIT,
	.m_Prescaler 	= I2C_CLOCK_PRESCALER,
//	.m_Start 		= I2C_START_STATE,
//	.m_Stop 		= I2C_STOP_STATE,
//	.m_ACK 			= I2C_ACK_STATE,
	.m_Address		= I2C_SLAVE_ADDRESS,
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
	strI2C_Config_GLB.m_Mode		= I2C_MODE_INIT;
	strI2C_Config_GLB.m_Status		= I2C_STATE_INIT,
	strI2C_Config_GLB.m_Prescaler 	= I2C_CLOCK_PRESCALER;
//	strI2C_Config_GLB.m_Start 		= I2C_START_STATE;
//	strI2C_Config_GLB.m_Stop 		= I2C_STOP_STATE;
//	strI2C_Config_GLB.m_ACK 		= I2C_ACK_STATE;
	strI2C_Config_GLB.m_Address		= I2C_SLAVE_ADDRESS;
	strI2C_Config_GLB.m_I2CEN 		= I2C_INIT_STATE;
	strI2C_Config_GLB.m_I2CIE 		= I2C_INT_STATE;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strI2C_Config_GLB;
	}
	I2C_vidInit();
}

void I2C_vidInit(void){

// SCL frequency =  F_CPU / (16 + 2 * TWBR * pow(4,TWPS))
	u32 u32TWBR = 1u;
	for(u8 i = strI2C_Config_GLB.m_Prescaler ; i-- ; )	u32TWBR *= 4;
	S_TWI->m_TWBR = (u8)(((f32)F_CPU / I2C_SCL_FREQ - 16) / 2 * u32TWBR);

	S_TWI->m_TWSR.sBits.m_TWPS  = strI2C_Config_GLB.m_Prescaler;

//	S_TWI->m_TWCR.sBits.m_TWSTA = strI2C_Config_GLB.m_Start;
//	S_TWI->m_TWCR.sBits.m_TWSTO = strI2C_Config_GLB.m_Stop;
//	S_TWI->m_TWCR.sBits.m_TWEA  = strI2C_Config_GLB.m_ACK;

	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN;

	S_TWI->m_TWCR.sBits.m_TWIE  = strI2C_Config_GLB.m_I2CIE;
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;		// The TWINT Flag must be cleared by software by writing a logic one to it

	S_TWI->m_TWAR.sBits.m_TWGCE = I2C_WRITE;
	S_TWI->m_TWAR.sBits.m_TWA   = strI2C_Config_GLB.m_Address;

	//GPIO_u8SetPinDirection(I2C_PORT, I2C_SCL_PIN, PIN_OUTPUT);
	//GPIO_u8SetPinDirection(I2C_PORT, I2C_SDA_PIN, PIN_OUTPUT);

}

void I2C_vidEnable(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
}
void I2C_vidDisable(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_RESET;
}

u8 I2C_u8GetStatus(void){
	u8 u8RetValue = GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK);
	switch(u8RetValue){
		case I2C_Bus_Error:
		case I2C_NoInfo:
		case I2C_MT_ARB_LOST:
			strI2C_Config_GLB.m_Mode = I2C_MODE_INIT;
			break;

		case I2C_MT_SLA_ACK:
		case I2C_MT_SLA_NACK:
		case I2C_MT_DATA_ACK:
		case I2C_MT_DATA_NACK:
			strI2C_Config_GLB.m_Mode = I2C_Master_Transmit;
			break;

		case I2C_MR_SLA_ACK:
		case I2C_MR_SLA_NACK:
		case I2C_MR_DATA_ACK:
		case I2C_MR_DATA_NACK:
			strI2C_Config_GLB.m_Mode = I2C_Master_Receive;
			break;

		case I2C_SR_SLA_ACK:
		case I2C_SR_SLA_ARB_LOST:
		case I2C_SR_GCALL_ACK:
		case I2C_SR_GCALL_ARB_LOST:
		case I2C_SR_DATA_ACK:
		case I2C_SR_DATA_NACK:
		case I2C_SR_GCALL_Data_ACK:
		case I2C_SR_GCALL_Data_ARB_LOST:
			strI2C_Config_GLB.m_Mode = I2C_Slave_Receive;
			break;

		case I2C_ST_SLA_ACK:
		case I2C_ST_ARB_LOST:
		case I2C_ST_DATA_ACK:
		case I2C_ST_DATA_NACK:
		case I2C_ST_LAST_Data:
			strI2C_Config_GLB.m_Mode = I2C_Slave_Transmit;
			break;

		default:
			break;
	}
	return (u8)u8RetValue;
}

/********************************************************************************************************************/

//LCTY_INLINE u8 I2C_u8CollisionFlag(void){return S_TWI->m_TWCR.sBits.m_TWWC;}
//LCTY_INLINE u8 I2C_u8TransmitFlag(void) {return S_TWI->m_TWCR.sBits.m_TWINT;}

LCTY_INLINE void I2C_vidWait(void){
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;// The TWINT Flag must be cleared by software by writing a logic one to it
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
	while(S_TWI->m_TWCR.sBits.m_TWINT);
}


LBTY_tenuErrorStatus I2C_u8SetSTART(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_SET;
	I2C_vidWait();

	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) == I2C_Start){
	}else{
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetRepeatSTART(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_SET;
	I2C_vidWait();

	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) == I2C_RepeatStart){
	}else{
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetAddress(u8 u8Address, u8 Operation){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if((Operation == I2C_WRITE) || (Operation == I2C_WRITE)){

		S_TWI->m_TWAR.sBits.m_TWA   = strI2C_Config_GLB.m_Address = u8Address;
		S_TWI->m_TWAR.sBits.m_TWGCE = Operation;
		S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_RESET;
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

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetData(u8 u8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	S_TWI->m_TWDR = u8Data;
	if(S_TWI->m_TWCR.sBits.m_TWWC){
		u8RetErrorState = LBTY_WRITE_ERROR;
	}else{
		I2C_vidWait();

		switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
			case I2C_MT_DATA_ACK:
			case I2C_MT_DATA_NACK:
				break;
			default:
				u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8GetDataNACK(u8* pu8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	S_TWI->m_TWCR.sBits.m_TWEA = LBTY_RESET;
	I2C_vidWait();

	switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
		case I2C_MR_DATA_NACK:
			*pu8Data = S_TWI->m_TWDR;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8GetDataACK(u8* pu8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	S_TWI->m_TWCR.sBits.m_TWEA = LBTY_SET;
	I2C_vidWait();

	switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
		case I2C_MR_DATA_ACK:
			*pu8Data = S_TWI->m_TWDR;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8SetSTOP(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	S_TWI->m_TWCR.sBits.m_TWSTO = LBTY_SET;
	I2C_vidWait();

	if(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK) == I2C_Stop){
	}else{
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus I2C_u8SendBuffer(u8* pu8Data, u8 u8Size){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu8Data == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(strTX_GLB.m_u8Status == TX_IDLE){
			strTX_GLB.m_pu8Data  = pu8Data;
			strTX_GLB.m_u8Size   = u8Size;
			strTX_GLB.m_u8Idx    = LBTY_u8ZERO;
			strTX_GLB.m_u8Status = TX_BUSY;

			strI2C_Config_GLB.m_Status = I2C_IDLE;
			I2C_vidTX_Step();
			I2C_vidEnableINT();
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus I2C_u8ReceiveBuffer(u8* pu8Data, u8 u8Size){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu8Data == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(strRX_GLB.m_u8Status == RX_IDLE){
			strRX_GLB.m_pu8Data  = pu8Data;
			strRX_GLB.m_u8Size   = u8Size;
			strRX_GLB.m_u8Idx    = LBTY_u8ZERO;
			strRX_GLB.m_u8Status = RX_BUSY;

			strI2C_Config_GLB.m_Status = I2C_IDLE;
			I2C_vidRX_Step();
			I2C_vidEnableINT();
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
	switch(I2C_u8GetStatus()){
		case I2C_Master_IDLE:
		case I2C_Slave_IDLE:
			if((strRX_GLB.m_u8Status == RX_IDLE) && (strTX_GLB.m_u8Status == TX_IDLE)){
				pFuncCallBack_I2C();
			}
			break;
		case I2C_Master_Transmit:
		case I2C_Slave_Transmit:
			I2C_vidTX_Step();
			break;
		case I2C_Master_Receive:
		case I2C_Slave_Receive:
			I2C_vidRX_Step();
			break;
		default:
			break;
	}
}

void I2C_vidTX_Step(void){

	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_RESET;
	switch(strI2C_Config_GLB.m_Status){
		case I2C_IDLE:		I2C_vidIDLE();		I2C_vidTX_Step();	return;
		case I2C_START:		I2C_vidSTART();							break;
		case I2C_ADDRESS:	I2C_vidAddress();	I2C_vidTX_Step();	return;
		case I2C_RW:		I2C_vidRW();							break;
		case I2C_ACK:		I2C_vidACK();		I2C_vidTX_Step();	return;
		case I2C_DATA:
			switch(strI2C_Config_GLB.m_Mode){
				case I2C_Master_Transmit:
				case I2C_Slave_Transmit:
					I2C_vidData(&strTX_GLB.m_pu8Data[strTX_GLB.m_u8Idx++]);
					if(strTX_GLB.m_u8Idx < strTX_GLB.m_u8Size){
						strI2C_Config_GLB.m_Status  = I2C_IDLE;
						I2C_vidTX_Step();
						return;
					}else{
						strTX_GLB.m_u8Status = TX_IDLE;
					}
					break;
				case I2C_Master_Receive:
				case I2C_Slave_Receive:
				case I2C_Master_IDLE:
				case I2C_Slave_IDLE:
				default:
					break;
			}
			break;
		case I2C_STOP:		I2C_vidSTOP();							break;
		case I2C_ERROR:		I2C_vidERROR();		I2C_vidTX_Step();	return;
		default:			strI2C_Config_GLB.m_Status = I2C_IDLE;	break;
	}
	I2C_vidResetINT_Flag();
}

void I2C_vidRX_Step(void){

	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_RESET;
	switch(strI2C_Config_GLB.m_Status){
		case I2C_IDLE:		I2C_vidIDLE();		I2C_vidRX_Step();	return;
		case I2C_START:		I2C_vidSTART();							break;
		case I2C_ADDRESS:	I2C_vidAddress();	I2C_vidRX_Step();	return;
		case I2C_RW:		I2C_vidRW();							break;
		case I2C_ACK:		I2C_vidACK();							break;
		case I2C_DATA:
			switch(strI2C_Config_GLB.m_Mode){
				case I2C_Master_Receive:
				case I2C_Slave_Receive:
					I2C_vidData(&strRX_GLB.m_pu8Data[strRX_GLB.m_u8Idx++]);
					if(strRX_GLB.m_u8Idx < strRX_GLB.m_u8Size){
						strI2C_Config_GLB.m_Status  = I2C_IDLE;
						I2C_vidRX_Step();
						return;
					}else{
						strRX_GLB.m_u8Status = RX_IDLE;
					}
					break;
				case I2C_Master_Transmit:
				case I2C_Slave_Transmit:
				case I2C_Master_IDLE:
				case I2C_Slave_IDLE:
				default:
					break;
			}
			break;
		case I2C_STOP:		I2C_vidSTOP();							break;
		case I2C_ERROR:		I2C_vidERROR();		I2C_vidRX_Step();	return;
		default:			strI2C_Config_GLB.m_Status = I2C_IDLE;	break;
	}
	I2C_vidResetINT_Flag();
}

/*************************** E N D (I2C_prg.c) ******************************/
