#include <fstream>

#include <string>

using namespace std;

ifstream in("bart.in");
ofstream out("bart.out");

const int nmax = 5e5;
int n, zfunction[nmax + 2]; string str;

void computezfunction(){
    zfunction[1] = 0;

    for(int i = 2, st = 1, dr = 1; i <= n; i++){
        zfunction[i] = max(zfunction[i], min(zfunction[i - st + 1], dr - i + 1));
        for(; str[i + zfunction[i]] == str[zfunction[i] + 1]; ){
            zfunction[i]++; st = i; dr = i + zfunction[i] - 1;
        }
    }

    return;
}

int main(){

    in>>str; n = str.size();
    str = '#' + str + '#';

    computezfunction();

    for(int i = 2; i <= n; i++){
        if(zfunction[i] == n - i + 1){
            out<<str.substr(1, i - 1)<<"\n";
            return 0;
        }
    }

    out<<str.substr(1, n)<<"\n";

    return 0;
}
