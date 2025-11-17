#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2e5;
int n, nrq, a[nmax + 2], value, wherey;

struct myaint{
    int tree[4 * nmax + 2];

    void build(int node, int st, int dr){
        if(st == dr){
            tree[node] = a[st];
        }else{
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
            tree[node] = max(tree[(node << 1)], tree[(node << 1) | 1]);
        }
    }

    void update(int node, int st, int dr, int idx){
        if(st == dr){
            tree[node] = a[st];
        }else{
            int mij = (st + dr) >> 1;
            if(idx <= mij) update((node << 1), st, mij, idx);
            if(mij < idx) update((node << 1) | 1, mij + 1, dr, idx);
            tree[node] = max(tree[(node << 1)], tree[(node << 1) | 1]);
        }
    }

    int query(int node, int st, int dr, int value){
        if(st == dr){
            return st;
        }else{
            int mij = (st + dr) >> 1;
            if(tree[(node << 1)] >= value){
                return query((node << 1), st, mij, value);
            }else{ return query((node << 1) | 1, mij + 1, dr, value); }
        }
    }
} myaint;

int main(){

    in>>n>>nrq;
    for(int i = 1; i <= n; i++)
        in>>a[i];

    myaint.build(1, 1, n);

    for(int itq = 1; itq <= nrq; itq++){
        in>>value;

        if(myaint.tree[1] < value){ out<<"0\n"; continue; }

        wherey = myaint.query(1, 1, n, value);
        a[wherey] -= value; myaint.update(1, 1, n, wherey);

        out<<wherey<<" ";
    }; out<<"\n";

    return 0;
}
