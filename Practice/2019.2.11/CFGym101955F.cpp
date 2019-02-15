#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define RG register
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=10100;
const int maxM=30300;
const int maxW=1205;
const int Mod=1e9+7;

class PolyC{
    public:
    int S[maxW];
    void Init(){
        mem(S,0);return;
    }
};

int n,m,W,WW;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN],Nw[maxN];
int Pw[maxW][maxW],Fac[maxN],Ifc[maxN];
int Q[maxN];
int Poly[maxW],Ans[maxW],Lyop[maxW];
PolyC Dp[maxN][3],Y;

int QPow(int x,int cnt);
PolyC operator + (PolyC A,PolyC B);
PolyC operator * (PolyC A,PolyC B);

int main(){
    RG int i,j,k,lst;
    for (i=1;i<maxW;++i) for (j=Pw[i][0]=1;j<maxW;++j) Pw[i][j]=1ll*Pw[i][j-1]*i%Mod;
    Fac[0]=Ifc[0]=1;for (i=1;i<maxN;++i) Fac[i]=1ll*Fac[i-1]*i%Mod;
    Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
    int Case;scanf("%d",&Case);
    for (int ci=1;ci<=Case;++ci){
        edgecnt=-1;mem(Head,-1);mem(Dg,0);mem(Poly,0);mem(Ans,0);mem(Lyop,0);Y.Init();
        scanf("%d%d%d",&n,&m,&W);WW=W*3;
        for (i=1;i<=n;++i) Dp[i][1].Init(),Dp[i][2].Init();
        for (i=1;i<=n;++i) scanf("%d",&Nw[i]);
        for (i=1;i<=m;++i){
            int u,v;scanf("%d%d",&u,&v);
            Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;++Dg[v];
        }
        int qL=1,qR=0;
        for (i=1;i<=n;++i) if (Dg[i]==0) Q[++qR]=i;
        while (qL<=qR) for (int u=Q[qL++],i=Head[u];i!=-1;i=Next[i]) if ((--Dg[V[i]])==0) Q[++qR]=V[i];
        for (i=n;i>=1;i--){
            int u=Q[i];
            for (j=1;j<=WW;++j) Dp[u][0].S[j]=Pw[j][Nw[u]];
            for (j=Head[u];j!=-1;j=Next[j]){
                int v=V[j];
                Dp[u][2]=Dp[u][2]+Dp[v][2]+Dp[u][0]*Dp[v][1]+Dp[u][1]*Dp[v][0];
                Dp[u][1]=Dp[u][1]+Dp[v][1]+Dp[u][0]*Dp[v][0];
                Dp[u][0]=Dp[u][0]+Dp[v][0];
            }
            Y=Y+Dp[u][2];
        }
        /*
        for (i=1;i<=n;++i){
            for (int b=0;b<=2;b++){
                for (j=1;j<=W*3;++j) cout<<Dp[b][i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
        //*/
        //for (i=1;i<=WW;++i) cout<<Y.S[i]<<" ";cout<<endl;
        Poly[0]=1;
        for (i=0;i<=WW;++i){
            k=(Mod-i)%Mod;
            for (j=WW+1;j>=1;j--) Lyop[j]=(Poly[j-1]+1ll*Poly[j]*k%Mod)%Mod;
            Lyop[0]=1ll*Poly[0]*k%Mod;
            for (j=0;j<=WW+1;++j) Poly[j]=Lyop[j];
            //cout<<"After:(x-"<<i<<")"<<endl;
            //for (j=0;j<=WW+1;++j) cout<<Poly[j]<<" ";cout<<endl;
        }
        //cout<<"Poly:";for (i=0;i<=WW+1;++i) cout<<Poly[i]<<" ";cout<<endl;
        for (i=0;i<=WW;++i){
            k=(Mod-i)%Mod;
            Lyop[WW+1]=0;
            for (j=WW+1,lst=0;j>=1;j--){
                lst=(lst+Poly[j])%Mod;Lyop[j-1]=lst;
                lst=(Mod-1ll*lst*k%Mod)%Mod;
            }
            //cout<<"Div:(x-"<<i<<")"<<endl;
            //for (j=0;j<=WW+1;++j) cout<<Lyop[j]<<" ";cout<<endl;
            int div=1;
            //for (j=0;j<=WW;++j) if (j!=i) div=1ll*div*QPow(j-i,Mod-2)%Mod;
            
            if (i!=0) div=1ll*div*Ifc[i]%Mod;
            if (i!=W*3) div=1ll*div*Ifc[W*3-i]%Mod;
            if ((W*3-i)&1) div=Mod-div;
            //*/
            div=1ll*div*Y.S[i]%Mod;
            for (j=0;j<=WW;++j) Ans[j]=(Ans[j]+1ll*Lyop[j]*div%Mod)%Mod;
        }
        printf("Case #%d: ",ci);
        for (i=1;i<W*3;++i) printf("%d ",Ans[i]);printf("%d\n",Ans[W*3]);
    }
    return 0;
}
int QPow(int x,int cnt){
    x=(x+Mod)%Mod;
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
PolyC operator + (PolyC A,PolyC B){
    PolyC R;
    for (int i=0;i<=WW;i++) R.S[i]=(A.S[i]+B.S[i])%Mod;
    return R;
}
PolyC operator * (PolyC A,PolyC B){
    PolyC R;
    for (int i=0;i<=WW;i++) R.S[i]=1ll*A.S[i]*B.S[i]%Mod;
    return R;
}