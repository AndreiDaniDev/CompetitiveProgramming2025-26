#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5;
int n, a[nmax + 2];
int dp[nmax + 2];

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    int tests; in>>tests;
    for(int it = 1; it <= tests; it++){
        in>>n; dp[0] = 1;
        for(int i = 1; i <= n; i++)
            in>>a[i], dp[i] = 0;

        for(int i = 1; i <= n; i++){
            if(i - a[i] - 1 >= 0) dp[i] |= dp[i - a[i] - 1];
            if(i + a[i] <= n) dp[i + a[i]] |= dp[i - 1];
        }

        out<<(dp[n] ? "Yes\n" : "No\n");
    }

    return 0;
}
