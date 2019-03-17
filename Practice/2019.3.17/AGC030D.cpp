#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=3010;
const int Mod=1e9+7;
const int inv2=500000004;

int n,Q,Seq[maxN];
int F[maxN][maxN],G[maxN][maxN];

void Plus(int &x,int y);
int main(){
    scanf("%d%d",&n,&Q);
    for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) F[i][j]=Seq[i]<Seq[j];
    for (int qi=1;qi<=Q;qi++){
        int x,y;scanf("%d%d",&x,&y);
        if (x==y) continue;
        for (int i=1;i<=n;i++) if (i!=y&&i!=x){
            Plus(G[i][x],1ll*F[i][x]*inv2%Mod);Plus(G[i][y],1ll*F[i][x]*inv2%Mod);
            Plus(G[x][i],1ll*F[x][i]*inv2%Mod);Plus(G[y][i],1ll*F[x][i]*inv2%Mod);
        }
        for (int i=1;i<=n;i++) if (i!=x&&i!=y){
            Plus(G[i][y],1ll*F[i][y]*inv2%Mod);Plus(G[i][x],1ll*F[i][y]*inv2%Mod);
            Plus(G[y][i],1ll*F[y][i]*inv2%Mod);Plus(G[x][i],1ll*F[y][i]*inv2%Mod);
        }
        G[y][x]=G[x][y]=1ll*(F[x][y]+F[y][x])%Mod*inv2%Mod;
        for (int i=1;i<=n;i++) F[x][i]=G[x][i],F[i][x]=G[i][x],F[y][i]=G[y][i],F[i][y]=G[i][y];
        for (int i=1;i<=n;i++) G[x][i]=G[i][x]=G[y][i]=G[i][y]=0;
    }
    int Ans=0;
    for (int i=1;i<=n;i++) for (int j=1;j<i;j++) Plus(Ans,F[i][j]);
    for (int i=1;i<=Q;i++) Ans=2ll*Ans%Mod;
    printf("%d\n",Ans);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}