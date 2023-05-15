#include <stdlib.h>
#include <math.h>

#include <dp.h>

#define COL 'c'
#define ROW 'r'
#define SYM 's'
#define EDG 'e'

char get_route_elem(char** route, unsigned long r, unsigned long c){
    char mask = 0b00000011;
    mask <<= 2 * (c % 4);
    char val = route[r][c / 4] | mask;
    val >>= 2 * (c % 4);
    if(val == 0b00000000)
        return EDG;
    else if(val == 0b00000001)
        return COL;
    else if(val == 0b00000010)
        return ROW;
    else if(val == 0b00000011)
        return SYM;
    else
        return EDG;
}

void set_route_elem(char** route, unsigned long r, unsigned long c, char val){
    char mask = 0b00000011;
    mask <<= 2 * (c % 4);
    route[r][c / 4] &= ~mask;

    if(val == EDG)
        mask = 0b00000000;
    else if(val == COL)
        mask = 0b00000001;
    else if(val == ROW)
        mask = 0b00000010;
    else if(val == SYM)
        mask = 0b00000011;
    mask <<= 2 * (c % 4);
    route[r][c / 4] |= mask;

    return;
}

void route_to_ret(size_t a_size, size_t b_size, char** route, size_t* ret_size, unsigned long*** ret){
    size_t n = (a_size + b_size - 1);
    unsigned long** match = (unsigned long**)malloc(sizeof(unsigned long*) * n);

    unsigned long i = a_size - 1;
    unsigned long j = b_size - 1;
    unsigned long l = 0;
    unsigned long l_max;
    while(1){
        match[l] = (unsigned long*)malloc(sizeof(unsigned long) * 2);
        match[l][0] = i;
        match[l][1] = j;
        char d = get_route_elem(route, i, j);
        if(d == SYM){
            --i;
            --j;
        }
        else if(d == ROW){
            --i;
        }
        else if(d == COL){
            --j;
        }
        else{
            l_max = l;
            break;
        }
        ++l;
    }

    *ret_size = l_max + 1;
    *ret = (unsigned long**)malloc(sizeof(unsigned long*) * *ret_size);
    for(l = 0; l <= l_max; ++l){
        *ret[l] = (unsigned long*)malloc(sizeof(unsigned long) * 2);
        *ret[l][0] = match[l_max - l][0];
        *ret[l][1] = match[l_max - l][1];
    }

    for(l = 0; l <= l_max; ++l)
        free(match[l]);
    free(match);

    return;
}



void matching(size_t a_size, size_t b_size, int* a, int* b, int move_cost, int diff_cost, size_t* ret_size, unsigned long*** ret, unsigned long* cost){
    if(a_size <= 0 || b_size <= 0 || a_size < b_size){
        *ret_size = 0;
        return;
    }

    size_t route_row_size = a_size / 4 + 1;
    size_t route_col_size = b_size / 4 + 1;

    unsigned long** dp = (unsigned long**)malloc(sizeof(unsigned long*) * 2);
    dp[0] = (unsigned long*)malloc(sizeof(unsigned long) * b_size);
    dp[1] = (unsigned long*)malloc(sizeof(unsigned long) * b_size);
    char** route = (char**)malloc(sizeof(char*) * route_row_size);
    for(int i = 0; i < a_size; ++i){
        route[i] = (char*)calloc(route_col_size, sizeof(char));
    }

    // initial value
    dp[0][0] = diff_cost * abs(a[0] - b[0]);
    set_route_elem(route, 0, 0, EDG);
    for(int j = 1; j < b_size; ++j){
        dp[0][j] = dp[0][j] + diff_cost * abs(a[0] - b[j]) + move_cost;
        set_route_elem(route, 0, j, COL);
    }

    // calc
    for(unsigned long i = 1; i < a_size; ++i){
        dp[1][0] = dp[0][0] + move_cost + diff_cost * abs(a[i] - b[0]);
        set_route_elem(route, i, 0, ROW);

        for(unsigned long j = 1; j < b_size; ++j){
            dp[1][j] = diff_cost * abs(a[i] - b[j]);

            int r = move_cost + dp[0][j];
            int c = move_cost + dp[1][j - 1];
            int s = dp[0][j - 1];
            if(s <= r && s <= c){
                dp[1][j] += s;
                set_route_elem(route, i, j, SYM);
            }
            else if(r <= c){
                dp[1][j] += r;
                set_route_elem(route, i, j, ROW);
            }
            else{
                dp[1][j] += c;
                set_route_elem(route, i, j, COL);
            }
        }

        for(unsigned long j = 0; j < b_size; ++j){
            dp[0][j] = dp[1][j];
        }
    }

    free(dp[0]);
    free(dp[1]);
    free(dp);

    route_to_ret(a_size, b_size, route, ret_size, ret);

    for(int i = 0; i < a_size; ++i)
        free(route[i]);
    free(route);

    return;
}