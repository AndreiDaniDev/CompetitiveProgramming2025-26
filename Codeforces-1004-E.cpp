#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

#include <queue>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 1e5;
int n, kk, a, b, costt, summycostt;

vector <pii> muchii[nmax + 2];

int flagg[nmax + 2];
int degree[nmax + 2];
int paths, nodes;

int dist[nmax + 2];

int check(int maxweight){

    nodes = n; paths = 0;

    queue <int> dq;
    for(int i = 1; i <= n; i++){
        if(muchii[i].size() == 1)
            dq.push(i);

        flagg[i] = 0;
        dist[i] = 0;

        degree[i] = muchii[i].size();
        paths += (degree[i] >= 3);
    }

    for(; !dq.empty(); ){
        int node = dq.front(), flaggadd = 0; dq.pop();
        pii myedge = make_pair(0, 0);

        for(auto nxt : muchii[node]){
            if(!flagg[nxt.x])
                myedge = nxt;
        }

        if(dist[node] + myedge.y <= maxweight){
            /// ---> update max dist <--- ///
            dist[myedge.x] = max(dist[myedge.x], dist[node] + myedge.y);
            flagg[node] = 1;

            paths -= (degree[myedge.x] == 3);
            degree[myedge.x]--; ///tree pruning

            nodes--; ///we kill this node ;)

            if(degree[myedge.x] == 1)
                dq.push(myedge.x);
        }

    }

    return (paths == 0 && nodes <= kk);
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>kk;
    for(int i = 1; i <= n - 1; i++){
        in>>a>>b>>costt; summycostt += costt;
        muchii[a].push_back(make_pair(b, costt));
        muchii[b].push_back(make_pair(a, costt));
    }

    int st = 0, dr = summycostt, mij, bestt = summycostt;

    for(; st <= dr; ){
        mij = (st + dr) >> 1;

        if(check(mij)){
            bestt = mij; dr = mij - 1;
        }else{ st = mij + 1; }
    }

    out<<bestt<<"\n";

    return 0;
}
