#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <dp_matching.h>

float euclid_dist(int size, float* a, float* b){
    float sqsum = 0.0f;
    float temp;
    for(int i = 0; i < size; ++i){
        temp = a[i] - b[i];
        sqsum += temp * temp;
    }

    return sqrtf(sqsum);
}

double dp_matching(int a_size, int b_size, float** a, float** b, int frame_size){
    double** dp = (double**)malloc(sizeof(double*) * 2);
    dp[0] = (double*)malloc(sizeof(double) * b_size);
    dp[1] = (double*)malloc(sizeof(double) * b_size);

    dp[0][0] = euclid_dist(frame_size, a[0], b[0]);
    for(int j = 1; j < b_size; ++j){
        dp[0][j] = dp[0][j - 1] + euclid_dist(frame_size, a[0], b[j]);
    }

    for(int i = 1; i < a_size; ++i){
        dp[1][0] = dp[0][0] + euclid_dist(frame_size, a[i], b[0]);

        for(int j = 1; j < b_size; ++j){
            float dist = euclid_dist(frame_size, a[i], b[j]);
            double s = dp[0][j - 1] + 2.0 * dist;
            double r = dp[0][j]     + dist;
            double c = dp[1][j - 1] + dist;

            if(s <= r && s <= c){
                dp[1][j] = s;
            }
            else if(r <= c){
                dp[1][j] = r;
            }
            else{
                dp[1][j] = c;
            }
        }

        for(int j = 0; j < b_size; ++j){
            dp[0][j] = dp[1][j];
        }
    }

    double total_dist = dp[a_size - 1][b_size - 1];
    free(dp[0]);
    free(dp[1]);
    free(dp);

    return total_dist / (double)(a_size + b_size);
}