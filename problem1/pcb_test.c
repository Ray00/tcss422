/*
 * pcb_test.c
 *
 *  Created on: Jan 8, 2016
 *      Author: nabilfadili
 */

#include "pcb.h"

int main() {
	printf("~PCB ADT Test~\n");

	PCB_p testProcess = PCB_constructor();
	PCB_setProcessNumber(testProcess, 1);
	PCB_setPriority(testProcess, 13);

	PCB_toString(testProcess);

	exit(0);
}

