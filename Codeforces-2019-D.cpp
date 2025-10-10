#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2 * 1e5;
int n, ttime, a[nmax + 2];

int dpminlf[nmax + 2];
int dpminrg[nmax + 2];
int ways = 0;

int dpfreq[nmax + 2];

struct segmenttree{
    int tree[4 * nmax + 2];
    int lazy[4 * nmax + 2];

    void build(int node, int st, int dr){
        lazy[node] = 0; ///reset lazy
        if(st == dr){
            tree[node] = -st + dpfreq[st];
        }else{
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
            tree[node] = max(tree[(node << 1)], tree[(node << 1) | 1]);
        }
    }

    void propagate(int node, int st, int dr){
        if(lazy[node] && st != dr){
            lazy[(node << 1)] += lazy[node];
            lazy[(node << 1) | 1] += lazy[node];

            tree[(node << 1)] += lazy[node];
            tree[(node << 1) | 1] += lazy[node];

            lazy[node] = 0;
        }
    }

    void rangeupdate(int node, int st, int dr, int lf, int rg, int value){
        propagate(node, st, dr);

        if(lf <= st && dr <= rg){
            lazy[node] += value;
            tree[node] += value;
        }else{
            int mij = (st + dr) >> 1;
            if(lf <= mij) rangeupdate((node << 1), st, mij, lf, rg, value);
            if(mij < rg) rangeupdate((node << 1) | 1, mij + 1, dr, lf, rg, value);

            tree[node] = max(tree[(node << 1)], tree[(node << 1) | 1]);
        }
    }

} myaint;

void solve(){
    in>>n; ways = 0;
    for(int i = 1; i <= n; i++){
        in>>a[i];
    }

    /// ---> Precalc DP <---

    ttime = (1 << 30);
    for(int i = 1; i <= n; i++){
        ttime = min(ttime, a[i]);
        dpminlf[i] = ttime;

        ttime = max(0, ttime - 1);
    }

    ttime = (1 << 30);
    for(int i = n; i >= 1; i--){
        ttime = min(ttime, a[i]);
        dpminrg[i] = ttime;

        ttime = max(0, ttime - 1);
    }

    dpfreq[1] = 1; ///start pos
    for(int i = 1; i <= n; i++)
        dpfreq[dpminrg[i]]++;

    for(int i = 1; i <= n; i++)
        dpfreq[i] += dpfreq[i - 1];

    myaint.build(1, 0, n);

    for(int i = 1; i <= n; i++){
        myaint.rangeupdate(1, 0, n, dpminrg[i], n, -1);
        ways += (myaint.tree[1] <= 0);
        myaint.rangeupdate(1, 0, n, dpminlf[i], n, 1);
    }

    out<<ways<<"\n";

    for(int i = 0; i <= n; i++)
        dpfreq[i] = 0; /// ahh...

    return;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    int tests = 1; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        solve();
    }

    return 0;
}
