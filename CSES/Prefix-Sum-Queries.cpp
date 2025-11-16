#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2e5;
int n, a[nmax + 2], nrq, typee, lf, rg;

int64_t partialsum[nmax + 2];

struct segmenttree{
    int64_t tree[4 * nmax + 2];
    int64_t lazy[4 * nmax + 2];

    void build(int node, int st, int dr){
        lazy[node] = 0;

        if(st == dr){
            tree[node] = partialsum[st];
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
            tree[(node << 1)] += lazy[node];

            lazy[(node << 1) | 1] += lazy[node];
            tree[(node << 1) | 1] += lazy[node];

            lazy[node] = 0;
        }
    }

    void update(int node, int st, int dr, int lf, int rg, int value){
        propagate(node, st, dr);

        if(lf <= st && dr <= rg){
            lazy[node] += value;
            tree[node] += value;
        }else{
            int mij = (st + dr) >> 1;
            if(lf <= mij) update((node << 1), st, mij, lf, rg, value);
            if(mij < rg) update((node << 1) | 1, mij + 1, dr, lf, rg, value);

            tree[node] = max(tree[(node << 1)], tree[(node << 1) | 1]);
        }
    }

    int64_t query(int node, int st, int dr, int lf, int rg){
        propagate(node, st, dr);
        if(lf <= st && dr <= rg){
            return tree[node];
        }else{
            int mij = (st + dr) >> 1; int64_t qry = -(1ll << 60);
            if(lf <= mij) qry = max(qry, query((node << 1), st, mij, lf, rg));
            if(mij < rg) qry = max(qry, query((node << 1) | 1, mij + 1, dr, lf, rg));

            tree[node] = max(tree[(node << 1)], tree[(node << 1) | 1]);
            return qry;
        }
    }
} myaint;

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>nrq;
    for(int i = 1; i <= n; i++){
        in>>a[i], partialsum[i] = partialsum[i - 1] + a[i];
    }

    myaint.build(1, 1, n);

    for(int itq = 1; itq <= nrq; itq++){
        in>>typee>>lf>>rg;
        if(typee == 1){
            myaint.update(1, 1, n, lf, n, -a[lf] + rg);
            a[lf] = rg; ///update value
        }else{
            int64_t qry = myaint.query(1, 1, n, lf, rg);
            if(lf != 1) qry -= myaint.query(1, 1, n, lf - 1, lf - 1);
            out<<max(int64_t(0), qry)<<"\n";
        }
    }

    return 0;
}
