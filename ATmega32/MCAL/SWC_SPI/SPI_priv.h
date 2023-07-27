/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SPI_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of Union bit field of "SPI Control Register"         */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
	u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_SPR : 2;			/*!< SPI Clock Rate Select 1 and 0 */
    	__IO u8 m_CPHA: 1;			/*!< Clock Phase */
    	__IO u8 m_CPOL: 1;			/*!< Clock Polarity */
    	__IO u8 m_MSTR: 1;			/*!< Master/Slave Select */
    	__IO u8 m_DORD: 1;			/*!< Data Order */
    	__IO u8 m_SPE : 1;			/*!< SPI Enable */
    	__IO u8 m_SPIE: 1;			/*!< SPI Interrupt Enable */
    }sBits;
}SPCR_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "SPI Status Register"          */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
	u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_SPI2X: 1;			/*!< Double SPI Speed Bit */
        __I  u8        : 5;			/*!< Reversed */
        __I  u8 m_WCOL : 1;			/*!< Write Collision Flag */
        __I  u8 m_SPIF : 1;			/*!< SPI Interrupt Flag */
    }sBits;
}SPSR_type;

/*************************************************************************/

/** @brief : SPI Registers                                                    */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
    __IO SPCR_type m_SPCR;			/*!< SPI Control Reg */
    __IO SPSR_type m_SPSR;			/*!< SPI Status Reg */
    __IO u8        m_SPDR;			/*!< SPI Data Reg */
}SPI_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** SPI **/
#define S_SPI           ((SPI_type* const)0x2DU)
#define SPCR            (*(volatile u8* const)0x2DU)
#define SPSR            (*(volatile u8* const)0x2EU)
#define SPDR            (*(volatile u8* const)0x2FU)

/* ************************************************************************** */

#define SPI_SPR_MASK			3u
#define SPI_SPI2X_BIT			2u

/* ************************************************************************** */

#define SPI_PORT				B
#define SPI_MOSI_PIN			GPIO_SPI_MOSI
#define SPI_MISO_PIN			GPIO_SPI_MISO
#define SPI_SCK_PIN				GPIO_SPI_SCK
#define SPI_SS_PIN				GPIO_SPI_SS

#define SPI_MODE_MASK			(1<<SPI_SS_PIN) | (1<<SPI_SCK_PIN) | (1<<SPI_MOSI_PIN)

#define SPI_SS_ENABLE			PIN_Low
#define SPI_SS_DISABLE			PIN_High

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* SPI_PRIV_H_ */
/*************************** E N D (SPI_priv.h) ******************************/
