#ifndef _DP_H_
#define _DP_H_

// route[i][0/1] = index of a/b of i th pair
void matching(int a_size, int b_size, double** a, double** b, int frame_size, int* route_size, int*** route, double* dist);

#endif