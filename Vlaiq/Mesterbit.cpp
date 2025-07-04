#include <iostream>
#define in cin
#define out cout
#include <bitset>
#include <algorithm>

using namespace std;

const int nmax = 1e6, lgmax = 20;
int n, a[nmax + 2], value, bits[lgmax + 2];

int sor[lgmax + 2];
bitset <(1 << lgmax) + 2> freq;
int nextt[nmax + 2];
int unq;

void add(int value){
    unq += (freq[value] == 0);
    freq[value] = 1; return;
}

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    in>>n;
    for(int i = 1; i <= n; i++)
        in>>a[i], add(a[i]);

    for(int b = 0; b <= lgmax; b++)
        bits[b] = n + 1;

    for(int i = n; i >= 1; i--){
        value = 0; ///mi se pare ciudat cu a[i] = capatul dreapta

        for(int b = 0; b <= lgmax; b++){
            sor[b] |= a[i];
            if(a[i] & (1 << b)){
                bits[b] = i;
                sor[b] = a[i];
            }

            add(sor[b]);
        }
    }

    out<<unq<<"\n";

    return 0;
}
