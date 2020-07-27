//referece: http://insilab.org/maxclique/
//referece: 陳建宏（d08944003），吳冠霖(r08922115)
#include <bits/stdc++.h>
// #include </Users/natsuki/Documents/University_Taiwan/M1_fall/AlgorithmDesign/HW/hw4/stdc++.h>
using namespace std;
//-------------------------------------------------//
class Max_Clique {
		const bool* const* e;
		int pk, level;
		const float Tlimit;
		class Vertices {
				class Vertex {
						int i, d;
				public:
						void set_i(const int ii)  { i = ii; }
						int get_i() const { return i; }
						void set_degree(int dd) { d = dd; }
						int get_degree() const { return d; }
				};
				Vertex *v;
				int sz;
				static bool desc_degree(const Vertex vi, const Vertex vj) { return (vi.get_degree() > vj.get_degree()); }
		public:
				Vertices(int size) : sz(0) { v = new Vertex[size]; }
				~Vertices () {}
				void dispose() { if (v) delete [] v; }
				void sort() { std::sort(v, v+sz, desc_degree); }
				void init_colors();
				void set_degrees(Max_Clique&);
				int size() const { return sz; }
				void push(const int ii) { v[sz++].set_i(ii); };
				void pop() { sz--; };
				Vertex& at(const int ii) const { return v[ii]; };
				Vertex& end() const { return v[sz - 1]; };
		};
		class ColorClass {
				int *i;
				int sz;
		public:
				ColorClass() : sz(0), i(0) {}
				ColorClass(const int sz) : sz(sz), i(0) { init(sz); }
				~ColorClass() { if (i) delete [] i;}
				void init(const int sz) { i = new int[sz]; rewind(); }
				void push(const int ii) { i[sz++] = ii; };
				void pop() { sz--; };
				void rewind() { sz = 0; };
				int size() const { return sz; }
				int& at(const int ii) const { return i[ii]; }
				ColorClass& operator=(const ColorClass& dh) {
				for (int j = 0; j < dh.sz; j++) i[j] = dh.i[j];
				sz = dh.sz;
				return *this;
				}
  		};
		Vertices V;
		ColorClass *C, q_max, Q;
		class StepCount {
				int i1, i2;
		public:
				StepCount() : i1(0), i2(0) {}
				void set_i1(const int ii)  { i1 = ii; }
				int get_i1() const { return i1; }
				void set_i2(const int ii)  { i2 = ii; }
				int get_i2() const { return i2; }
				void inc_i1()  { i1++; }
		};
		StepCount *S;
		bool matrixection(const int i, const int j) const { return e[i][j]; }
		bool cut1(const int, const ColorClass&);
		void cut2(const Vertices&, Vertices&);
		void color_sort(Vertices&);
		void expand_dyn(Vertices);
		void _mcq(int*&, int&);
		void degree_sort(Vertices &R) { R.set_degrees(*this); R.sort(); }
public:
		Max_Clique(const bool* const*, const int, const float=0.025);
		int steps() const { return pk; }
		void mcqdyn(int* &Max_Clique, int &sz) { _mcq(Max_Clique, sz); }
		~Max_Clique() {
				if (C) delete [] C;
				if (S) delete [] S;
				V.dispose();
		};
};

Max_Clique::Max_Clique (const bool* const* matrix, const int sz, const float tt) : pk(0), level(1), Tlimit(tt), V(sz), Q(sz), q_max(sz) {
		for (int i=0; i < sz; i++) V.push(i);
		e = matrix;
		C = new ColorClass[sz + 1];
		for (int i=0; i < sz + 1; i++) C[i].init(sz + 1);
		S = new StepCount[sz + 1];
}

void Max_Clique::_mcq(int* &Max_Clique, int &sz) {
		V.set_degrees(*this);
		V.sort();
		V.init_colors();
		for (int i=0; i < V.size() + 1; i++) {
				S[i].set_i1(0);
				S[i].set_i2(0);
		}
		expand_dyn(V);
		Max_Clique = new int[q_max.size()];
		for (int i=0; i<q_max.size(); i++) {
				Max_Clique[i] = q_max.at(i);
		}
		sz = q_max.size();
}

void Max_Clique::Vertices::init_colors() {
		const int max_degree = v[0].get_degree();
		for (int i = 0; i < max_degree; i++)
				v[i].set_degree(i + 1);
		for (int i = max_degree; i < sz; i++)
				v[i].set_degree(max_degree + 1);
}

void Max_Clique::Vertices::set_degrees(Max_Clique &m) {
		for (int i=0; i < sz; i++) {
				int d = 0;
				for (int j=0; j < sz; j++){
						if (m.matrixection(v[i].get_i(), v[j].get_i())) d++;
				}
				v[i].set_degree(d);
		}
}

bool Max_Clique::cut1(const int pi, const ColorClass &A) {
		for (int i = 0; i < A.size(); i++)
		if (matrixection(pi, A.at(i)))
				return true;
		return false;
}

void Max_Clique::cut2(const Vertices &A, Vertices &B) {
		for (int i = 0; i < A.size() - 1; i++) {
		if (matrixection(A.end().get_i(), A.at(i).get_i()))
				B.push(A.at(i).get_i());
		}
}

void Max_Clique::color_sort(Vertices &R) {
		int j = 0;
		int maxno = 1;
		int min_k = q_max.size() - Q.size() + 1;
		C[1].rewind();
		C[2].rewind();
		int k = 1;
		for (int i=0; i < R.size(); i++) {
				int pi = R.at(i).get_i();
				k = 1;
				while (cut1(pi, C[k])) k++;
				if (k > maxno) {
						maxno = k;
						C[maxno + 1].rewind();
				}
				C[k].push(pi);
				if (k < min_k) {
						R.at(j++).set_i(pi);
				}
		}
		if (j > 0) R.at(j-1).set_degree(0);
		if (min_k <= 0) min_k = 1;
		for (k = min_k; k <= maxno; k++)
				for (int i = 0; i < C[k].size(); i++) {
						R.at(j).set_i(C[k].at(i));
						R.at(j++).set_degree(k);
				}
}
void Max_Clique::expand_dyn(Vertices R) {
		S[level].set_i1(S[level].get_i1() + S[level - 1].get_i1() - S[level].get_i2());
		S[level].set_i2(S[level - 1].get_i1());
		while (R.size()) {
    		if (Q.size() + R.end().get_degree() > q_max.size()) {
    		Q.push(R.end().get_i());
    		Vertices Rp(R.size());
    		cut2(R, Rp);
    		if (Rp.size()) {
        		if ((float)S[level].get_i1()/++pk < Tlimit) {
          				degree_sort(Rp);
        		}
        		color_sort(Rp);
						S[level].inc_i1();
						level++;
						expand_dyn(Rp);
						level--;
      		}
    		else if (Q.size() > q_max.size()) {
						q_max = Q;
      		}
      		Rp.dispose();
      		Q.pop();
    }
    else {
    		return;
    }
    R.pop();
  		}
}


//-------------------------------------------------//
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    bool **matrix;
    int N;
		cin>>N;
		matrix = new bool*[N];
		for (int i = 0; i < N; i++){
				matrix[i] = new bool[N];
				string ROW;
				cin>>ROW;
				for (int j = 0; j < N; j++){
						matrix[i][j] = bool(ROW	[j]-48);
				}
		}

		int matrix_N = 0;
		vector<int> order;
		for (int i = 0; i < N; i++){
				if (matrix[i][i] == 1){
						matrix_N++;
						order.push_back(i);
				}
		}

		bool **new_matrix;
		new_matrix = new bool*[matrix_N];
		for (int i = 0; i < matrix_N; i++){
				new_matrix[i] = new bool[matrix_N];
				for (int j = 0; j < matrix_N; j++){
						new_matrix[i][j] = matrix[order[i]][order[j]];
				}
		}

		for (int i = 0; i < matrix_N; i++){
				for (int j = i + 1; j < matrix_N; j++){
						if (new_matrix[i][j] == 1 && new_matrix[j][i] == 0){
								new_matrix[i][j] = 0;
						}
						if (new_matrix[i][j] == 0 && new_matrix[j][i] == 1){
								new_matrix[j][i] = 0;
						}
				}
		}

    int *q_max;
    int q_size;
    Max_Clique md(new_matrix, matrix_N, 0.025);
    md.mcqdyn(q_max, q_size);

		bool print_o[N] = {0};
		for (int i = 0; i < q_size; i++){
				print_o[order[q_max[i]] + 1] = 1;
				cout<<order[q_max[i]] + 1<<" ";
		}

		//printout
		for (int i = 1; i <= N; i++){
				if (print_o[i] == 0){
						cout<<i<<" ";
				}
		}

    return 0;
}
