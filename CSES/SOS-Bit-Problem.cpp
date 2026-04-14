#include <iostream>
#define in cin
#define out cout

using namespace std;

/**
5
3 7 2 9 2

3 2 5
4 1 5
2 4 4
1 1 3
2 4 4
**/

const int nmax = 2e5, valmax = 1048575, lgmax = 20;
int n, a[nmax + 2], freq[valmax + 2], dp[valmax + 2];

int answer[3][nmax + 2];

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    in>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i], freq[a[i]]++;
    }

    /// ---> solve task 1 <--- ///
    for(int val = 0; val <= valmax; val++){
        dp[val] = freq[val];
    }

    for(int bit = 0; bit <= lgmax - 1; bit++){
        for(int msk = 0; msk <= valmax; msk++){
            if(msk & (1 << bit)){ continue; }
            dp[msk | (1 << bit)] += dp[msk];
        }
    }

    for(int i = 1; i <= n; i++){
        answer[0][i] = dp[a[i]];
        answer[2][i] = n - dp[valmax ^ a[i]];
    }

    /// ---> solve task 2 <--- ///
    for(int val = 0; val <= valmax; val++){
        dp[val] = freq[val];
    }

    for(int bit = 0; bit <= lgmax - 1; bit++){
        for(int msk = valmax; msk >= 0; msk--){
            if(msk & (1 << bit)){ continue; }
            dp[msk] += dp[msk | (1 << bit)];
        }
    }

    for(int i = 1; i <= n; i++){
        answer[1][i] = dp[a[i]];
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= 2; j++)
            out<<answer[j][i]<<" ";
        out<<"\n";
    }

    return 0;
}
