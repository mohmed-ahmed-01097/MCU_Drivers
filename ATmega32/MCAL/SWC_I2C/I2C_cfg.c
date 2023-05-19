/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
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

extern volatile I2C_tstrConfiguration strI2C_Config_GLB;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void I2C_vidIDLE(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWIE  = strI2C_Config_GLB.m_I2CIE = LBTY_SET;
	strI2C_Config_GLB.m_Status  = I2C_START;
}
void I2C_vidSTART(void){
	S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
	strI2C_Config_GLB.m_Status  = I2C_ADDRESS;
}
void I2C_vidAddress(void){
	switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
		case I2C_Start:
		case I2C_RepeatStart:
			S_TWI->m_TWAR.sBits.m_TWA   = strI2C_Config_GLB.m_Address;
			strI2C_Config_GLB.m_Status  = I2C_RW;
			break;
		default:
			strI2C_Config_GLB.m_Status = I2C_ERROR;
	}
}
void I2C_vidRW(void){
	switch(strI2C_Config_GLB.m_Mode){
		case I2C_Master_Transmit:
		case I2C_Slave_Transmit:
			S_TWI->m_TWAR.sBits.m_TWGCE = I2C_WRITE;
			S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_RESET;
			S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
			strI2C_Config_GLB.m_Status  = I2C_ACK;
			break;
		case I2C_Master_Receive:
		case I2C_Slave_Receive:
			S_TWI->m_TWAR.sBits.m_TWGCE = I2C_READ;
			S_TWI->m_TWCR.sBits.m_TWSTA = LBTY_RESET;
			S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
			strI2C_Config_GLB.m_Status  = I2C_ACK;
			break;
		case I2C_Master_IDLE:
		case I2C_Slave_IDLE:
		default:
			S_TWI->m_TWAR.sBits.m_TWGCE = I2C_WRITE;
			strI2C_Config_GLB.m_Status  = I2C_ERROR;
			break;
	}
}
void I2C_vidACK(void){
	switch(GET_MASK(S_TWI->m_TWSR.u_Reg, I2C_STATUS_MASK)){
		case I2C_MT_SLA_ACK:
		case I2C_MT_SLA_NACK:
		case I2C_MR_SLA_NACK:
			strI2C_Config_GLB.m_Status = I2C_DATA;
			break;
		case I2C_MT_DATA_ACK:
		case I2C_MT_DATA_NACK:
		case I2C_MR_DATA_NACK:
			strI2C_Config_GLB.m_Status = I2C_STOP;
			break;
		case I2C_MR_SLA_ACK:
			S_TWI->m_TWCR.sBits.m_TWEA  = LBTY_SET;
			strI2C_Config_GLB.m_Status = I2C_DATA;
			break;
		case I2C_MR_DATA_ACK:
			S_TWI->m_TWCR.sBits.m_TWEA  = LBTY_SET;
			strI2C_Config_GLB.m_Status = I2C_STOP;
			break;
		case I2C_MT_ARB_LOST:
		default:
			strI2C_Config_GLB.m_Status = I2C_ERROR;
	}
}
void I2C_vidData(u8* pu8Data){
	switch(strI2C_Config_GLB.m_Mode){
		case I2C_Master_Transmit:
		case I2C_Slave_Transmit:
			S_TWI->m_TWDR = *pu8Data;
			S_TWI->m_TWCR.sBits.m_TWEN = strI2C_Config_GLB.m_I2CEN = LBTY_SET;
			strI2C_Config_GLB.m_Status = I2C_ACK;
			break;
		case I2C_Master_Receive:
		case I2C_Slave_Receive:
			*pu8Data = S_TWI->m_TWDR;
			strI2C_Config_GLB.m_Status = I2C_ACK;
			break;
		case I2C_Master_IDLE:
		case I2C_Slave_IDLE:
		default:
			strI2C_Config_GLB.m_Status = I2C_ERROR;
			break;
	}
}
void I2C_vidSTOP(void){
	S_TWI->m_TWCR.sBits.m_TWSTO = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_RESET;
	S_TWI->m_TWCR.sBits.m_TWIE  = strI2C_Config_GLB.m_I2CIE = LBTY_RESET;
	strI2C_Config_GLB.m_Status  = I2C_IDLE;
}
void I2C_vidERROR(void){
	S_TWI->m_TWCR.sBits.m_TWEN  = strI2C_Config_GLB.m_I2CEN = LBTY_RESET;
	strI2C_Config_GLB.m_Status  = I2C_IDLE;
}

/*************************** E N D (I2C_cfg.c) ******************************/
