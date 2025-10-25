#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

#include <vector>
#include <algorithm>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 4 * 1e5;
const int maxint = (1 << 30);

int n, countt, kk, nvs;
pii a[nmax + 2], norm[nmax + 2];
vector <pii> muchii[nmax + 2];

int pairidx[nmax + 2];
int visited[nmax + 2];

int father[nmax + 2];

void normalize(){

    nvs = 0;
    for(int i = 1; i <= n; i++){
        norm[i] = make_pair(a[i].x, i);
    }

    norm[0] = make_pair(-maxint, -maxint);
    sort(norm + 1, norm + 1 + n);

    for(int i = 1; i <= n; i++){
        nvs += (norm[i].x != norm[i - 1].x);
        a[norm[i].y].x = nvs;
    }

    for(int i = 1; i <= n; i++){
        norm[i] = make_pair(a[i].y, i);
    }

    sort(norm + 1, norm + 1 + n);

    for(int i = 1; i <= n; i++){
        nvs += (norm[i].x != norm[i - 1].x);
        a[norm[i].y].y = nvs;
    }

    return;
}

int stk[nmax + 2];
pii pairstk[nmax + 2];

void dfs(int node, int fatheredge){
    visited[node] = 1;

    for(auto nxt : muchii[node]){
        if(!visited[nxt.x])
            dfs(nxt.x, nxt.y);
    }

    stk[0] = 0;
    for(auto nxt : muchii[node]){
        if(pairidx[nxt.y]){ continue; }
        if(nxt.y == fatheredge){ continue; }
        stk[++stk[0]] = nxt.y;
    }

    if(fatheredge && !pairidx[fatheredge]){
        stk[++stk[0]] = fatheredge;
    }

    ///out<<"For: "<<node<<" -> ";
    ///for(int i = 1; i <= stk[0]; i++)
    ///    out<<stk[i]<<" "; out<<"\n";

    for(int i = 1; i + 1 <= stk[0]; i += 2){
        pairidx[stk[i]] = 1;
        pairidx[stk[i + 1]] = 1;

        pairstk[++kk] = make_pair(stk[i], stk[i + 1]);
    }

    return;
}

void solve(){

    in>>n; n *= 2; kk = 0;
    for(int i = 1; i <= n; i++){
        in>>a[i].x>>a[i].y;
    }

    normalize();

    for(int i = 1; i <= n; i++){
        muchii[a[i].x].push_back(make_pair(a[i].y, i));
        muchii[a[i].y].push_back(make_pair(a[i].x, i));
    }

    for(int i = 1; i <= n; i++){
        if(!visited[i]){ dfs(i, 0); }
    }

    out<<kk<<"\n";

    stk[0] = 0;
    for(int i = 1; i <= n; i++){
        if(!pairidx[i]){ stk[++stk[0]] = i; }
    }

    for(int it = 1; it <= kk; it++)
        out<<pairstk[it].x<<" "<<pairstk[it].y<<"\n";

    for(int it = 1; it + 1 <= stk[0]; it += 2)
        out<<stk[it]<<" "<<stk[it + 1]<<"\n";

    for(int i = 0; i <= 2 * n; i++){
        muchii[i].clear();
        visited[i] = 0;
        pairidx[i] = 0;
    }

    return;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    int tests = 1; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        solve();
    }

    return 0;
}
