/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : May 19, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

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

#ifdef	SWC_I2C

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "INTP.h"

#include "I2C_int.h"
#include "I2C_cfg.h"

void I2C_vidINT(void);
static u8 u8char = '0';
static volatile u8 u8Flag = LBTY_SET;
int main(void){

	I2C_vidInit();
	I2C_vidSetCallBack_OverFlow(I2C_vidINT);

	GPIO_u8SetPortDirection(D, PORT_OUTPUT);

    INTP_vidEnable();

    if(I2C_MODE == I2C_Master){
    	I2C_u8SendBuffer((u8*)"Hello MAAM\n\r", 12, I2C_SLAVE_ADDRESS);
    	I2C_u8SendBuffer((u8*)"Hello MAAM\n\r", 12, 0x50);
		u8Flag = LBTY_RESET;
    }
    if(I2C_MODE == I2C_Slave){
//   		I2C_u8ReceiveBuffer((u8*)(&u8char), 12, I2C_SLAVE_ADDRESS);
    	I2C_SlaveListen(&u8char, 12);
    }
    while(!u8Flag);

   	while(1){
   		if(I2C_MODE == I2C_Master){
   	    	vidMyDelay_ms(500);
//   	    	I2C_u8SendBuffer((u8*)(&u8char), 1/*12*/, I2C_SLAVE_ADDRESS);
   	    	I2C_u8SetChar(++u8char, I2C_SLAVE_ADDRESS);
   			I2C_u8GetChar( &u8char, I2C_SLAVE_ADDRESS);
   		}
   		if(I2C_MODE == I2C_Slave){
//   			I2C_u8ReceiveBuffer((u8*)(&u8char), 1/*12*/, I2C_SLAVE_ADDRESS);
   			I2C_SlaveListen(&u8char, 1);
   		}

   		GPIO_u8SetPortValue(D, u8char);
   	}
   	return 0;
}

void I2C_vidINT(void){
	u8Flag = LBTY_SET;
}

#endif


/*************************** E N D (main.c) ******************************/
