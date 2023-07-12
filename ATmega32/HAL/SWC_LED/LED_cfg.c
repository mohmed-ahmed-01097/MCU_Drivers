/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LED_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_int.h"
#include "LED_cfg.h"
#include "LED_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
const LED_tstrConfig kau8LEDConfiguration_LGB[LED_Num] = {
#ifdef LED0
		 {.m_Connection = LED0_CON, .m_PinCfg =
		{.m_Port = LED0_PORT, .m_Pin = LED0_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED0_CON}}
#endif
#ifdef LED1
		,{.m_Connection = LED1_CON, .m_PinCfg =
		{.m_Port = LED1_PORT, .m_Pin = LED1_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED1_CON}}
#endif
#ifdef LED2
		,{.m_Connection = LED2_CON, .m_PinCfg =
		{.m_Port = LED2_PORT, .m_Pin = LED2_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED2_CON}}
#endif
#ifdef LED3
		,{.m_Connection = LED3_CON, .m_PinCfg =
		{.m_Port = LED3_PORT, .m_Pin = LED3_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED3_CON}}
#endif
#ifdef LED4
		,{.m_Connection = LED4_CON, .m_PinCfg =
		{.m_Port = LED4_PORT, .m_Pin = LED4_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED4_CON}}
#endif
#ifdef LED5
		,{.m_Connection = LED5_CON, .m_PinCfg =
		{.m_Port = LED5_PORT, .m_Pin = LED5_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED5_CON}}}
#endif
#ifdef LED6
		,{.m_Connection = LED6_CON, .m_PinCfg =
		{.m_Port = LED6_PORT, .m_Pin = LED6_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED6_CON}}
#endif
#ifdef LED7
		,{.m_Connection = LED7_CON, .m_PinCfg =
		{.m_Port = LED7_PORT, .m_Pin = LED7_PIN, .m_Dir = PIN_OUTPUT, .m_Value = LED7_CON}}
#endif
};
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


/*************************** E N D (LED_cfg.c) ******************************/
