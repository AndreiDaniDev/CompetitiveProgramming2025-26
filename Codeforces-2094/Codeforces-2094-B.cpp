#include <iostream>
#define in cin
#define out cout
 
using namespace std;
 
int nrq, n, m, lf, rg;
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
 
    in>>nrq;
    for(int t = 1; t <= nrq; t++){
        in>>n>>m>>lf>>rg;
        m = n - m;
 
        if(rg > m){
            rg -= m;
            m = 0;
        }else if(m){
            m -= rg;
            rg = 0;
        }
 
        if(m && lf < m){
            lf += m;
            m = 0;
        }else if(m){
            m += lf;
            lf = 0;
        }
 
        out<<lf<<" "<<rg<<"\n";
    }
 
    return 0;
}
