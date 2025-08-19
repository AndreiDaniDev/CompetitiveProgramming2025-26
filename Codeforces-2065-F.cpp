#include <iostream>
#define in cin
#define out cout

#include <vector>
#include <map>

using namespace std;

const int nmax = 5 * 1e5;
int n, a[nmax + 2], x, y;
vector <int> muchii[nmax + 2];
int answer[nmax + 2];

map <int, int> colors;

int dp[nmax + 2], flagg = 0, target;
void dfs(int node, int father, int depth){
    dp[node] = dp[father] + ((a[node] == target) ? 1 : -1);

    if(depth >= 2){ flagg |= (dp[node] >= 1); }
    if(depth >= 3){ return; }

    if(flagg){ return; }

    for(auto nxt : muchii[node]){
        if(nxt != father)
            dfs(nxt, node, depth + 1);
    }
}

int main(){
    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    int tests = 1; in>>tests;
    for(int __t = 1; __t <= tests; __t++){

        in>>n;
        for(int i = 1; i <= n; i++)
            in>>a[i], muchii[i].push_back(i);

        for(int i = 1; i <= n - 1; i++){
            in>>x>>y;
            muchii[x].push_back(y);
            muchii[y].push_back(x);
        }

        for(int node = 1; node <= n; node++){
            colors.clear();
            for(auto nxt : muchii[node])
                colors[a[nxt]]++;

            for(auto nxt : muchii[node])
                answer[a[nxt]] |= (colors[a[nxt]] >= 2);
        }

        for(int i = 1; i <= n; i++)
            out<<answer[i]; out<<"\n";

        for(int i = 1; i <= n; i++)
            muchii[i].clear(), answer[i] = 0;

    }

    return 0;
}
