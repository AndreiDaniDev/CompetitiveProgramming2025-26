#include <iostream>

#include <cmath>
#include <iomanip>

using namespace std;

const int nmax = 1e5;
long double n, m, expectedvalue;

int main(){

    cin.tie(NULL); ios_base::sync_with_stdio(false); cout.tie(NULL);

    cin>>n>>m;

    expectedvalue = double(n) - double(n * pow(double(n - 1) / double(n), m));

    cout<<fixed<<setprecision(9)<<expectedvalue<<"\n";

    return 0;
}
