# Simple hash [![Build Status](https://travis-ci.org/mkfifo/simple_hash.svg)](https://travis-ci.org/mkfifo/simple_hash) [![Coverage Status](https://coveralls.io/repos/mkfifo/simple_hash/badge.svg?branch=master)](https://coveralls.io/r/mkfifo/simple_hash?branch=master) <a href="https://scan.coverity.com/projects/4851"> <img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/4851/badge.svg"/> </a>
A simple implementation of an unordered chaining hash table written in pure C99 with no external dependencies

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
        sh_update(t, "hello", &data_2);

        /* insert or update as need be */
        sh_set(t, "boop", &data_2);

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

Internal implementation
-----------------------

Simple hash is an unhardened unordered chaining hash.

Every incoming key is first hashed, this hash is then taken and modulo-d to find
an appropriate bucket for it, each bucket contains a pointer to an entry.

So each bucket is one of:

 - null - which means this bucket is empty
 - the head of a linked list of items that all belong in this bucket

Simple hash will not automatically resize when it becomes loaded,
but an `sh_resize` function is provided for this (which will automatically
rehash all items).

It is expected that in the future simple hash will automatically resize itself 
based on loading.

Simple hash is not hardened and so is not recommended for use cases which would
expose it to attackers.

A rough diagram of the internals of how a simple hash of size 8 would look:

      sh_table
    size    = 8
    n_elems = 4
    entries = *
              |
              v
              [ 0 | * | 0 | 0 | 0 | 0 | * | 0 ]
                    |                   |
                    |                   v
                    |                   sh_entry
                    |                 hash = Z
                    |                 key  = *
                    |                 data = *
                    |                 next = 0
                    v
                    sh_entry
                  hash = X
                  key  = *
                  data = *
                  next = *
                        /
                       /
                      /
                     /
                    v
                    sh_entry
                  hash = X
                  key  = *
                  data = *
                  next = v
                        /
                       /
                      /
                     /
                    v
                    sh_entry
                  hash = Y
                  key  = *
                  data = *
                  next = 0

Here we can see an sh_table of size 8 containing 4 entries.

3 of those entries have landed in the same bucket of [1].
Of those 3, two have collided on the hash 'X' (but have different keys),
this means that `X % 8 == Y % 8 == 1`

We also have a single item in bucket [6], so we know `Z % 8 == 6`.

