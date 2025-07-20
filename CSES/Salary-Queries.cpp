#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second
#include <algorithm>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 2 * 1e5;
int n, nrq, a[nmax + 2], val, k;
int nvs;

struct query{
    char type; int a, b;
} queries[nmax + 2];

pii norm[2 * nmax + 2]; int countt;
int actually[2 * nmax + 2];

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int tree[2 * nmax + 2];

    void add(int pos, int val){
        for(int i = pos; i <= nvs; i += f(i))
            tree[i] += val;
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
        in>>a[i], norm[++countt] = make_pair(a[i], i);

    for(int i = 1; i <= nrq; i++){
        in>>queries[i].type>>queries[i].a>>queries[i].b;

        if(queries[i].type == '!')
            norm[++countt] = make_pair(queries[i].b, -i);
    }

    sort(norm + 1, norm + 1 + countt);

    for(int i = 1; i <= countt; i++){
        nvs += (norm[i].x != norm[i - 1].x);
        actually[i] = nvs;

        if(norm[i].y > 0){
            a[norm[i].y] = nvs;
        }else{ queries[-norm[i].y].b = nvs; }
    }

    for(int i = 1; i <= n; i++)
        aib.tree[a[i]]++;
    for(int i = 1; i <= nvs; i++){
        ///aib.tree[i] += freq[i];
        if(i + f(i) <= nvs)
            aib.tree[i + f(i)] += aib.tree[i];
    }

    for(int i = 1; i <= nrq; i++){
        if(queries[i].type == '!'){
            aib.add(a[queries[i].a], -1);
            a[queries[i].a] = queries[i].b;
            aib.add(a[queries[i].a], 1);
        }else{
            int st = 1, dr = countt, mij, nrmval = 0;
            for(; st <= dr; ){
                mij = (st + dr) >> 1;

                if(queries[i].a <= norm[mij].x){
                    nrmval = mij, dr = mij - 1;
                }else{ st = mij + 1; }
            }
            queries[i].a = actually[nrmval];

            st = 1, dr = countt, nrmval = 0;
            for(; st <= dr; ){
                mij = (st + dr) >> 1;

                if(norm[mij].x <= queries[i].b){
                    nrmval = mij, st = mij + 1;
                }else{ dr = mij - 1; }
            }
            queries[i].b = actually[nrmval];

            ///out<<queries[i].a<<" "<<queries[i].b<<" | ";
            out<<(aib.sum(queries[i].b) - aib.sum(queries[i].a - 1))<<"\n";
        }
    }

    return 0;
}
