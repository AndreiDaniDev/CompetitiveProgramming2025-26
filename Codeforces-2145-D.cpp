#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 30, cnkmax = 435;
int n, k, nn, kk;

int dp[nmax + 2][cnkmax + 2];
int way[nmax + 2][cnkmax + 2];

int cnk2[nmax + 2], path[nmax + 2];

void solve(){
    in>>n>>k;
    k = cnk2[n] - k;
    nn = n; kk = k;

    if(dp[n][k] < 0){
        out<<"0\n";
        return;
    }

    for(path[0] = 0; nn; ){
        int val = way[nn][kk];
        path[++path[0]] = val;

        nn -= val;
        kk -= cnk2[val];
    }

    for(int i = 1; i <= path[0]; i++){
        for(int val = n - path[i] + 1; val <= n; val++)
            out<<val<<" "; n -= path[i];
    }; out<<"\n";
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    for(int i = 0; i <= nmax; i++){
        for(int j = 1; j <= cnkmax; j++)
            dp[i][j] = -(1 << 30);
    }

    for(int i = 1; i <= nmax; i++)
        cnk2[i] = i * (i - 1) / 2;

    dp[0][0] = 0; ///base case
    for(int value = 1; value <= nmax; value++){
        for(int length = value; length <= nmax; length++){
            for(int cnk = cnk2[value]; cnk <= cnkmax; cnk++){
                if(dp[length][cnk] < dp[length - value][cnk - cnk2[value]] + 1){
                    dp[length][cnk] = dp[length - value][cnk - cnk2[value]] + 1;
                    way[length][cnk] = value;
                }
            }
        }
    }

    int tests = 1; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        solve();
    }

    return 0;
}
