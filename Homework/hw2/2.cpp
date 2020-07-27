#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

#define MAX_SEC 100000
#define MAX_NOTE 300

using namespace std;

int move(int a, int b, int K){
    return max(0, abs(a-b)-K);
}

int calc(int N, int M, int K, int array[]){

    int dp[2][MAX_NOTE] = {0};
    for(int i=0 ; i < M ; i++){
          dp[0][i] = 0;
    }
    int memo_1, memo_2, effort, move_right, move_left, temp;
    for(int i=1; i < N ; i++){
        memo_1 = i%2;
        memo_2 = (i+1)%2;
        move_right = move(array[i-1], array[i], K);
        for(int j=0; j < M ; j++ ){
            move_left = move(array[i-1], j, K);
            effort = dp[memo_2][array[i-1]] + move_right + move_left;
            for(int k=0 ; k < M ; k++){
                temp = min(move(k, j, K) + move_right, move(k, array[i], K) + move_left);
                effort = min(effort, dp[memo_2][k] + temp);
            }
            dp[memo_1][j] = effort;
        }
    }

    effort = dp[memo_1][0];
    for(int i=1 ; i<M ; i++){
        effort = min(effort, dp[memo_1][i]);
    }
        return effort;
}

int main(){
    int array[MAX_SEC];
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 0; i < N ; i++)
        scanf("%d", &array[i]);

    printf("%d\n", calc(N, M, K, array));
}
