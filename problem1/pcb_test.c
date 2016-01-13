/*
 * pcb_test.c
 *
 *  Created on: Jan 8, 2016
 *      Author: nabilfadili
 */

#include <stdlib.h>
#include <time.h>
#include "pcb.h"

//int main() {
//	printf("~PCB ADT Test~\n");
//    //Create (instantiate) a PCB structure in the heap
//	PCB_p testProcess = PCB_constructorWithEmpty();
//    
//    //Print the newly created object to the screen before
//    puts(PCB_toString(testProcess)); //added by Ray
//    
//	int i;
//	srand((unsigned) time(NULL));
//    //Populate the new pcb with appropriate data
//	for (i = 0; i < 5; ++i) {
//		PCB_setProcessNumber(testProcess, i);
//        // Generate random numbers between 0 and 31 for priorities for each pcb
//		PCB_setPriority(testProcess, rand() % 31);
//        //Print out the contents of the structure for a second time
//		puts(PCB_toString(testProcess));
//	}
//	PCB_destructor(testProcess);
//	exit(0);
//}
