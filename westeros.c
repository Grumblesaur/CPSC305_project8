#include <stdio.h>
#include <string.h>
#include "westeros.h"

// really, this whole thing is a constructor for the "struct order" type
struct order * place_order(struct customer *customer, char *description,
	int quant, float unit_price_in_gold, int *num_orders) {
	
	// allocate memory for this order
	struct order *this_order = (struct order*) malloc(sizeof(struct order));
	
	// track unique order numbers in the data segment for permanence
	static int order_num = 1;
	
	// point this order at the customer we received
	this_order->cust = customer;
	
	// copy the item description
	strcpy(this_order->desc, description);

	// copy the number of items
	this_order->quantity = quant;
	
	// copy the price
	this_order->unit_price_in_gold = unit_price_in_gold;
	
	// give the current order an ID number, then increment for next order
	this_order->order_num = order_num++;
	
	// determine whether this is a rush order
	if (strcmp(customer.family, "Lannister") == 0) {
		this_order->rush = 1;
	} else {
		this_order->rush = 0;
	}

	// we don't know where this thing is gonna point to later, make it NULL	
	this_order->next = NULL;
	
	//TODO: figure out what to do with the num_orders argument
	// -- this will probably require looking at Stephen's assignment page	
	
}

int fulfill_order(char *customer_name, int order_num, float *revenue) {
	// do stuff here
}

void get_order_history(struct order_history *order_history) {
	// do for extra credit
}
