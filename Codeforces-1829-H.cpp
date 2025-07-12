#include <iostream>
#define in cin
#define out cout

#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("popcnt")

using namespace std;

const int nmax = 2 * 1e5, valmax = 63, mod = 1e9 + 7;
int n, k, a[nmax + 2], ways,  bit, dp[2][nmax + 2];

int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

void solve(){
    in>>n>>k; bit = 1;
    for(int i = 1; i <= n; i++){
        in>>a[i];

        for(int val = 0; val <= valmax; val++)
            dp[bit][val] = dp[bit ^ 1][val];

        dp[bit][a[i]]++;

        for(int val = 0; val <= valmax; val++){
            dp[bit][val & a[i]] += dp[bit ^ 1][val];
            dp[bit][val & a[i]] = add(dp[bit][val & a[i]], 0);
        }

        bit ^= 1;
    }

    bit ^= 1;
    for(int val = 0; val <= valmax; val++){
        if(__builtin_popcount(val) == k)
            ways = add(ways, dp[bit][val]);
    }

    out<<ways<<"\n";

    ways = 0;
    for(int val = 0; val <= valmax; val++)
        dp[0][val] = 0, dp[1][val] = 0;

    return;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    int tests; in>>tests;
    for(int i = 1; i <= tests; i++)
        solve();

    return 0;
}
