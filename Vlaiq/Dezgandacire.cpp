#include <iostream>
#define in cin
#define out cout
#include <string>
#include <stack>

using namespace std;

const int nmax = 2 * 1e5;
int n; string s, type;
stack <char> sign;

int main(){

    in>>s; n = s.size();
    s = '#' + s + '#';

    for(int i = 1; i <= n; i++){
        if(s[i] == ')'){ out<<")"; sign.pop(); continue; }
        if(s[i] == ','){ out<<sign.top(); continue; }
        if('A' <= s[i] && s[i] <= 'Z'){ out<<s[i]; continue; }

        type = s.substr(i, 3);

        out<<"("; i += 3;

        if(type == "sum"){
            sign.push('+');
        }else if(type == "sub"){
            sign.push('-');
        }else if(type == "mul"){
            sign.push('*');
        }else if(type == "div"){
            sign.push('/');
        }
    }

    out<<"\n";

    return 0;
}
