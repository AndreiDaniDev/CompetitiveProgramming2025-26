#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 1000;
int n, k, a[nmax + 2];

int64_t check(int ttime){
    int64_t packets = 0;
    for(int i = 1; i <= n; i++)
        packets += (ttime / a[i]);
    return packets;
}

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>k;
    for(int i = 1; i <= n; i++)
        in>>a[i];

    int st = 1, dr = (1 << 30), mij, pos = -1;

    for(; st <= dr; ){
        mij = (st + dr) >> 1;
        if(check(mij) >= k){
            pos = mij, dr = mij - 1;
        }else{ st = mij + 1; }
    }

    out<<pos<<"\n";

    return 0;
}
