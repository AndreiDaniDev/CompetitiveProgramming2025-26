#include <fstream>
#include <string>
#include <algorithm>

#include <vector>

using namespace std;

ifstream in("expresie7.in");
ofstream out("expresie7.out");

const int nmax = 1e5;
int n; string str;

/**
E = T + T + ... + T
T = sum max
F = median
**/

int solve(int &pos);
int termen(int &pos);
int factor(int &pos);
int getvalue(int &pos);
int stk[nmax + 2];

int solve(int &pos){
    int summ = 0;

    for(; pos <= n; ){
        if(str[pos] == ','){ pos++; continue; }

        if(str[pos] == '('){ pos++; summ += termen(pos); continue; }
        if(str[pos] == '['){ pos++; summ += factor(pos); continue; }

        summ += getvalue(pos);
    }

    return summ;
}

int termen(int &pos){

    vector <int> values(0);
    int basestktop = stk[0];

    for(; pos <= n && str[pos] != ')'; ){
        if(str[pos] == ','){ pos++; continue; }
        if(str[pos] == '('){ pos++; values.push_back(termen(pos)); continue; }
        if(str[pos] == '['){ pos++; values.push_back(factor(pos)); continue; }

        values.push_back(getvalue(pos));
    }
    pos++; ///skip str[pos] == ')'

    int summax = -(1 << 30), summ = 0;
    for(auto val : values){
        summ += val;
        summax = max(summax, summ);
        summ = max(summ, 0);
    }

    return summax;
}

int factor(int &pos){

    vector <int> values(0);
    for(; pos <= n && str[pos] != ']'; ){
        if(str[pos] == ','){ pos++; continue; }
        if(str[pos] == '('){ pos++; values.push_back(termen(pos)); continue; }
        if(str[pos] == '['){ pos++; values.push_back(factor(pos)); continue; }

        values.push_back(getvalue(pos));
    }
    pos++; ///skip str[pos] == ']'

    sort(values.begin(), values.end());
    return values[(values.size() - 1) / 2];
}

int numbers = 0;
int getvalue(int &pos){
    int sgn = ((str[pos] == '-') ? -1 : 1);
    pos += (str[pos] == '-'); numbers++;

    int value = 0;
    for(; pos <= n && '0' <= str[pos] && str[pos] <= '9'; )
        value = 10 * value + str[pos] - '0', pos++;

    return value * sgn;
}

int main(){

    in>>str; n = str.size();
    str = '#' + str + '#';

    int pos = 1;
    int answer = solve(pos);

    out<<numbers<<"\n"<<answer<<"\n";

    return 0;
}
