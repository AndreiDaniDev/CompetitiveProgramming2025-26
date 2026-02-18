#include <fstream>

#pragma GCC optimize("O3")

using namespace std;

ifstream in("arpsohood.in");
ofstream out("arpsohood.out");

const int nmax = 500, mod = 666013;
int n, kk, dp[nmax + 2], dplastt[nmax + 2];

/// ---> combinatorics <--- ///

inline int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

int exp(int a, int b){
    if(b <= 0) return 1;
    int exp2 = exp(a, b >> 1);
    exp2 = 1ll * exp2 * exp2 % mod;
    return ((b & 1) ? 1ll * exp2 * a % mod : exp2);
}

int cnk[nmax + 2][nmax + 2];

void precompute(){

    cnk[0][1] = 1; ///base case
    for(int i = 1; i <= nmax; i++){
        cnk[i][0] = 1;
        for(int j = 1; j <= i; j++)
            cnk[i][j] = add(cnk[i - 1][j], cnk[i - 1][j - 1]);
    }

    return;
}

int main(){

    in>>n>>kk; precompute();

    for(int i = 1; i <= n; i++){
        dp[i] = 1; ///only one unq value
    }

    for(int targets = 2; targets <= kk; targets++){

        for(int i = 1; i <= n; i++){
            dplastt[i] = dp[i]; dp[i] = 0;
        }

        for(int i = targets; i <= n; i++){
            ///we have smth like an array with i values from the first targets-th values

            for(int j = targets - 1; j <= i - 1; j++){
                dp[i] = add(dp[i], 1ll * dplastt[j] * cnk[i][j] % mod);
            }
        }
    }

    out<<dp[n]<<"\n";

    return 0;
}
