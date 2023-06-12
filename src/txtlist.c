#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <txtlist.h>

// If last four letters of file name = ".txt" , return 1
int is_txt(char* file_name){
    int len = 0;
    while(file_name[len] != '\0'){
        ++len;
    }

    if(len < 5) return 0;
    if(
        file_name[len - 1] == 't' &&
        file_name[len - 2] == 'x' &&
        file_name[len - 3] == 't' &&
        file_name[len - 4] == '.'
    ){
        return 1;
    }
    else return 0;
}

char* duplicate_str(char* s){
    int len = 0;
    while(s[len] != '\0'){
        ++len;
    }

    char* s_copy = (char*)malloc(sizeof(char) * len);
    for(int i = 0; i < len; ++i){
        s_copy[i] = s[i];
    }

    return s_copy;
}

TXTLIST* get_txtlist(char* dir_name, int max_txtlist_size){
    DIR* dir = opendir(dir_name);
    char** txtlist = (char**)malloc(sizeof(char*) * max_txtlist_size);
    struct dirent* entry;

    int cnt = 0;
    while(cnt < max_txtlist_size && (entry = readdir(dir)) != NULL){
        if(is_txt(entry->d_name)){
            txtlist[cnt] = duplicate_str(entry->d_name);
//            printf("%s, %d, %d\n", txtlist[cnt], &txtlist[cnt], &entry->d_name);
            ++cnt;
        }
    }


    TXTLIST* ret = (TXTLIST*)malloc(sizeof(TXTLIST));
    ret->len = cnt;
    ret->elem = (char**)malloc(sizeof(char*) * cnt);
    for(int i = 0; i < cnt; ++i){
        ret->elem[i] = txtlist[i];
    }
    free(txtlist);

    return ret;
}

void free_txtlist(TXTLIST* txtlist){
    int l = txtlist->len;
    for(int i = 0; i < l; ++i){
        free(txtlist->elem[i]);
    }
    free(txtlist->elem);
    free(txtlist);
    return;
}