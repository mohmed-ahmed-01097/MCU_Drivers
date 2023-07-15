/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PUSH_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "PUSH_int.h"
#include "PUSH_cfg.h"
#include "PUSH_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
const PUSH_tstrConfig kau8PushConfiguration_LGB[PUSH_Num] = {
#ifdef PUSH0
		 {.m_Active = PUSH0_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH0_PORT, .m_Pin = PUSH0_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH1
		,{.m_Active = PUSH1_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH1_PORT, .m_Pin = PUSH1_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH2
		,{.m_Active = PUSH2_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH2_PORT, .m_Pin = PUSH2_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH3
		,{.m_Active = PUSH3_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH3_PORT, .m_Pin = PUSH3_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH4
		,{.m_Active = PUSH4_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH4_PORT, .m_Pin = PUSH4_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH5
		,{.m_Active = PUSH5_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH5_PORT, .m_Pin = PUSH5_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH6
		,{.m_Active = PUSH6_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH6_PORT, .m_Pin = PUSH6_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
#ifdef PUSH7
		,{.m_Active = PUSH7_ACTIVE, .m_PinCfg =
		{.m_Port = PUSH7_PORT, .m_Pin = PUSH7_PIN, .m_Dir = PIN_INPUT, .m_Res = PULL_None}}
#endif
};
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


/*************************** E N D (PUSH_cfg.c) ******************************/
