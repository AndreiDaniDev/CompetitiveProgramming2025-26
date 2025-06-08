#include <iostream>
#define in cin
#define out cout
#include <algorithm>

using namespace std;

const int nmax = 1000, valmax = 1000000;
int n, a[nmax + 2], triangles;

int istriangle(int a, int b, int c){
    ///c > b - a and c > a - b and c < a + b
    /// ---> max(b - a + 1, a - b + 1) <= c <= a + b - 1 <--- ///
    return ((a + b > c) && (a + c > b) && (b + c > a));
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n;
    for(int i = 1; i <= n; i++)
        in>>a[i];
    sort(a + 1, a + 1 + n);

    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            int low = max(a[i] - a[j] + 1, a[j] - a[i] + 1), top = a[i] + a[j] - 1;
            int st = 1, dr = i - 1, mij, pmin = -1, pmax = -1;

            for(; st <= dr; ){
                mij = (st + dr) >> 1;
                if(a[mij] >= low){
                    pmin = mij; dr = mij - 1;
                }else{ st = mij + 1; }
            }

            if(pmin == -1){ continue; }

            st = pmin, dr = i - 1;

            for(; st <= dr; ){
                mij = (st + dr) >> 1;
                if(a[mij] <= top){
                    pmax = mij; st = mij + 1;
                }else{ dr = mij - 1; }
            }

            triangles += (pmax - pmin + 1);
        }
    }

    out<<triangles<<"\n";

    return 0;
}
