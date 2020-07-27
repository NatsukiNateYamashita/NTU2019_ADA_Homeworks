#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

#define MAX_NUM 100
using namespace std;

int Max_Power(int N, int K,int A[], int B[]){
    int i, j;
    for (i = 0; i < N-1; i++){
        for (j = 0; j < N-i-1; j++){
            if (B[j] < B[j+1]){
              swap(B[j], B[j+1]);
              swap(A[j], A[j+1]);
            }
        }
    }
    // int pokemon[MAX_NUM];
    // for (int i = 0; i < N; i++) {
    //   int a = A[i];
    //   int b = B[i];
    //   pokemon[i] = (a,b);
    // }

    //sort(B, B+N, greater<int>());
    //sort(A, A+N, greater<int>());
    for (int i = 0; i < N; i++) {
        // printf("%d\n", B[i]);
        // printf("%d\n", A[i]);
    }

    int B_dp[MAX_NUM];
    B_dp[0] = 1;
    for (int i = 1; i <= K; i++){
        B_dp[i] = B_dp[i-1] + B[i-1]; // B_dp is ordered by number of battle
         // printf("%d\n", B[i-1]);
    }
    int dp[MAX_NUM];
    dp[0] = 0;
    for (int i = 1; i <= K; i++){
        if (A[i] != 0){
            dp[i] = B_dp[i]*A[i];
        }
    }

    int max_power = dp[K-1];
    return max_power;

}

int main(){
    int N, K;
    scanf("%d%d", &N, &K);

    int a, b, A[MAX_NUM], B[MAX_NUM];
    for (int i = 0; i < N; i++){
        scanf("%d%d", &a, &b);
        A[i] = a;
        B[i] = b;
    }

    printf("%d\n", Max_Power(N, K, A, B));
    return 0;
}
