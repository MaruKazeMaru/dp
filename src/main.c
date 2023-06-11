#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include <dp.h>
#include <wavio.h>


int main(int argc, char** argv){
    if(argc < 3){
        printf("too few arguments\n");
        return 1;
    }
    DIR* dir_template = opendir(argv[1]);
    DIR* dir_unknown = opendir(argv[2]);
    if(dir_template == NULL || dir_unknown == NULL){
        printf("can not open directory\n");
        return 1;
    }
    struct dirent* d_or_f;
    char** file_template_names = (char*)malloc(sizeof(char) * 110);

    d_or_f = readdir(dir_template);
    while(d_or_f != NULL){
        int len = d_or_f->d_reclen;
    }

    return 0;
}