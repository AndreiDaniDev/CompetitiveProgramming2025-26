#include <iostream>
#define in cin
#define out cout
#include <vector>

using namespace std;

const int nmax = 5 * 1e5;
int n, a, b, sumheight, sumdepth;
vector <int> muchii[nmax + 2];

int flagg[nmax + 2];
int height[nmax + 2];
int depth[nmax + 2];
int bestt;

int fheight[nmax + 2];
int fdepth[nmax + 2];

void dfs(int node, int hheight){

    flagg[node] = 1; ///mark current node
    height[node] = hheight;
    depth[node] = height[node]; ///leaf only

    for(auto nxt : muchii[node]){
        if(!flagg[nxt]){
            dfs(nxt, hheight + 1);
            depth[node] = max(depth[node], depth[nxt]);
        }
    }
}

void solve(){
    in>>n; bestt = (1 << 30);
    for(int i = 1; i <= n - 1; i++){
        in>>a>>b;
        muchii[a].push_back(b);
        muchii[b].push_back(a);
    }

    dfs(1, 1);

    ///for(int i = 1; i <= n; i++)
    ///    out<<"Node: "<<i<<" -> "<<height[i]<<" "<<depth[i]<<"\n";

    for(int i = 1; i <= n; i++){
        fheight[height[i]]++;
        fdepth[depth[i]]++;
    }

    for(int i = 1; i <= depth[1]; i++){
        ///fheight[i] += fheight[i - 1];
        fdepth[i] += fdepth[i - 1];
    }

    for(int i = depth[1]; i >= 1; i--)
        fheight[i] += fheight[i + 1];

    for(int i = 1; i <= depth[1]; i++){

        ///out<<"Height -: "<<i<<" -> "<<fdepth[i - 1]<<"\n";
        ///out<<"Height +: "<<i<<" -> "<<fheight[i + 1]<<"\n";

        bestt = min(bestt, fheight[i + 1] + fdepth[i - 1]);
    }

    out<<bestt<<"\n";

    for(int i = 1; i <= n; i++){
        height[i] = 0; depth[i] = 0;
        fheight[i] = 0; fdepth[i] = 0;
        muchii[i].clear(); flagg[i] = 0;
    }

    return;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    int tests; in>>tests;
    for(int i = 1; i <= tests; i++)
        solve();

    return 0;
}
