#include <iostream>

#define in cin
#define out cout

#include <string>

using namespace std;

const int nmax = 50;
int n, m, xx, yy; string qry;

void solveline(int line){
    qry.clear(); qry.push_back('?'); qry.push_back(' ');

    for(int i = 1; i <= line - 1; i++) qry.push_back('v');
    for(int i = 1; i <= m; i++) qry.push_back('>');

    out<<qry<<"\n"; out.flush();

    in>>xx>>yy;

    if(yy != m - 1){ out<<"! "<<xx<<" "<<yy + 1<<"\n"; out.flush(); exit(0); }
    if(xx != line - 1){ out<<"! "<<xx + 1<<" "<<0<<"\n"; out.flush(); exit(0); }

    return;
}

void solvevertical(){
    qry.clear(); qry.push_back('?'); qry.push_back(' ');

    for(int i = 1; i <= n; i++) qry.push_back('v');

    out<<qry<<"\n"; out.flush();

    in>>xx>>yy;

    if(xx != n - 1){ out<<"! "<<xx + 1<<" "<<0<<"\n"; out.flush(); exit(0); }

    return;
}

int main(){

    in>>n>>m;

    solvevertical();
    solveline(1);
    solveline(2);

    qry.clear(); qry.push_back('?'); qry.push_back(' ');

    qry.push_back('v'); qry.push_back('v');

    for(int line = 3; line <= n; line++){
        for(int it = 1; it <= m; it++){
            qry.push_back('^');
            qry.push_back('>');
            qry.push_back('v');
        }

        for(int it = 1; it <= m; it++){
            qry.push_back('<');
        }
        qry.push_back('v');
    }

    for(int it = 1; it <= m; it++){
        qry.push_back('>');
    }

    out<<qry<<"\n"; out.flush();
    in>>xx>>yy;

    out<<"! "<<xx<<" "<<yy + 1<<"\n";

    return 0;
}
