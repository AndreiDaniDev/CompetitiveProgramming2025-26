#include <fstream>

#include <vector>

using namespace std;

ifstream in("bipartit1.in");
ofstream out("bipartit1.out");

const int nmax = 15;
int n, m, xx, yy; vector <int> edges[nmax + 2];

int color[nmax + 2];

void dfscolor(int node, int nodecolor){
    color[node] = nodecolor;

    for(auto nxt : edges[node]){
        if(color[nxt] == nodecolor){
            out<<"NU\n"; exit(0);
        }

        if(!color[nxt]) dfscolor(nxt, 3 - nodecolor);
    }
    return;
}

int main(){

    in>>n>>m;
    for(int i = 1; i <= m; i++){
        in>>xx>>yy;
        edges[xx].push_back(yy);
        edges[yy].push_back(xx);
    }

    for(int node = 1; node <= n; node++){
        if(!color[node]){
            dfscolor(node, 1);
        }
    }

    out<<"DA\n";
    for(int i = 1; i <= n; i++){ if(color[i] == color[1]) out<<i<<" "; }; out<<"\n";
    for(int i = 1; i <= n; i++){ if(color[i] != color[1]) out<<i<<" "; }; out<<"\n";

    return 0;
}
