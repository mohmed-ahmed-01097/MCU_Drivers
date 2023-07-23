/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SERVO_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SERVO_PRIV_H_
#define SERVO_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if defined(PWM0) || defined(PWM2) || defined(PWM1)

#if defined(PWM0) || defined(PWM2)
#define SERVO_INIT_PERIOD		(0.002f)
#elif defined(PWM1)
#define SERVO_INIT_PERIOD		(0.02f)
#endif

#define SERVO_ZERO_ANGLE		(10000.0f * 0.001f / SERVO_INIT_PERIOD)
#define SERVO_ANGLE_RATIO		(SERVO_ZERO_ANGLE / 180.0f)

#else

#define SERVO_ZERO_ANGLE		(10000.0f)
#define SERVO_ANGLE_RATIO		(SERVO_ZERO_ANGLE / 180.0f)

#endif

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

#endif /* SERVO_PRIV_H_ */
/*************************** E N D (SERVO_priv.h) *****************************/