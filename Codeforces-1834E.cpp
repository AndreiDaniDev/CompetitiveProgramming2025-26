#include <iostream>
#define in cin
#define out cout

#include <algorithm>
#include <set>

using namespace std;

const int nmax = 3e5;
int n, a[nmax + 2];

int64_t stklcm[nmax + 2], maxvall = 0;
set <int64_t> unqvalues;

int64_t __lcm(int64_t a0, int64_t a1){
    return (a0 / __gcd(a0, a1)) * a1;
}

int64_t solve(){
    in>>n; maxvall = 1ll * n * n;
    for(int i = 1; i <= n; i++){
        in>>a[i];
    }

    stklcm[0] = 0; unqvalues.clear();

    for(int i = 1; i <= n; i++){
        stklcm[++stklcm[0]] = 1;

        int sizee = stklcm[0]; stklcm[0] = 0;
        int64_t lasttvalue = -1;

        for(int j = 1; j <= sizee; j++){
            stklcm[j] = __lcm(stklcm[j], a[i]);

            if(stklcm[j] <= maxvall && stklcm[j] != lasttvalue){
                stklcm[++stklcm[0]] = stklcm[j];
                unqvalues.insert(stklcm[j]);
                lasttvalue = stklcm[j];
            }
        }
    }

    int64_t vall = 0;
    for(auto f : unqvalues){
        vall++;

        if(f != vall){
            return vall;
        }
    }

    return vall + 1;
}

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tests; in>>tests;
    for(int i = 1; i <= tests; i++){
        out<<solve()<<"\n";
    }

    return 0;
}
