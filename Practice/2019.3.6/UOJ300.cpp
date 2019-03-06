#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
const int maxN=252000;
const int maxB=18;
const int Block=5020;
const int Mod=1000000007;

int n,Seq[maxN];
int num,Num[maxN];
int Cnt[(1<<maxB)+10],F[(1<<maxB)+10],Dp[maxN];

int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    int Ans=0;
    for (int l=1,r;l<=n;l=r+1){
        r=min(n,l+Block);memcpy(F,Cnt,sizeof(Cnt));
        for (int i=0;i<maxB;i++) for (int j=0;j<(1<<maxB);j++) if ((j>>i)&1) F[j^(1<<i)]=(F[j^(1<<i)]+F[j])%Mod;
        for (int i=l;i<=r;i++){
            Dp[i]=F[Seq[i]];
            for (int j=l;j<i;j++) if ((Seq[i]|Seq[j])==Seq[j]) Dp[i]=(Dp[i]+Dp[j])%Mod;
            Ans=(Ans+Dp[i])%Mod;Dp[i]=(Dp[i]+1)%Mod;Cnt[Seq[i]]=(Cnt[Seq[i]]+Dp[i])%Mod;
        }
    }
    printf("%d\n",Ans);return 0;
}