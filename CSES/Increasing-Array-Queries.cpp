#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

#include <vector>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 2e5;
int n, a[nmax + 2], nrq, lf, rg;
int64_t answer[nmax + 2], partialsum[nmax + 2];

int64_t solve(int st, int dr){
    int64_t ways = 0; int bestt = 0;

    for(int i = st; i <= dr; i++){
        bestt = max(bestt, a[i]);
        ways += (bestt - a[i]);
    }

    return ways;
}

vector <pii> queries[nmax + 2];

struct segmenttree{

    int64_t tree[4 * nmax + 2];
    int64_t lazy[4 * nmax + 2];

    void propagate(int node, int st, int dr){
        if(lazy[node] && st != dr){
            lazy[(node << 1)] = lazy[node];
            lazy[(node << 1) | 1] = lazy[node];

            int mij = (st + dr) >> 1;
            tree[(node << 1)] = 1ll * lazy[node] * (mij - st + 1);
            tree[(node << 1) | 1] = 1ll * lazy[node] * (dr - mij);

            lazy[node] = 0;
        }
    }

    void build(int node, int st, int dr){
        tree[node] = 0; lazy[node] = 0;

        if(st != dr){
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
        }

        return;
    }

    void update(int node, int st, int dr, int lf, int rg, int value){
        propagate(node, st, dr);
        if(lf <= st && dr <= rg){
            tree[node] = 1ll * value * (dr - st + 1);
            lazy[node] = value;
        }else{
            int mij = (st + dr) >> 1;
            if(lf <= mij) update((node << 1), st, mij, lf, rg, value);
            if(mij < rg) update((node << 1) | 1, mij + 1, dr, lf, rg, value);

            tree[node] = (tree[(node << 1)] + tree[(node << 1) | 1]);
        }
    }

    int64_t query(int node, int st, int dr, int lf, int rg){
        propagate(node, st, dr);
        if(lf <= st && dr <= rg){
            return tree[node];
        }else{
            int mij = (st + dr) >> 1; int64_t qry = 0;
            if(lf <= mij) qry += query((node << 1), st, mij, lf, rg);
            if(mij < rg) qry += query((node << 1) | 1, mij + 1, dr, lf, rg);

            tree[node] = (tree[(node << 1)] + tree[(node << 1) | 1]);
            return qry;
        }
    }
} myaint;

int stk[nmax + 2];
int stklastt[nmax + 2];

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>nrq;
    for(int i = 1; i <= n; i++){
        in>>a[i], partialsum[i] = partialsum[i - 1] + a[i];
    }

    for(int it = 1; it <= nrq; it++){
        in>>lf>>rg;
        queries[lf].push_back(make_pair(rg, it));
    }

    for(int i = n; i >= 1; i--){
        stk[++stk[0]] = a[i];
        stklastt[stk[0]] = i;

        int lasttval = i;

        for(int it = stk[0]; it >= 1; it--){
            if(stk[it] > a[i]){ break; }

            lasttval = stklastt[it]; stk[0]--;
        }

        stk[++stk[0]] = a[i];
        stklastt[stk[0]] = lasttval;

        myaint.update(1, 1, n, i, stklastt[stk[0]], a[i]);

        for(auto f : queries[i]){
            answer[f.second] = myaint.query(1, 1, n, i, f.first);
            answer[f.second] -= (partialsum[f.first] - partialsum[i - 1]);
        }
    }

    for(int it = 1; it <= nrq; it++)
        out<<answer[it]<<"\n";

    return 0;
}
