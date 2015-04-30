#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "westeros.h"

int main(int argc, char *argv[]) {

    int ec = 0;

    if (argc != 2) {
        printf("Usage: %s ec=[true|false].\n", argv[0]);
        return 1;
    }
    if (!strcmp(argv[1],"ec=true")) {
        ec = 1;
    }

    init_db();

    /* (Test lookup_customer.) */
    struct customer *cust1 = lookup_customer("Catelyn");
    assert(strcmp(cust1->family,"Stark") == 0);
    cust1 = lookup_customer("Daenerys");
    assert(strcmp(cust1->sigil,"Dragon") == 0);
    cust1 = lookup_customer("Skywalker");
    assert(cust1 == NULL);


    /* Test place_order. */
    int num;
    struct order *order1 = place_order(
        lookup_customer("Catelyn"),
        "Buttons",
        100,
        .02,
        &num);
    assert(num == 1);

    struct order *order2 = place_order(
        lookup_customer("Catelyn"),
        "Beer",
        50,
        .5,
        &num);
    assert(num == 2);
    assert(strcmp(order1->desc, "Buttons") == 0);
    assert(strcmp(order1->cust->sigil, "Direwolf") == 0);
    assert(order1->rush == 0);
    int order1_num = order1->order_num;
    assert(strcmp(order2->desc, "Beer") == 0);
    assert(strcmp(order2->cust->sigil, "Direwolf") == 0);
    assert(order2->rush == 0);
    int order2_num = order2->order_num;

    struct order *order3 = place_order(
        lookup_customer("Cersei"),
        "Daggers",
        2,
        230,
        &num);
    assert(num == 1);
    assert(order3->rush == 1);
    int order3_num = order3->order_num;

    struct order *order4 = place_order(
        lookup_customer("Catelyn"),
        "Chicken dinners",
        200,
        1,
        &num);
    assert(num == 3);
    assert(order4->rush == 0);
    int order4_num = order4->order_num;

    assert(order1_num != order3_num);
    assert(order3_num != order4_num);
    assert(order1_num != order4_num);
    assert(order2_num != order1_num != order3_num != order4_num);


    /* Test get_order_history. */
    if (ec == 1) {
        struct order_history hist;
        strcpy(hist.cust_name,"Catelyn");
        get_order_history(&hist);
        assert(strcmp(hist.cust_name,"Catelyn") == 0);
        assert(hist.total_business_in_gold == 227);
        assert(strcmp(hist.most_expensive_item,"Chicken dinners") == 0);
        assert(hist.num_recent_orders == 3);
        assert(strcmp(hist.recent_orders[0].desc,"Chicken dinners") == 0);
        assert(strcmp(hist.recent_orders[1].desc,"Beer") == 0);
        assert(strcmp(hist.recent_orders[2].desc,"Buttons") == 0);

        strcpy(hist.cust_name,"Cersei");
        get_order_history(&hist);
        assert(strcmp(hist.cust_name,"Cersei") == 0);
        assert(hist.total_business_in_gold == 460);
        assert(strcmp(hist.most_expensive_item,"Daggers") == 0);
        assert(hist.num_recent_orders == 1);
        assert(strcmp(hist.recent_orders[0].cust->sigil,"Lion") == 0);
    }

    /* Test fulfill_order. */
    float revenue;
    int yes = fulfill_order("Catelyn", order1_num, &revenue);
    assert(yes == 1);
    assert(revenue == 2);

    int no = fulfill_order("Catelyn", order1_num, &revenue);
    assert(no == 0);
    no = fulfill_order("Catelyn", order3_num, &revenue);
    assert(no == 0);
    yes = fulfill_order("Cersei", order3_num, &revenue);
    assert(yes == 1);
    assert(revenue == 460);

    yes = fulfill_order("Catelyn", order4_num, &revenue);
    assert(yes == 1);
    assert(revenue == 200);

    yes = fulfill_order("Catelyn", order2_num, &revenue);
    assert(yes == 1);
    assert(revenue == 25);

    printf("Summer is coming. ");
    if (ec == 1) {
        printf("(Extra credit! 150/100)\n");
    } else {
        printf("(100/100)\n");
    }
	
	return 0;
}
