#include "hashtable.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots){
	hashtable_t *ht = malloc(sizeof(hashtable_t));
	ht->bins = num_slots;
	ht->set = malloc(sizeof(bag_t) * ht->bins);
	for (int i = 0; i < ht->bins; i++){
		ht->set[i] = set_new();
	}
	return ht;
	
/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
}
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	int bin = *key % ht->bins;
	return set_insert(ht->set[bin], key, item);

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
}
void *hashtable_find(hashtable_t *ht, const char *key){
	int bin = *key % ht->bins;
	
	if (ht == NULL|| key == NULL){
		return NULL;
	}
	return set_find(ht->set[bin],key);

}	
/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item)){
	if (fp == NULL){
	}
	else if (ht == NULL){
		fprintf(fp,"(null)");
	}
	else{
		for (int i = 0; i < ht->bins; i++){
			set_print(ht->set[i],fp, itemprint);
		}
	}
/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
}
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) ){

	if (ht == NULL || itemfunc ==NULL){
	}
	else{
		for (int i = 0; i < ht->bins; i++){
			set_iterate(ht->set[i],arg, itemfunc);
		}
	}
/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
}
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ){

	if (ht == NULL ){
	}
	else{
		for (int i = 0; i < ht->bins; i++){
			set_delete(ht->set[i], itemdelete);
		}
		free(ht->set);
		ht->set = NULL;
		free(ht);
		ht = NULL;
	}

}

