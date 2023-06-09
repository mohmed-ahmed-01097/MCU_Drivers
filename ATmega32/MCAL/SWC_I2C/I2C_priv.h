/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 13, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef I2C_PRIV_H_
#define I2C_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define I2C_STATUS_BIT					3u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

static inline void I2C_vidWait(void){
	S_TWI->m_TWCR.sBits.m_TWINT = LBTY_SET;
	S_TWI->m_TWCR.sBits.m_TWEN  = LBTY_SET;
	while(!S_TWI->m_TWCR.sBits.m_TWINT);
}

#endif /* I2C_PRIV_H_ */
/*************************** E N D (I2C_priv.h) ******************************/
