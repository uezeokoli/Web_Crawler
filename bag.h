#ifndef SET_H_
#define SET_H_

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pairs {
	const char *key;
	void *item;
} Pairs;

typedef struct bag_t {
    int num_pairs;   // current number of records
    int max;    // allocated number of records
    Pairs *pairs; // array of records, i.e., name-id pairs
} bag_t;

/* Create a new (empty) set; return NULL if error. */
bag_t* set_new(void);

/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool set_insert(bag_t *set, const char *key, void *item);

/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(bag_t *set, const char *key);

/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void set_print(bag_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) );

/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(bag_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void set_delete(bag_t *set, void (*itemdelete)(void *item) );

void delSet(bag_t *set);


#endif // SET_H_
