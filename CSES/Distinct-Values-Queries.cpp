#include <iostream>
#define in cin
#define out cout
#include <algorithm>
#include <map>

using namespace std;

const int nmax = 2 * 1e5;
int n, nrq, a[nmax + 2], st, dr;

map <int, int> lasttidx;

struct query{
    int lf, rg, qidx;
    query() : lf(0), rg(0), qidx(0) {};
    query(int st, int dr, int idx) : lf(st), rg(dr), qidx(idx) {};

    bool operator < (const query &obj) const {
        return lf > obj.lf; ///sort in decreasing value of lf
    }
} queries[nmax + 2];
int answer[nmax + 2];

inline int f(int x){ return (x & (-x)); }
struct frenwicktree{
    int tree[nmax + 2];

    void update(int pos, int value){
        for(int i = pos; i <= n; i += f(i))
            tree[i] += value;
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

    in>>n>>nrq;
    for(int i = 1; i <= n; i++)
        in>>a[i];

    for(int i = 1; i <= nrq; i++)
        in>>st>>dr, queries[i] = query(st, dr, i);
    sort(queries + 1, queries + 1 + nrq);

    int qidx = 1;
    for(int i = n; i >= 1; i--){
        if(lasttidx[a[i]])
            aib.update(lasttidx[a[i]], -1);

        aib.update(i, 1);
        lasttidx[a[i]] = i;

        for(; qidx <= nrq && queries[qidx].lf == i; qidx++)
            answer[queries[qidx].qidx] = aib.sum(queries[qidx].rg);
    }

    for(int i = 1; i <= nrq; i++)
        out<<answer[i]<<"\n";

    return 0;
}
