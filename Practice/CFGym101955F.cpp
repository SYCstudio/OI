#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=10100;
const int maxM=30300;
const int maxW=1300;
const int Mod=1e9+7;

int n,m,W;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN],Nw[maxN];
int Pw[maxW][maxW],Dp[maxN][maxW];

int main(){
    for (int i=1;i<maxW;i++)
        for (int j=Pw[i][0]=1;j<maxW;j++) Pw[i][j]=1ll*Pw[i][j-1]*i%Mod;
    int Case;scanf("%d",&Case);
    while (Case--){
        edgecnt=-1;mem(Head,-1);mem(Dp,0);mem(Dg,0);
        scanf("%d%d%d",&n,&m,&W);
        for (int i=1;i<=n;i++) scanf("%d",&Nw[i]);
        for (int i=1;i<=m;i++){
            int u,v;scanf("%d%d",&u,&v);
            Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;++Dg[v];
        }
    }
}