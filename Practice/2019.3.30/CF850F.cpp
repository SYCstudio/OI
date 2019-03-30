#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int Mod=1e9+7;

int n,A[maxN],F[maxN];

int QPow(int x,int cnt);
int main(){
    int s=0,mx=0;
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&A[i]),s=(s+A[i])%Mod,mx=max(mx,A[i]);
    F[1]=1ll*(s-1)*(s-1)%Mod*QPow(s,Mod-2)%Mod;
    for (int i=1;i<mx;i++) F[i+1]=((2ll*F[i]-F[i-1]+Mod)%Mod-1ll*(s-1)*QPow(s-i,Mod-2)%Mod+Mod)%Mod;
    int Ans=0;for (int i=1;i<=n;i++) Ans=(Ans+F[A[i]])%Mod;
    printf("%d\n",Ans);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}