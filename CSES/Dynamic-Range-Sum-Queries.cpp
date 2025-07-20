#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5;
int n, nrq, type, k, u;
int a[nmax + 2];

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int64_t tree[nmax + 2];

    void add(int pos, int val){
        for(int i = pos; i <= n; i += f(i))
            tree[i] += val;
    }

    int64_t sum(int pos){
        int64_t s = 0;
        for(int i = pos; i >= 1; i -= f(i))
            s += tree[i];
        return s;
    }
} aib;

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>nrq;
    for(int i = 1; i <= n; i++){
        in>>a[i];

        aib.tree[i] += a[i];
        if(i + f(i) <= n)
            aib.tree[i + f(i)] += aib.tree[i];
    }

    for(int it = 1; it <= nrq; it++){
        in>>type>>k>>u;
        if(type == 1){
            aib.add(k, -a[k] + u);
            a[k] = u;
        }else{
            out<<(aib.sum(u) - aib.sum(k - 1))<<"\n";
        }
    }

    return 0;
}
