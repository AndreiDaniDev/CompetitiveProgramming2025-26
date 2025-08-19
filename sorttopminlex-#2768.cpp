#include <iostream>
#define in cin
#define out cout

#include <queue>

using namespace std;

const int nmax = 100000;
int n, k, a, b, toposort[nmax + 2];
vector <int> muchii[nmax + 2];

int indegree[nmax + 2];

priority_queue <int> pq;

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>k;
    for(int i = 1; i <= k; i++){
        in>>a>>b;
        muchii[a].push_back(b);

        indegree[b]++; ///Edge a -> b
    }

    toposort[0] = 0;
    for(int i = 1; i <= n; i++)
        if(!indegree[i]) pq.push(-i);

    for(; !pq.empty(); ){
        int node = -pq.top(); pq.pop();
        toposort[++toposort[0]] = node;

        for(auto nxt : muchii[node]){
            indegree[nxt]--;
            if(!indegree[nxt])
                pq.push(-nxt);
        }
    }

    for(int i = 1; i <= n; i++)
        out<<toposort[i]<<" "; out<<"\n";

    return 0;
}
