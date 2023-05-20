/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PROGMEM.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : May 20, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef PROGMEM_H_
#define PROGMEM_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define PROGMEM 		LCTY_PROGMEM

// Used to declare a static pointer to a string in program space.
// # define PSTR(s) ((const PROGMEM char *)(s))
#define PSTR(s) 		(__extension__({static char __c[] PROGMEM = (s); &__c[0];}))

/* ************************************************************************** */

#define __LPM_byte_classic__(addr)   \
(__extension__({                \
    uint16_t __addr16 = (uint16_t)(addr); \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm" "\n\t"            \
        "mov %0, r0" "\n\t"     \
        : "=r" (__result)       \
        : "z" (__addr16)        \
        : "r0"                  \
    );                          \
    __result;                   \
}))

#define __LPM_byte_enhanced__(addr)  \
(__extension__({                \
    uint16_t __addr16 = (uint16_t)(addr); \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm %0, Z" "\n\t"      \
        : "=r" (__result)       \
        : "z" (__addr16)        \
    );                          \
    __result;                   \
}))

#define __LPM_word_classic__(addr)          \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint16_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_word_enhanced__(addr)         \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint16_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z"    "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
    );                                      \
    __result;                               \
}))

#define __LPM_dword_classic__(addr)         \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint32_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %C0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %D0, r0"   "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_dword_enhanced__(addr)        \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint32_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z+"   "\n\t"              \
        "lpm %C0, Z+"   "\n\t"              \
        "lpm %D0, Z"    "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
    );                                      \
    __result;                               \
}))

#define __LPM_float_classic__(addr)         \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    float __result;                         \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %C0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %D0, r0"   "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_float_enhanced__(addr)        \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    float __result;                         \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z+"   "\n\t"              \
        "lpm %C0, Z+"   "\n\t"              \
        "lpm %D0, Z"    "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
    );                                      \
    __result;                               \
}))

#if defined (__AVR_HAVE_LPMX__)
#define __LPM_BYTE(addr)    __LPM_byte_enhanced__(addr)
#define __LPM_WORD(addr)    __LPM_word_enhanced__(addr)
#define __LPM_DWORD(addr)   __LPM_dword_enhanced__(addr)
#define __LPM_FLOAT(addr)   __LPM_float_enhanced__(addr)
#else
#define __LPM_BYTE(addr)    __LPM_byte_classic__(addr)
#define __LPM_WORD(addr)    __LPM_word_classic__(addr)
#define __LPM_DWORD(addr)   __LPM_dword_classic__(addr)
#define __LPM_FLOAT(addr)   __LPM_float_classic__(addr)
#endif


#define pgm_read_byte_near(address_short) 	__LPM_BYTE((uint16_t)(address_short))

#define pgm_read_word_near(address_short) 	__LPM_WORD((uint16_t)(address_short))

#define pgm_read_dword_near(address_short)  __LPM_DWORD((uint16_t)(address_short))

#define pgm_read_float_near(address_short) 	__LPM_FLOAT((uint16_t)(address_short))


#define pgm_read_byte(address_short)    pgm_read_byte_near(address_short)

#define pgm_read_word(address_short)    pgm_read_word_near(address_short)

#define pgm_read_dword(address_short)   pgm_read_dword_near(address_short)

#define pgm_read_float(address_short)   pgm_read_float_near(address_short)

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* PROGMEM_H_ */
/*************************** E N D (PROGMEM.h) ******************************/
