
#ifndef WESTEROS_H
#define WESTEROS_H

struct order;

struct customer {
    char name[40];
    char family[20];
    char sigil[20];
    struct order *orders;
};

struct order {
    struct customer *cust;
    int order_num;
    char desc[40];
    int quantity;
    float unit_price_in_gold;
    unsigned char rush;
    struct order *next;
}; 

struct order_history {
    char cust_name[40];
    float total_business_in_gold;
    char most_expensive_item[40];
    struct order recent_orders[10];
    int num_recent_orders;
};


/* Functions you must write. */

struct order *place_order(struct customer *customer, char *description, 
    int quant, float unit_price_in_gold, int *num_orders);

int fulfill_order(char *customer_name, int order_num, float *revenue);

/* (Write this one too for extra credit.) */
void get_order_history(struct order_history *order_history);



/* Functions Stephen is giving to you to use. */

void init_db(void);

struct customer *lookup_customer(char *customer_name);

#endif
