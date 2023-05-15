#ifndef _DP_H_
#define _DP_H_

// ret[i][0/1] = index of a/b of i th pair
// a must be longer than b
void matching(size_t a_size, size_t b_size, int* a, int* b, int move_cost, int diff_cost, size_t* ret_size, size_t*** ret, unsigned long* cost);

#endif