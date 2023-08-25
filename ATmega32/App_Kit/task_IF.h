/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : task_IF.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Aug 1, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef TASK_IF_H_
#define TASK_IF_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

extern void _vidLcdTask(u8* puStr);
extern void Task(u8* puStr, void(*task)(void));

#if defined(AMIT_KIT)

extern void _vidLedTask(void);
extern void _vidBuzzerTask(void);
extern void _vidRelayTask(void);
extern void _vidSegTask(void);
extern void _vidAdcTask(void);
extern void _vidEepromTask(void);

#elif defined(ETA32_KIT)

extern void _vidDioTask(void);
extern void _vidSegTask(void);
extern void _vidUartTask(void);
extern void _vidIRTask(void);
extern void _vidEEI2CTask(void);

extern void _vidRtcTask(void);
extern void _vidVarTask(void);
extern void _vidTempTask(void);
extern void _vidMotorTask(void);
extern void _vidPwmTask(void);

#elif defined(ETA32_MINI_KIT)

extern void _vidDioTask(void);
extern void _vidSegTask(void);
extern void _vidAdcTask(void);
extern void _vidComTask(void);
extern void _vidUartTask(void);
extern void _vidIRTask(void);
extern void _vidEEI2CTask(void);

extern void _vidTmrTask(void);
extern void _vidPwmTask(void);
extern void _vidMotorTask(void);

#endif

#endif /* TASK_IF_H_ */
/*************************** E N D (task_IF.h) ******************************/
