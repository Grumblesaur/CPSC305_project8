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
		while (curr->next != NULL) {
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
	// use Stephen's function to pull the customer from the database
	struct customer * cust = lookup_customer(customer_name);
	
	struct order * curr = cust->orders;
	
	signed char order_exists = 0; // this is a boolean; 0 : false, -1 : true
	float cash = 0; // we'll write this to the data pointed at by revenue
	
	// make sure the customer has placed orders
	if (curr != NULL) {
		// if they have, look for the order we've been asked to fulfill
		while (curr->next != NULL) {
			if (curr->order_num == order_num) {
				// obtain transaction info
				order_exists = -1;
				cash = curr->unit_price_in_gold * (float) curr->quantity;
				break;
			}
			curr = curr->next;
		}
	} else {
		*revenue = 0;
		return 0;
	}
	
	if (order_exists == 0) {
		*revenue = 0;
		return 0;
	}
	
	struct order * temp = NULL;
	// if the order was at the front of the line
	if (cust->orders->order_num == order_num) {
		temp = cust->orders->next->next;
		free(cust->orders);
		cust->orders = temp;
		printf("Reached deletion condition 1.\n");
		*revenue = cash;
		return 1;

	} else {
		// neat way to do a for loop; found when searching for a refresher
		// on linked list operations. thanks stackexchange
		for (curr = cust->orders; curr != NULL; curr = curr->next) {
			printf("Deletion condition 2.\n");
			if (curr->order_num == order_num) {
				temp = curr->next->next;
				free(curr->next);
				curr->next = temp;
				break;
			}
		}
	}
		
	*revenue = cash;
	return 1;
}

void get_order_history(struct order_history *order_history) {
	// do for extra credit
}
