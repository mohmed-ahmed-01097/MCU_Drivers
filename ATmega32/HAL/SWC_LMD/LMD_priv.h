/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LMD_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LMD_PRIV_H_
#define LMD_PRIV_H_

#include "LMD_cfg.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define LMD_ACTIVE_HIGH			LBTY_u8MAX
#define LMD_ACTIVE_LOW			LBTY_u8ZERO

#define LMD_ROW_MUX				1u
#define LMD_COL_MUX				2u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
// ROWs of the LED Matrix
const u8 IMAGES[][8] = {
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  {0x3C, 0x42, 0x99, 0xA5, 0x81, 0xA5, 0x42, 0x3C},
  {0x3C, 0x42, 0x81, 0xBD, 0x81, 0xA5, 0x42, 0x3C},
  {0x3C, 0x42, 0xA5, 0x99, 0x81, 0xA5, 0x42, 0x3C},
  {0x0c, 0x0c, 0x3f, 0x0c, 0x3f, 0x1e, 0x33, 0x33},
  {0x00, 0x3f, 0x67, 0x06, 0x0f, 0x26, 0x36, 0x1c},
  {0x3c, 0x42, 0x99, 0x85, 0x85, 0x99, 0x42, 0x3c},
  {0x3c, 0x42, 0xa5, 0x9d, 0xa5, 0x9d, 0x42, 0x3c},
  {0xfe, 0xfe, 0x7c, 0x7c, 0x38, 0x38, 0x10, 0x00},
  {0x10, 0x38, 0x38, 0x7c, 0x7c, 0xfe, 0xfe, 0x00},
  {0x06, 0x1e, 0x7e, 0xfe, 0x7e, 0x1e, 0x06, 0x00},
  {0xc0, 0xf0, 0xfc, 0xfe, 0xfc, 0xf0, 0xc0, 0x00},
  {0x7c, 0x92, 0xaa, 0x82, 0xaa, 0x82, 0x7c, 0x00},
  {0x7c, 0xee, 0xd6, 0xfe, 0xd6, 0xfe, 0x7c, 0x00},
  {0x10, 0x38, 0x7c, 0xfe, 0xfe, 0xee, 0x44, 0x00},
  {0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00},
  {0x38, 0x10, 0x54, 0xfe, 0x54, 0x38, 0x10, 0x00},
  {0x38, 0x10, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00},
  {0x00, 0x38, 0x7c, 0x7c, 0x7c, 0x38, 0x00, 0x00},
  {0x0c, 0x12, 0x12, 0x9c, 0xa0, 0xc0, 0xf0, 0x00},
  {0x38, 0x44, 0x44, 0x38, 0x10, 0x7c, 0x10, 0x00},
  {0x06, 0x0e, 0x0c, 0x08, 0x08, 0x28, 0x18, 0x00},
  {0x06, 0x6e, 0xec, 0xc8, 0x88, 0x98, 0xf0, 0x00},
  {0x10, 0x54, 0x38, 0xee, 0x38, 0x54, 0x10, 0x00},
  {0x10, 0x38, 0x54, 0x10, 0x54, 0x38, 0x10, 0x00},
  {0x66, 0x66, 0x00, 0x66, 0x66, 0x66, 0x66, 0x00},
  {0x00, 0x28, 0x44, 0xfe, 0x44, 0x28, 0x00, 0x00},
  {0x03, 0x06, 0x3e, 0x66, 0x66, 0x66, 0x00, 0x00},
  {0x00, 0xd8, 0xd8, 0xd8, 0xde, 0xdb, 0xdb, 0xfe},
  {0x00, 0x00, 0x33, 0x66, 0xcc, 0x66, 0x33, 0x00},
  {0x03, 0xf3, 0xf6, 0xec, 0xbd, 0x33, 0x63, 0xc3},
  {0xf0, 0x33, 0x66, 0xcc, 0x7b, 0x33, 0x63, 0xc3},

  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18},   	//>!
  {0x00, 0x00, 0x00, 0x00, 0x28, 0x6c, 0x6c, 0x00},   	//"
  {0x00, 0x36, 0x36, 0x7f, 0x36, 0x7f, 0x36, 0x36},   	//#
  {0x00, 0x0c, 0x1f, 0x30, 0x1e, 0x03, 0x3e, 0x0c},   	//$
  {0x00, 0x30, 0x33, 0x06, 0x0c, 0x18, 0x33, 0x03},   	//%
  {0x00, 0x6e, 0x33, 0x3b, 0x6e, 0x1c, 0x36, 0x1c},   	//&
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x06},   	//'
  {0x00, 0x18, 0x0c, 0x06, 0x06, 0x06, 0x0c, 0x18},   	//(
  {0x00, 0x06, 0x0c, 0x18, 0x18, 0x18, 0x0c, 0x06},   	//)
  {0x00, 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00},   	//*
  {0x00, 0x00, 0x0c, 0x0c, 0x3f, 0x0c, 0x0c, 0x00},  	//+
  {0x06, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00},   	//,
  {0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00},   	//-
  {0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00},   	//.
  {0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},   	//>/
  {0x00, 0x3e, 0x67, 0x6f, 0x7b, 0x73, 0x63, 0x3e},
  {0x00, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0e, 0x0c},
  {0x00, 0x3f, 0x33, 0x06, 0x1c, 0x30, 0x33, 0x1e},
  {0x00, 0x1e, 0x33, 0x30, 0x1c, 0x30, 0x33, 0x1e},
  {0x00, 0x78, 0x30, 0x7f, 0x33, 0x36, 0x3c, 0x38},
  {0x00, 0x1e, 0x33, 0x30, 0x30, 0x1f, 0x03, 0x3f},
  {0x00, 0x1e, 0x33, 0x33, 0x1f, 0x03, 0x06, 0x1c},
  {0x00, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x33, 0x3f},
  {0x00, 0x1e, 0x33, 0x33, 0x1e, 0x33, 0x33, 0x1e},
  {0x00, 0x0e, 0x18, 0x30, 0x3e, 0x33, 0x33, 0x1e},
  {0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00},  	//:
  {0x06, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00},  	//;
  {0x00, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18},  	//<
  {0x00, 0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00},  	//=
  {0x00, 0x06, 0x0c, 0x18, 0x30, 0x18, 0x0c, 0x06},  	//>
  {0x0c, 0x0c, 0x00, 0x0c, 0x18, 0x30, 0x33, 0x1e}, 	//?
  {0x00, 0x1e, 0x03, 0x7b, 0x7b, 0x7b, 0x63, 0x3e},  	//@
  {0x00, 0x33, 0x33, 0x3f, 0x33, 0x33, 0x1e, 0x0c},
  {0x00, 0x3f, 0x66, 0x66, 0x3e, 0x66, 0x66, 0x3f},
  {0x00, 0x3c, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3c},
  {0x00, 0x1f, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1f},
  {0x00, 0x7f, 0x46, 0x16, 0x1e, 0x16, 0x46, 0x7f},
  {0x00, 0x0f, 0x06, 0x16, 0x1e, 0x16, 0x46, 0x7f},
  {0x00, 0x7c, 0x66, 0x73, 0x03, 0x03, 0x66, 0x3c},
  {0x00, 0x33, 0x33, 0x33, 0x3f, 0x33, 0x33, 0x33},
  {0x00, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1e},
  {0x00, 0x1e, 0x33, 0x33, 0x30, 0x30, 0x30, 0x78},
  {0x00, 0x67, 0x66, 0x36, 0x1e, 0x36, 0x66, 0x67},
  {0x00, 0x7f, 0x66, 0x46, 0x06, 0x06, 0x06, 0x0f},
  {0x00, 0x63, 0x63, 0x6b, 0x7f, 0x7f, 0x77, 0x63},
  {0x00, 0x63, 0x63, 0x73, 0x7b, 0x6f, 0x67, 0x63},
  {0x00, 0x1c, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1c},
  {0x00, 0x0f, 0x06, 0x06, 0x3e, 0x66, 0x66, 0x3f},
  {0x00, 0x38, 0x1e, 0x3b, 0x33, 0x33, 0x33, 0x1e},
  {0x00, 0x67, 0x66, 0x36, 0x3e, 0x66, 0x66, 0x3f},
  {0x00, 0x1e, 0x33, 0x38, 0x0e, 0x07, 0x33, 0x1e},
  {0x00, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x2d, 0x3f},
  {0x00, 0x3f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33},
  {0x00, 0x0c, 0x1e, 0x33, 0x33, 0x33, 0x33, 0x33},
  {0x00, 0x63, 0x77, 0x7f, 0x6b, 0x63, 0x63, 0x63},
  {0x00, 0x63, 0x36, 0x1c, 0x1c, 0x36, 0x63, 0x63},
  {0x00, 0x1e, 0x0c, 0x0c, 0x1e, 0x33, 0x33, 0x33},
  {0x00, 0x7f, 0x66, 0x4c, 0x18, 0x31, 0x63, 0x7f},
  {0x00, 0x1e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1e},   	//[
  {0x00, 0x40, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03},   	//\<
  {0x00, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1e},   	//]
  {0x00, 0x00, 0x00, 0x00, 0x63, 0x36, 0x1c, 0x08},   	//^
  {0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   	//_
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x06},   	//`
  {0x00, 0x6e, 0x33, 0x3e, 0x30, 0x1e, 0x00, 0x00},
  {0x00, 0x3b, 0x66, 0x66, 0x3e, 0x06, 0x06, 0x07},
  {0x00, 0x1e, 0x33, 0x03, 0x33, 0x1e, 0x00, 0x00},
  {0x00, 0x6e, 0x33, 0x33, 0x3e, 0x30, 0x30, 0x38},
  {0x00, 0x1e, 0x03, 0x3f, 0x33, 0x1e, 0x00, 0x00},
  {0x00, 0x0f, 0x06, 0x06, 0x0f, 0x06, 0x36, 0x1c},
  {0x1f, 0x30, 0x3e, 0x33, 0x33, 0x6e, 0x00, 0x00},
  {0x00, 0x67, 0x66, 0x66, 0x6e, 0x36, 0x06, 0x07},
  {0x00, 0x1e, 0x0c, 0x0c, 0x0c, 0x0e, 0x00, 0x0c},
  {0x1e, 0x33, 0x33, 0x30, 0x30, 0x30, 0x00, 0x30},
  {0x00, 0x67, 0x36, 0x1e, 0x36, 0x66, 0x06, 0x07},
  {0x00, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0e},
  {0x00, 0x63, 0x6b, 0x7f, 0x7f, 0x33, 0x00, 0x00},
  {0x00, 0x33, 0x33, 0x33, 0x33, 0x1f, 0x00, 0x00},
  {0x00, 0x1e, 0x33, 0x33, 0x33, 0x1e, 0x00, 0x00},
  {0x0f, 0x06, 0x3e, 0x66, 0x66, 0x3b, 0x00, 0x00},
  {0x78, 0x30, 0x3e, 0x33, 0x33, 0x6e, 0x00, 0x00},
  {0x00, 0x0f, 0x06, 0x66, 0x6e, 0x3b, 0x00, 0x00},
  {0x00, 0x1f, 0x30, 0x1e, 0x03, 0x3e, 0x00, 0x00},
  {0x00, 0x18, 0x2c, 0x0c, 0x0c, 0x3e, 0x0c, 0x08},
  {0x00, 0x6e, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00},
  {0x00, 0x0c, 0x1e, 0x33, 0x33, 0x33, 0x00, 0x00},
  {0x00, 0x36, 0x7f, 0x7f, 0x6b, 0x63, 0x00, 0x00},
  {0x00, 0x63, 0x36, 0x1c, 0x36, 0x63, 0x00, 0x00},
  {0x1f, 0x30, 0x3e, 0x33, 0x33, 0x33, 0x00, 0x00},
  {0x00, 0x3f, 0x26, 0x0c, 0x19, 0x3f, 0x00, 0x00},
  {0x00, 0x38, 0x0c, 0x0c, 0x07, 0x0c, 0x0c, 0x38},   //{
  {0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},   //|
  {0x00, 0x07, 0x0c, 0x0c, 0x38, 0x0c, 0x0c, 0x07},   //}
  {0x00, 0x00, 0x00, 0x18, 0x3b, 0x6e, 0x0c, 0x00},   //~
};
const u8 IMAGES_LEN = sizeof(IMAGES)/8;
//https://xantorohara.github.io/led-matrix-editor/

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* LMD_PRIV_H_ */
/*************************** E N D (LMD_priv.h) ******************************/
