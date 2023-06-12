#ifndef _TXTLIST_H_
#define _TXTLIST_H_

typedef struct{
    int len;
    char** elem;
} TXTLIST;

TXTLIST* get_txtlist(char* dir_name, int max_txtlist_size);

void free_txtlist(TXTLIST* txtlist);

#endif