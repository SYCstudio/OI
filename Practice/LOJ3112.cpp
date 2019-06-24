#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=110;
const int maxM=10100;

int n,m;
int D1[maxN][maxM],D2[maxN][maxM];
ll Sml[maxN],Smr[maxN];


namespace GEN{
    unsigned SA,SB,SC,lim;
    int getweight();
}
using GEN::getweitgh;

int main(){
    scanf("%d%d",&n,&m);
    scanf("%llu%llu%llu%d",&GEN::SA,&GEN::SB,&GEN::SC,&GEN::lim);

    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) D1[i][j]=getweight();
    for (int i=1;i<n;i++) for (int j=1;j<=m;j++) D2[i][j]=getweight();

    for (int i=1;i<=m;i++){
    }
}
namespace GEN{
    int getweight() {
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB;
	SB = SC;
	SC^ = t ^ SA;
	return SC % lim + 1;
    }
}
