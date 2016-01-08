/*
 * pcb_test.c
 *
 *  Created on: Jan 8, 2016
 *      Author: nabilfadili
 */

#include <stdlib.h>
#include <time.h>
#include "pcb.h"

int main() {
	printf("~PCB ADT Test~\n");
	PCB_p testProcess = PCB_constructor();
	int i;
	srand(time(NULL));
	for (i = 0; i < 5; ++i) {
		PCB_setProcessNumber(testProcess, i);
		PCB_setPriority(testProcess, rand() % 31);
		PCB_toString(testProcess);
	}
	PCB_destructor(testProcess);
	exit(0);
}

