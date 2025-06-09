#include <fstream>
#include <stack>

using namespace std;

ifstream in("nrapp.in");
ofstream out("nrapp.out");

const int nmax = 100000;
int n, a[nmax + 2], nrq, value;
int nxtst[nmax + 2], nxtdr[nmax + 2];
stack <int> st, dr;

char type;

int main(){

    in>>n;

    for(int i = 1; i <= n; i++)
        in>>a[i];

    for(int i = 1; i <= n; i++){
        for(; !st.empty() && a[st.top()] >= a[i]; st.pop());
        nxtst[i] = (st.empty() ? 0 : st.top()); st.push(i);
    }

    for(int i = n; i >= 1; i--){
        for(; !dr.empty() && a[dr.top()] >= a[i]; dr.pop());
        nxtdr[i] = (dr.empty() ? n + 1 : dr.top()); dr.push(i);
    }

    in>>nrq;
    for(int i = 1; i <= nrq; i++){
        in>>type>>value;
        if(type == 'S'){
            out<<nxtst[value]<<"\n";
        }else{ out<<nxtdr[value]<<"\n"; }
    }

    return 0;
}
