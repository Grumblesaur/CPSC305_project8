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
	static int order_num = 0;

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
	
	printf("%s has placed order %d.\n", customer->name, order_num - 1);
	
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
	
	printf("%s wants order #%d now.\n", customer_name, order_num);
	
	// make sure the customer has placed orders
	if (curr != NULL) {
		printf("step 1\n");
		if (curr->order_num != order_num) {
			printf("step 2\n");
			while(curr->next != NULL) {
				if (curr->order_num == order_num) {
					printf("Found order #%d by looping\n", order_num);
					order_exists = -1;
					cash = curr->unit_price_in_gold * curr->quantity;
					break;
				}
				curr = curr->next;
				printf("iterated while loop\n");
			}
		} else {
			printf("step 3\n");
			order_exists = -1;
			cash = curr->unit_price_in_gold * curr->quantity;
		}
	} else {
		*revenue = 0;
		printf("Bailed out.\n");
		return 0;
	}
	
	if (order_exists == 0) {
		*revenue = 0;
		printf("Bailed out.\n");
		return 0;
	}
	
	struct order * temp = NULL;
	// if the order was at the front of the line
	if (cust->orders->order_num == order_num) {
		printf("Deleting order #%d.\n", order_num);
		temp = cust->orders->next;
		free(cust->orders);
		cust->orders = temp;
		if (temp != NULL) {
			printf("Next order in line is #%d.\n", cust->orders->order_num);
		}
	} else {
		curr = cust->orders;
		if (curr->order_num == order_num) {
			printf("Deleting order #%d.\n", order_num);
			temp = curr->next;
			free(curr);
			cust->orders = temp;
			if (temp != NULL) {
				printf("Next in line is #%d.\n", cust->orders->order_num);
			}
		} else {
			while (curr->next != NULL) {
				if (curr->order_num == order_num) {
					printf("Deleting order #%d.\n", order_num);
					temp = curr->next->next;
					free(curr->next);
					curr->next = temp;
					printf("Next is #%d.\n", temp->order_num);
					break;
				}
			curr = curr->next;
			}
		}
	}
		
	*revenue = cash;
	return 1;
}

void get_order_history(struct order_history *order_history) {
	// do for extra credit
}
