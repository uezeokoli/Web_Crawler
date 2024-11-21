#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "crawler.h"
#include "curl.h"
#include "url.h"
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
	// Fill in with your implementation
	if (!pagedir_init(pageDirectory)){ // if fails to initialize directory exit
		fprintf(stderr,"failed to initialize directory\n");
		exit(1);
	}
//	else{
//		pagedir_init(pageDirectory);
//	}
	size_t parse_length;
	if (!download(seedURL,parse_length)){
		fprintf(stderr,"invalid url\n");
		exit(1);
	}
	int max = atoi(maxDepth);
	if (max > 10 || max < 0){ // if maxdepth not in range [0 - 10] exit
		fprintf(stderr,"Depth out of range\n");
		exit(1);
	}
	
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
	// Fill in with your implementation
	int depth = 0;
	int bag_ind = 0;
	int id_num = 1;
	hashtable_t *ht = hashtable_new(1);
	hashtable_insert(ht, seedURL, "seen");                                              
	bag_t *bag = set_new();
	bag->pairs[bag_ind].key = seedURL;
	bag->pairs[bag_ind].item = 0;
	bag->num_pairs++;
	while (bag->num_pairs != 0){
		
			if (bag->pairs[bag_ind].key != NULL){
				
				if (pageFetcher(bag->pairs[bag_ind].key,bag->pairs[bag_ind].item)){
					sleep(1);
					webpage_t *wp = pageFetcher(bag->pairs[bag_ind].key,bag->pairs[bag_ind].item);
					if (wp->depth <= maxDepth){
						printf("%d Fetched: %s\n",wp->depth, wp->url);
						pagedir_save(wp,pageDirectory,id_num);
						id_num++;
						bag_ind++;
						pageScan(wp,bag,ht);
					}
					else{
						//printf("done: %d\n",wp->depth);
						break;
					}

	
						
				}
			}
		//}
	}
	return;
}


webpage_t *pageFetcher(char *url, int depth){
	webpage_t *wp = malloc(sizeof(webpage_t));
	wp->url = url;
	wp->length = 0;
	wp->html = download(url, wp->length);
	wp->depth = depth;
	return wp;
}
/**
 * Scans a webpage for URLs.
 */
void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
	// Fill in with your implementation
	printf("%d Scanning: %s\n",page->depth, page->url);
	int depth = page->depth;
	int pos = 0;
	int past_pos = 0;
	int dif = 1;
    	char *html = page->html; //webpage_getHTML(page);
    	char *url;
    	bool stop = false;
    	while (dif != 0) {
        // Normalize the URL
        	url = GetNextURL(page,page->html,&pos);
        	dif = pos - past_pos;
		past_pos = pos;
        // Check if the URL is internal
        	if (url == NULL){
        		break;
        	}
        	if (strstr(url, "#")!= NULL){
        		continue;
        	}
        	if (strcmp(url,"#")==0){
        		continue;
        	}

        	char *normalized_url = normalizeURL(page->url,url);
        	printf("%d Found: %s\n",page->depth,normalized_url);
        		
        	
        	if (isInternalURL(page->url, normalized_url)) {
            // Check if the URL has not been seen before
			for (int i = 0; i < pagesSeen->set[0]->num_pairs;i++){
				if (!strcmp(pagesSeen->set[0]->pairs[i].key, normalized_url)){
					printf("%d IgnDupl: %s\n",page->depth,normalized_url);
					stop = true;
					break;
				}
			}

                	if(stop){
                		stop = false;
                		continue;
                	}
			printf("%d Added: %s\n",page->depth,normalized_url);
                	hashtable_insert(pagesSeen,normalized_url, "seen");
                	set_insert(pagesToCrawl,normalized_url, depth+1);
            		

            		//free(url); // Free the normalized URL
            	
		}
		printf("%d IgnExtrn: %s\n",page->depth,normalized_url);
		/*
		else {
     		//free(url); // Free the normalized URL for non-internal links
  	      	}
  	 */
    	}
    	
}

char *GetNextURL(webpage_t *wp, const char *html, int *pos) {
// Ensure html pointer is not NULL
	
	
	const char *newpos = strstr(html +*pos, "<a");
	if (newpos == NULL){
		return NULL;
	}
	
	//if(html == NULL || *pos >= strlen(html)){
	//	return NULL;
	//}
	
	const char* link_start_tag = "href=\"";
	const char* link_end_tag = "\"";
	
	//find the next occurence of "<a href="
	const char* link_start = strstr(newpos, link_start_tag);
	if(link_start == NULL) {
		return NULL; // No more URLS found
	}
	
	//Move the position to the start of the URL
	//*pos = link_start - html + strlen(link_start_tag);
	
	link_start += strlen(link_start_tag);
	
	const char* link_end = strstr(link_start, link_end_tag);
	if (link_end == NULL) {
		return NULL; // URL format is invalid
	}
	
	//Calculate URL length
	int url_length = link_end - (link_start);
	
	//Allocate memory for the URL
	char* url = malloc(url_length +1);
	if (url == NULL){
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	
	//COPY the URL to the allocated memory
	strncpy(url, link_start, url_length);
	url[url_length] = '\0';
	
	*pos = link_end - html;
	
	return url;
	
	
	

}


int main(const int argc, char *argv[]) {
	// Fill in with your implementation
	
	if (argc != 4){
		fprintf(stderr, "incorrect number of arguments\n");
		exit(1);
	}

	if (isalpha(*argv[3]) != 0){
		fprintf(stderr, "invalid number for maxDepth\n");
		exit(1);
	}
	parseArgs(argc, argv,argv[1],argv[2],argv[3]);
	
	char *seedURL = argv[1];
	char *pageDirectory = argv[2];
	const int maxDepth = atoi(argv[3]);
	crawl(seedURL,pageDirectory,maxDepth);



}
