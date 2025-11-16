#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2e5, maxint = (1 << 30);
int n, a[nmax + 2], nrq, typee, kk, xx;

struct mynode{
    int costtst, costtdr, length;

    mynode() : costtst(maxint), costtdr(maxint), length(0) {};
    mynode(int lff, int rgg, int lengthy) : costtst(lff), costtdr(rgg), length(lengthy) {};

    mynode operator ^ (const mynode &obj) const {
        mynode xornode = mynode();

        xornode.costtst = min((*this).costtst, (*this).length + obj.costtst);
        xornode.costtdr = min((*this).costtdr + obj.length, obj.costtdr);

        xornode.length = (*this).length + obj.length;

        return xornode;
    }
};

struct segmenttree{
    mynode tree[4 * nmax + 2];

    void build(int node, int st, int dr){
        if(st == dr){
            tree[node] = mynode(a[st], a[st], 1);
        }else{
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
            tree[node] = (tree[(node << 1)] ^ tree[(node << 1) | 1]);
        }
    }

    void update(int node, int st, int dr, int idx){
        if(st == dr){
            tree[node] = mynode(a[st], a[st], 1);
        }else{
            int mij = (st + dr) >> 1;
            if(idx <= mij) update((node << 1), st, mij, idx);
            if(mij < idx) update((node << 1) | 1, mij + 1, dr, idx);

            tree[node] = (tree[(node << 1)] ^ tree[(node << 1) | 1]);
        }
    }

    mynode query(int node, int st, int dr, int lf, int rg){
        if(lf <= st && dr <= rg){
            return tree[node];
        }else{
            int mij = (st + dr) >> 1; mynode qry = mynode();

            if(lf <= mij) qry = (qry ^ query((node << 1), st, mij, lf, rg));
            if(mij < rg) qry = (qry ^ query((node << 1) | 1, mij + 1, dr, lf, rg));

            return qry;
        }
    }
} myaint;

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>nrq;
    for(int i = 1; i <= n; i++)
        in>>a[i];

    myaint.build(1, 1, n);
    for(int itq = 1; itq <= nrq; itq++){
        in>>typee>>kk;
        if(typee == 1){
            in>>a[kk];
            myaint.update(1, 1, n, kk);
        }else{
            mynode qrylf = myaint.query(1, 1, n, 1, kk);
            mynode qryrg = myaint.query(1, 1, n, kk, n);
            out<<min(qrylf.costtdr, qryrg.costtst)<<"\n";
        }
    }

    return 0;
}
