
#include <stdio.h>
#include <string.h>
#include "westeros.h"

struct customer cust_db[100];
int num_custs = 0;

struct customer *lookup_customer(char *customer_name) {
    int i;
    for (i=0; i<num_custs; i++) {
        if (!strcmp(cust_db[i].name,customer_name)) {
            return cust_db + i;
        }
    }
    return NULL;
}

void init_db(void) {
    strcpy(cust_db[0].name,"Catelyn"); 
    strcpy(cust_db[0].family,"Stark");
    strcpy(cust_db[0].sigil,"Direwolf");
    cust_db[0].orders = NULL;

    strcpy(cust_db[1].name,"Robb"); 
    strcpy(cust_db[1].family,"Stark");
    strcpy(cust_db[1].sigil,"Direwolf");
    cust_db[1].orders = NULL;

    strcpy(cust_db[2].name,"Daenerys"); 
    strcpy(cust_db[2].family,"Targaryen");
    strcpy(cust_db[2].sigil,"Dragon");
    cust_db[2].orders = NULL;

    strcpy(cust_db[3].name,"Cersei"); 
    strcpy(cust_db[3].family,"Lannister");
    strcpy(cust_db[3].sigil,"Lion");
    cust_db[3].orders = NULL;

    strcpy(cust_db[4].name,"Robert"); 
    strcpy(cust_db[4].family,"Baratheon");
    strcpy(cust_db[4].sigil,"Stag");
    cust_db[4].orders = NULL;

    num_custs = 5;
}


