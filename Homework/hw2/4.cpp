#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

//reference: 陳建宏（d08944003），TA

double Max(double a, double b, double c){
    return max(max(a, b), c);
}

int64_t Calc_Hour (int64_t n, int64_t s1, int64_t s2, int64_t s3, int64_t enemy[]){
    int64_t fleet[3]={s1,s2,s3};
    sort(fleet, fleet+3);

    double EnemyStrength[7] = {0};
    for (int64_t i = 0; i < n; i++){
        if (enemy[i] <= fleet[0]){
            EnemyStrength[0] += 1;
        }else if (enemy[i] <= fleet[1]){
            EnemyStrength[1] += 1;
        }else if (fleet[0]+fleet[1] <= fleet[2] && enemy[i] <= fleet[0]+fleet[1]){
            EnemyStrength[2] += 1;
        }else if (fleet[0]+fleet[1] > fleet[2] && enemy[i] <= fleet[2]){
            EnemyStrength[2] += 1;
        }else if (fleet[0]+fleet[1] <= fleet[2] && enemy[i] <= fleet[2]){
            EnemyStrength[3] += 1;
        }else if (fleet[0]+fleet[1] > fleet[2] && enemy[i] <= fleet[0]+fleet[1]){
            EnemyStrength[3] += 1;
        }else if (enemy[i] <= fleet[0]+fleet[2]){
            EnemyStrength[4] += 1;
        }else if (enemy[i] <= fleet[1]+fleet[2]){
            EnemyStrength[5] += 1;
        }else if (enemy[i] <= fleet[0]+fleet[1]+fleet[2]){
            EnemyStrength[6] += 1;
        }else{
            return -1;
        }
    }

    int64_t hour = 0;
    double temp = 0.0;
    // for s1 + s2 + s3
    hour += EnemyStrength[6];
    // for s3 + s2
    hour += EnemyStrength[5];
    EnemyStrength[0] = max(EnemyStrength[0] - EnemyStrength[5], 0.0);
    // for s3 + s1
    hour += EnemyStrength[4];
    if (EnemyStrength[1] >= EnemyStrength[4]){
        EnemyStrength[1] = EnemyStrength[1] - EnemyStrength[4];
    }else{
        EnemyStrength[0] = max(EnemyStrength[0] - EnemyStrength[1] - EnemyStrength[4], 0.0);
        EnemyStrength[1] = 0.0;
    }

    // for s2 + s1 > s3
    if (fleet[0] + fleet[1] > fleet[2]){
        hour += EnemyStrength[3];
        temp = EnemyStrength[3];
        if (EnemyStrength[2] >= EnemyStrength[3]){
            EnemyStrength[2] = EnemyStrength[2] - EnemyStrength[3];
        }else{
            temp -= EnemyStrength[2];
            if (EnemyStrength[1] >= temp){
                EnemyStrength[1] = EnemyStrength[1] - temp;
            }else{
                EnemyStrength[0] = max(EnemyStrength[0] - temp - EnemyStrength[1], 0.0);
                EnemyStrength[1] = 0.0;
            }
            EnemyStrength[2] = 0.0;
        }
        temp = 0.0;
    }

    // for s2 + s1 < s3
    else if (fleet[0] + fleet[1] <= fleet[2]){
        hour += EnemyStrength[3];
        int cnt_b = EnemyStrength[3];
        int cnt_a = EnemyStrength[3];

        if (EnemyStrength[1] >= EnemyStrength[3]){
            EnemyStrength[1] = EnemyStrength[1] - EnemyStrength[3];
        }else{
            cnt_b -= EnemyStrength[1];
            EnemyStrength[1] = 0.0;
        }

        // for s1
        if (EnemyStrength[0] >= EnemyStrength[3]){
            EnemyStrength[0] = EnemyStrength[0] - EnemyStrength[3];
        }else{
            cnt_a -= EnemyStrength[0];
            EnemyStrength[0] = 0.0;
        }

        // for s1 + s2
        if (cnt_a >= 0 && cnt_b >= 0){
            int MinStrength = min(cnt_a, cnt_b);
            EnemyStrength[2] -= MinStrength;
            cnt_a -= MinStrength;
            cnt_b -= MinStrength;
        }

        if (cnt_b > 0){
            EnemyStrength[0] = max(EnemyStrength[0] - cnt_b, 0.0);
        }
    }

    int64_t MinStrength = INT8_MAX;
    for (int64_t i = 0; i <= ceil(EnemyStrength[2] / 2); i++){
        for (int64_t j = 0; j <= Max(EnemyStrength[0], EnemyStrength[1], EnemyStrength[2]); j++){
            int64_t a = EnemyStrength[2];
            int64_t b = EnemyStrength[1];
            int64_t c = EnemyStrength[0];
            a -= 2 * i;     a -= j;
            b += a;         b -= j;
            c += b;         c -= j;
            if (a<=0 && b<=0 && c<=0 && (i+j) < MinStrength){
                MinStrength = (i + j);
            }
        }
    }
    hour += MinStrength;
    return hour;
}

int main(){
    int64_t n;
    cin >> n;
    int64_t s1, s2, s3;
    cin >> s1;    cin >> s2;    cin >> s3;
    int64_t enemy[n];
    for(int64_t i = 0; i < n; i++) cin >> enemy[i];
    int64_t hour = Calc_Hour(n, s1, s2, s3, enemy);
    cout << hour;
    return 0;
}
