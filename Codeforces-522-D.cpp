#include <iostream>
#define in cin
#define out cout

#include <map>
#include <algorithm>

using namespace std;

const int nmax = 5 * 1e5;
int n, nrq, a[nmax + 2];
map <int, int> nextt;

struct query{
    int lf, rg, qidx;

    bool operator < (const query &obj) const {
        return lf > obj.lf;
    }
} queries[nmax + 2];
int answer[nmax + 2];

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int tree[nmax + 2];

    void add(int pos, int value){
        for(int i = pos; i <= n; i += f(i))
            tree[i] = min(tree[i], value);
    }

    int query(int pos){
        int mini = (1 << 30);
        for(int i = pos; i >= 1; i -= f(i))
            mini = min(mini, tree[i]);
        return mini;
    }
} aib;

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>nrq;
    for(int i = 1; i <= n; i++)
        in>>a[i], aib.tree[i] = (1 << 30);

    for(int i = 1; i <= nrq; i++){
        in>>queries[i].lf>>queries[i].rg;
        queries[i].qidx = i;
    }

    sort(queries + 1, queries + 1 + nrq);

    int idx = 1;
    for(int i = n; i >= 1; i--){
        if(nextt.find(a[i]) != nextt.end())
            aib.add(nextt[a[i]], nextt[a[i]] - i);
        nextt[a[i]] = i;

        for(; idx <= nrq && queries[idx].lf == i; idx++)
            answer[queries[idx].qidx] = aib.query(queries[idx].rg);
    }

    for(int i = 1; i <= nrq; i++){
        if(answer[i] == (1 << 30))
            answer[i] = -1;
        out<<answer[i]<<"\n";
    }

    return 0;
}
