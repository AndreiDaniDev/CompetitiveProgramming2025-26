#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 2e5, maxint = (1 << 30);
int n, a[nmax + 2], nrq, lff, rgg;

struct mynode{
    int64_t subsecvmaxx;
    int64_t prefsum;
    int64_t suffsum;
    int64_t summ;

    mynode() : prefsum(0), suffsum(0), summ(0), subsecvmaxx(0) {};

    mynode(int value){
        subsecvmaxx = max(0, value);
        prefsum = value;
        suffsum = value;
        summ = value;
    }

    mynode operator ^ (const mynode &obj) const {
        mynode xornode = mynode();

        xornode.summ = (*this).summ + obj.summ;
        xornode.prefsum = max((*this).prefsum, (*this).summ + obj.prefsum);
        xornode.suffsum = max((*this).suffsum + obj.summ, obj.suffsum);

        xornode.subsecvmaxx = max(xornode.subsecvmaxx, (*this).subsecvmaxx);
        xornode.subsecvmaxx = max(xornode.subsecvmaxx, obj.subsecvmaxx);

        xornode.subsecvmaxx = max(xornode.subsecvmaxx, (*this).suffsum + obj.prefsum);

        return xornode;
    }
};

struct segmenttree{
    mynode tree[4 * nmax + 2];

    void build(int node, int st, int dr){
        if(st == dr){
            tree[node] = mynode(a[st]);
        }else{
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
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
        in>>lff>>rgg;
        mynode qry = myaint.query(1, 1, n, lff, rgg);
        out<<qry.subsecvmaxx<<"\n";
    }

    return 0;
}
