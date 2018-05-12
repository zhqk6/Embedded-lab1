/*
 * hzklab1.c
 *
 *  Created on: Jan 28, 2016
 *      Author: zhqk6
 */
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fp;
	unsigned long *PFDR,*PFDDR;
	unsigned long *PBDR,*PBDDR;  //create pointer to port B/F DR/DDR
    unsigned long *ptr;  //create pointer to mmap
    unsigned char state;  //create button's state
    int button;

    fp = open("/dev/mem",O_RDWR);
	if(fp == -1){
		printf("\n error\n");
	    return(-1);  // failed open
	}
	ptr = (unsigned long*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fp,0x80840000);
    if(ptr == MAP_FAILED){
    	printf("\n Unable to map memory space \n");
    	return(-2);
    }  // failed mmap
	PBDR = ptr+1;
    PBDDR = ptr+5;
    PFDR = ptr+12;
    PFDDR = ptr+13;  // according to their physical address
    *PBDDR |= 0xE0;
    *PFDDR |= 0x02;  // give output/input, pbddr 11100000, pfddr 00000010

    printf("Please press your button number:\n");
    scanf("%d",&button);
        if( button <0 || button > 4 ){
         printf("The button number should be 0-4. \n");
         scanf("%d",&button);
        }
     state = *PBDR;
     switch(button){
     case 0: while(state & 0x01){
    	state = *PBDR;
        printf("press button please\n");
        fflush(stdout);
        printf("this is used for distinguishing\n");
        fflush(stdout);
     }
     break;
     case 1: while(state & 0x02){
       	state = *PBDR;
           printf("press button please\n");
           fflush(stdout);
           printf("this is used for distinguishing\n");
           fflush(stdout);
        }
        break;
     case 2: while(state & 0x04){
       	state = *PBDR;
           printf("press button please\n");
           fflush(stdout);
           printf("this is used for distinguishing\n");
           fflush(stdout);
        }
        break;
     case 3: while(state & 0x08){
       	state = *PBDR;
           printf("press button please\n");
           fflush(stdout);
           printf("this is used for distinguishing\n");
           fflush(stdout);
        }
        break;
     case 4: while(state & 0x10){
       	state = *PBDR;
           printf("press button please\n");
           fflush(stdout);
           printf("this is used for distinguishing\n");
           fflush(stdout);
        }
        break;
     }   // 5 cases for buttons which is on bit0-4 portB

       while(1){
        *PFDR = 0xFF;
        msync(NULL,4096,MS_SYNC);
        usleep(100000);
        *PFDR = 0xFD;
        msync(NULL,4096,MS_SYNC);
        usleep(100000);
    }  //create square wave
    close(fp);
    return 0;
}
