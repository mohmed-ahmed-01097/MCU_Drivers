/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : USART_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 10, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef USART_CFG_H_
#define USART_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define USART_OPERATION_MODE				USART_Asynchronous
#define USART_OPERATION_POLARITY			USART_Transmit_Rising_Receive_Falling
#define USART_OPERATION_SPEED				USART_Speed_x1
#define USART_OPERATION_MULTI_PROCESSOR		LBTY_RESET
#define USART_OPERATION_FREQ				F_CPU

#define USART_BUAD_RATE_INIT				USART_BuadRate_9600
#define USART_CHAR_SIZE_INIT				USART_8_bit
#define USART_PARITY_MODE_INIT				USART_Parity_Even
#define USART_STOP_BIT_INIT					USART_Stop_1_bit

#define USART_TRANSMIT_INT					LBTY_SET
#define USART_RECEIVE_INT					LBTY_SET

#define USART_TRANSMIT_COMPLETE_INT			LBTY_RESET
#define USART_RECEIVE_COMPLETE_INT			LBTY_RESET
#define USART_DATA_REG_EMPTY_INT			LBTY_RESET

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* USART_CFG_H_ */
/*************************** E N D (USART_cfg.h) ******************************/
