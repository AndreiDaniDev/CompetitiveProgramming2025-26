#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5, mod = 1e9 + 7;
int n, pairs, k, lf, rg;
int a[nmax + 2], countt, ways;

int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

int coef, prodcnk;

int exp(int a, int b){
    if(b == 0){ return 1; }
    int exp2 = exp(a, b >> 1);
    exp2 = 1ll * exp2 * exp2 % mod;
    return ((b & 1) ? 1ll * exp2 * a % mod : exp2);
}

int fact[nmax + 2], invfact[nmax + 2];;
void precompute(){
    fact[0] = 1;
    for(int i = 1; i <= n; i++)
        fact[i] = 1ll * fact[i - 1] * i % mod;
    invfact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--)
        invfact[i] = 1ll * (i + 1) * invfact[i + 1] % mod;
    return; ///precompute for cnk(n, k)
}

int cnk(int n, int k){
    if(n < 0 || k < 0 || n - k < 0){ return 0; }
    return 1ll * fact[n] * invfact[k] % mod * invfact[n - k] % mod;
}

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>pairs>>k; ///no need for actual pairs
    ///n - 2 * pairs = pairs with one element
    ///pairs = pairs with two elements
    for(int i = 1; i <= pairs; i++) in>>lf>>rg;

    precompute();
    coef = 1;

    lf = n - 2 * pairs;
    rg = pairs;

    for(int countt = 0; countt <= min(rg, k); countt++){

        prodcnk = 1ll * coef * cnk(rg, countt) % mod;
        prodcnk = 1ll * prodcnk * cnk(lf, k - countt) % mod;

        ways = add(ways, prodcnk);
        coef = 2ll * coef % mod;
    }

    out<<ways<<"\n";

    /**
    void bkt(int lastt, int inset, int cnk){
        if(inset == k){ ways = add(ways, cnk); }
        if(inset >= k){ return; }
    
        for(int i = lastt + 1; i <= countt; i++)
            bkt(i, inset + 1, 1ll * cnk * a[i] % mod);
    }
    
    for(int i = 1; i <= n - 2 * pairs; i++)
        a[++countt] = 1;
    for(int i = 1; i <= pairs; i++)
        a[++countt] = 2;

    bkt(0, 0, 1);
    **/
  
    return 0;
}
