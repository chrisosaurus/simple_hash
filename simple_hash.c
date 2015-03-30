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


/**********************************************
 **********************************************
 **********************************************
 ******** simple helper functions *************
 **********************************************
 **********************************************
 ***********************************************/

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

/* initialise an existing sh_entry
 *
 * returns 1 on success
 * returns 0 on error
 */
static unsigned int sh_entry_init(struct sh_entry *entry,
                                  unsigned long int hash,
                                  char *key,
                                  size_t key_len,
                                  void *data,
                                  struct sh_entry *next){

    if( ! entry ){
        puts("sh_entry_init: entry was null");
        return 0;
    }

    if( ! key ){
        puts("sh_entry_init: key was null");
        return 0;
    }

    /* we allow data to be null */

    /* we allow next to be null */

    /* if hash is 0 we issue a warning and recalculate */
    if( hash == 0 ){
        puts("warning sh_entry_init: provided hash was 0, recalculating");
        hash = sh_hash(key);
    }

    /* if key_len is 0 we issue a warning and recalcualte */
    if( key_len == 0 ){
        puts("warning sh_entry_init: provided key_lenb was 0, recalcuating");
        key_len = strlen(key);
    }

    /* setup our simple fields */
    entry->hash    = hash;
    entry->key_len = key_len;
    entry->data    = data;
    entry->next    = next;

    /* we duplicate the string */
    entry->key = sh_strdupn(key, key_len);
    if( ! entry->key ){
        puts("sh_entry_init: call to sh_strdup failed");
        return 0;
    }

    /* return success */
    return 1;
}

/* allocate and initialise a new sh_entry
 *
 * returns pointer on success
 * returns 0 on failure
 */
static struct sh_entry * sh_entry_new(unsigned long int hash,
                                      char *key,
                                      size_t key_len,
                                      void *data,
                                      struct sh_entry *next){
    struct sh_entry *she = 0;

    /* alloc */
    she = calloc(1, sizeof(struct sh_entry));
    if( ! she ){
        puts("sh_entry_new: call to calloc failed");
        return 0;
    }

    /* init */
    if( ! sh_entry_init(she, hash, key, key_len, data, next) ){
        puts("sh_entry_new: call to sh_entry_init failed");
        return 0;
    }

    return she;
}


/* find the sh_entry that should be holding this key
 *
 * returns a pointer to it on success
 * return 0 on failure
 */
static struct sh_entry * sh_find_entry(struct sh_table *table, char *key){
    puts("sh_find_entry: unimplemented");
    return 0;
}



/**********************************************
 **********************************************
 **********************************************
 ******** simple_hash.h implementation ********
 **********************************************
 **********************************************
 ***********************************************/


/* takes a char* representing a string
 *
 * returns an unsigned long integer hash value on success
 * returns 0 on error
 */
unsigned long int sh_hash(char *key){
    puts("sh_hash: unimplemented");
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
 * this will only free the *table pointer if `free_table` is set to 1
 * this will only free the *data pointers if `free_data` is set to 1
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_destroy(struct sh_table *table, unsigned int free_table, unsigned int free_data){
    /* iterator through table */
    size_t i = 0;
    /* current entry */
    struct sh_entry *cur_she = 0;
    /* next entry to consider */
    struct sh_entry *next_she = 0;

    if( ! table ){
        puts("sh_destroy: table undef");
        return 0;
    }

    /* iterate through `entries` list
     * and then iterate through each entry within it
     * freeing them and their appropriate parts
     */
    for( i=0; i < table->size; ++i ){
        next_she = table->entries[i];
        while( next_she ){
            cur_she = next_she;
            next_she = next_she->next;

            /* always free key as it is strdupn-ed */
            free(cur_she->key);

            /* only free data if we are asked to */
            if( free_data ){
                free(cur_she->data);
            }
        }
    }

    /* free entires table */
    free(table->entries);

    /* finally free table if asked to */
    if( free_table ){
        free(table);
    }

    return 1;
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

    table->size    = size;
    table->n_elems = 0;

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
    puts("sh_resize unimplemented");
    return 0;
}

/* check if the supplied key already exists in this hash
 *
 * returns 1 on success (key exists)
 * returns 0 if key doesn't exist or on error
 */
unsigned int sh_exists(struct sh_table *table, char *key){
    struct sh_entry *she = 0;

    if( ! table ){
        puts("sh_exists: table undef");
        return 0;
    }

    if( ! key ){
        puts("sh_exists: key undef");
        return 0;
    }

    /* find entry */
    she = sh_find_entry(table, key);
    if( ! she ){
        /* not found */
        return 0;
    }

    /* found */
    return 1;
}

/* insert `data` under `key`
 * this will only success if !sh_exists(table, key)
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_insert(struct sh_table *table, char *key, void *data){
    puts("sh_insert: unimplemented");
    return 0;
}

/* set `data` under `key`
 * this will only succeed if sh_exists(table, key)
 *
 * returns old data on success
 * returns 0 on error
 */
void * sh_set(struct sh_table *table, char *key, void *data){
    struct sh_entry *she = 0;
    void * old_data = 0;

    if( ! table ){
        puts("sh_get: table undef");
        return 0;
    }

    if( ! key ){
        puts("sh_get: key undef");
        return 0;
    }

    /* allow data to be null */

    /* find entry */
    she = sh_find_entry(table, key);
    if( ! she ){
        /* not found */
        return 0;
    }

    /* save old data */
    old_data = she->data;

    /* overwrite */
    she->data = data;

    /* return old data */
    return old_data;
}

/* get `data` stored under `key`
 *
 * returns data on success
 * returns 0 on error
 */
void * sh_get(struct sh_table *table, char *key){
    struct sh_entry *she = 0;

    if( ! table ){
        puts("sh_get: table undef");
        return 0;
    }

    if( ! key ){
        puts("sh_get: key undef");
        return 0;
    }

    /* find entry */
    she = sh_find_entry(table, key);
    if( ! she ){
        /* not found */
        return 0;
    }

    /* found */
    return she->data;
}

/* delete entry stored under `key`
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_delete(struct sh_table *table, char *key){
    puts("sh_delete: unimplemented");
    return 0;
}


