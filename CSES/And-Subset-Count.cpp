#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2e5, valmax = (1 << 18) - 1, lgmax = 18, mod = 1e9 + 7;
int n, a[nmax + 2], frsupramask[valmax + 2], pow2[nmax + 2], ways[valmax + 2];

int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

int main(){

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i]; frsupramask[a[i]]++;
    }

    ///frsupramask[msk] = #values that are x = msk | y
    for(int bit = 0; bit <= lgmax - 1; bit++){
        for(int msk = 0; msk <= valmax; msk++){
            if(msk & (1 << bit)){ continue; }
            frsupramask[msk] += frsupramask[msk | (1 << bit)];
        }
    }

    pow2[0] = 1; ///init
    for(int i = 1; i <= n; i++){
        pow2[i] = add(pow2[i - 1], pow2[i - 1]);
    }

    for(int msk = 0; msk <= valmax; msk++){
        ways[msk] = add(pow2[frsupramask[msk]], mod - 1);
    }

    for(int bit = 0; bit <= lgmax - 1; bit++){
        for(int msk = valmax; msk >= 0; msk--){
            if(msk & (1 << bit)){ continue; }
            ways[msk] = add(ways[msk], mod - ways[msk | (1 << bit)]);
        }
    }

    for(int i = 0; i <= n; i++){
        out<<ways[i]<<" ";
    }; out<<"\n";

    return 0;
}
