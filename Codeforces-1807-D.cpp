#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5;
int n, nrq, lf, rg, k, a[nmax + 2];

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    int tests; in>>tests;
    for(int it = 1; it <= tests; it++){
        in>>n>>nrq;
        for(int i = 1; i <= n; i++)
            in>>a[i], a[i] &= 1, a[i] += a[i - 1];

        for(int i = 1; i <= nrq; i++){
            in>>lf>>rg>>k;
            out<<((a[lf - 1] + a[n] - a[rg] + (k & 1) * (rg - lf + 1)) % 2 == 1 ? "Yes\n" : "No\n");
        }
    }

    return 0;
}
