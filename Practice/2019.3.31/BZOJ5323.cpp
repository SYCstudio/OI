#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=10100000;
const int Mod=1e9+7;

int L,R;
bool use[maxN];
int Fc[maxN],Ifc[maxN];

int QPow(int x,int cnt);
int C(int n,int m);
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxN-1]=QPow(Fc[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
    scanf("%d%d",&L,&R);int cnt=0;
    for (int i=L;i<=R;i++)
        if (!use[i]){
            ++cnt;
            for (int j=i+i;j<=R;j+=i) use[j]=1;
        }
    int sum=0;
    for (int i=cnt;i<=R-L+1;i++) sum=(sum+1ll*i*C(i-1,i-cnt)%Mod)%Mod;
    sum=1ll*sum*Fc[cnt]%Mod*Fc[R-L+1-cnt]%Mod;
    printf("%d\n",sum);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        cnt>>=1;x=1ll*x*x%Mod;
    }
    return ret;
}
int C(int n,int m){
    if (n<0||m<0||n<m) return 0;
    return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}