/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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

const  u8 kau8ActiveChannel_LGB[] = {
#ifdef ADC_CH0
		ADC_CH0
#endif
#ifdef ADC_CH1
		, ADC_CH1
#endif
#ifdef ADC_CH2
		, ADC_CH2
#endif
#ifdef ADC_CH3
		, ADC_CH3
#endif
#ifdef ADC_CH4
		, ADC_CH4
#endif
#ifdef ADC_CH5
		, ADC_CH5
#endif
#ifdef ADC_CH6
		, ADC_CH6
#endif
#ifdef ADC_CH7
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
