#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=505000;
const int maxM=maxN<<1;

int n;
ll X[maxN],R[maxN],Stk[maxN];
int edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM],D[maxN];
int top,St[maxN],Mn[maxN],Mx[maxN];
int dfncnt,dfn[maxN],low[maxN],idcnt,Id[maxN],ink[maxN];
vector<int> T[maxN];

void Add_Edge(int u,int v);
void tarjan(int u);
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%lld%lld",&X[i],&R[i]);
    top=0;memset(Hd,-1,sizeof(Hd));
    for (int i=1;i<=n;i++){
        while (top&&Stk[top]<X[i]) --top;
        if (top) Add_Edge(i,St[top]);
        while (top&&Stk[top]<=X[i]+R[i]) --top;
        St[++top]=i;Stk[top]=X[i]+R[i];
    }
    top=0;
    for (int i=n;i>=1;i--){
        while (top&&Stk[top]>X[i]) --top;
        if (top) Add_Edge(i,St[top]);
        while (top&&Stk[top]>=X[i]-R[i]) --top;
        St[++top]=i;Stk[top]=X[i]-R[i];
    }
    top=0;
    for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
    for (int i=1;i<=n;i++) for (int j=Hd[i];j!=-1;j=Nt[j]) if (Id[i]!=Id[V[j]]) T[Id[i]].push_back(Id[V[j]]),++D[Id[V[j]]];
    int ql=1,qr=0;for (int i=1;i<=idcnt;i++) if (!D[i]) St[++qr]=i;
    while (ql<=qr)
        for (int u=St[ql++],i=0,sz=T[u].size();i<sz;i++){
            int v=T[u][i];
            Mn[v]=min(Mn[v],Mn[u]);Mx[v]=max(Mx[v],Mx[u]);--D[v];
            if (!D[v]) St[++qr]=v;
        }
    //for (int i=1;i<=n;i++) cout<<"("<<Mn[Id[i]]<<" "<<Mx[Id[i]]<<")"<<endl;
    int Ans=0;
    for (int i=1;i<=n;i++) Ans=(Ans+1ll*i*(Mx[Id[i]]-Mn[Id[i]]+1)%1000000007)%1000000007;
    printf("%d\n",Ans);return 0;
}
void Add_Edge(int u,int v){
    //cout<<"Add:"<<u<<" "<<v<<endl;
    Nt[++edgecnt]=Hd[u];Hd[u]=edgecnt;V[edgecnt]=v;return;
}
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;St[++top]=u;ink[u]=1;
    for (int i=Hd[u];i!=-1;i=Nt[i]){
        int v=V[i];
        if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if (ink[v]) low[u]=min(low[u],low[v]);
    }
    if (dfn[u]==low[u]){
        int v;++idcnt;Mn[idcnt]=n+1;Mx[idcnt]=0;
        do v=St[top--],Id[v]=idcnt,ink[v]=0,Mn[idcnt]=min(Mn[idcnt],v),Mx[idcnt]=max(Mx[idcnt],v);while (v!=u);
    }
    return;
}