/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : EEPROM_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef EEPROM_PRIV_H_
#define EEPROM_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of Union bit field of "EEPROM Control Register"      */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_EERE : 1;			/*!< EEPROM Read Enable */
    	__IO u8 m_EEWE : 1;			/*!< EEPROM Write Enable */
    	__IO u8 m_EEMWE: 1;			/*!< EEPROM Master Write Enable */
    	__IO u8 m_EERIE: 1;			/*!< EEPROM Ready Interrupt Enable */
    	__IO u8        : 4;
    }sBits;
}EECR_type;

/*************************************************************************/

/** @brief : EEPROM Registers                                                 */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
    __IO EECR_type  m_EECR ;
    __IO u8         m_EEDR ;
    __IO u16        m_EEAR : 10;
    __IO u16               : 6;
}EEPROM_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "MCU Control Register"         */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_SPMEN : 1;     		/*!<  Store Program Memory Enable */
        __I  u8         : 7;
    }sBits;
}SPMCR_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** EEPROM **/
#define S_EEPROM        ((EEPROM_type* const)0x3CU)
#define EECR            (*(volatile u8* const)0x3CU)
#define EEDR            (*(volatile u8* const)0x3DU)
#define EEARL           (*(volatile u8* const)0x3EU)
#define EEARH           (*(volatile u8* const)0x3FU)

/** Store Program Memory Control Register **/
#define S_SPMCR         ((SPMCR_type* const)0x57U)
#define SPMCR           (*(volatile u8* const)0x57U)

/* ************************************************************************** */

#define EEPROM_MAX_ADDRESS					1023u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* EEPROM_PRIV_H_ */
/*************************** E N D (EEPROM_priv.h) ******************************/
