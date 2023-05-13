#include <stdlib.h>
#include <math.h>
#include "dp.h"

void route_to_ret(int a_size, int b_size, char** route, int* ret_size, int*** ret){
    int n = (a_size + b_size - 1);
    int** match = (int**)malloc(sizeof(int*) * n);

    int i = a_size - 1;
    int j = b_size - 1;
    int l = 0;
    int l_max;
    while(1){
        match[l] = (int*)malloc(sizeof(int) * 2);
        match[l][0] = i;
        match[l][1] = j;
        if(route[i][j] == 's'){
            --i;
            --j;
        }
        else if(route[i][j] == 'r'){
            --i;
        }
        else if(route[i][j] == 'c'){
            --j;
        }
        else{
            l_max = l;
            break;
        }
        ++l;
    }

    *ret_size = l_max + 1;
    *ret = (int**)malloc(sizeof(int*) * *ret_size);
    for(l = 0; l <= l_max; ++l){
        *ret[l] = (int*)malloc(sizeof(int) * 2);
        *ret[l][0] = match[l_max - l][0];
        *ret[l][1] = match[l_max - l][1];
    }

    for(l = 0; l <= l_max; ++l)
        free(match[l]);
    free(match);

    return;
}

void matching(int a_size, int b_size, int* a, int* b, int move_cost, int diff_cost, int* ret_size, int*** ret){
    if(a_size <= 0 || b_size <= 0){
        *ret_size = 0;
        return;
    }

    int** dp = (int**)malloc(sizeof(int*) * a_size);
    char** route = (char**)malloc(sizeof(char*) * a_size);
    for(int i = 0; i < a_size; ++i){
        dp[i] = (int*)malloc(sizeof(int) * b_size);
        route[i] = (char*)malloc(sizeof(char) * b_size);
    }

    // initial value
    dp[0][0] = diff_cost * abs(a[0] - b[0]);
    route[0][0] = 'e';
    for(int i = 1; i < a_size; ++i){
        dp[i][0] = diff_cost * abs(a[i] - b[0]) + move_cost;
        route[i][0] = 'r';
    }
    for(int j = 1; j < a_size; ++j){
        dp[0][j] = diff_cost * abs(a[0] - b[j]) + move_cost;
        route[0][j] = 'c';
    }

    // calc
    for(int i = 1; i < a_size; ++i){
        for(int j = 1; j < b_size; ++j){
            dp[i][j] = diff_cost * abs(a[i] - b[j]);

            int r = move_cost + dp[i - 1][j];
            int c = move_cost + dp[i][j - 1];
            int s = dp[i - 1][j - 1];
            if(s <= r && s <= c){
                dp[i][j] += s;
                route[i][j] = 's';
            }
            else if(r <= c){
                dp[i][j] += r;
                route[i][j] = 'r';
            }
            else{
                dp[i][j] += c;
                route[i][j] = 'c';
            }
        }
    }

    for(int i = 0; i < a_size; ++i)
        free(dp[i]);
    free(dp);

    route_to_ret(a_size, b_size, route, ret_size, ret);

    for(int i = 0; i < a_size; ++i)
        free(route[i]);
    free(route);

    return;
}