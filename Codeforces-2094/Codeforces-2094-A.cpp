#include <iostream>
#define in cin
#define out cout
#include <string>
 
using namespace std;
 
int nrq; string a, b, c;
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
    in>>nrq;
    for(int t = 1; t <= nrq; t++){
        in>>a>>b>>c;
        out<<a[0]<<b[0]<<c[0]<<"\n";
    }
 
    return 0;
}
