#include <iostream>
#define in cin
#define out cout
#include <string>

#pragma GCC target("popcnt")

using namespace std;

const int nmax = 2 * 1e5;
int n, lf[nmax + 2], rg[nmax + 2];
string s; int bestt;

inline int bits(int x){
    return __builtin_popcount(x);
}

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    int tests; in>>tests;
    for(int it = 1; it <= tests; it++){
        in>>n>>s; s = '#' + s + '#';

        lf[0] = 0; rg[n + 1] = 0;
        for(int i = 1; i <= n; i++) lf[i] = (lf[i - 1] | (1 << (s[i] - 'a')));
        for(int i = n; i >= 1; i--) rg[i] = (rg[i + 1] | (1 << (s[i] - 'a')));

        bestt = __builtin_popcount(lf[n]);
        for(int i = 1; i <= n; i++)
            bestt = max(bestt, bits(lf[i]) + bits(rg[i + 1]));
        out<<bestt<<"\n";
    }

    return 0;
}
