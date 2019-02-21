#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define RG register
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=110;
const int maxM=10100;

int n,m,K,Mod,G;
int Mat[maxN][maxN];
int Eu[maxM],Ev[maxM],Ec[maxM];

int GetG(int M);
int QPow(int x,int cnt);
void Plus(int &x,int y);
int Gauss();

int main(){
    //freopen("in","r",stdin);
    int sum=0,i,j,w;
    scanf("%d%d%d%d",&n,&m,&K,&Mod);G=GetG(Mod);
    //cout<<"G:"<<G<<endl;
    for (i=1;i<=m;++i) scanf("%d%d%d",&Eu[i],&Ev[i],&Ec[i]);
    for (i=0;i<=K-1;++i){
        w=QPow(G,(Mod-1)/K*i);mem(Mat,0);
        for (j=1;j<=m;++j){
            int wc=QPow(w,Ec[j]);
            Plus(Mat[Eu[j]][Eu[j]],wc);Plus(Mat[Ev[j]][Ev[j]],wc);
            Plus(Mat[Eu[j]][Ev[j]],Mod-wc);Plus(Mat[Ev[j]][Eu[j]],Mod-wc);
        }
        Plus(sum,Gauss());
    }
    sum=1ll*sum*QPow(K,Mod-2)%Mod;
    printf("%d\n",sum);return 0;
}
int GetG(int M){
    static int pcnt,P[200];
    int phi=M-1;
    for (int i=2;1ll*i*i<=phi;i++)
        if (phi%i==0){
            P[++pcnt]=i;while (phi%i==0) phi/=i;
        }
    if (phi!=1) P[++pcnt]=phi;
    for (int g=1;;g++){
        bool flag=1;
        for (int i=1;i<=pcnt&&flag;i++) if (QPow(g,(Mod-1)/P[i])==1) flag=0;
        if (flag) return g;
    }
}
int QPow(RG int x,RG int cnt){
    RG int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void Plus(int &x,int y){
    if (y>=Mod) y-=Mod;
    x+=y;if (x>=Mod) x-=Mod;
}
int Gauss(){
    RG int ret=1,i,j,k,now,inv,mul;
    for (i=1;i<n;++i){
        now=i;while (!Mat[now][i]) ++now;
        if (now!=i){
            ret=Mod-ret;
            for (j=i;j<n;++j) swap(Mat[i][j],Mat[now][j]);
        }
        ret=1ll*ret*Mat[i][i]%Mod;
        inv=QPow(Mat[i][i],Mod-2);
        for (j=i+1;j<n;++j)
            if (i!=j&&Mat[j][i]){
                mul=1ll*inv*Mat[j][i]%Mod;
                for (k=i;k<n;++k) Plus(Mat[j][k],Mod-1ll*Mat[i][k]*mul%Mod);
            }
    }
    return ret;
}