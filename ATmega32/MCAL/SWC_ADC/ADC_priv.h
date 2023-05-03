/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Mar 27, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define IS_CHANNEL(channel)		((channel >= ADC0) && (channel <= ADC7))

#define ADC_PORT				A

#define ADC_MAX					1023u
#define ADC_VBG_1V22			1.22f

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* ADC_PRIV_H_ */
/*************************** E N D (ADC_priv.h) ******************************/
