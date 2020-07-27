#include <algorithm>
#define MAX_NUM 2000000
using namespace std;
//reference: 陳建宏（d08944003），TA

#include <array>
#include <iostream>
#include <random>

namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
int c_lead, c_team;
Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada

/*******************************************************************************
 * Example usage:
 * const int kN = 2000000;
 * int leadership[kN], team_value[kN];
 * int main() {
 *   int n = ada::Init(); // Get N
 *   for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
 *   for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
 * }
 ******************************************************************************/

int leadership[MAX_NUM], team_value[MAX_NUM];

int Count (int leadership[], int team_value[], int n){
    const unsigned int M = 1000000007;
    int64_t plus[MAX_NUM+1] = {0};
    int distance;

    plus[0] = team_value[0];
    for(int i = 1 ; i < n ; i++)
        plus[i] = plus[i-1] + team_value[i];
    plus[n] = M;

    int64_t dp[MAX_NUM+1] = {0};
    dp[n] = 1;
    int64_t total[MAX_NUM+1] = {0};
    total[n] = 1;
    for (int i = n-1; i >= 0 ; i--){
        total[i] = (total[i+1] + dp[i+1]) % M;
        distance = std::lower_bound(plus + i + 1, plus + n, plus[i] + leadership[i]) - (plus+i+1);
        if(plus[i] + leadership[i] == plus[i+distance+1])
            distance +=1;
        dp[i] = (dp[i+1] + total [i+1] - total[i+distance+1] + M ) % M;
    }
    int64_t cnt = dp[0] % M;
    return cnt;
}

int main(){
    int n = ada::Init();
    for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
    for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();

    int cnt = Count (leadership, team_value, n);
    printf("%d\n", cnt);
}
