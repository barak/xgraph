/* $Header$ */

#ifndef ST_INCLUDED
#define ST_INCLUDED

/* Function prototypes */
#ifdef __STDC__
#define ARGS(args)	args
#else
#define ARGS(args)	()
#endif

extern char st_pkg_name[];

/* Fatal error codes */
#define ST_NO_MEM	0
#define ST_BAD_RET	1
#define ST_BAD_GEN	2


typedef struct st_table_entry {
    char *key;
    char *record;
    struct st_table_entry *next;
}ST_TABLE_ENTRY;


typedef struct st_table {
    int (*compare)();
    int (*hash)();
    int num_bins;
    int num_entries;
    int max_density;
    int reorder_flag;
    double grow_factor;
    ST_TABLE_ENTRY **bins;
}ST_TABLE;


typedef struct st_generator {
    ST_TABLE *table;
    ST_TABLE_ENTRY *entry;
    int st_index;
}ST_GENERATOR;

#define st_is_member(table,key) st_lookup(table,key,(char **) 0)
#define st_count(table) ((table)->num_entries)

enum st_retval {ST_CONTINUE, ST_STOP, ST_DELETE};

extern ST_TABLE *st_init_table_with_params
  ARGS((int (*compare)(), int (*hash)(), int size, int density,
	double grow_factor, int reorder_flag));

extern ST_TABLE *st_init_table
  ARGS((int (*compare)(), int (*hash)()));

extern void st_free_table
  ARGS((ST_TABLE *table));

extern int st_lookup
  ARGS((ST_TABLE *table, char *key, char **value));

extern int st_insert
  ARGS((ST_TABLE *table, char *key, char *value));

extern void st_add_direct
  ARGS((ST_TABLE *table, char *key, char *value));

extern int st_find_or_add
  ARGS((ST_TABLE *table, char *key, char ***slot));

extern int st_find
  ARGS((ST_TABLE *table, char *key, char ***slot));

extern ST_TABLE *st_copy
  ARGS((ST_TABLE *old_table));

extern int st_delete
  ARGS((ST_TABLE *table, char **keyp, char **value));

extern int st_foreach
  ARGS((ST_TABLE *table, enum st_retval (*func)(), char *arg));

extern int st_strhash
  ARGS((char *string, int modulus));

extern int st_numhash
  ARGS((char *x, int size));

extern int st_ptrhash
  ARGS((char *x, int size));

extern int st_numcmp
  ARGS((char *x, char *y));

extern int st_ptrcmp
  ARGS((char *x, char *y));

extern ST_GENERATOR *st_init_gen
  ARGS((ST_TABLE *table));

extern int st_gen
  ARGS((ST_GENERATOR *gen, char **key_p, char **value_p));

extern void st_free_gen
  ARGS((ST_GENERATOR *gen));

#define ST_DEFAULT_MAX_DENSITY 5
#define ST_DEFAULT_INIT_TABLE_SIZE 11
#define ST_DEFAULT_GROW_FACTOR 2.0
#define ST_DEFAULT_REORDER_FLAG 0

#define st_foreach_item(table, gen, key_p, value_p) \
    for(gen=st_init_gen(table); st_gen(gen,key_p,value_p) || (st_free_gen(gen),0);)

#endif /* ST_INCLUDED */
