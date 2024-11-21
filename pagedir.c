#include "pagedir.h"
#include <stdio.h>
bool pagedir_init(const char *pageDirectory) {
	// Fill in with your implementation
	bool create = mkdir(pageDirectory); //mkdir() function returns 0 if successful
	if (!create){
		rmdir(pageDirectory);
		return false;
	}
	return true;
}	

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
	// Fill in with your implementation
	if (documentID == 1){
		char crawlfile[100];
		strcpy(crawlfile,pageDirectory);
		strcat(crawlfile, "/");
		strcat(crawlfile, pageDirectory);
		strcat(crawlfile,".crawler");
		fopen(crawlfile,"w");

	}
	char id[10];
	sprintf(id,"%d",documentID);
	char filename[100];
	strcpy(filename,pageDirectory);
	strcat(filename, "/");
	strcat(filename,id);
	FILE *file = fopen(filename,"w");
	fprintf(file,"%s\n%d\n%s", page->url,page->depth,page->html);
	
	
}



