/*
 * hzklab2Week2.c
 *
 *  Created on: Feb 1, 2016
 *      Author: zhqk6
 */


#ifndef MODULE
#define MODULE
#endif

#ifndef __KERNEL__
#define __KERNEL__
#endif


#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

int init_module(void){
unsigned long *PBDR;
unsigned long *PBDDR;
unsigned long *ptr;
ptr = (unsigned long*)__ioremap(0x80840000,4096,0);
PBDR = ptr+1;
PBDDR = ptr+5;  // according to their physical address
*PBDDR |= 0xFF;
*PBDR |= 0x60; // give output/input , pbddr  11111111, pbdr 01100000
	printk( "hello! \n");
    return 0;
}
void cleanup_module(void){
	unsigned long *PBDR;
	unsigned long *PBDDR;
	unsigned long *ptr;
	ptr = (unsigned long*)__ioremap(0x80840000,4096,0);
	PBDR = ptr+1;
	PBDDR = ptr+5;
	*PBDDR |= 0xFF;
	*PBDR &= 0x00; // give pbdr 00000000 to turn on the light
	printk("goodbye! \n");
}
