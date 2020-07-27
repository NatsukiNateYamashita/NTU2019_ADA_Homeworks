//reference:https://www.geeksforgeeks.org/find-paths-given-source-destination/
//reference:https://www.geeksforgeeks.org/shortest-path-weighted-graph-weight-edge-1-2/
//reference: 陳建宏（d08944003），TA
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <deque>
#include<bits/stdc++.h>
#include <stack>
#include <limits.h>
#include <stdio.h>
#include <list>
#include <vector>
#define MAX_NUM 200000

using namespace std;

typedef pair<int64_t, int64_t> iPair;

int64_t num[MAX_NUM], parent[MAX_NUM], dis[MAX_NUM];
bool v[MAX_NUM];

struct Distance_Edge{
  int64_t x, y, w1, w2;
  bool operator<(const Distance_Edge &rhs) const{
    return (rhs.w1 < w1);
  }
};
struct Danger_Edge{
    int64_t x, y, w;
};

bool check(Danger_Edge a, Danger_Edge b){
  return a.w < b.w;
}

int64_t findParent(int64_t a){
  while(a != parent[a]){
    a = parent[a];
  }
  return a;
}

int64_t Kruskal(Danger_Edge edge[], int64_t s, int64_t t, int64_t n, int64_t m)
{
    for(int64_t i = 0; i < n; i++){
        parent[i]=i;
        num[i]=1;
    }

    sort(edge, edge+m, check);

    int64_t i, maxDamage;
    for(i = 0; i < m && findParent(s) != findParent(t); i++){
        int64_t a,b;
        a = findParent(edge[i].x);
        b = findParent(edge[i].y);
        if (a != b)
        {
            if (num[a] > num[b])
            {
              parent[b] = a;
              num[a] += num[b];
            }
            else
            {
              parent[a] = b;
              num[b] += num[a];
            }
        }
        maxDamage = edge[i].w;
    }

    return maxDamage;
}

int64_t Dijkstra(deque<Distance_Edge> G[], int64_t s, int64_t t, int64_t maxDanger)
{
    priority_queue<Distance_Edge> pq;
    Distance_Edge temp, pqedge;

    memset(v, 0, sizeof(v));
    memset(dis, 0x6f, sizeof(dis));

    pqedge.x = s;
    dis[s] = 0;
    pq.push(pqedge);
    while (!pq.empty())
    {
        pqedge = pq.top();
        pq.pop();
        int x = pqedge.x;
        if (v[x] == 0)
        {
            v[x] = 1;
            for (int64_t i = 0; i < G[x].size(); i++)
            {
                if (v[G[x][i].y] == 0)
                {
                    if (dis[G[x][i].y] > dis[x] + G[x][i].w1 && G[x][i].w2 <= maxDanger)
                    {
                        dis[G[x][i].y] = dis[x] + G[x][i].w1;
                        temp.x = G[x][i].y;
                        temp.w1 = dis[G[x][i].y];
                        pq.push(temp);
                    }
                }
            }
        }
        if (v[t] == 1)
            return dis[t];
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t n, m, s, t, v1, v2, d, l;
    scanf(" %lld", &n); // number of vertex
    scanf(" %lld", &m); // number of edges
    scanf(" %lld", &s); // source
    scanf(" %lld", &t); // target

    Distance_Edge temp;
    Danger_Edge edge[m];
    deque<Distance_Edge> G[n];

    int64_t c = 0;
    bool flag = true;
    for (int64_t i = 0; i < m ; i++)
    {
      scanf(" %lld", &v1); // start vertex
      scanf(" %lld", &v2); // end vertex
      scanf(" %lld", &d); // distance between v1 & v2
      scanf(" %lld", &l); // danger level between v1 & v2

        edge[i].x = v1;
        edge[i].y = v2;
        edge[i].w = l;

        temp.x = v1;
        temp.y = v2;
        temp.w1 = d;
        temp.w2 = l;
        G[v1].push_back(temp);
        temp.x = v2;
        temp.y = v1;
        temp.w1 = d;
        temp.w2 = l;
        G[v2].push_back(temp);
        if (flag == true)
            if (c == 0)
                c = l;
            else{
                if (c!=l)
                    flag = false;
            }
        }
    int64_t maxDanger;
    if (flag == true)
        maxDanger = c;
    else
        maxDanger = Kruskal(edge, s, t, n, m);

    int64_t minDist = Dijkstra(G, s, t, maxDanger);
    cout << minDist << " " << maxDanger << "\n";

    return 0;
}
