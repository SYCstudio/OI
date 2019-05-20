#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=20200;
const int Mod=998244353;

int n,m,X;
int B[maxN];

int QPow(int x,int cnt);
int main(){
    scanf("%d%d%d",&n,&m,&X);for (int i=0;i<=m;i++) scanf("%d",&B[i]);
    for (int i=1;i<=m;i++) for (int j=m;j>=i;j--) B[j]=(B[j]-B[j-1]+Mod)%Mod;
    int Ans=0,mul=1;
    for (int i=0;i<=m;i++){
	Ans=(Ans+1ll*mul*B[i]%Mod)%Mod;
	mul=1ll*mul*(n-i)%Mod*X%Mod*QPow(i+1,Mod-2)%Mod;
    }
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
