/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SEG_cfg.h													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SEG_CFG_H_
#define SEG_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if 	AMIT_KIT

#define SEG_DECODER
#define SEG_PORT_COM0		C
#define SEG_PIN_COM0		AMIT_7Seg_COM0
#define SEG_PORT_COM1		C
#define SEG_PIN_COM1		AMIT_7Seg_COM1

#define SEG_PINS			4u
#define SEG_PORT_DATA		C
#define SEG_A				AMIT_7Seg_A
#define SEG_B				AMIT_7Seg_B
#define SEG_C				AMIT_7Seg_C
#define SEG_D				AMIT_7Seg_D
#define SEG_h				AMIT_C0

#elif	ETA32_KIT

#define SEG_DECODER
#define SEG_PORT_COM0		B
#define SEG_PIN_COM0		Eta32_7Seg_COM0
#define SEG_PORT_COM1		B
#define SEG_PIN_COM1		Eta32_7Seg_COM1
#define SEG_PORT_COM2		A
#define SEG_PIN_COM2		Eta32_7Seg_COM2
#define SEG_PORT_COM3		A
#define SEG_PIN_COM3		Eta32_7Seg_COM3

#define SEG_PINS			4u
#define SEG_PORT_DATA		B
#define SEG_A				Eta32_7Seg_A
#define SEG_B				Eta32_7Seg_B
#define SEG_C				Eta32_7Seg_C
#define SEG_D				Eta32_7Seg_D
#define SEG_h				Eta32_LED_R

#else

#define SEG_PORT_COM0		C
#define SEG_PIN_COM0		0u
#define SEG_PORT_COM1		C
#define SEG_PIN_COM1		1u
#define SEG_PORT_COM2		C
#define SEG_PIN_COM2		2u
#define SEG_PORT_COM3		C
#define SEG_PIN_COM3		3u
#define SEG_PORT_COM4		C
#define SEG_PIN_COM4		4u
#define SEG_PORT_COM5		C
#define SEG_PIN_COM5		5u

#define SEG_PINS			8u
#define SEG_PORT_DATA		B
#define SEG_a				0u
#define SEG_b				1u
#define SEG_c				2u
#define SEG_d				3u
#define SEG_e				4u
#define SEG_f				5u
#define SEG_g				6u
#define SEG_h				7u

#endif

#define SEG_FLOAT_MUL		100
#define SEG_DELAY			5u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* SEG_CFG_H_ */
/*************************** E N D (SEG_cfg.h) ******************************/
