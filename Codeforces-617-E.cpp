#include <iostream>
#define in cin
#define out cout
#include <algorithm>

using namespace std;

const int nmax = 1e5, block = 400, valmax = (1 << 20);
int n, nrq, k, a[nmax + 2], lf, rg;
int64_t ways;

struct query{
    int lf, rg, qidx;

    bool operator < (const query &obj) const {
        if(lf / block != obj.lf / block)
            return lf < obj.lf;
        return ((lf / block) & 1) ? (rg < obj.rg) : (rg > obj.rg);
    }
} queries[nmax + 2];
int64_t answer[nmax + 2];

int freqxor[valmax + 2];

void add(int i){
    ways += freqxor[a[i] ^ k];
    freqxor[a[i]]++;
}

void subtract(int i){
    freqxor[a[i]]--;
    ways -= freqxor[a[i] ^ k];
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false);

    in>>n>>nrq>>k;
    for(int i = 1; i <= n; i++)
        in>>a[i], a[i] ^= a[i - 1];

    for(int i = 1; i <= nrq; i++){
        in>>queries[i].lf>>queries[i].rg;

        queries[i].lf--; ///we start from a[lf - 1]
        queries[i].qidx = i;
    }

    sort(queries + 1, queries + 1 + nrq);

    lf = queries[1].lf; rg = queries[1].rg;
    for(int i = lf; i <= rg; i++){ add(i); }
    answer[queries[1].qidx] = ways;

    for(int i = 2; i <= nrq; i++){
        for(; lf > queries[i].lf; add(--lf));
        for(; rg < queries[i].rg; add(++rg));
        for(; lf < queries[i].lf; subtract(lf++));
        for(; rg > queries[i].rg; subtract(rg--));
        answer[queries[i].qidx] = ways;
    }

    for(int i = 1; i <= nrq; i++)
        out<<answer[i]<<"\n";

    return 0;
}
