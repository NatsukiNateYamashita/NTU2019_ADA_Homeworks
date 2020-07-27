//reference: TA -> do not quite understand in Monday(10/14)
//討論：陳健宏
#include<iostream>
#include<cstdio>
#include <climits>
using namespace std;

int64_t min(int64_t a, int64_t b){
   return (a < b)? a : b;
}
int64_t max(int64_t a, int64_t b){
   return (a > b)? a : b;
}

int64_t MultiGoodSubArray(int64_t A[], int64_t l, int64_t m, int64_t h){
    int64_t l_max = INT_MIN;
    int64_t l_min = INT_MAX;
    int64_t r_max = INT_MIN;
    int64_t r_min = INT_MAX;
    int64_t max_here = INT_MIN;
    int64_t min_here = INT_MAX;
    int64_t cnt = 0;

    l_max = INT_MIN;
    l_min = INT_MAX;
    for (int64_t i = m; i >= l; i--){
      l_max = max(l_max, A[i]);
      l_min = min(l_min, A[i]);

      r_max = INT_MIN;
      r_min = INT_MAX;
      for (int64_t j = m+1; j <= h; j++){
        r_max = max(r_max, A[j]);
        r_min = min(r_min, A[j]);

        max_here = INT_MIN;
        min_here = INT_MAX;
        max_here = max(l_max, r_max);
        min_here = min(l_min, r_min);
        if ((max_here - min_here) == (j - i))
          cnt += 1;
      }
    }
    return cnt;
}

int64_t SoloGoodSubArray(int64_t A[], int64_t l, int64_t h){
    if (l == h)
      return 1;
    int64_t m = (l+h) / 2;
    int64_t cnt = 0;
    cnt += SoloGoodSubArray(A, l, m);
    cnt += SoloGoodSubArray(A, m+1, h);
    cnt += MultiGoodSubArray(A, l, m, h);
    return cnt;
}

int main(){
    int64_t N;
  	scanf("%lld", &N);
    int64_t A[N];
    for(int64_t i=0; i < N; i++)
		  scanf("%lld", &A[i]);
    printf("%lld", SoloGoodSubArray(A, 0, N-1));
    return 0;
}
