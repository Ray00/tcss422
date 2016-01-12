/*
 * fifoqueue.c
 *
 *  Created on: Jan 7, 2016
 *      Author: Ray Kim
 */

#include "fifoqueue.h"

/* (Inner Class)
 * Function:  NODE_constructor
 * --------------------
 * constructs a node object which contains the PCB address and pointer
 * to the next node in the FIFO queue
 *  
 *  params: 	PCB_p pointer to underlying PCB
 *  returns: 	NODE_STR_p pointer to node object
 */
NODE_STR_p NODE_constructor(PCB_p pcb_pointer){
	
	NODE_STR_p node_pointer = (NODE_STR_p) malloc(sizeof(NODE_STR));

	//set pcb_addr to pcb_pointer
	node_pointer->pcb_addr = pcb_pointer;

	//set next_node to null
	node_pointer->next_node = NULL;

	return node_pointer;

}


/* (Inner Class)
 * Function:  NODE_destructor
 * --------------------
 * constructs a FIFO queue object, returning a pointer to the queue object
 * in the heap
 *
 *  params: 	NODE_STR_p pointer to node that will be destroyed
 *  returns: 	int function exit status code
 */
void NODE_destructor(NODE_STR_p node_str_p){
    PCB_destructor(node_str_p->pcb_addr);  // Kyle fixed. Don't forget to free pcb
	free(node_str_p);
}


/*
 * Function:  FIFO_constructor
 * --------------------
 * constructs a FIFO queue object, returning a pointer to the queue object
 * in the heap
 *
 *  returns: 	PCB_QUEUE_STR_p pointer to the queue object in the heap
 */
PCB_QUEUE_STR_p FIFO_constructor(void) {

	PCB_QUEUE_STR_p queue_pointer = (PCB_QUEUE_STR_p) malloc(sizeof(PCB_QUEUE_STR));

	//initialization
	queue_pointer->head_node = NULL;
	queue_pointer->tail_node = NULL;
	queue_pointer->num_nodes = 0;
    queue_pointer->free_node = NULL;

	return queue_pointer;
}


/*
 * Function:  FIFO_destructor
 * --------------------
 * releases resources of FIFO queue object
 * also destroys all PCB objects contained within the FIFO queue object
 *
 *
 *  params: 	PCB_QUEUE_STR_p this
 *  returns:	int number of nodes released(freed)
 */
int FIFO_destructor(PCB_QUEUE_STR_p this){

	int freed_nodes;
	freed_nodes = 0;

	//loop through all nodes and free their resources
//	while (this->num_nodes > 0) {
//
//		NODE_STR_p temp_node_p = dequeue(this);
//		free(temp_node_p->pcb_addr);
//		free(temp_node_p);
//		freed_nodes += 1;
//	}
    
    while (this->head_node != NULL) {
        NODE_destructor(FIFO_dequeue(this)); // freeing node by using destructor function.
        freed_nodes++;
    }
	return freed_nodes;

}


/*
 * Function:  FIFO_enqueue
 * --------------------
 * adds a PCB into a node, then adds that node to the tail end of the FIFO queue
 *
 *
 *  params: 	PCB_QUEUE_STR_p this
 * 				PCB_p that will be added into a node, that will be added
 *              at the tail end of the queue
 *  returns:	int function exit status code
 */
int FIFO_enqueue(PCB_QUEUE_STR_p this, PCB_p pcb_p){
    
    NODE_STR_p node_pointer = this->free_node;
    
    //check if free_node in "this" is available
    if (node_pointer != NULL) {
        //make sure free_node is no longer available in next enqueue call
        this->free_node = NULL;
        
        node_pointer->pcb_addr = pcb_p; //save pcb to free_node
    } else {
        node_pointer = NODE_constructor(pcb_p);
    }
    
    
	//if num of nodes in this is 0, set passed in node as head and tail
	if (this->num_nodes == 0) {
		this->head_node = node_pointer;
        this->tail_node = node_pointer;
    } else {
        this->tail_node->next_node = node_pointer;
        this->tail_node = node_pointer;
    }

	//increment num_nodes
	this->num_nodes += 1;
	return 0;       // FIXME (Kyle) I'm just curious. Why don't we use void type to avoid return statement?

}


/*
 * Function:  FIFO_dequeue
 * --------------------
 * Removes the head node, then takes the pcb object from the node and returns it
 *
 *
 *  params: 	PCB_QUEUE_STR_p this
 *  returns:	PCB_p head node that will be taken off the queue
 */
PCB_p FIFO_dequeue(PCB_QUEUE_STR_p this){

	NODE_STR_p return_node_p = this->head_node;
    PCB_p return_pcb_p = return_node_p->pcb_addr;
    
	//return NULL if queue is empty
	if (this->num_nodes < 1 || return_node_p == NULL) {
		return NULL;
	}

	this->head_node = return_node_p->next_node;

	//decrement num_nodes
	this->num_nodes -= 1;

    //save freed node to this->free_node or free() if this->free_node already exists
    if (this->free_node == NULL) {
        this->free_node = return_node_p;
    } else {
        free(return_node_p);
    }
    
	return return_pcb_p;
}



/*
 * Function:  FIFO_toString
 * --------------------
 * prints the current state of the queue
 *
 *
 *  params: 	PCB_QUEUE_STR_p this, the underlying queue struct
 *  returns:	char * containing string
 */
char * FIFO_toString(PCB_QUEUE_STR_p this) {
    char * result = (char *) malloc(sizeof(char) * 1000);
    strcpy(result, "Q: ");
    NODE_STR_p cur = this->head_node;
    if (cur != NULL) {
        char pID[50] = "";
        sprintf(pID, "P%d", cur->pcb_addr->process_num);
        strcat(result, pID);
        cur = cur->next_node;
    }
    while (cur != NULL) {
        strcat(result, "->");
        char pID[5];
        sprintf(pID, "P%d", cur->pcb_addr->process_num);
        strcat(result, pID);
        cur = cur->next_node;
    }
    strcat(result, "-*");
    return result;
}
