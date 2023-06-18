#include <stdio.h>
#include <stdlib.h>


#include <dp_matching.h>
//#include <city.h>
//#include <txtlist.h>

int main(int argc, char** argv){
/*
    CITY* city = get_city(argv[1]);

    printf("city\n");
    printf("file_name   =%s\n", city->file_name);
    printf("content     =%s\n", city->content);
    printf("data_len    =%d\n", city->data_len);
    printf("data[ 0][ 0]=%lf\n", city->data[0][0]);
    printf("data[%d][14]=%lf\n", city->data_len - 1, city->data[city->data_len - 1][14]);

    free_city(city);
*/
/*
    TXTLIST* txtlist = get_txtlist(argv[1], 220);

    printf("txtlist_size=%d\n", txtlist->len);
    printf("txtlist[ 0]=%s\n", txtlist->elem[0]);
    printf("txtlist[%d]=%s\n", txtlist->len - 1, txtlist->elem[txtlist->len - 1]);

    free(txtlist);
*/

    float** a = (float**)malloc(sizeof(float) * 2);
    a[0] = (float*)malloc(sizeof(float) * 2);
    a[1] = (float*)malloc(sizeof(float) * 2);
    a[0][0] = 0.0f;
    a[0][1] = 1.0f;
    a[1][0] = 1.0f;
    a[1][1] = -1.0f;

    float** b = (float**)malloc(sizeof(float) * 3);
    b[0] = (float*)malloc(sizeof(float) * 2);
    b[1] = (float*)malloc(sizeof(float) * 2);
    b[2] = (float*)malloc(sizeof(float) * 2);
    b[0][0] = 0.0f;
    b[0][1] = 2.0f;
    b[1][0] = 1.0f;
    b[1][1] = 1.0f;
    b[2][0] = -1.0f;
    b[2][1] = 0.0f;

    double total_dist = dp_matching(2, 3, a, b, 2);
    printf("%lf\n", total_dist);

    return 0;
}