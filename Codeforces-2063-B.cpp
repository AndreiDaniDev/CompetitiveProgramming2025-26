#include <iostream>
#define in cin
#define out cout

#include <algorithm>

using namespace std;

const int nmax = 1e5;
int n, lf, rg, a[nmax + 2];

int64_t summin = 0;
int64_t leftt[nmax + 2];
int64_t mid[nmax + 2];
int64_t rightt[nmax + 2];

void solve(){
    in>>n>>lf>>rg; summin = 0;
    for(int i = 1; i <= n; i++)
        in>>a[i];

    leftt[0] = 0; mid[0] = 0; rightt[0] = 0;

    for(int i = 1; i < lf; i++){
        leftt[++leftt[0]] = a[i];
    }

    for(int i = lf; i <= rg; i++){
        mid[++mid[0]] = a[i];
        summin += a[i];
    }

    for(int i = rg + 1; i <= n; i++){
        rightt[++rightt[0]] = a[i];
    }

    ///O(n log n)
    sort(leftt + 1, leftt + 1 + leftt[0]);
    sort(mid + 1, mid + 1 + mid[0], [](int64_t a, int64_t b){ return a > b; });
    sort(rightt + 1, rightt + 1 + rightt[0]);

    ///O(n) for partial sums
    for(int i = 2; i <= leftt[0]; i++){
        leftt[i] += leftt[i - 1];
    }

    for(int i = 2; i <= mid[0]; i++){
        mid[i] += mid[i - 1];
    }

    for(int i = 2; i <= rightt[0]; i++){
        rightt[i] += rightt[i - 1];
    }

    leftt[0] = min(leftt[0], mid[0]);
    rightt[0] = min(rightt[0], mid[0]);

    for(int i = 1; i <= leftt[0]; i++){
        summin = min(summin, leftt[i] + mid[mid[0]] - mid[i]);
    }

    for(int i = 1; i <= rightt[0]; i++){
        summin = min(summin, rightt[i] + mid[mid[0]] - mid[i]);
    }

    out<<summin<<"\n";
    return;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    int tests = 0; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        solve(); ///solve one test case
    }

    return 0;
}
