#include <iostream>
#define in cin
#define out cout

#include <vector>

using namespace std;

const int nmax = 3 * 1e5;
int n, a, b, maxi;
int diameter, wheremx;
vector <int> muchii[nmax + 2];

int dpdown[nmax + 2];
int dpup[nmax + 2];

int dfsdpdown(int node, int parent){
    dpdown[node] = -1;

    for(auto nxt : muchii[node]){
        if(nxt != parent){
            dfsdpdown(nxt, node);
            dpdown[node] = max(dpdown[node], dpdown[nxt]);
        }
    }

    dpdown[node] += 1; ///we add one edge
}

int dfsdpup(int node, int parent){
    int mx1 = -(1 << 30), mx2 = -(1 << 30);

    for(auto nxt : muchii[node]){
        if(nxt == parent){ continue; }

        if(mx1 < dpdown[nxt]){
            mx2 = mx1, mx1 = dpdown[nxt];
        }else{ mx2 = max(mx2, dpdown[nxt]); }
    }

    for(auto nxt : muchii[node]){
        if(nxt != parent){
            int depth = ((mx1 == dpdown[nxt]) ? mx2 : mx1);

            dpup[nxt] = max(dpup[nxt], dpup[node] + 1);
            dpup[nxt] = max(dpup[nxt], depth + 2);

            dfsdpup(nxt, node);
        }
    }
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n;
    for(int i = 1; i <= n - 1; i++){
        in>>a>>b;
        muchii[a].push_back(b);
        muchii[b].push_back(a);
    }

    dfsdpdown(1, 0);
    dfsdpup(1, 0);

    for(int i = 1; i <= n; i++){
        diameter = max(diameter, dpdown[i]);
        diameter = max(diameter, dpup[i]);
    }

    for(int i = 1; i <= n; i++){
        maxi = diameter;

        maxi = max(maxi, 1 + dpdown[i]);
        maxi = max(maxi, 1 + dpup[i]);

        out<<maxi<<"\n";
    }

    return 0;
}
