#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 1000;
int n, a[nmax + 2], sorted[nmax + 2];

map <int, vector <int>> mpwhere;
int nexttperm[nmax + 2];

int visited[nmax + 2];

vector <pii> swaps0;
vector <pii> swaps1;

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i], sorted[i] = a[i];
    }

    sort(sorted + 1, sorted + 1 + n);

    for(int i = 1; i <= n; i++){
        mpwhere[sorted[i]].push_back(i);
    }

    for(int i = 1; i <= n; i++){
        nexttperm[i] = mpwhere[a[i]].back();
        mpwhere[a[i]].pop_back();
    }

    for(int i = 1, where; i <= n; i++){
        if(visited[i]){ continue; }

        vector <int> cycle;

        where = i;
        for(; !visited[where]; ){
            visited[where] = 1;

            cycle.push_back(where);

            where = nexttperm[where];
        }

        if(cycle.size() == 1){ continue; }

        for(int lf = 0, rg = cycle.size() - 1 - (cycle.size() & 1); lf < rg; lf++, rg--)
            swaps0.push_back(make_pair(cycle[lf], cycle[rg]));

        if(cycle.size() & 1) swaps1.push_back(make_pair(cycle[0], cycle.back()));
    }

    out<<(!!(swaps0.size()) + !!(swaps1.size()))<<"\n";
    if(swaps0.size()){ out<<swaps0.size()<<" "; for(auto f : swaps0) out<<f.x<<" "<<f.y<<" "; out<<"\n"; }
    if(swaps1.size()){ out<<swaps1.size()<<" "; for(auto f : swaps1) out<<f.x<<" "<<f.y<<" "; out<<"\n"; }

    return 0;
}
