#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
const int maxN=2010;
const int Mod=1e9+7;
const int inf=2000000000;

int n,num;
ll Seq[maxN],Num[maxN];
class BIT{
    public:
    int B[maxN];
    void Add(int p,int x){
        while (p<=num){
            B[p]=(B[p]+x)%Mod;p+=(p)&(-p);
        }
        return;
    }
    int Sum(int p){
        int ret=0;
        while (p){
            ret=(ret+B[p])%Mod;p-=(p)&(-p);
        }
        return ret;
    }
};

BIT B[maxN];
int F[maxN][maxN],G[maxN];
int Fc[maxN];

void Plus(int &x,int y);
int main(){
    Fc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%lld",&Seq[i]),Num[i]=Seq[i];Num[n+1]=-inf;
    sort(&Num[1],&Num[n+2]);num=unique(&Num[1],&Num[n+2])-Num-1;
    for (int i=1;i<=n;i++) Seq[i]=Dct(Seq[i]);
    B[0].Add(1,1);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=i;j++) F[i][j]=B[j-1].Sum(Seq[i]);
        for (int j=1;j<=i;j++) B[j].Add(Seq[i],F[i][j]),Plus(G[j],F[i][j]);
    }

    int Ans=0;
    for (int i=1;i<=n;i++){
        Ans=(Ans+1ll*G[i]*Fc[n-i]%Mod)%Mod;
        Ans=(Ans-1ll*G[i+1]*Fc[n-i-1]%Mod*(i+1)%Mod+Mod)%Mod;
    }
    printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}