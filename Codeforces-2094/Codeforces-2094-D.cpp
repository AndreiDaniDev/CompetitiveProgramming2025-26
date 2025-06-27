#include <iostream>
#define in cin
#define out cout
#include <string>
 
using namespace std;
 
const int nmax = 2 * 1e5;
int nrq, n, m; string a, b;
 
int typea[nmax + 2];
int typeb[nmax + 2];
 
int solve(){
    ///b = from a
    int countta = 0;
    int counttb = 0;
 
    a = '#' + a + '#';
    b = '#' + b + '#';
 
    if(a[1] != b[1]){ return 0; }
 
    /// ---> For a <--- ///
    for(int i = 1; i <= n; i++){
        if(a[i] != a[i - 1]){
            typea[++countta] = 1;
        }else{ typea[countta]++; }
    }
 
    /// ---> For b <--- ///
    for(int i = 1; i <= m; i++){
        if(b[i] != b[i - 1]){
            typeb[++counttb] = 1;
        }else{ typeb[counttb]++; }
    }
 
    if(countta != counttb){ return 0; }
 
    for(int i = 1; i <= countta; i++){
        if(!(typea[i] <= typeb[i] && typeb[i] <= 2 * typea[i]))
            return 0;
    }
 
    return 1;
}
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
 
    in>>nrq;
    for(int t = 1; t <= nrq; t++){
        in>>a>>b; n = a.size(); m = b.size();
        out<<(solve() ? "YES\n" : "NO\n");
    }
 
    return 0;
}
