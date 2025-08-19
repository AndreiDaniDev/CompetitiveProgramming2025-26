#include <iostream>
#define in cin
#define out cout

#include <utility>
#define x first
#define y second

using namespace std;

typedef pair <int, int> pii;
const int nmax = 2 * 1e5;
int n, a[nmax + 2], freq[nmax + 2];
int64_t pairs;

int prefixprimes;
int prefixpairs;

int maxfactor[nmax + 2];
int primes[nmax + 2];

int divisible[nmax + 2];

int maxvalue;

pii factors[nmax + 2];

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    for(int i = 2; i <= nmax; i++){
        if(maxfactor[i]){ continue; }
        maxfactor[i] = i;

        factors[i] = make_pair(i, 1);
        primes[++primes[0]] = i;

        for(int j = 2 * i; j <= nmax; j += i)
            maxfactor[j] = 1;
    }

    for(int i = 1; i <= primes[0]; i++){
        for(int j = i; j <= primes[0]; j++){
            if(1ll * primes[i] * primes[j] > nmax){ break; }
            factors[primes[i] * primes[j]] = make_pair(primes[i], primes[j]);
            maxfactor[primes[i] * primes[j]] = (1 << 30);
        }
    }


    int tests = 1; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        in>>n;


        prefixprimes = 0; pairs = 0; maxvalue = 0;
        for(int i = 1; i <= n; i++)
            freq[i] = 0, divisible[i] = 0;

        for(int i = 1; i <= n; i++)
            in>>a[i], freq[a[i]] += (maxfactor[a[i]] >= 2);

        for(int i = 2; i <= n; i++){
            for(int j = 2 * i; j <= n; j += i)
                divisible[i] += freq[j];
        }

        for(int val = 2; val <= n; val++){
            if(maxfactor[val] <= 1){ continue; }

            if(maxfactor[val] == val){
                ///val = prime

                pairs += 1ll * prefixprimes * freq[val];
                pairs += 1ll * divisible[val] * freq[val];
                prefixprimes += freq[val];
            }else{
                pairs += (1ll * freq[val] * (freq[val] + 1) / 2);
            }
        }

        out<<pairs<<"\n";
    }


    return 0;
}
