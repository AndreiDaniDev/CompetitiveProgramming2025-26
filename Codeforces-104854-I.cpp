#include <iostream>
#define in cin
#define out cout

#include <string>
#include <vector>

#include <utility>
#define x first
#define y second

#include <set>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 100, valmax = 2 * 1e5;
int n, k, nrq, a[nmax + 2], target[nmax + 2], unqset;

string myname[nmax + 2];
vector <pii> property[nmax + 2];
pii mydata; int path[nmax + 2];

int used[nmax + 2];

/***
3 6
1 2 1
cat 1 1 1
dog 1 1 2
happy 1 2 1
sad 1 2 2
jumpy 2 2 1 3 1
sleeping 1 3 2
***/

int check(vector <pii> &obj){
    for(auto f : obj){
        if(a[f.x] != 0){ continue; }
        if(f.y != target[f.x]){ return 0; }
    }

    for(auto f : obj){
        if(a[f.x] != 0){ continue; }
        a[f.x] = f.y; unqset--;
    }

    return 1;
}

int checkok(){
    for(int i = 1; i <= n; i++){
        if(target[i] != a[i] && target[i] != valmax)
            return 0;
    }
    return 1;
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    in>>n>>k; unqset = n;
    for(int i = 1; i <= n; i++){
        in>>target[i];
        target[i] += valmax;
    }

    for(int i = 1; i <= k; i++){
        in>>myname[i]>>nrq;
        for(int it = 1; it <= nrq; it++){
            in>>mydata.x>>mydata.y;

            mydata.y += valmax;
            property[i].push_back(mydata);
        }
    }

    for(int itq = 1; itq <= k; itq++){

        int flagg = 0;

        ///After max K iterations -> we have no elements
        for(int i = 1; i <= k; i++){
            if(used[i]){ continue; }

            if(check(property[i])){
                used[i] = 1;
                path[++path[0]] = i;
                flagg = 1;
            }
        }

        if(!flagg){ break; }
        if(!unqset){ break; }
    }

    if(!checkok()){
        out<<"IMPOSSIBLE\n";
        return 0;
    }

    for(int it = path[0]; it >= 1; it--){
        out<<myname[path[it]]<<" ";
    }; out<<"\n";

    return 0;
}
