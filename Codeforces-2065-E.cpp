#include <iostream>
#define in cin
#define out cout

using namespace std;

int nrq, n, k;
int type[2], bit;

int main(){
    in.tie(NULL) -> sync_with_stdio(false);

    in>>nrq;
    for(int __t = 1; __t <= nrq; __t++){
        in>>type[0]>>type[1]>>k;
        n = type[0] + type[1];

        if(k < max(type[0], type[1]) - min(type[0], type[1])){
            out<<"-1\n"; continue;
        }else if(k > max(type[0], type[1])){ out<<"-1\n"; continue; }

        bit = (type[1] > type[0]);
        for(int i = 1; i <= k; i++)
            out<<bit, type[bit]--;

        for(int i = k + 1; i <= n; i++){
            bit ^= 1; ///switch type
            if(!type[bit]) bit ^= 1;
            out<<bit, type[bit]--;
        }
        out<<"\n";
    }

    return 0;
}
