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
int Pw[maxW][maxW],Fac[maxN],Ifc[maxN];
int Dp[3][maxN][maxW],Bp[3][maxW],Q[maxN],Y[maxN];
int Poly[maxN],Ans[maxN],Lyop[maxN];

int QPow(int x,int cnt);

int main(){
    for (int i=1;i<maxW;i++)
        for (int j=Pw[i][0]=1;j<maxW;j++) Pw[i][j]=1ll*Pw[i][j-1]*i%Mod;
    Fac[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
    Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
    int Case;scanf("%d",&Case);
    for (int ci=1;ci<=Case;ci++){
        edgecnt=-1;mem(Head,-1);mem(Dp,0);mem(Dg,0);mem(Poly,0);mem(Ans,0);
        scanf("%d%d%d",&n,&m,&W);
        for (int i=1;i<=n;i++) scanf("%d",&Nw[i]);
        for (int i=1;i<=m;i++){
            int u,v;scanf("%d%d",&u,&v);
            Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;++Dg[v];
        }
        int qL=1,qR=0;
        for (int i=1;i<=n;i++) if (Dg[i]==0) Q[++qR]=i;
        while (qL<=qR) for (int u=Q[qL++],i=Head[u];i!=-1;i=Next[i]) if ((--Dg[V[i]])==0) Q[++qR]=V[i];
        for (int i=n;i>=1;i--){
            int u=Q[i];
            for (int j=1;j<=W*3;j++) Dp[0][u][j]=Pw[j][Nw[u]];
            for (int j=Head[u];j!=-1;j=Next[j]){
                for (int k=1;k<=W*3;k++){
                    Bp[0][k]=(Dp[0][u][k]+Dp[0][V[i]][k])%Mod;
                    Bp[1][k]=((Dp[1][u][k]+Dp[1][V[i]][k])%Mod+1ll*Dp[0][u][k]*Dp[0][V[i]][k]%Mod)%Mod;
                    Bp[2][k]=(((Dp[2][u][k]+Dp[2][V[i]][k])%Mod+1ll*Dp[0][u][k]*Dp[1][V[i]][k]%Mod)%Mod+1ll*Dp[1][u][k]*Dp[0][V[i]][k]%Mod)%Mod;
                }
                for (int k=1;k<=W*3;k++){
                    Dp[0][u][k]=Bp[0][k];Dp[1][u][k]=Bp[1][k];Dp[2][u][k]=Bp[2][k];
                    Bp[0][k]=Bp[1][k]=Bp[2][k]=0;
                }
            }
            for (int j=1;j<=W*3;j++) Y[j]=(Y[j]+Dp[2][u][j])%Mod;
        }
        Poly[0]=1;
        for (int i=0;i<=W*3;i++){
            int k=(Mod-i)%Mod;
            for (int j=W*3;j>=1;j--) Lyop[j]=(Poly[j-1]+1ll*Poly[j]*k%Mod)%Mod;
            Lyop[0]=1ll*Poly[0]*k%Mod;
            for (int j=0;j<=W*3;j++) Poly[i]=Lyop[i];
        }
        for (int i=0;i<=W*3;i++){
            int k=(Mod-i)%Mod;
            for (int j=W*3,lst=0;j>=0;j--){
                lst=(lst+Poly[j])%Mod;Lyop[j]=lst;
                lst=(Mod-1ll*lst*k%Mod)%Mod;
            }
            int div=1;
            if (i!=0) div=1ll*div*Ifc[i]%Mod;
            if (i!=W*3) div=1ll*div*Ifc[W*3-i]%Mod;
            if ((W*3-i)&1) div=Mod-div;
            div=1ll*div*Y[i]%Mod;
            for (int j=0;j<=W*3;j++) Ans[j]=(Ans[j]+1ll*Lyop[j]*div%Mod)%Mod;
        }
        printf("Case #%d: ",ci);
        for (int i=1;i<W*3;i++) printf("%d ",Ans[i]);printf("%d\n",Ans[W*3]);
    }
    return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}