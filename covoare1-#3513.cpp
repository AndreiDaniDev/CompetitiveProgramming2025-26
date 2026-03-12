#include <fstream>

#include <queue>

using namespace std;

ifstream in("covoare1.in");
ofstream out("covoare1.out");

const int nmax = 1e6;
int n, m, kk, xx, yy;

struct intervalstruct{
    int st, dr, height;

    intervalstruct(int lf = 0, int rg = 0, int hh = 0) : st(lf), dr(rg), height(hh) {};

    bool operator < (const intervalstruct &obj) const {
        if(height == obj.height)
            return st > obj.st;
        return height > obj.height;
    }
} myrange;

priority_queue <intervalstruct> pq;

int main(){

    in>>n>>m>>kk; pq.push(intervalstruct(1, m, 1));

    for(int i = 1; i <= kk; i++){
        in>>xx>>yy;

        for(; pq.size() >= 2; ){
            intervalstruct range1 = pq.top(); pq.pop();
            intervalstruct range2 = pq.top(); pq.pop();

            if(range1.height == range2.height && range1.dr + 1 == range2.st){
                pq.push(intervalstruct(range1.st, range2.dr, range1.height));
            }else{ pq.push(range1); pq.push(range2); break; }
        }

        myrange = pq.top(); pq.pop();

        out<<myrange.height<<" "<<myrange.st<<"\n";

        pq.push(intervalstruct(myrange.st, myrange.st + yy - 1, myrange.height + xx));

        myrange.st += yy;
        if(myrange.st <= myrange.dr){
            pq.push(myrange);
            ///out<<"pushedf : "<<myrange.st<<" "<<myrange.dr<<"\n";
        }
    }

    return 0;
}
