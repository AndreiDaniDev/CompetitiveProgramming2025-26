#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5, block = 500, sqrtmax = nmax / block + 1;
int n, nrq, value, a[nmax + 2];

inline int f(int x){ return (x & (-x)); }
struct blocktree{
    int tree[sqrtmax + 2], blocks;

    int getblock(int x){ return (x / block); }
    int getleftt(int x){ return x * block; }
    int getrightt(int x){ return (x + 1) * block - 1; }

    void add(int pos, int x){
        int blk = getblock(pos);
        int lf = max(1, getleftt(blk));
        int rg = min(n, getrightt(blk));
        int flagg = (a[pos] == tree[blk]);

        a[pos] = x;

        if(!flagg){ return; }

        tree[blk] = -(1 << 30);
        for(int i = lf; i <= rg; i++)
            tree[blk] = max(tree[blk], a[i]);
    }

    int query(int value){
        for(int blk = 0; blk <= blocks; blk++){
            if(tree[blk] >= value){
                int lf = max(1, getleftt(blk));
                int rg = min(n, getrightt(blk));

                for(int i = lf; i <= rg; i++){
                    if(a[i] >= value) return i;
                }
            }
        }

        return 0;
    }
} sqrtdecomp;

/**
8 5
3 2 4 1 5 5 2 6
4 4 7 1 1
**/

int main(){

    in>>n>>nrq;

    sqrtdecomp.blocks = (n / block + !!(n % block));

    for(int i = 1; i <= n; i++){
        in>>a[i];

        int blk = sqrtdecomp.getblock(i);
        sqrtdecomp.tree[blk] = max(
            sqrtdecomp.tree[blk], a[i]
        );
    }

    /**for(int it = 1; it <= n; it++)
        out<<a[it]<<" "; out<<"\n";**/

    for(int i = 1; i <= nrq; i++){
        in>>value;

        int pos = sqrtdecomp.query(value);
        if(pos){ sqrtdecomp.add(pos, a[pos] - value); }

        out<<pos<<" ";
        /**for(int it = 1; it <= n; it++)
            out<<a[it]<<" "; out<<"\n";**/
    }

    return 0;
}
