//reference: https://colab.research.google.com/github/BenLangmead/comp-genomics-class/blob/master/notebooks/Minhash.ipynb
//reference: https://towardsdatascience.com/scalable-jaccard-similarity-using-minhash-and-spark-85d00a007c5e
//reference: https://tech.preferred.jp/ja/blog/minhash/
//reference: https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/
//reference: 陳建宏（d08944003），吳冠霖(r08922115)

#include <bits/stdc++.h>
// #include </Users/natsuki/Documents/University_Taiwan/M1_fall/AlgorithmDesign/HW/hw4/stdc++.h>

using namespace std;

struct node{
    int V;
    node(int t):V(t){}
};

class Graph{
private:
		int num_v;
		vector<vector<node> > Adjacents;
		vector<int> sorted;
    vector<vector<int> > matrix;
    int K;

public:
		Graph():num_v(0){};
		Graph(int N):num_v(N){
    		Adjacents.resize(num_v);
        matrix.resize(num_v);
        K = 300;
        for (int i = 0; i < num_v; i++){
            matrix[i].resize(K);
        }
    };

    void AddEdge(int U, int V){
    		Adjacents[U].push_back(node(V));
    }

		void topologicalSortUtil(int v, vector<bool>& visited){
				visited[v] = true;
				vector<node>::iterator i;
				for (i = Adjacents[v].begin(); i != Adjacents[v].end(); ++i)
						if (!visited[i->V])
								topologicalSortUtil(i->V, visited);
				sorted.push_back(v);
		}

		void topologicalSort(){
				vector<bool> visited(num_v);
				for (int i = 1; i < num_v; i++)
						if (visited[i] == false)
								topologicalSortUtil(i, visited);
		}

    void Random_Generator(int k){
        for (int i = 0; i < num_v; i++){
            matrix[i][k] = rand();
        }
    }

    void MiniHash(){
        for (int k = 0; k < K; k++){
            Random_Generator(k);
            for (int i = 0; i < sorted.size(); i++){
                for (int j = 0; j < Adjacents[sorted[i]].size(); j++){
                    matrix[sorted[i]][k] = min(matrix[sorted[i]][k], matrix[Adjacents[sorted[i]][j].V][k]);
                }
            }
        }
    }

    double Jaccard(int a, int b){
        double count = 0;
        for (int i = 0; i < K; i++){
            if (matrix[a][i] == matrix[b][i]){
                count++;
            }
        }
        return count/(double)K;
    }

};

int main(){
    ios_base::sync_with_stdio(false);
		cin.tie(nullptr);

    int N, Q, M;
    cin >> N >> M >> Q;

    int U[M], V[M];
    for (int i = 0; i < M; i++)
        cin >> U[i] >> V[i];

    int X[Q], Y[Q];
    for (int i = 0; i < Q; i++)
        cin >> X[i] >> Y[i];

    Graph g(N + 1);
    for (int i = 0; i < M; i++)
        g.AddEdge(U[i], V[i]);

    g.topologicalSort();
    g.MiniHash();

    for (int i = 0; i < Q; i++)
        cout<< g.Jaccard(X[i], Y[i])<<endl;

    return 0;
}
