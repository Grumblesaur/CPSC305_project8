#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "westeros.h"

// really, this whole thing is a constructor for the "struct order" type
struct order * place_order(struct customer *customer, char *description,
	int quant, float unit_price_in_gold, int *num_orders) {
	
	// allocate memory for this order
	struct order *this_order = (struct order*) malloc(sizeof(struct order));
	
	// track unique order numbers in the data segment for permanence
	static int order_num = 1;

	// dumbly copy-initialize these fields	
	this_order->cust = customer;
	strcpy(this_order->desc, description);
	this_order->quantity = quant;
	this_order->unit_price_in_gold = unit_price_in_gold;
	this_order->order_num = order_num++;
	
	// determine whether this is a rush order
	if (strcmp(customer->family, "Lannister") == 0) {
		this_order->rush = 1;
	} else {
		this_order->rush = 0;
	}
	
	this_order->next = NULL;
	
	// code for adding to a linked list and counting order numbers
	static int counter = 0; // not sure if correct, but it works for now.
	struct order * curr;
	if (customer->orders != NULL) {
		curr = customer->orders;
		while(curr->next != NULL) {
			++counter;
			curr = curr->next;
		}
		curr->next = this_order;
		++counter;
	} else {
		customer->orders = this_order;
		counter = 1;
	}
	
	// add one more for THIS order, increment value pointed at by num_orders
	*num_orders = counter;
	return this_order;		
}

int fulfill_order(char *customer_name, int order_num, float *revenue) {
	// do stuff here
}

void get_order_history(struct order_history *order_history) {
	// do for extra credit
}
