#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 1e5;
int n, value;
int64_t nrinv = 0;

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int tree[nmax + 2], intotal;

    void add(int pos, int val){
        for(int i = pos; i <= n; i += f(i))
            tree[i] += val;
        intotal += val;
    }

    int sum(int pos){
        int s = 0;
        for(int i = pos; i >= 1; i -= f(i))
            s += tree[i];
        return s;
    }
} aib;

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>value;

        nrinv += (aib.intotal - aib.sum(value));
        aib.add(value, 1);
    }

    out<<nrinv<<"\n";

    return 0;
}
