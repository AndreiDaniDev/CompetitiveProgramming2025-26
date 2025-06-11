#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 1e5;
int n, k, a[nmax + 2];

int check(int length){
    int bamboo = 0;
    for(int i = 1; i <= n; i++)
        bamboo += (a[i] / length);
    return bamboo;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>k;
    for(int i = 1; i <= n; i++)
        in>>a[i];

    int st = 1, dr = 30000, mij, pos = -1;

    for(; st <= dr; ){
        mij = (st + dr) >> 1;
        if(check(mij) >= k){
            pos = mij, st = mij + 1;
        }else{ dr = mij - 1; }
    }

    out<<pos<<"\n";

    return 0;
}
