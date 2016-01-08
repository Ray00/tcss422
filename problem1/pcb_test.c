/*
 * pcb_test.c
 *
 *  Created on: Jan 8, 2016
 *      Author: nabilfadili
 */

#include "pcb.h"

int main() {
	PCB_p testPCB1 = createNewPCB();
	PCB_p testPCB2 = createNewPCB();
	setPCB_id(testPCB1, 0);
	setPCB_priority(testPCB1, 13);
	setPCB_id(testPCB2, 1);
	setPCB_priority(testPCB2, 3);

	printf("id = %d\npriority = %d\n", testPCB1->id, testPCB1->priority);
	printf("id = %d\npriority = %d", getPCB_id(testPCB2), getPCB_priority(testPCB2));
}

