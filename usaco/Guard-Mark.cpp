#include <fstream>

using namespace std;

ifstream in("guard.in");
ofstream out("guard.out");

const int nmax = 20, maxint = (1 << 30);
int n, targetheight, bestt;

int height[nmax + 2];
int weight[nmax + 2];
int strength[nmax + 2];

int dp[(1 << nmax) + 2];
///dp[msk] = max safety factor with cows from msk and bottom cow = i

int weightmsk[(1 << nmax) + 2];
int heightmsk[(1 << nmax) + 2];
int msb[(1 << nmax) + 2], idx;

int main(){

    in>>n>>targetheight; bestt = -maxint;
    for(int i = 0; i <= n - 1; i++){
        in>>height[i]>>weight[i]>>strength[i];
    }

    msb[0] = -1; ///log2(0) = -1
    for(int i = 1; i < (1 << n); i++){
        msb[i] = 1 + msb[i >> 1];

        weightmsk[i] = weightmsk[i ^ (1 << msb[i])] + weight[msb[i]];
        heightmsk[i] = heightmsk[i ^ (1 << msb[i])] + height[msb[i]];
    }

    dp[0] = maxint;
    for(int msk = 1; msk < (1 << n); msk++){
        dp[msk] = -maxint;

        for(int bit = 0; (1 << bit) <= msk; bit++){
            if((msk & (1 << bit)) && strength[bit] >= weightmsk[msk ^ (1 << bit)]){ ///we have this bit
                dp[msk] = max(dp[msk], min(dp[msk ^ (1 << bit)], strength[bit] - weightmsk[msk ^ (1 << bit)]));
            }
        }

        if(heightmsk[msk] >= targetheight)
            bestt = max(bestt, dp[msk]);
    }

    ((bestt < 0) ? out<<"Mark is too tall\n" : out<<bestt<<"\n");

    return 0;
}
