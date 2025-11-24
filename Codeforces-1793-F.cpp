#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

#include <vector>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 3e5, qmax = 1e6;
const int block = 575;
const int maxint = (1 << 30);
int n, a[nmax + 2], nrq, lf, rg;

int dp[nmax + 2], whereval[nmax + 2];

vector <pii> queries[nmax + 2];
int answer[qmax + 2];

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int tree[nmax + 2];

    void update(int node, int value){
        for(int i = node; i <= n; i += f(i))
            tree[i] = min(tree[i], value);
    }

    int query(int node){
        int qry = maxint;
        for(int i = node; i >= 1; i -= f(i))
            qry = min(qry, tree[i]);
        return qry;
    }
} myaib;

int myabs(int x){ return ((x < 0) ? -x : x); }
void updateval(int idx){ ///update in O(n)

    for(int i = idx + 1; i <= n && i <= idx + block; i++){
        if(dp[i] > myabs(a[idx] - a[i])){
            dp[i] = myabs(a[idx] - a[i]);
            myaib.update(i, dp[i]);
        }
    }

    for(int value = max(1, a[idx] - block); value <= min(n, a[idx] + block); value++){
        int i = whereval[value];
        if(i <= idx){ continue; }

        if(dp[i] > myabs(a[idx] - a[i])){
            dp[i] = myabs(a[idx] - a[i]);
            myaib.update(i, dp[i]);
        }

    }

    whereval[a[idx]] = idx;

    return;
}

int main(){

    in.tie(NULL); ios_base::sync_with_stdio(false); out.tie(NULL);

    in>>n>>nrq;
    for(int i = 1; i <= n; i++){
        in>>a[i], dp[i] = maxint;
        whereval[a[i]] = -1;

        myaib.tree[i] = maxint;
    }

    for(int itq = 1; itq <= nrq; itq++){
        in>>lf>>rg;
        queries[lf].push_back(make_pair(rg, itq));
    }

    for(int i = n; i >= 1; i--){
        updateval(i);
        for(auto f : queries[i]){
            answer[f.y] = myaib.query(f.x);
        }
    }

    for(int itq = 1; itq <= nrq; itq++){
        out<<answer[itq]<<"\n";
    }

    return 0;
}
