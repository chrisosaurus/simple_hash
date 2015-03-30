#include <limits.h> /* ULONG_MAX */
#include <stdio.h> /* puts, printf */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* strcmp, strlen */
#include <stddef.h> /* size_t */

#include "simple_hash.h"

/* FIXME temporary crutches */
/* ignore unused parameter warnings */
#pragma GCC diagnostic ignored "-Wunused-parameter"
/* ignore unused function warnings */
#pragma GCC diagnostic ignored "-Wunused-function"

/* internal strdup equivalent
 *
 * returns char* to new memory containing a strcpy on success
 * returns 0 on error
 */
static char * sh_strdupn(char *str, size_t len){
    /* our new string */
    char *new_str = 0;

    if( ! str ){
        puts("sh_strdup: str undef");
        return 0;
    }

    /* if len is 0 issue a warning and recalculate
     * note that if strlen is still 0 then all is well
     */
    if( len == 0 ){
        puts("sh_strdup: provided len was 0, recalculating");
        len = strlen(str);
    }

    /* allocate our new string
     * len + 1 to fit null terminator
     */
    new_str = calloc(len + 1, sizeof(char));
    if( ! new_str ){
        puts("sh_strdup: call to calloc failed");
        return 0;
    }

    /* perform copy */
    if( ! strncpy(new_str, str, len) ){
        puts("sh_strdup: call to strncpy failed");
        return 0;
    }

    /* ensure null terminator
     * do not rely on calloc as we may switch
     * to alt. alloc. later
     */
    new_str[len] = '\0';

    return new_str;
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
 *
 * note the error value is indistinguishable from the 0th bucket
 * this function can only error if table is null
 * so the caller can distinguish these 2 cases
 */
size_t sh_pos(struct sh_table *table, unsigned long int hash){
    if( ! table ){
        puts("sh_pos: table undef");
        return 0;
    }

    /* force hash value into a bucket */
    return hash % table->size;
}

/* allocate and initialise an ew sh_table of size size
 *
 * returns pointer on success
 * returns 0 on error
 */
struct sh_table * sh_new(size_t size){
    struct sh_table *sht = 0;

    /* alloc */
    sht = calloc(1, sizeof(struct sh_table));
    if( ! sht ){
        puts("sh_new: calloc failed");
        return 0;
    }

    /* init */
    if( ! sh_init(sht, size) ){
        puts("sh_new: call to sh_init failed");
        return 0;
    }

    return sht;
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
    if( ! table ){
        puts("sh_init: table undef");
        return 0;
    }

    table->size = size;

    /* calloc our buckets (pointer to sh_entry) */
    table->entries = calloc(size, sizeof(struct sh_entry *));
    if( ! table->entries ){
        puts("sh_init: calloc failed");
        return 0;
    }

    return 1;
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


