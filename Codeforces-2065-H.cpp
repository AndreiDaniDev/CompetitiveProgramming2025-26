#include <iostream>
#define in cin
#define out cout

#include <string>

using namespace std;

const int nmax = 2 * 1e5, mod = 998244353;
int n, pow2[nmax + 2], nrq, value;
int a[nmax + 2]; string bitsstr;

int ways = 0;

int add(int x, int y){
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}

struct mydata{
    int lefttbit0, righttbit0;
    int lefttbit1, righttbit1;

    mydata(int a0 = 0, int b0 = 0, int a1 = 0, int b1 = 0){
        lefttbit0 = a0; righttbit0 = b0;
        lefttbit1 = a1; righttbit1 = b1;
    }

    mydata& operator += (const mydata &obj) {
        lefttbit0 = add(add(lefttbit0, obj.lefttbit0), mod);
        lefttbit1 = add(add(lefttbit1, obj.lefttbit1), mod);

        righttbit0 = add(add(righttbit0, obj.righttbit0), mod);
        righttbit1 = add(add(righttbit1, obj.righttbit1), mod);

        return (*this);
    }
};

inline int f(int x){ return (x & (-x)); }
struct fenwicktree{
    mydata tree[nmax + 2], roottree;

    void update(int pos, mydata value){
        for(int i = pos; i <= n; i += f(i))
            tree[i] += value;
        roottree += value;
    }

    mydata query(int pos){
        mydata answer = mydata();
        for(int i = pos; i >= 1; i -= f(i))
            answer += tree[i];
        return answer;
    }
} aib;

int getcontribution(int idx){
    int countt = 0;

    mydata prefix = aib.query(idx);

    if(a[idx] == 0){
        countt = add(countt, 1ll * pow2[n - idx] * prefix.lefttbit1 % mod);
        countt = add(countt, 1ll * pow2[idx - 1] * add(aib.roottree.righttbit1 - prefix.righttbit1, mod) % mod);
    }else if(a[idx] == 1){
        countt = add(countt, 1ll * pow2[n - idx] * prefix.lefttbit0 % mod);
        countt = add(countt, 1ll * pow2[idx - 1] * add(aib.roottree.righttbit0 - prefix.righttbit0, mod) % mod);
    }

    return countt;
}

void solve(){
    n = 0; in>>bitsstr>>nrq;
    for(auto f : bitsstr){
        a[++n] = (f - '0');
    }

    ways = pow2[n] - 1; ///empty subsecv
    for(int i = 1; i <= n; i++){
        if(a[i] == 0){ aib.update(i, mydata(pow2[i - 1], pow2[n - i], 0, 0)); }
        if(a[i] == 1){ aib.update(i, mydata(0, 0, pow2[i - 1], pow2[n - i])); }

        mydata partialpref = aib.query(i - 1);

        if(a[i] == 0){ ways = add(ways, 1ll * pow2[n - i] * partialpref.lefttbit1 % mod); }
        if(a[i] == 1){ ways = add(ways, 1ll * pow2[n - i] * partialpref.lefttbit0 % mod); }
    }

    for(int itq = 1; itq <= nrq; itq++){
        in>>value;

        /// ---> Subtract value contribution <--- ///
        ways = add(add(ways, -getcontribution(value)), mod);

        /// ---> Update value and aib <--- ///
        a[value] ^= 1;

        mydata where = mydata(
            pow2[value - 1] * ((a[value] == 0) ? 1 : -1),
            pow2[n - value] * ((a[value] == 0) ? 1 : -1),
            pow2[value - 1] * ((a[value] == 1) ? 1 : -1),
            pow2[n - value] * ((a[value] == 1) ? 1 : -1)
        );

        aib.update(value, where);

        /// ---> Add value contribution <--- ///
        ways = add(ways, getcontribution(value));

        out<<ways<<" ";

    }; out<<"\n";

    aib.roottree = mydata();
    for(int i = 1; i <= n; i++){
        aib.tree[i] = mydata();
    }
}

int main(){

    in.tie(NULL) -> sync_with_stdio(false); out.tie(NULL);

    pow2[0] = 1;
    for(int i = 1; i <= nmax; i++){
        pow2[i] = 1ll * 2 * pow2[i - 1] % mod;
    }

    int tests = 1; in>>tests;
    for(int __t = 1; __t <= tests; __t++){
        solve();
    }

    return 0;
}
