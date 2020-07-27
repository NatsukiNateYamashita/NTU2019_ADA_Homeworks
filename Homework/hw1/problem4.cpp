#include<iostream>
#include<string>
#include<algorithm>
using namespace std;


int64_t min(int64_t a, int64_t b){
	return (a < b) ? a : b;
}

int64_t Min(int64_t a, int64_t b, int64_t c) {
   return min(min(a, b), c);
}

int64_t MinOperation(string S1, string S2){
int64_t m = S1.size();
int64_t n = S2.size();
int64_t c[m+1][n+1];
// cout<< m << endl;
// cout<< n << endl;

// cout<<S1<<S2<<"\n";
if (m == 0) return 0;
if (n == 0) return 0;
for(int64_t i = 0; i <= m; i++)
  c[i][0] = i;
for(int64_t j = 0; j <= n; j++)
  c[0][j] = j;
for(int64_t i = 1; i <= m; i++){
  for(int64_t j = 1; j <= n; j++){
    if (S1[i-1] != S2[j-1]){
      c[i][j] = c[i-1][j-1];
      // cout<< "i="<<i<<"  "<<"j="<<j<<"\n"<<"c[i][j]="<<c[i][j]<<"  c[m][n]="<<c[m][n] << endl;
    }else{
      c[i][j] = 1+Min(c[i-1][j-1],c[i-1][j], c[i][j-1]);
      // cout<< "i="<<i<<"  "<<"j="<<j<<"\n"<<"c[i][j]="<<c[i][j]<<"  c[m][n]="<<c[m][n] << endl;
    }
  }
}
int64_t cc[n+1][m+1];
// cout<< m << endl;
// cout<< n << endl;

// cout<<S1<<S2<<"\n";
if (m == 0) return 0;
if (n == 0) return 0;
for(int64_t i = 0; i <= n; i++)
  cc[i][0] = i;
for(int64_t j = 0; j <= m; j++)
  cc[0][j] = j;
for(int64_t i = 1; i <= n; i++){
  for(int64_t j = 1; j <= m; j++){
    if (S1[i-1] != S2[j-1]){
      cc[i][j] = cc[i-1][j-1];
      // cout<< "i="<<i<<"  "<<"j="<<j<<"\n"<<"c[i][j]="<<c[i][j]<<"  c[m][n]="<<c[m][n] << endl;
    }else{
      cc[i][j] = 1+Min(cc[i-1][j-1],cc[i-1][j], cc[i][j-1]);
      // cout<< "i="<<i<<"  "<<"j="<<j<<"\n"<<"c[i][j]="<<c[i][j]<<"  c[m][n]="<<c[m][n] << endl;
    }
  }
}
// cout<< m << endl;
// cout<< n << endl;
return min(Min(c[m][n],c[m][0],c[0][n]),Min(cc[n][m],cc[n][0],cc[0][m]));
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  string S1;
  cin>>S1;
  string S2;
  cin>>S2;
  // cout<<S1<<S2<<"\n";
  cout<<MinOperation(S1,S2)<<"\n";
  return 0;
}
