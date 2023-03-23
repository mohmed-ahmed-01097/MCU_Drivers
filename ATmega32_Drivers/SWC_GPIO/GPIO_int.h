/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_int.h
/* Author      : MAAM
/* Version     : v00
/* date        : Mar 23, 2023
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SWC_GPIO_GPIO_INT_H_
#define SWC_GPIO_GPIO_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */
typedef enum{
    INPUT = 0u,
    OUTPUT = 1u
}IO_Pin_type;

typedef enum{
    Low = 0u,
    High = 1u
}PORT_type;

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

/** Data Direction Register as input/Output **/
/** Pull-up Configuration **/
/** Port Data Register **/
/** Port Input Pins I/O location is read only **/

#endif /* SWC_GPIO_GPIO_INT_H_ */
/*************************** E N D (GPIO_int.h) ******************************/
