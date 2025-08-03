#include <iostream>
#define in cin
#define out cout

#include <vector>

#include <utility>
#define x first
#define y second
#include <algorithm>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 2 * 1e5;
int n, m, costt[nmax + 2], a, b;

vector <int> muchii[nmax + 2];
vector <int> revmuchii[nmax + 2];

pii norm[nmax + 2]; int notsure;

int flagg, visited[nmax + 2];
int bestt, answer[nmax + 2], maxi;

void dfsfather(int node, int value){
    visited[node] = flagg;

    notsure -= (answer[node] == -1);
    answer[node] = max(answer[node], value);

    for(auto nxt : revmuchii[node]){
        if(visited[nxt] != flagg && answer[nxt] == -1)
            dfsfather(nxt, value);
    }
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>m; notsure = n; ///we dont know the answer for N values
    for(int i = 1; i <= n; i++){
        in>>costt[i]; answer[i] = -1;
        norm[i] = make_pair(costt[i], i);
    }

    for(int i = 1; i <= m; i++){
        in>>a>>b;
        muchii[a].push_back(b);
        revmuchii[b].push_back(a);
    }

    sort(norm + 1, norm + 1 + n);
    for(int i = n; i >= 1; i--){
        flagg += (norm[i].x != norm[i - 1].x);
        dfsfather(norm[i].y, norm[i].x);

        if(notsure == 0){ break; }
    }

    for(int i = 1; i <= n; i++)
        out<<answer[i]<<" "; out<<"\n";

    return 0;
}
