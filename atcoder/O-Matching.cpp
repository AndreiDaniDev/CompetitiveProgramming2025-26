#include <iostream>
#define in cin
#define out cout
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC target("popcnt")

using namespace std;

const int nmax = 21, mod = 1e9 + 7;
int n, a[nmax + 2][nmax + 2], dp[(1 << nmax) + 2];

vector <int> msks[nmax + 2];

int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

int main(){

    in>>n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            in>>a[i][j];
    }

    for(int i = 1; i < (1 << n); i++)
        msks[__builtin_popcount(i)].push_back(i);

    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        for(auto mask : msks[i]){
            for(int k = 1; k <= n; k++){
                if(mask & (1 << (k - 1)))
                    dp[mask] = add(dp[mask], dp[(mask ^ (1 << (k - 1)))] * a[i][k]);
            }
        }
    }

    out<<dp[(1 << n) - 1]<<"\n";

    return 0;
}
