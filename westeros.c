#include <stdio.h>
#include <string.h>
#include "westeros.h"

struct order * place_order(struct customer *customer, char *description,
	int quant, float unit_price_in_gold, int *num_orders) {
	
	// do stuff here
}

int fulfill_order(char *customer_name, int order_num, float *revenue) {
	// do stuff here
}

void get_order_history(struct order_history *order_history) {
	// do for extra credit
}