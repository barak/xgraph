/*LINTLIBRARY*/
/*
 * String Table (Hash) Package
 *
 * Peter Moore
 * University of California, Berkeley
 * 1985
 *
 * This is a general purpose hash table package.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "copyright.h"
#include "st.h"
#include "xgraph.h"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define nil(type) ((type *) 0)
#define alloc(type) (type *) malloc(sizeof(type))

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define ST_NUMCMP(x,y) ((int) (x) - (int) (y))
#define ST_NUMHASH(x,size) (ABS((int)x)%(size))
#define ST_PTRHASH(x,size) ((int)((unsigned)(x)>>2)%size)
#define EQUAL(func, x, y) \
    ((((func) == st_numcmp) || ((func) == st_ptrcmp)) ?\
      (ST_NUMCMP((x),(y)) == 0) : ((*func)((x), (y)) == 0))


#define do_hash(key, table)\
    ((table->hash == st_ptrhash) ? ST_PTRHASH((key),(table)->num_bins) :\
     (table->hash == st_numhash) ? ST_NUMHASH((key), (table)->num_bins) :\
     (*table->hash)((key), (table)->num_bins))

char st_pkg_name[] = "st";

/* Possible error conditions */
char *st_no_mem = "out of memory";
char *st_bad_ret = "bad return code from function passed to st_foreach";
char *st_bad_gen = "null or zero generator";

/* Forward declarations */
int st_numhash(), st_ptrhash(), st_numcmp(), st_ptrcmp();
static void rehash();
static void errRaise();


ST_TABLE *st_init_table_with_params(compare, hash, size, density, grow_factor,
				    reorder_flag)
int (*compare)();
int (*hash)();
int size;
int density;
double grow_factor;
int reorder_flag;
/* Detailed table allocator */
{
    ST_TABLE *new;

    new = alloc(ST_TABLE );
    if (!new) {
	errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);
	/* NOTREACHED */
    }
    new->compare = compare;
    new->hash = hash;
    new->num_entries = 0;
    new->max_density = density;
    new->grow_factor = grow_factor;
    new->reorder_flag = reorder_flag;
    if (size <= 0) {
	size = 1;
    }
    new->num_bins = size;
    new->bins = 
	(ST_TABLE_ENTRY **) calloc((unsigned)size, sizeof(ST_TABLE_ENTRY *));
    if (!new->bins) {
	free((char *) new);
	errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);
	/* NOTREACHED */
    }
    return new;
}

ST_TABLE *st_init_table(compare, hash)
int (*compare)();
int (*hash)();
/* Default table allocator */
{
    return st_init_table_with_params(compare, hash, ST_DEFAULT_INIT_TABLE_SIZE,
				     ST_DEFAULT_MAX_DENSITY,
				     ST_DEFAULT_GROW_FACTOR,
				     ST_DEFAULT_REORDER_FLAG);
}
			    

void
st_free_table(table)
ST_TABLE *table;
/* Destroy a table */
{
    register ST_TABLE_ENTRY *ptr, *next;
    int i;

    for(i = 0; i < table->num_bins ; i++) {
	ptr = table->bins[i];
	while (ptr != nil(ST_TABLE_ENTRY)) {
	    next = ptr->next;
	    free((char *) ptr);
	    ptr = next;
	}
    }
    free((char *) table->bins);
    free((char *) table);
}


#define PTR_NOT_EQUAL(table, ptr, user_key)\
(ptr != nil(ST_TABLE_ENTRY) && !EQUAL(table->compare, user_key, (ptr)->key))

#define FIND_ENTRY(table, hash_val, key, ptr, last) \
    (last) = &(table)->bins[hash_val];\
    (ptr) = *(last);\
    while (PTR_NOT_EQUAL((table), (ptr), (key))) {\
	(last) = &(ptr)->next; (ptr) = *(last);\
    }\
    if ((ptr) != nil(ST_TABLE_ENTRY) && (table)->reorder_flag) {\
	*(last) = (ptr)->next;\
	(ptr)->next = (table)->bins[hash_val];\
	(table)->bins[hash_val] = (ptr);\
    }

int st_lookup(table, key, value)
ST_TABLE *table;
register char *key;
char **value;
/* Look up item in table -- return zero if not found */
{
    int hash_val;
    register ST_TABLE_ENTRY *ptr, **last;

    hash_val = do_hash(key, table);

    FIND_ENTRY(table, hash_val, key, ptr, last);
    
    if (ptr == nil(ST_TABLE_ENTRY)) {
	return 0;
    } else {
	if (value != nil(char *))  *value = ptr->record; 
	return 1;
    }
}

#define ADD_DIRECT(table, key, value, hash_val, new)\
{\
    if (table->num_entries/table->num_bins >= table->max_density) {\
	(void) rehash(table);\
	hash_val = do_hash(key,table);\
    }\
    \
    new = alloc(ST_TABLE_ENTRY);\
    \
    if (new) {\
	new->key = key;\
	new->record = value;\
	new->next = table->bins[hash_val];\
	table->bins[hash_val] = new;\
	table->num_entries++;\
    } else {\
	errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);\
	/* NOTREACHED */ \
    } \
}

int st_insert(table, key, value)
register ST_TABLE *table;
register char *key;
char *value;
/* Insert an item into the table - replacing if it already exists */
{
    int hash_val;
    ST_TABLE_ENTRY *new;
    register ST_TABLE_ENTRY *ptr, **last;

    hash_val = do_hash(key, table);

    FIND_ENTRY(table, hash_val, key, ptr, last);

    if (ptr == nil(ST_TABLE_ENTRY)) {
	ADD_DIRECT(table,key,value,hash_val,new);
	return 0;
    } else {
	ptr->record = value;
	return 1;
    }
}

void st_add_direct(table, key, value)
ST_TABLE *table;
char *key;
char *value;
/* Add item to table without checking for existing item */
{
    int hash_val;
    ST_TABLE_ENTRY *new;
    
    hash_val = do_hash(key, table);
    ADD_DIRECT(table, key, value, hash_val, new);
}

int st_find_or_add(table, key, slot)
ST_TABLE *table;
char *key;
char ***slot;
/* Return slot for key - make one if one doesn't exist */
{
    int hash_val;
    ST_TABLE_ENTRY *new, *ptr, **last;

    hash_val = do_hash(key, table);

    FIND_ENTRY(table, hash_val, key, ptr, last);

    if (ptr == nil(ST_TABLE_ENTRY)) {
	ADD_DIRECT(table, key, (char *)0, hash_val, new);
	if (slot != nil(char **)) *slot = &new->record;
	return 0;
    } else {
	if (slot != nil(char **)) *slot = &ptr->record;
	return 1;
    }
}

int st_find(table, key, slot)
ST_TABLE *table;
char *key;
char ***slot;
/* Finds an entry in table */
{
    int hash_val;
    ST_TABLE_ENTRY *ptr, **last;

    hash_val = do_hash(key, table);

    FIND_ENTRY(table, hash_val, key, ptr, last);

    if (ptr == nil(ST_TABLE_ENTRY)) {
	return 0;
    } else {
	if (slot != nil(char **)) *slot = &ptr->record;
	return 1;
    }
}

static void rehash(table)
register ST_TABLE *table;
/* Grows table */
{
    register ST_TABLE_ENTRY *ptr, *next, **old_bins = table->bins;
    int i, old_num_bins = table->num_bins, hash_val;

    table->num_bins = table->grow_factor*old_num_bins;
    
    if (table->num_bins%2 == 0) {
	table->num_bins += 1;
    }
    
    table->bins = 
      (ST_TABLE_ENTRY **) calloc((unsigned) table->num_bins,
	    sizeof(ST_TABLE_ENTRY *));

    if (!table->bins) {
	/* If out of memory: don't resize */
      	table->bins = old_bins;
	table->num_bins = old_num_bins;
	return;
    }
    
    table->num_entries = 0;

    for(i = 0; i < old_num_bins ; i++) {
	ptr = old_bins[i];
	while (ptr != nil(ST_TABLE_ENTRY)) {
	    next = ptr->next;
	    hash_val = do_hash(ptr->key, table);
	    ptr->next = table->bins[hash_val];
	    table->bins[hash_val] = ptr;
	    table->num_entries++;
	    ptr = next;
	}
    }
    free((char *) old_bins);
}

ST_TABLE *st_copy(old_table)
ST_TABLE *old_table;
{
    ST_TABLE *new_table;
    ST_TABLE_ENTRY *ptr, *new;
    int i, num_bins = old_table->num_bins;

    new_table = alloc(ST_TABLE );
    if (new_table == nil(ST_TABLE )) {
	errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);
	/* NOTREACHED */
    }
    
    *new_table = *old_table;
    new_table->bins = 
      (ST_TABLE_ENTRY **) calloc((unsigned) num_bins, sizeof(ST_TABLE_ENTRY *));
    
    if (new_table->bins == nil(ST_TABLE_ENTRY *)) {
	free((char *) new_table);
	errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);
	/* NOTREACHED */
    }

    for(i = 0; i < num_bins ; i++) {
	new_table->bins[i] = nil(ST_TABLE_ENTRY);
	ptr = old_table->bins[i];
	while (ptr != nil(ST_TABLE_ENTRY)) {
	    new = alloc(ST_TABLE_ENTRY);
	    if (new == nil(ST_TABLE_ENTRY)) {
		free((char *) new_table->bins);
		free((char *) new_table);
		errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);
		/* NOTREACHED */
	    }
	    *new = *ptr;
	    new->next = new_table->bins[i];
	    new_table->bins[i] = new;
	    ptr = ptr->next;
	}
    }
    return new_table;
}

int st_delete(table, keyp, value)
register ST_TABLE *table;
register char **keyp;
char **value;
{
    int hash_val;
    char *key = *keyp;
    register ST_TABLE_ENTRY *ptr, **last;

    hash_val = do_hash(key, table);

    FIND_ENTRY(table, hash_val, key, ptr ,last);
    
    if (ptr == nil(ST_TABLE_ENTRY)) {
	return 0;
    }

    *last = ptr->next;
    if (value != nil(char *)) *value = ptr->record;
    *keyp = ptr->key;
    free((char *) ptr);
    table->num_entries--;
    return 1;
}

int st_foreach(table, func, arg)
ST_TABLE *table;
enum st_retval (*func)();
char *arg;
{
    ST_TABLE_ENTRY *ptr, **last;
    enum st_retval retval;
    int i;

    for(i = 0; i < table->num_bins; i++) {
	last = &table->bins[i]; ptr = *last;
	while (ptr != nil(ST_TABLE_ENTRY)) {
	    retval = (*func)(ptr->key, ptr->record, arg);
	    switch (retval) {
	    case ST_CONTINUE:
		last = &ptr->next; ptr = *last;
		break;
	    case ST_STOP:
		return 0;
	    case ST_DELETE:
		*last = ptr->next;
		free((char *) ptr);
		ptr = *last;
		break;
	    default:
		errRaise(st_pkg_name, ST_BAD_RET, st_bad_ret);
		/* NOTREACHED */
	    }
	}
    }
    return 1;
}

int st_strhash(string, modulus)
register char *string;
int modulus;
{
    register int val = 0;
    register int c;
    
    while ((c = *string++) != '\0') {
	val = val*997 + c;
    }

    return ((val < 0) ? -val : val)%modulus;
}

int st_numhash(x, size)
char *x;
int size;
{
    return ST_NUMHASH(x, size);
}

int st_ptrhash(x, size)
char *x;
int size;
{
    return ST_PTRHASH(x, size);
}

int st_numcmp(x, y)
char *x;
char *y;
{
    return ST_NUMCMP(x, y);
}

int st_ptrcmp(x, y)
char *x;
char *y;
{
    return ST_NUMCMP(x, y);
}

ST_GENERATOR *
st_init_gen(table)
ST_TABLE *table;
/* Initializes generation of items in table */
{
    ST_GENERATOR *gen;

    gen = alloc(ST_GENERATOR);
    if (!gen) {
	errRaise(st_pkg_name, ST_NO_MEM, st_no_mem);
	/* NOTREACHED */
    }
    gen->table = table;
    gen->entry = nil(ST_TABLE_ENTRY);
    gen->st_index = 0;
    return gen;
}


int 
st_gen(gen, key_p, value_p)
ST_GENERATOR *gen;
char **key_p;
char **value_p;
/* Generates next item in generation sequence */
{
    register int i;

    if (!gen) {
	errRaise(st_pkg_name, ST_BAD_GEN, st_bad_gen);
	/* NOTREACHED */
    }
    
    if (gen->entry == nil(ST_TABLE_ENTRY)) {
	/* try to find next entry */
	for(i = gen->st_index; i < gen->table->num_bins; i++) {
	    if (gen->table->bins[i] != nil(ST_TABLE_ENTRY)) {
		gen->st_index = i+1;
		gen->entry = gen->table->bins[i];
		break;
	    }
	}
	if (gen->entry == nil(ST_TABLE_ENTRY)) {
	    return 0;		/* that's all folks ! */
	}
    }
    *key_p = gen->entry->key;
    if (value_p != 0) *value_p = gen->entry->record;
    gen->entry = gen->entry->next;
    return 1;
}


void
st_free_gen(gen)
ST_GENERATOR *gen;
{
    if (gen) {
	free((char *) gen);
    } else {
	errRaise(st_pkg_name, ST_BAD_GEN, st_bad_gen);
	/* NOTREACHED */
    }
}


static void errRaise(pkg, num, msg)
char *pkg;
int num;
char *msg;
/*
 * In this standalone version of st, and error raise causes
 * an abort after printing a message.
 */
{
    (void) fprintf(stderr, "%s: %s\n", pkg, msg);
    abort();
}
