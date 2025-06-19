#include <iostream>
#define in cin
#define out cout
#include <algorithm>

using namespace std;

const int nmax = 2 * 1e5;
int nrq, n, m, a[nmax + 2], sum[nmax + 2];
int idx, perm[nmax + 2];
int64_t score;

int main(){

    in.tie(NULL) -> sync_with_stdio(false);
    in>>nrq;

    for(int __t = 1; __t <= nrq; __t++){
        in>>n>>m; score = 0;
        for(int i = 1; i <= n; i++){
            sum[i] = 0; perm[i] = i;
            for(int j = 1; j <= m; j++){
                in>>a[++idx];
                sum[i] += a[idx];
            }
        }

        sort(perm + 1, perm + 1 + n, [](int x, int y){
            return sum[x] > sum[y];
        });

        idx = n * m;
        for(int i = 1; i <= n; i++){
            int it = m * (perm[i] - 1);
            for(int j = 1; j <= m; j++){
                score += 1ll * a[it + j] * idx;
                idx--;
            }
        }

        out<<score<<"\n";
    }

    return 0;
}
