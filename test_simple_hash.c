/*  gcc simple_hash.c test_simple_hash.c -Wall -Wextra -Werror -o test_sh
 * ./test_sh
 */
#include <assert.h>

#include "simple_hash.h"

void new_insert_get_destroy(void){
    /* our simple hash table */
    struct sh_table *table = 0;

    /* some keys */
    char *key_1 = "bbbbb";
    char *key_2 = "aaaaa";
    char *key_3 = "ccccc";

    /* some data */
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;

    /* temporary data pointer used for testing get */
    int *data = 0;


    puts("testing new");
    table = sh_new(32);
    assert(table);
    assert( 32 == table->size );
    assert( 0 == table->n_elems );


    puts("testing insert and get");
    puts("one insert");
    assert( sh_insert(table, key_1, &data_1) );
    assert( 1 == table->n_elems );
    assert( 0 == sh_get(table, key_2) );
    assert( 0 == sh_get(table, key_3) );

    puts("one get");
    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );


    puts("two insert");
    assert( sh_insert(table, key_2, &data_2) );
    assert( 2 == table->n_elems );
    assert( 0 == sh_get(table, key_3) );

    puts("two get");
    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );


    puts("three insert");
    assert( sh_insert(table, key_3, &data_3) );
    assert( 3 == table->n_elems );

    puts("three get");
    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );


    assert( sh_destroy(table, 1, 0) );
}

int main(void){
    new_insert_get_destroy();
    return 0;
}

