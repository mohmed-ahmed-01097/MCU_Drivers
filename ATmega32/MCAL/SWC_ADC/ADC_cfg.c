/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_cfg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 27, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "ADC_int.h"
#include "ADC_cfg.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

const  u8 pu8ActiveChannel_LGB[ADC_CHANNELS_NUM] = {
#if (ADC_CHANNELS_NUM >= 1)
		ADC_CH0
#endif
#if (ADC_CHANNELS_NUM >= 2)
		, ADC_CH1
#endif
#if (ADC_CHANNELS_NUM >= 3)
		, ADC_CH2
#endif
#if (ADC_CHANNELS_NUM >= 4)
		, ADC_CH3
#endif
#if (ADC_CHANNELS_NUM >= 5)
		, ADC_CH4
#endif
#if (ADC_CHANNELS_NUM >= 6)
		, ADC_CH5
#endif
#if (ADC_CHANNELS_NUM >= 7)
		, ADC_CH6
#endif
#if (ADC_CHANNELS_NUM >= 8)
		, ADC_CH7
#endif
};

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


/*************************** E N D (ADC_cfg.c) ******************************/
