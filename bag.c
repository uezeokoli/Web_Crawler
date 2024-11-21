#include "bag.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* Create a new (empty) set; return NULL if error. */
bag_t* set_new(void){
	bag_t* set = malloc(sizeof(bag_t));
	set->num_pairs = 0;
	set->max = 1;
	set->pairs = malloc(sizeof(Pairs));
	return set;
/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
}
bool set_insert(bag_t *set, const char *key, void *item){

	if (set->num_pairs == set->max){
    	    set->max *= 2;
    	    set->pairs = realloc(set->pairs,sizeof(Pairs) * set->max); 
    	    }
    	for (int i = 0; i < set->num_pairs; i++){
    		if (set->pairs[i].key == key) {
    			return 0;
    		}
    	}
    	if (key == NULL){
    		return 0;
    	}
    	else if (item == NULL){
    		return 0;
    	}
    	set->pairs[set->num_pairs].key = key;
    	set->pairs[set->num_pairs].item = item;
    	set->num_pairs++;
    	return 1;
   
/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
}
void *set_find(bag_t *set, const char *key){
	
	if (set == NULL || key == NULL){
		return NULL;
	}
	
	for (int i = 0; i < set->num_pairs; i++){
		if (set->pairs[i].key == key){
			return set->pairs[i].item;
		}
	}
	
	return NULL;
	
	
/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
}
void set_print(bag_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) ){
	if (fp == NULL){
	}
	else if (set == NULL){
		fprintf(fp,"(null)");
	}
	else if (itemprint == NULL){
	}
	else{
		for (int i = 0; i < set->num_pairs; i++){
			itemprint(fp, set->pairs[i].key, set->pairs[i].item);
		}
	}
/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
}
void set_iterate(bag_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) ){
	if (set == NULL || itemfunc == NULL){
	}
	else {
		for (int i = 0; i < set->num_pairs; i++){
			itemfunc(arg, set->pairs[i].key, set->pairs[i].item);
		}
	}
/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
}
void set_delete(bag_t *set, void (*itemdelete)(void *item) ){
	if (set == NULL){
	}
	else if (itemdelete == NULL){
		free(set->pairs);
		set->pairs = NULL;
		free(set);
		set = NULL;

	}
	else{
		for (int i = 0; i < set->num_pairs; i++){

			itemdelete(set->pairs[i].item);
		}
		free(set->pairs);
		set->pairs = NULL;
		free(set);
		set = NULL;
			
		
	}
}

void delSet(bag_t *set){
	free(set);
	set = NULL;
}
