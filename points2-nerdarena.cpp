#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("points2.in");
ofstream out("points2.out");

const int nmax = 36;
int n, half;

int64_t ways, k, a[nmax + 2];
int64_t subsets[(1 << (nmax / 2)) + 2];

void bkt1(int lastt, int64_t summ){

    int st = 1, dr = subsets[0], mij, pos = subsets[0] + 1;

    ///a[i] + b[j] >= k
    for(; st <= dr; ){
        mij = (st + dr) >> 1;

        if(k <= summ + subsets[mij]){
            pos = mij; dr = mij - 1;
        }else{ st = mij + 1; }
    }
    ways += (subsets[0] - pos + 1);

    for(int i = lastt + 1; i <= half; i++)
        bkt1(i, summ + a[i]);
}

void bkt2(int lastt, int64_t summ){
    subsets[++subsets[0]] = summ;

    for(int i = lastt + 1; i <= n; i++)
        bkt2(i, summ + a[i]);
}

int main(){

    in>>n>>k; half = (n / 2);
    for(int i = 1; i <= n; i++)
        in>>a[i];

    bkt2(half, 0); sort(subsets + 1, subsets + 1 + subsets[0]);
    ///for(int i = 1; i <= subsets[0]; i++)
    ///    out<<subsets[i]<<" "; out<<"\n";

    bkt1(0, 0);
    out<<ways<<"\n";

    return 0;
}
