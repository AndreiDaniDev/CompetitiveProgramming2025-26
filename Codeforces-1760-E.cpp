#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5;
int n, a[nmax + 2], fone, fzero;

int64_t solve(int flip){
    int64_t ones = 0, inversions = 0;
    for(int i = 1; i <= n; i++){
        if(i == flip) a[i] ^= 1;

        if(a[i] == 1){ ones++; }
        if(a[i] == 0){ inversions += ones; }

        if(i == flip) a[i] ^= 1;
    }
    return inversions;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    int tests; in>>tests;
    for(int it = 1; it <= tests; it++){
        in>>n; int64_t bestt = -(1ll << 60);
        fone = 0; fzero = 0;

        for(int i = 1; i <= n; i++){
            in>>a[i];
            if(a[i] == 1) fone = i;
            if(a[i] == 0 && !fzero) fzero = i;
        }

        bestt = solve(0);
        if(fone) bestt = max(bestt, solve(fone));
        if(fzero) bestt = max(bestt, solve(fzero));

        out<<bestt<<"\n";
    }

    return 0;
}
