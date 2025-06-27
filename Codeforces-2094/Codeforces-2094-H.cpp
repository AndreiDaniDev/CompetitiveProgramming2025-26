#include <iostream>
#define in cin
#define out cout
#include <vector>
 
using namespace std;
 
const int nmax = 1e5, valmax = 1e5;
int tests, nrq, n, a[nmax + 2];
int lf, rg, k;
 
vector <int> divizors[valmax + 2];
vector <int> position[valmax + 2];
 
int getbestt(int val, int bound){
    int st = 0, dr = position[val].size() - 1, mij, pos = n + 1;
    for(; st <= dr; ){
        mij = (st + dr) >> 1;
        if(bound <= position[val][mij]){
            dr = mij - 1; pos = position[val][mij];
        }else{ st = mij + 1; }
    }
    return pos;
}
 
int64_t func(int k, int lf, int rg){
    int64_t sum = 0;
    for(int i = lf; i <= rg; ){
        for(; k % a[i] == 0; k /= a[i]);
 
        int idx = rg + 1;
        for(auto div : divizors[k])
            idx = min(idx, getbestt(div, i));
 
        sum += 1ll * (idx - i) * k;
        i = idx;
    };
    return sum;
}
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
 
    for(int i = 1; i <= valmax; i++){
        for(int j = i; j <= valmax; j += i)
            divizors[j].push_back(i);
    }
 
    in>>tests;
    for(int t = 1; t <= tests; t++){
 
        in>>n>>nrq;
        for(int i = 1; i <= n; i++){
            in>>a[i]; ///keep track where they are
            position[a[i]].push_back(i);
        }
 
        for(int i = 1; i <= nrq; i++){
            in>>k>>lf>>rg;
            out<<func(k, lf, rg)<<"\n";
        }
 
        for(int i = 1; i <= n; i++)
            position[a[i]].clear();
    }
 
    return 0;
}
