#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

#include <algorithm>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 50000, lgmax = 17;
int n, actually[nmax + 2];

struct myvalue{
    int x, y, idx;

    myvalue() : x(0), y(0), idx(0) {};

    bool operator < (const myvalue &obj) const {
        return x < obj.x;
    }
} a[nmax + 2];

int lg2[nmax + 2];
pii rmq[lgmax][nmax + 2];

inline pii query(int st, int dr){
    int e = lg2[dr - st + 1];
    return min(rmq[e][st], rmq[e][dr - (1 << e) + 1]);
}

int father[nmax + 2];
int lfson[nmax + 2];
int rgson[nmax + 2];

int dividebuild(int st, int dr){
    if(!(st <= dr)){ return 0; }

    pii qry = query(st, dr);

    int lf = dividebuild(st, qry.second - 1);
    int rg = dividebuild(qry.second + 1, dr);

    father[lf] = qry.second; ///set father
    father[rg] = qry.second; ///set father

    lfson[qry.second] = lf; ///set child
    rgson[qry.second] = rg; ///set child

    return qry.second;
}

int check(){
    for(int i = 1; i <= n; i++){
        if(lfson[i]) if(!(a[lfson[i]].x <= a[i].x)){ return 0; }
        if(rgson[i]) if(!(a[rgson[i]].x >= a[i].x)){ return 0; }

        if(father[i]) if(!(a[father[i]].y < a[i].y)){ return 0; }
    }
    return 1;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i].x>>a[i].y;
        a[i].idx = i;
    }

    sort(a + 1, a + 1 + n);

    for(int i = 1; i <= n; i++){
        actually[a[i].idx] = i;
    }

    /// ---> Build RMQ for divide build <--- ///

    lg2[0] = -1; ///init log of base 2
    for(int i = 1; i <= n; i++){
        lg2[i] = lg2[i >> 1] + 1;
        rmq[0][i] = make_pair(a[i].y, i);
    }

    for(int p = 1; (1 << p) <= n; p++){
        for(int i = 1; i + (1 << p) - 1 <= n; i++)
            rmq[p][i] = min(rmq[p - 1][i], rmq[p - 1][i + (1 << (p - 1))]);
    }

    dividebuild(1, n);

    out<<"YES\n"; ///we can always build one
    for(int it = 1; it <= n; it++){
        int i = actually[it];

        out<<(father[i] ? a[father[i]].idx : 0)<<" ";
        out<<(lfson[i] ? a[lfson[i]].idx : 0)<<" ";
        out<<(rgson[i] ? a[rgson[i]].idx : 0)<<"\n";
    }

    ///out<<check()<<"\n";

    return 0;
}
