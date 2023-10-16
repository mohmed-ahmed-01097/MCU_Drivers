/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SERVO_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SERVO_CFG_H_
#define SERVO_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define SERVO_PORT			D
#define SERVO_PORT_REG		S_GPIOD
#define SERVO_PIN			GPIO_TMR_OC1B

#define SERVO_MAX_ANGLE		180u
#define SERVO_MIN_ANGLE		0u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* SERVO_CFG_H_ */
/*************************** E N D (SERVO_cfg.h) ******************************/
