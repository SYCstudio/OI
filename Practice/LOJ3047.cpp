#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxN=101000;
const int maxM=25;

class Num{
public:
    ll a,b,c;
    Num(){
	a=b=0;c=1;return;
    }
    Num(ll x,ll y){
	if (x<0) x=-x,y=-y;
	a=x/y;
    }
};

int n;

int main(){
}
