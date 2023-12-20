#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>
#include "bag.h"


typedef struct {
	char *url;
	char *html;
	size_t length;
	int depth;
} webpage_t;

//typedef struct {
	// Fill in with your implementation
//} bag_t;

//typedef struct {
	// Fill in with your implementation
//} hashtable_t;

webpage_t *pageFetcher(char *url, int depth);

char *GetNextURL(webpage_t *wp, const char *html, int *pos);
#endif
