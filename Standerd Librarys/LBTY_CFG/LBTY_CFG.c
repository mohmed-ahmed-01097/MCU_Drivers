#include <stdio.h>
#include "LBTY_CFG.h"

void main(void){

	printf("The size of u8  is %d bytes\n", sizeof(u8)) ;
	printf("The size of u16 is %d bytes\n", sizeof(u16));
	printf("The size of u32 is %d bytes\n", sizeof(u32));
	printf("The size of u64 is %d bytes\n", sizeof(u64));

	printf("\n\r");
	printf("The size of s8  is %d bytes\n", sizeof(s8)) ;
	printf("The size of s16 is %d bytes\n", sizeof(s16));
	printf("The size of s32 is %d bytes\n", sizeof(s32));
	printf("The size of s64 is %d bytes\n", sizeof(s64));

	printf("\n\r");
	printf("The size of f32 is %d bytes\n", sizeof(f32));
	printf("The size of f64 is %d bytes\n", sizeof(f64));
}
