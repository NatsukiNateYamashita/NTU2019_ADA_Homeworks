#include<iostream>
#include<cstdio>
using namespace std;

int64_t ab(int64_t a){
	return (a <= 0) ? 0 : a;
}

int64_t max(int64_t a, int64_t b){
	return (a > b) ? a : b;
}

int64_t Max(int64_t a, int64_t b, int64_t c){
	return max(max(a, b), c);
}

int64_t MaxCrossSubarray(int64_t array[], int64_t left, int64_t mid, int64_t right){
	int64_t sum = 0;
	int64_t left_sum = INT8_MIN;
	for (int64_t i = mid; i >= left; i--){
		sum = sum + array[i];
		if (sum > left_sum)
			left_sum = sum;
	}
	sum = 0;
	int64_t right_sum = INT8_MIN;
	for (int64_t i = mid+1; i <= right; i++){
		sum = sum + array[i];
		if (sum > right_sum)
			right_sum = sum;
  }
	return left_sum + right_sum;
}

int64_t MaxSubarray(int64_t array[], int64_t left, int64_t right){
	if (left == right)
		return array[left];
	else{
		int64_t mid;
		mid = (left + right)/2;
		return Max(MaxSubarray(array, left, mid), MaxSubarray(array, mid+1, right), MaxCrossSubarray(array, left, mid, right));
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int64_t N, Q;
	 scanf("%lld%lld", &N, &Q);

  int64_t A[N];
	for(int64_t i = 0; i < N; i++)
		scanf("%lld", &A[i]);

	int64_t P[Q],V[Q];
	for (int64_t i = 0; i < Q; i++)
		scanf("%lld%lld", &P[i], &V[i]);
	//
	// cout<<N<<endl;
	// cout<<Q<<endl;
	// for (int64_ti = 0; i < Q; i++)
	// 	cout<<A[i]<<" ";
	// cout<<*P<<endl;
	// cout<<*V<<endl;
	printf("%lld", MaxSubarray(A, 0, N-1));
	for(int64_t i = 0; i < Q; i++){
		A[P[i]-1]=V[i];
		// for (int64_ti = 0; i < Q; i++)
		// 	cout<<A[i]<<" ";
		printf("\n%lld", ab(MaxSubarray(A, 0, N-1)));
	}
	return 0;
}
