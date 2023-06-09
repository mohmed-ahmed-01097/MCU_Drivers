/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : I2C_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 13, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef I2C_CFG_H_
#define I2C_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define I2C_PORT			C
#define I2C_SDA_PIN			GPIO_I2C_SDA
#define I2C_SCL_PIN			GPIO_I2C_SCL

#ifdef I2C_MASTER

#else
#ifdef I2C_SLAVE

#endif
#endif

#define I2C_SLAVE_ADDRESS			0x7A
#define I2C_SCL_FREQ				1000u
#define I2C_CLOCK_PRESCALER			I2C_Prescaler_4

#define I2C_START_STATE				LBTY_SET
#define I2C_STOP_STATE				LBTY_SET
#define I2C_ACK_STATE				LBTY_SET

#define I2C_INT_STATE				LBTY_SET
#define I2C_ACK_STATE				LBTY_SET

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* I2C_CFG_H_ */
/*************************** E N D (I2C_cfg.h) ******************************/
