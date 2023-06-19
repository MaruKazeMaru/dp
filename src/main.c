#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dp_matching.h>
#include <city.h>
#include <txtlist.h>

char* path_join(char* dir, char* file){
    int ld = 0, lf = 0;
    while(dir[ld] != '\0'){
        ++ld;
    }
    while(file[lf] != '\0'){
        ++lf;
    }

    char* path = (char*)malloc(sizeof(char) * (ld + lf + 2));
    for(int i = 0; i < ld; ++i){
        path[i] = dir[i];
    }
    path[ld] = '/';
    for(int i = 0; i < lf; ++i){
        path[i + ld + 1] = file[i];
    }
    path[ld + lf + 2] = '\0';

    return path;
}

char* my_strcpy(char* original){
    int l = 0;
    while(original[l] != '\0'){
        ++l;
    }

    char* copy = (char*)malloc(sizeof(char) * (l + 1));
    for(int i = 0; i < l; ++i){
        copy[i] = original[i];
    }
    copy[l] = '\0';

    return copy;
}

int main(int argc, char** argv){
    char* dir_template = argv[1];
    char* dir_unknown = argv[2];

    TXTLIST* txtlist_template = get_txtlist(dir_template, 110);
    TXTLIST* txtlist_unknown  = get_txtlist(dir_unknown, 110);

    // output
    // id O/X truth result

    for(int i = 0; i < txtlist_unknown->len; ++i){
        char* path = path_join(dir_unknown, txtlist_unknown->elem[i]);
        CITY* city_unknown = get_city(path);
        free(path);


        double min = 100000000.0;
        char* arg_min = (char*)malloc(1);

        for(int j = 0; j < txtlist_template->len; ++j){
            char* path = path_join(dir_template, txtlist_template->elem[j]);
            CITY* city_template = get_city(path);
            free(path);


            double dist = dp_matching(city_unknown->data_len, city_template->data_len, city_unknown->data, city_template->data, 15);

            if(dist < min){
                min = dist;
                free(arg_min);
                arg_min = my_strcpy(city_template->content);
            }

            free_city(city_template);
        }

        printf("%02d ", i);
        if(strcmp(arg_min, city_unknown->content)){
            printf("X");
        }
        else{
            printf("O");
        }
        printf(" %s %s\n", city_unknown->content, arg_min);

        free_city(city_unknown);
    }

    free_txtlist(txtlist_template);
    free_txtlist(txtlist_unknown);


/*
    TXTLIST* txtlist = get_txtlist(argv[1], 110);

    printf("txtlist_size=%d\n", txtlist->len);
    printf("txtlist[ 0]=%s\n", txtlist->elem[0]);
    printf("txtlist[%d]=%s\n", txtlist->len - 1, txtlist->elem[txtlist->len - 1]);

    free(txtlist);

    CITY* city = get_city(argv[1]);

    printf("city\n");
    printf("file_name   =%s\n", city->file_name);
    printf("content     =%s\n", city->content);
    printf("data_len    =%d\n", city->data_len);
    printf("data[ 0][ 0]=%lf\n", city->data[0][0]);
    printf("data[%d][14]=%lf\n", city->data_len - 1, city->data[city->data_len - 1][14]);

    free_city(city);

    double** a = (double**)malloc(sizeof(double*) * 2);
    a[0] = (double*)malloc(sizeof(double) * 2);
    a[1] = (double*)malloc(sizeof(double) * 2);
    a[0][0] = 0.0;
    a[0][1] = 1.0;
    a[1][0] = 1.0;
    a[1][1] = -1.0;

    double** b = (double**)malloc(sizeof(double*) * 3);
    b[0] = (double*)malloc(sizeof(double) * 2);
    b[1] = (double*)malloc(sizeof(double) * 2);
    b[2] = (double*)malloc(sizeof(double) * 2);
    b[0][0] = 0.0;
    b[0][1] = 2.0;
    b[1][0] = 1.0;
    b[1][1] = 1.0;
    b[2][0] = -1.0;
    b[2][1] = 0.0;
    double total_dist = dp_matching(3, 2, b, a, 2);
    printf("%lf\n", total_dist);
*/
    return 0;
}