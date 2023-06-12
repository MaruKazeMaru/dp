#ifndef _CITY_H_
#define _CITY_H_

typedef struct{
    char* file_name;
    char* content;
    int data_len;
    double** data;
}CITY;

CITY* get_city(char* file_name);
void free_city(CITY* city);

#endif