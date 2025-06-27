#include <iostream>
#define in cin
#define out cout
#include <deque>
 
using namespace std;
 
const int nmax = 2 * 1e5;
int64_t nrq, n, type, value, sz, sum;
int64_t score, revscore;
deque <int64_t> dqfront, dqback;
 
int main(){
    in.tie(NULL) -> sync_with_stdio(false);
 
    in>>nrq;
    for(int t = 1; t <= nrq; t++){
        for(; !dqfront.empty(); dqfront.pop_back());
        for(; !dqback.empty(); dqback.pop_back());
 
        in>>n;
 
        score = 0; revscore = 0;
        sz = 0; sum = 0;
 
        for(int i = 1; i <= n; i++){
            in>>type;
            if(type == 3){ ///add a value
                in>>value;
 
                dqfront.push_back(value);
                dqback.push_front(value);
 
                sz++; sum += value;
                score += 1ll * sz * value;
                revscore += sum;
 
            }else if(type == 2){ ///reverse
                swap(dqfront, dqback);
                swap(score, revscore);
            }else if(type == 1){ ///cyclic reverse
                value = dqfront.back();
                dqfront.pop_back();
                dqfront.push_front(value);
 
                score += sum;
                score -= 1ll * sz * value;
 
                value = dqback.front();
                dqback.pop_front();
                dqback.push_back(value);
 
                revscore -= sum;
                revscore += 1ll * sz * value;
            }
 
            out<<score<<"\n";
        }
    }
 
    return 0;
}
