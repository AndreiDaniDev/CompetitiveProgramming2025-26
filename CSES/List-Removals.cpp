#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5;
int n, a[nmax + 2], val, k;

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int tree[nmax + 2];

    void add(int pos, int val){
        for(int i = pos; i <= n; i += f(i))
            tree[i] += val;
    }

    int sum(int pos){
        int s = 0;
        for(int i = pos; i >= 1; i -= f(i))
            s += tree[i];
        return s;
    }

    int getkth(int k){
        int pos = 0;
        for(int b = 18; b >= 0; b--){
            if(pos + (1 << b) <= n && tree[pos + (1 << b)] < k)
                pos += (1 << b), k -= tree[pos];
        }
        return pos + 1;
    }
} aib;

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i];

        aib.tree[i] += 1;
        if(i + f(i) <= n)
            aib.tree[i + f(i)] += aib.tree[i];
    }

    for(int i = 1; i <= n; i++){
        in>>k;

        val = aib.getkth(k);
        aib.add(val, -1);

        out<<a[val]<<" ";
    }

    return 0;
}
