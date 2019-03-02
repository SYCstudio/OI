#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
const int maxN=250200*4;
const int maxM=maxN*4;

int n,m,Ca[maxN],Cb[maxN];
int num,Num[maxN];
int edgecnt=0,Hd[maxN],Nt[maxM],V[maxM],Dg[maxM];
int vis[maxN],top,St[maxN],sumd;

void Add_Edge(int u,int v);
void dfs(int u);
int main(){
    scanf("%d",&n);memset(Hd,-1,sizeof(Hd));
    for (int i=1;i<=n;i++) scanf("%d%d",&Ca[i],&Cb[i]),Num[++num]=Ca[i],Num[++num]=Cb[i];
    sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
    for (int i=1;i<=n;i++) Ca[i]=Dct(Ca[i]),Cb[i]=Dct(Cb[i]),Add_Edge(Ca[i],Cb[i]);
    long long Ans=0;
    for (int i=1;i<=num;i++)
        if (!vis[i]){
            sumd=top=0;dfs(i);
            if (sumd==top*2) for (int j=1;j<=top;j++) Ans=Ans+1ll*(Dg[St[j]]-1)*Num[St[j]];
            else{
                sort(&St[1],&St[top+1]);
                Ans=Ans+1ll*Dg[St[top]]*Num[St[top]];
                for (int j=1;j<top;j++) Ans=Ans+1ll*(Dg[St[j]]-1)*Num[St[j]];
            }
        }
    printf("%lld\n",Ans);return 0;
}
void Add_Edge(int u,int v){
    ++Dg[u];++Dg[v];
    Nt[++edgecnt]=Hd[u];Hd[u]=edgecnt;V[edgecnt]=v;
    Nt[++edgecnt]=Hd[v];Hd[v]=edgecnt;V[edgecnt]=u;
    return;
}
void dfs(int u){
    St[++top]=u;sumd+=Dg[u];vis[u]=1;
    for (int i=Hd[u];i!=-1;i=Nt[i]) if (!vis[V[i]]) dfs(V[i]);
    return;
}
