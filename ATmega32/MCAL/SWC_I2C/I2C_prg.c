/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

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

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void I2C_vidInit(void){

// SCL frequency =  F_CPU / (16 + 2 * TWBR * pow(4,TWPS))
	u32 u32TWBR = 1u;
	for(u8 i = I2C_CLOCK_PRESCALER ; i-- ; )	u32TWBR *= 4;
	S_TWI->m_TWBR = (F_CPU / I2C_SCL_FREQ - 16) / 2 * u32TWBR;

	S_TWI->m_TWAR.sBits.m_TWGCE = LBTY_RESET;
	S_TWI->m_TWAR.sBits.m_TWA   = I2C_SLAVE_ADDRESS;

	S_TWI->m_TWSR.sBits.m_TWPS  = I2C_CLOCK_PRESCALER;

	S_TWI->m_TWCR.sBits.m_TWSTA = I2C_START_STATE;
	S_TWI->m_TWCR.sBits.m_TWSTO = I2C_STOP_STATE;
	S_TWI->m_TWCR.sBits.m_TWEA  = I2C_ACK_STATE;

	S_TWI->m_TWCR.sBits.m_TWEN  = LBTY_SET;

	S_TWI->m_TWCR.sBits.m_TWIE  = I2C_INT_STATE;
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_RESET;

	S_TWI->m_TWCR.sBits.m_TWWC;

	//GPIO_u8SetPinDirection(I2C_PORT, I2C_SCL_PIN, PIN_OUTPUT);
	//GPIO_u8SetPinDirection(I2C_PORT, I2C_SDA_PIN, PIN_OUTPUT);

}

void I2C_vidEnable(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = LBTY_SET;
}
void I2C_vidDisable(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = LBTY_RESET;
}

void I2C_vidEnableINT(void){
	S_TWI->m_TWCR.sBits.m_TWIE  = LBTY_SET;
}
void I2C_vidDisableINT(void){
	S_TWI->m_TWCR.sBits.m_TWIE  = LBTY_RESET;
}


void I2C_vidSlaveInit(u8 u8Address){

	S_TWI->m_TWAR.sBits.m_TWGCE = LBTY_RESET;
	S_TWI->m_TWAR.sBits.m_TWA   = u8Address;

	S_TWI->m_TWCR.sBits.m_TWSTO = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWEA  = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;

	S_TWI->m_TWCR.sBits.m_TWIE  = I2C_INT_STATE;
	S_TWI->m_TWCR.sBits.m_TWEN  = LBTY_SET;
}

void I2C_vidWrite(u8 u8Char){
	S_TWI->m_TWDR = u8Char;
	I2C_vidWait();
}

void I2C_vidRead_ACK(u8* pu8Char){
	S_TWI->m_TWCR.sBits.m_TWEA  = LBTY_SET;
	I2C_vidWait();
	*pu8Char = S_TWI->m_TWDR;
}

void I2C_vidRead_NACK(u8* pu8Char){
	S_TWI->m_TWCR.sBits.m_TWEA  = LBTY_RESET;
	I2C_vidWait();
	*pu8Char = S_TWI->m_TWDR;
}

void I2C_vidSTART(void){
	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_SET;
	I2C_vidWait();
}

void I2C_vidAddress(u8 u8Address){
	S_TWI->m_TWAR.sBits.m_TWA   = u8Address;
	I2C_vidWait();
}

void I2C_vidSTOP(void){
	S_TWI->m_TWCR.sBits.m_TWSTO = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWEN  = LBTY_SET;
}

u8 I2C_u8GetStatus(void){
	return S_TWI->m_TWSR.sBits.m_TWS << I2C_STATUS_BIT;
}

u8 I2C_u8SlaveAvailable(void){
	u8 u8RetStatus = LBTY_RESET;
	I2C_vidWait();

	if(I2C_u8GetStatus() == I2C_MT_SLA_ACK){
		u8RetStatus = LBTY_SET;
	}
	return u8RetStatus;
}

/*************************** E N D (I2C_prg.c) ******************************/
