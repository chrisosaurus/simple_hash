# Simple hash [![Build Status](https://travis-ci.org/mkfifo/simple_hash.svg)](https://travis-ci.org/mkfifo/simple_hash) [![Coverage Status](https://coveralls.io/repos/mkfifo/simple_hash/badge.svg?branch=master)](https://coveralls.io/r/mkfifo/simple_hash?branch=master) <a href="https://scan.coverity.com/projects/4851"> <img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/4851/badge.svg"/> </a>
A simple implementation of a chaining hash table written in pure C99 with no external dependencies

Simple hash is licensed under the MIT license, see LICENSE for more details

Hashing function
----------------

simple_hash uses an implementation of djb2,
below is the reference implementation which can also be
found on [http://www.cse.yorku.ca/~oz/hash.html](http://www.cse.yorku.ca/~oz/hash.html)

    unsigned long
    hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

Example usage
--------------

    #include "simple_hash.h"

    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"

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

        return 0;
    }

