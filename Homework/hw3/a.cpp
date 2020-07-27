//reference: https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
//reference: 陳建宏（d08944003），TA
#include <stdio.h>
#include <set>
#include <list>
#include <vector>
#include <bits/stdc++.h>
#define MAX_NUM 262144
using namespace std;

vector<int> array1[MAX_NUM];
int array2[MAX_NUM], weight[MAX_NUM];
int cnt;
list<int> check_list;

void DFS(int x, int *check){
    check[x]++;
    check_list.push_back(x);
    if (check[x] == array1[x].size()){
        cnt += weight[x];
        DFS(array2[x], check);
    }
    return;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, x, n, q;
    scanf(" %d", &N);
    for(int i=0 ; i<N ; i++){
        weight[i] = 1;
        scanf(" %d", &x);
        x--;
        if(x == -1){
            array2[i] = -1;
            continue;
        }
        array1[x].push_back(i);
        array2[i] = x;
    }

    for (int i = 0; i < N; i++){
        if (array1[i].size()==1)
            continue;
        int out = array2[i];
        while (true){
            if (out == -1 || array1[out].size() > 1 || i == out)
                break;
            weight[i]++;
            out = array2[out];
        }
        array2[i] = out;
    }

    scanf(" %d", &q);
    int i, j, e;
    int check[N] = {0};
    for(i=0 ; i<q ; i++){
        cnt = 0;
        scanf(" %d", &n);
        for(j=0 ; j<n ; j++){
            scanf(" %d", &x);
            x--;
            cnt += weight[x];
            DFS(array2[x], check);

        }
        printf("%d\n", cnt);
        while (check_list.empty()==false){
            e = check_list.front();
            check[e] = 0;
            check_list.pop_front();
        }
    }

    return 0;
}
