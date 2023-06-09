/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_cfg.h													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 27, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if 	AMIT_KIT

//#define ADC_CHANNELS_NUM		4

#define ADC_CH0					ADC0
#define ADC_CH1					ADC1
#define ADC_CH2					ADC2
#define ADC_CH3					ADC3

#elif	ETA32_KIT

//#define ADC_CHANNELS_NUM		2

#define ADC_CH0					ADC0
#define ADC_CH1					ADC1

#else

//#define ADC_CHANNELS_NUM		8

#define ADC_CH0					ADC0
#define ADC_CH1					ADC1
#define ADC_CH2					ADC2
#define ADC_CH3					ADC3
#define ADC_CH4					ADC4
#define ADC_CH5					ADC5
#define ADC_CH6					ADC6
#define ADC_CH7					ADC7

#endif

#define ADC_ADJUSTMENT			LBTY_RESET

/** SFIOR **/
#define ADC_TRIG_SRC			ADC_Free_Running_Mode

/** ADC Control State **/
#define ADC_INIT_STATE			LBTY_SET
#define ADC_AUTO_TRIG			LBTY_RESET
#define ADC_IRQ_STATE			LBTY_RESET
#define ADC_PRESCALER			ADC_Division_Factor_2

/** ADC MUX **/
#define ADC_V_REF_SRC			ADC_AVCC
#define ADC_V_REF				5u

#define ADC_READ_DELAY			26u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

extern const u8 kau8ActiveChannel_LGB[ADC_CHANNELS_NUM];

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* ADC_CFG_H_ */
/*************************** E N D (ADC_cfg.h) ******************************/
