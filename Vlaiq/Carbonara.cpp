#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 1e5;
int n, a[nmax + 2], nrq, costt;
int type, idx, val;

int64_t solve(int st, int dr){
    int64_t sum = 0, bestt = -(1ll << 60);
    for(int i = st; i <= dr; i++){
        sum += a[i];
        bestt = max(bestt, sum);
        if(sum < 0) sum = 0;
    }
    return bestt;
}

struct segmenttree{
    int64_t treepref[4 * nmax + 2];
    int64_t treesuff[4 * nmax + 2];
    int64_t treesum[4 * nmax + 2];
    int64_t treesmax[4 * nmax + 2];

    int64_t sum, smax;

    void setnode(int node, int val){
        treepref[node] = val;
        treesuff[node] = val;
        treesum[node] = val;
        treesmax[node] = val;
    }

    void updatenode(int node){
        treepref[node] = max(treepref[(node << 1)], treesum[(node << 1)] + treepref[(node << 1) | 1]);
        treesuff[node] = max(treesuff[(node << 1) | 1], treesuff[(node << 1)] + treesum[(node << 1) | 1]);

        treesum[node] = (treesum[(node << 1)] + treesum[(node << 1) | 1]);

        treesmax[node] = max(treesmax[(node << 1)], treesmax[(node << 1) | 1]);
        treesmax[node] = max(treesmax[node], treesuff[(node << 1)] + treepref[(node << 1) | 1]);
    }

    void build(int node, int st, int dr){
        if(st == dr){
            setnode(node, a[st]);
        }else{
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
            updatenode(node);
        }
        ///out<<st<<" "<<dr<<" -> "<<treesmax[node]<<"\n";
    }

    void update(int node, int st, int dr, int idx){
        if(st == dr){
            setnode(node, a[st]);
        }else{
            int mij = (st + dr) >> 1;
            if(idx <= mij) update((node << 1), st, mij, idx);
            if(mij < idx) update((node << 1) | 1, mij + 1, dr, idx);

            updatenode(node);
        }
    }

    void query(int node, int st, int dr, int lf, int rg){
        if(lf <= st && dr <= rg){
            smax = max(smax, treesmax[node]);
            smax = max(smax, sum + treepref[node]);

            sum = max(sum + treesum[node], treesuff[node]);
        }else{
            int mij = (st + dr) >> 1;
            if(lf <= mij) query((node << 1), st, mij, lf, rg);
            if(mij < rg) query((node << 1) | 1, mij + 1, dr, lf, rg);
        }
    }
} aint;

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>nrq>>costt;
    for(int i = 1; i <= n; i++)
        in>>a[i], a[i] -= costt;
    aint.build(1, 1, n);

    for(int it = 1; it <= nrq; it++){
        in>>type>>idx>>val;
        if(type == 1){
            a[idx] = val - costt;
            aint.update(1, 1, n, idx);
        }else{
            aint.sum = 0;
            aint.smax = -(1 << 30);

            aint.query(1, 1, n, idx, val);
            ///out<<solve(idx, val)<<" | ";
            out<<aint.smax<<"\n";
        }
    }

    return 0;
}
