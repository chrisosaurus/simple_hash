#include <limits.h> /* ULONG_MAX */
#include <stdio.h> /* puts, printf */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* strcmp, strlen */
#include <stddef.h> /* size_t */

#include "simple_hash.h"

/* internal strdup equivalent
 *
 * returns char* to new memory containing a strcpy on success
 * returns 0 on error
 */
static char * sh_strdup(char *str){
    puts("unimplemented");
    return 0;
}

/* takes a char* representing a string
 *
 * returns an unsigned long integer hash value on success
 * returns 0 on error
 */
unsigned long int sh_hash(char *key){
    puts("unimplemented");
    return 0;
}

/* takes a table and a hash value
 *
 * returns the index into the table for this hash
 * returns 0 on error (if table is null)
 */
size_t sh_pos(struct sh_table *table, unsigned long int hash){
    puts("unimplemented");
    return 0;
}

/* allocate and initialise an ew sh_table of size size
 *
 * returns pointer on success
 * returns 0 on error
 */
struct sh_table * sh_new(size_t size){
    puts("unimplemented");
    return 0;
}

/* free an existing sh_table
 * this will free all the sh entries stored
 * this will free all the keys (as they are strdup-ed)
 *
 * this will only free the *data pointers if `free_data` is set to 1
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_destroy(struct sh_table *table, unsigned int free_data){
    puts("unimplemented");
    return 0;
}

/* initialise an already allocated sh_table to size size
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_init(struct sh_table *table, size_t size){
    puts("unimplemented");
    return 0;
}

/* resize an existing table to new_size
 * this will reshuffle all the buckets around
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_resize(struct sh_table *table, size_t new_size){
    puts("unimplemented");
    return 0;
}

/* check if the supplied key already exists in this hash
 *
 * returns 1 on success (key exists)
 * returns 0 if key doesn't exist or on error
 */
unsigned int sh_exists(struct sh_table *table, char *key){
    puts("unimplemented");
    return 0;
}

/* insert `data` under `key`
 * this will only success if !sh_exists(table, key)
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_insert(struct sh_table *table, char *key, void *data){
    puts("unimplemented");
    return 0;
}

/* set `data` under `key`
 * this will only succeed if sh_exists(table, key)
 *
 * returns old data on success
 * returns 0 on error
 */
void * sh_set(struct sh_table *table, char *key, void *data){
    puts("unimplemented");
    return 0;
}

/* get `data` stored under `key`
 *
 * returns data on success
 * returns 0 on error
 */
void * sh_get(struct sh_table *table, char *key){
    puts("unimplemented");
    return 0;
}

/* delete entry stored under `key`
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_delete(struct sh_table *table, char *key){
    puts("unimplemented");
    return 0;
}


