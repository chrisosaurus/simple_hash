Simple hash
===========

A simple implementation of a hash table written in pure C99 with no external dependencies

Simple hash is licensed under the MIT license, see LICENSE for more details

Example usage
--------------

    #include "simple_hash.h"

    int main(void){
        /* create a hash with 32 buckets */
        struct sh_table *t = sh_new(32);

        /* some data to store */
        int data_1 = 1;
        int data_2 = 2;

        /* return pointer */
        int *data;

        /* insert new data */
        sh_insert(t, "hello", &data_1);
        sh_insert(t, "world", &data_2);

        /* fetch */
        data = sh_get(t, "hello");

        /* delete existing data */
        sh_delete(t, "world");

        /* mutate existing data */
        sh_set(t, "hello", &data_2);

        /* check a key exists */
        if( sh_exists(t, "hello") ){
        }

        /* resize hash */
        sh_resize(t, 64);

        /* tidy up
         * free table
         * but do not free stored data
         * destroy(table, free_table, free_data) */
        sh_destroy(t,     1,          0);
    }

