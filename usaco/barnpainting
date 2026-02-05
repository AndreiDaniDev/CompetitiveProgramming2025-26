#include <fstream>
#include <vector>

using namespace std;

ifstream in("barnpainting.in");
ofstream out("barnpainting.out");

const int nmax = 1e5, mod = 1e9 + 7;
int n, kk, xx, yy, color[nmax + 2], dp[nmax + 2][3];
vector <int> edges[nmax + 2];

int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

void dfscompute(int node, int parent){

    /// ---> init dp for node <--- ///
    dp[node][0] = ((color[node] == 0) || (color[node] == 1));
    dp[node][1] = ((color[node] == 0) || (color[node] == 2));
    dp[node][2] = ((color[node] == 0) || (color[node] == 3));

    for(auto nxt : edges[node]){
        if(nxt != parent){
            dfscompute(nxt, node);

            dp[node][0] = 1ll * dp[node][0] * add(dp[nxt][1], dp[nxt][2]) % mod;
            dp[node][1] = 1ll * dp[node][1] * add(dp[nxt][0], dp[nxt][2]) % mod;
            dp[node][2] = 1ll * dp[node][2] * add(dp[nxt][0], dp[nxt][1]) % mod;
        }
    }

    return;
}

int main(){

    in>>n>>kk;
    for(int i = 1; i <= n - 1; i++){
        in>>xx>>yy;
        edges[xx].push_back(yy);
        edges[yy].push_back(xx);
    }

    for(int i = 1; i <= kk; i++){
        in>>xx>>yy;
        color[xx] = yy;
    }

    dfscompute(1, 0);

    out<<add(dp[1][0], add(dp[1][1], dp[1][2]))<<"\n";

    return 0;
}
