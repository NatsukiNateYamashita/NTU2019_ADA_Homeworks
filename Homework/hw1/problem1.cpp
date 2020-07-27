//reference: https://appdividend.com/2019/04/30/merge-sort-in-cpp-tutorial-with-example-cpp-merge-sort-program/
//reference: TA
//討論: 陳健宏
#include <cstdio>
#include <iostream>
using namespace std;



int64_t merge(int64_t n, int64_t p[],int64_t f[],int64_t upperbound[],int64_t lowerbound[],int64_t l, int64_t m, int64_t r){
    int64_t i, j, k;
    int64_t cnt = 0;
    int64_t upper_cnt = 0;
    int64_t lower_cnt = 0;
    int64_t temp_p[n];
    int64_t temp_upper[n];
    int64_t temp_lower[n];

    //upper_cnt
    i = l;
    j = m;
    while ((i <= m - 1) && (j <= r)) {
      if (p[i] <= upperbound[j]) {
        i ++;
      }else{
        j ++;
        upper_cnt = upper_cnt + (i - l);
      }
    }
    while (j <= r){
      j ++;
      upper_cnt = upper_cnt + (i - l);
    }

    //lower_cnt
    i = l;
    j = m;
    while ((i <= m - 1) && (j <= r)) {
      if (p[i] <= lowerbound[j]) {
        i ++;
      }else{
        j ++;
        lower_cnt = lower_cnt + (i - l);
      }
    }
    while (j <= r){
      j ++;
      lower_cnt = lower_cnt + (i - l);
    }

    //sort p[]
    i = l;
    j = m;
    k = l;
    while ((i <= m - 1) && (j <= r)) {
      if (p[i] <= p[j]) {
        temp_p[k] = p[i];
        k++;
        i++;
      }else{
        temp_p[k] = p[j];
        k++;
        j++;
      }
    }
    while (i <= m - 1){
      temp_p[k] = p[i];
      k++;
      i++;
    }
    while (j <= r){
      temp_p[k] = p[j];
      k++;
      j++;
    }
    for (i = l; i <= r; i++){
      p[i] = temp_p[i];
    }

    //sort upperbound[]
    i = l;
    j = m;
    k = l;
    while ((i <= m - 1) && (j <= r)){
      if (upperbound[i] <= upperbound[j]){
        temp_upper[k] = upperbound[i];
        k++;
        i++;
      }else{
        temp_upper[k] = upperbound[j];
        k++;
        j++;
      }
    }
    while (i <= m - 1){
      temp_upper[k] = upperbound[i];
      k++;
      i++;
    }
    while (j <= r){
      temp_upper[k] = upperbound[j];
      k++;
      j++;
    }
    for (i = l; i <= r; i++){
      upperbound[i] = temp_upper[i];
    }

    //sort lowerbound[]
    i = l;
    j = m;
    k = l;
    while ((i <= m - 1) && (j <= r)) {
      if (lowerbound[i] <= lowerbound[j]) {
        temp_lower[k] = lowerbound[i];
        k++;
        i++;
      }else{
        temp_lower[k] = lowerbound[j];
        k++;
        j++;
      }
    }
    while (i <= m - 1){
      temp_lower[k] = lowerbound[i];
      k++;
      i++;
    }
    while (j <= r){
      temp_lower[k] = lowerbound[j];
      k++;
      j++;
    }
    for (i = l; i <= r; i++){
      lowerbound[i] = temp_lower[i];
    }
    cnt = upper_cnt - lower_cnt;
    return cnt;
}

int64_t mergeSort(int64_t n, int64_t p[],int64_t f[],int64_t upperbound[],int64_t lowerbound[],int64_t l, int64_t r){
    int64_t cnt=0;
    if (l < r) {
      int64_t m = (l+r) /2;
      cnt = mergeSort(n, p, f, upperbound, lowerbound, l, m);
      cnt += mergeSort(n, p, f, upperbound, lowerbound, m+1, r);
      cnt += merge(n, p, f, upperbound, lowerbound, l, m+1, r);
    }
    return cnt;
}


int64_t count_greeting(int64_t n, int64_t p[], int64_t f[]){
    int64_t upperbound[n];
    int64_t lowerbound[n];
  for (int64_t i = 0; i < n; i++ ){
    upperbound[i] = p[i]+ f[i];
    lowerbound[i] = p[i]- f[i]-1;
  }
  int64_t l = 0;
  int64_t r = n-1;
  return mergeSort(n, p, f, upperbound, lowerbound, l, r);
}

int main(){
  int64_t N;
  scanf("%lld",&N);
  int64_t P[N];
  int64_t F[N];
  for ( int64_t i = 0; i < N; i++ )
    scanf("%lld",&P[i]);
  for ( int64_t i = 0; i < N; i++ )
    scanf("%lld",&F[i]);
  printf("%lld",count_greeting(N, P, F));

  return 0;
}
