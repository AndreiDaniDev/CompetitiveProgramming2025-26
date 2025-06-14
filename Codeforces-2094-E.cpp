#include <iostream>
#define in cin
#define out cout

using namespace std;

///https://codeforces.com/contest/2094/problem/E
const int nmax = 2 * 1e5, bitmax = 29;
int tests, n, a[nmax + 2], bits[bitmax + 2];
int64_t summax, sum;

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    in>>tests;
    for(int __t = 1; __t <= tests; __t++){

        in>>n; summax = 0;
        for(int i = 1; i <= n; i++)
            in>>a[i];

        for(int bit = 0; bit <= bitmax; bit++){
            for(int i = 1; i <= n; i++)
                bits[bit] += !!(a[i] & (1 << bit));
        }

        for(int i = 1; i <= n; i++){
            sum = 0;
            for(int bit = 0; bit <= bitmax; bit++){
                if(a[i] & (1 << bit)){
                    sum += 1ll * (n - bits[bit]) * (1 << bit);
                }else{ sum += 1ll * bits[bit] * (1 << bit); }
            }
            summax = max(summax, sum);
        }

        for(int bit = 0; bit <= bitmax; bit++)
            bits[bit] = 0;

        out<<summax<<"\n";
    }

    return 0;
}
