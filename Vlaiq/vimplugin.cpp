#include <iostream>
#define in cin
#define out cout

#include <string>
#include <stack>

using namespace std;

const int nmax = 1e6;
int n; string a;

struct state{
    int typee; char chr;

    state(int typeee = 0, char chrr = 0) : typee(typeee), chr(chrr) {};
};

struct mycheckstack{
    stack <state> rollstate;
    stack <char> stk;

    void add(int idx){
        if(a[idx] == '(' || a[idx] == '['){
            stk.push(a[idx]);
            rollstate.push(state(1, a[idx])); ///1 = push
        };

        if(a[idx] == ')'){
            if(stk.empty() || stk.top() != '('){
                stk.push(a[idx]);
                rollstate.push(state(1, a[idx]));
            }else{
                stk.pop();
                rollstate.push(state(0, '('));
            }
        }

        if(a[idx] == ']'){
            if(stk.empty() || stk.top() != '['){
                stk.push(a[idx]);
                rollstate.push(state(1, a[idx]));
            }else{
                stk.pop();
                rollstate.push(state(0, '['));
            }
        }
    }

    void rollback(){
        if(!rollstate.empty()){
            state mystate = rollstate.top(); rollstate.pop();

            if(mystate.typee == 1){ ///we pushed -> now we pop
                stk.pop();
            }else if(mystate.typee == 0){
                stk.push(mystate.chr);
            }
        }
        return;
    }

    int getstate(){
        return stk.empty();
    }
} mystk;

int main(){

    in>>n>>a; a = '#' + a + '#';

    for(int i = 1; i <= n; i++){
        if(a[i] == '*'){
            mystk.rollback();
        }else{ mystk.add(i); }

        out<<mystk.getstate();
    }; out<<"\n";

    return 0;
}
