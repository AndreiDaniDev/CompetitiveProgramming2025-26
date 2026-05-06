#include <iostream>
#define in cin
#define out cout

using namespace std;

const int nmax = 1e6, valmax = 1e7, fmax = 8;
int n, a[nmax + 2], maxfactor[valmax + 2], lastt[valmax + 2];

int maxleftt[nmax + 2], maxrightt[nmax + 2];
int factors[fmax + 2], counttf;

int father[nmax + 2];

void getfactors(int xx){
    int lastt = -1; counttf = 0;
    for(; xx > 1; ){
        if(lastt != maxfactor[xx]){
            factors[++counttf] = maxfactor[xx];
            lastt = maxfactor[xx];
        }
        xx /= maxfactor[xx];
    }
    return;
}

void solvedivide(int st, int dr, int parent){
    if(st > dr){ return; }

    int root = -1;

    for(int leftt = st, rightt = dr; leftt <= rightt; leftt++, rightt--){
        if(maxleftt[leftt] <= st && dr <= maxrightt[leftt]){ root = leftt; break; }
        if(maxleftt[rightt] <= st && dr <= maxrightt[rightt]){ root = rightt; break; }
    }

    if(root == -1){ out<<"impossible\n"; exit(0); }

    father[root] = parent;
    solvedivide(st, root - 1, root);
    solvedivide(root + 1, dr, root);

    return;
}

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    for(int i = 2; i <= valmax; i++){
        if(maxfactor[i]){ continue; }
        for(int j = i; j <= valmax; j += i){
            maxfactor[j] = i;
        }
    }

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i];
    }

    /// ---> precompute leftt <--- ///
    for(int vall = 1; vall <= valmax; vall++){
        lastt[vall] = 0;
    }

    for(int i = 1; i <= n; i++){
        getfactors(a[i]);

        for(int j = 1; j <= counttf; j++){
            maxleftt[i] = max(maxleftt[i], lastt[factors[j]] + 1);
            lastt[factors[j]] = i;
        }
    }

    /// ---> precompute rightt <--- ///
    for(int vall = 1; vall <= valmax; vall++){
        lastt[vall] = n + 1;
    }

    for(int i = n; i >= 1; i--){
        getfactors(a[i]); maxrightt[i] = n + 1;

        for(int j = 1; j <= counttf; j++){
            maxrightt[i] = min(maxrightt[i], lastt[factors[j]] - 1);
            lastt[factors[j]] = i;
        }
    }

    solvedivide(1, n, 0);

    for(int i = 1; i <= n; i++){
        out<<father[i]<<" ";
    }; out<<"\n";

    return 0;
}
