#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <dp.h>

#define COL 'c'
#define ROW 'r'
#define SYM 's'
#define EDG 'e'

char get_track_elem(char** route, int r, int c){
    char mask = 0b00000011;
    mask <<= 2 * (c % 4);
    char val = route[r][c / 4] & mask;
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

void set_track_elem(char** track, int r, int c, char val){
    char mask = 0b00000011;
    mask <<= 2 * (c % 4);
    track[r][c / 4] &= ~mask;

    if(val == EDG)
        mask = 0b00000000;
    else if(val == COL)
        mask = 0b00000001;
    else if(val == ROW)
        mask = 0b00000010;
    else if(val == SYM)
        mask = 0b00000011;
    mask <<= 2 * (c % 4);
    track[r][c / 4] |= mask;

    return;
}

void track_to_route(int a_size, int b_size, char** track, int* route_size, int*** route){
    size_t n = (a_size + b_size - 1);
    int** match = (int**)malloc(sizeof(int*) * n);

    int i = a_size - 1;
    int j = b_size - 1;
    int l = 0;
    int l_max;
    while(1){
        match[l] = (int*)malloc(sizeof(int) * 2);
        match[l][0] = i;
        match[l][1] = j;
        char d = get_track_elem(track, i, j);
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

    *route_size = l_max + 1;
    *route = (int**)malloc(sizeof(int*) * *route_size);
    for(l = 0; l <= l_max; ++l){
        *route[l] = (int*)malloc(sizeof(int) * 2);
        *route[l][0] = match[l_max - l][0];
        *route[l][1] = match[l_max - l][1];
    }

    for(l = 0; l <= l_max; ++l)
        free(match[l]);
    free(match);

    return;
}


double euclid_dist(double* a, double* b, int size){
    if(size <= 0){
        printf("@ dist() in src/dp_f.c : size <= 0\n");
        return 0.0;
    }
    double sqsum = 0.0;
    for(int i = 0; i < size; ++i)
        sqsum += (a[i] - b[i]) * (a[i] - b[i]);
    return sqrt(sqsum);
}


void matching(int a_size, int b_size, double** a, double** b, int frame_size, int* route_size, int*** route, double* dist){
    if(a_size <= 0 || b_size <= 0 || frame_size <= 0){
        *route_size = 0;
        return;
    }

    size_t track_row_size = a_size;
    size_t track_col_size = b_size / 4 + 1;

    double** dp = (double**)malloc(sizeof(double*) * 2);
    dp[0] = (double*)malloc(sizeof(double) * b_size);
    dp[1] = (double*)malloc(sizeof(double) * b_size);
    char** track = (char**)malloc(sizeof(char*) * track_row_size);
    for(int i = 0; i < track_row_size; ++i){
        track[i] = (char*)calloc(track_col_size, sizeof(char));
    }

    // initial value
    dp[0][0] = euclid_dist(a[0], b[0], frame_size);
    set_track_elem(track, 0, 0, EDG);
    for(int j = 1; j < b_size; ++j){
        dp[0][j] = dp[0][j - 1] + euclid_dist(a[0], b[j], frame_size);
        set_track_elem(track, 0, j, COL);
    }

    // calc
    for(int i = 1; i < a_size; ++i){
        dp[1][0] = dp[0][0] + euclid_dist(a[i], b[0], frame_size);
        set_track_elem(track, i, 0, ROW);

        for(int j = 1; j < b_size; ++j){
            double d = euclid_dist(a[i], b[j], frame_size);

            double r = dp[0][j] + d;
            double c = dp[1][j - 1] + d;
            double s = dp[0][j - 1] + 2.0f * d;
            if(s <= r && s <= c){
                dp[1][j] = s;
                set_track_elem(track, i, j, SYM);
            }
            else if(r <= c){
                dp[1][j] = r;
                set_track_elem(track, i, j, ROW);
            }
            else{
                dp[1][j] = c;
                set_track_elem(track, i, j, COL);
            }
        }

        for(int j = 0; j < b_size; ++j){
            dp[0][j] = dp[1][j];
        }
    }

    *dist = dp[1][b_size - 1];

    free(dp[0]);
    free(dp[1]);
    free(dp);

    track_to_route(a_size, b_size, track, route_size, route);

    for(int i = 0; i < track_row_size; ++i)
        free(track[i]);
    free(track);

    return;
}