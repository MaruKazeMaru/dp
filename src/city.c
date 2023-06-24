#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <city.h>

char* copy_first_line(char* s){
    int len = 0;
    while(s[len] != '\n'){
        ++len;
    }
    char* ret = (char*)malloc(sizeof(char) * len);

    for(int i = 0; i < len; ++i){
        ret[i] = s[i];
    }
    ret[len - 1] = '\0';

    return ret;
}

CITY* get_city(char* file_path){
    FILE* f = fopen(file_path, "r");

    CITY* city = (CITY*)malloc(sizeof(CITY));

    char temp[300];

    fgets(temp, 300, f);
    city->file_name = copy_first_line(temp);

    fgets(temp, 300, f);
    city->content = copy_first_line(temp);

    fgets(temp, 300, f);
    city->data_len = strtol(temp, NULL, 10);

    city->data = (double**)malloc(sizeof(double*) * city->data_len);
    for(int i = 0; i < city->data_len; ++i){
        fgets(temp, 300, f);

        city->data[i] = (double*)malloc(sizeof(double) * 15);

        char* s = strtok(temp, " ");
        city->data[i][0] = strtod(s, NULL);
        for(int j = 1; j < 15; ++j){
            s = strtok(NULL, " ");
            city->data[i][j] = strtod(s, NULL);
        }
    }

    fclose(f);

    return city;
}

void free_city(CITY* city){
    free(city->file_name);
    free(city->content);
    int l = city->data_len;
    for(int i = 0; i < l; ++i){
        free(city->data[i]);
    }
    free(city->data);
    free(city);
}