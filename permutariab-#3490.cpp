#include <fstream>

using namespace std;

ifstream in("permutariab.in");
ofstream out("permutariab.out");

const int nmax = 100000;
int n, a[nmax + 2];
int where[nmax + 2];

int64_t op;

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    int tree[nmax + 2], intotal;

    void add(int pos, int val){
        for(int i = pos; i <= n; i += f(i))
            tree[i] += val;
        intotal += val;
    }

    int sum(int pos){
        int s = 0;
        for(int i = pos; i >= 1; i -= f(i))
            s += tree[i];
        return s;
    }
} aib;

int main(){

    in>>n;
    for(int i = 1; i <= n; i++)
        in>>a[i], where[a[i]] = i;
    for(int i = 1; i <= n; i++)
        in>>a[i], a[i] = where[a[i]];

    for(int i = 1; i <= n; i++){
        op += (aib.intotal - aib.sum(a[i]));
        aib.add(a[i], 1);
    }

    out<<op<<"\n";

    return 0;
}
