#include <iostream>
#define in cin
#define out cout
 
using namespace std;
 
const int nmax = 800;
int nrq, n, a[nmax + 2][nmax + 2];
int perm[2 * nmax + 2];
int64_t missing;
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
 
    in>>nrq;
    for(int t = 1; t <= nrq; t++){
        in>>n; missing = (2 * n) * (2 * n + 1) / 2;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                in>>a[i][j];
        }
 
        for(int i = 1; i <= 2 * n; i++)
            perm[i] = 0;
 
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(a[i][j] != (i + j)){
                    perm[i + j] = a[i][j];
                }else if(!perm[i + j]){
                    perm[i + j] = i + j;
                }
            }
        }
 
        for(int i = 1; i <= 2 * n; i++)
            missing -= perm[i];
 
        perm[1] = missing;
        for(int i = 1; i <= 2 * n; i++)
            out<<perm[i]<<" "; out<<"\n";
    }
 
    return 0;
}
