#include <iostream>
#define in cin
#define out cout
#include <vector>
#include <set>
#include <utility>
 
using namespace std;
 
const int nmax = 2 * 1e5;
int nrq, n, m, k, freq;
int a[nmax + 2];
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
 
    in>>nrq;
    for(int t = 1; t <= nrq; t++){
        in>>n>>m>>k;
        freq = n * m / k;
 
        for(int value = 0; value < n * m; value++){
            a[value + 1] = value % k + 1;
        }
 
        if(m % k == 0){
            int idx = 0, lineit = 1;
 
            for(int i = 1; i <= n; i++){
                if(i & 1){
                    for(int j = 1; j <= m; j++)
                        out<<a[++idx]<<" ";
                }else{
                    lineit = (++idx);
                    for(int j = 2; j <= m; j++)
                        out<<a[++idx]<<" ";
                    out<<a[lineit]<<" ";
                }
                out<<"\n";
            }
        }else{
            int idx = 0;
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++)
                    out<<a[++idx]<<" ";
                out<<"\n";
            }
        }
    }
 
    return 0;
}
