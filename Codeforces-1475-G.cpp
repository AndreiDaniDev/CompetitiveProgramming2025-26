#include <iostream>
#define in cin
#define out cout
 
#include <algorithm>
#include <vector>
 
using namespace std;
 
const int nmax = 2 * 1e5;
int n, a[nmax + 2], dp[nmax + 2];
int lastt[nmax + 2], bestt;
 
vector <int> divizors[nmax + 2];
 
int main(){
 
    in.tie(NULL) -> sync_with_stdio(false);
 
    for(int i = 1; i <= nmax; i++){
        for(int j = i; j <= nmax; j += i)
            divizors[j].push_back(i);
    }
 
    int tests; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        in>>n; bestt = 0;
 
        for(int i = 1; i <= n; i++)
            in>>a[i], dp[i] = 0;
        sort(a + 1, a + 1 + n);
 
        for(int i = 1; i <= n; i++){
            for(auto f : divizors[a[i]])
                dp[i] = max(dp[i], dp[lastt[f]] + 1);
            lastt[a[i]] = i; bestt = max(bestt, dp[i]);
        }
 
        out<<(n - bestt)<<"\n";
 
        for(int i = 1; i <= n; i++)
            lastt[a[i]] = 0;
    }
 
    return 0;
}
