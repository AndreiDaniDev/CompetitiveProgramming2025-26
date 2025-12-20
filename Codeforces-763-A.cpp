#include <iostream>
#define in cin
#define out cout

#include <vector>

#include <utility>
#define x first
#define y second

using namespace std;

typedef pair <int, int> pii;
const int nmax = 1e5;
int n, a, b, color[nmax + 2];
vector <int> muchii[nmax + 2];

int xx, yy, unq;
pii edges[nmax + 2];

int dfscolor(int node, int parent, int rootcolor){
    int countt = (color[node] != rootcolor);

    for(auto nxt : muchii[node]){
        if(nxt != parent)
            countt += dfscolor(nxt, node, rootcolor);
    }

    return countt;
}

int check(int root){
    int okayy = 0;
    for(auto nxt : muchii[root]){
        okayy |= dfscolor(nxt, root, color[nxt]);
    }
    return !(okayy);
}

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    in>>n;
    for(int i = 1; i <= n - 1; i++){
        in>>a>>b;
        muchii[a].push_back(b);
        muchii[b].push_back(a);
        edges[i] = make_pair(a, b);
    }

    for(int i = 1; i <= n; i++){
        in>>color[i];

        unq += (color[1] != color[i]);
    }

    if(!unq){ out<<"YES\n1\n"; return 0; }

    for(int i = 1; i <= n - 1; i++){
        if(color[edges[i].x] != color[edges[i].y]){

            if(check(edges[i].x)){ out<<"YES\n"<<edges[i].x<<"\n"; return 0; }
            if(check(edges[i].y)){ out<<"YES\n"<<edges[i].y<<"\n"; return 0; }

            out<<"NO\n"; return 0;
        }
    }

    out<<"NO\n";
    return 0;
}
