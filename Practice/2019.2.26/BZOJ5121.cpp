#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=50500;
const int maxM=maxN<<1;
const int Block=250;
const int maxB=18;

int n;
ll Val[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Anc[Block][maxN],Fa[maxB][maxN],Dep[maxN],St[maxN];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
int LCA(int u,int v);
namespace DepFirst{
    int Mx[maxN],Dst[maxN],Top[maxN],Hb[maxN];
    vector<int> Up[maxN],Down[maxN];
    int main();
    void dfs1(int u,int fa);
    void dfs2(int u,int top);
    int Query(int u,int K);
}
int main(){
    //freopen("1.in","r",stdin);freopen("out","w",stdout);
    scanf("%d",&n);memset(Head,-1,sizeof(Head));
    for (int i=1;i<=n;i++) scanf("%lld",&Val[i]);
    for (int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);Add_Edge(u,v);Add_Edge(v,u);
    }
    dfs_init(1,0);
    for (int i=1;i<maxB;i++) for (int j=1;j<=n;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
    DepFirst::main();
    int Q;scanf("%d",&Q);
    while (Q--){
        int opt,s,t,k;scanf("%d%d%d%d",&opt,&s,&t,&k);
        //cerr<<opt<<" "<<s<<" "<<t<<" "<<k<<"|"<<Dep[s]<<" "<<Dep[t]<<endl;
        if (s==t){
            if (opt) printf("%lld\n",Val[s]);
            else if (Val[t]>1) Val[s]=floor(sqrt(Val[s]));
            continue;
        }
        int lca=LCA(s,t),d=Dep[s]+Dep[t]-Dep[lca]-Dep[lca];ll sum=0;
        //cout<<"lca:"<<lca<<endl;
        if (d%k){
            if (opt) sum+=Val[t];
            else if (Val[t]>1) Val[t]=floor(sqrt(Val[t]));
            t=DepFirst::Query(t,d%k);
            d-=d%k;
        }
        if (k<Block){
            int lst=0;
            while (Dep[s]>=Dep[lca]){
                int fa=Anc[k][s];
                if (opt){
                    sum+=Val[s];
                    if (Dep[fa]>=Dep[lca]) sum+=(Dep[s]-Dep[fa])/k-1;
                    else if (s!=lca) sum+=(Dep[s]-Dep[lca])/k;
                }
                else if (Val[s]>1) Val[s]=floor(sqrt(Val[s]));
                if (Val[s]==1) if (lst) Anc[k][lst]=fa;else;
                else lst=s;
                s=fa;
            }
            lst=0;
            while (Dep[t]>Dep[lca]){
                int fa=Anc[k][t];
                if (opt){
                    sum+=Val[t];
                    if (Dep[fa]>=Dep[lca]) sum+=(Dep[t]-Dep[fa])/k-1;
                    else sum+=(Dep[t]-Dep[lca]-1)/k;
                }
                else if (Val[t]>1) Val[t]=floor(sqrt(Val[t]));
                if (Val[t]==1) if (lst) Anc[k][lst]=fa;else;
                else lst=t;
                t=fa;
            }
        }
        else{
            while (Dep[s]>=Dep[lca]){
                int fa=DepFirst::Query(s,k);
                if (opt) sum+=Val[s];
                else if (Val[s]>1) Val[s]=floor(sqrt(Val[s]));
                s=fa;
            }
            while (Dep[t]>Dep[lca]){
                int fa=DepFirst::Query(t,k);
                if (opt) sum+=Val[t];
                else if (Val[t]>1) Val[t]=floor(sqrt(Val[t]));
                t=fa;
            }
        }
        if (opt) printf("%lld\n",sum);
    }
    return 0;
}
void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    return;
}
void dfs_init(int u,int fa){
    Fa[0][u]=fa;Dep[u]=Dep[fa]+1;St[Dep[u]]=u;
    for (int i=1;i<Block&&Dep[u]-i>=1;i++) Anc[i][u]=St[Dep[u]-i];
    for (int i=Head[u];i!=-1;i=Next[i]) if (V[i]!=fa) dfs_init(V[i],u);
    return;
}
int LCA(int u,int v){
    if (Dep[u]<Dep[v]) swap(u,v);for (int i=maxB-1;i>=0;i--) if (Fa[i][u]&&Dep[Fa[i][u]]>=Dep[v]) u=Fa[i][u];
    if (u==v) return u;for (int i=maxB-1;i>=0;i--) if (Fa[i][u]&&Fa[i][v]&&Fa[i][u]!=Fa[i][v]) u=Fa[i][u],v=Fa[i][v];
    return Fa[0][u];
}
namespace DepFirst{
    int main(){
        for (int i=2;i<maxN;i++) Hb[i]=Hb[i>>1]+1;
        dfs1(1,0);dfs2(1,1);
        for (int i=1;i<=n;i++)
            if (Top[i]==i){
                int len=0;
                for (int now=i;now;now=Mx[now]) Down[i].push_back(now),++len;
                for (int now=i;now&&len;now=Fa[0][now]) Up[i].push_back(now),--len;
            }
        return 0;
    }
    void dfs1(int u,int fa){
        Dst[u]=1;
        for (int i=Head[u];i!=-1;i=Next[i])
            if (V[i]!=fa){
                dfs1(V[i],u);Dst[u]=max(Dst[u],Dst[V[i]]+1);
                if (Dst[V[i]]+1>Dst[Mx[u]]+1) Mx[u]=V[i];
            }
        return;
    }
    void dfs2(int u,int top){
        Top[u]=top;if (Mx[u]) dfs2(Mx[u],top);
        for (int i=Head[u];i!=-1;i=Next[i]) if (V[i]!=Mx[u]&&V[i]!=Fa[0][u]) dfs2(V[i],V[i]);
        return;
    }
    int Query(int u,int k){
        //cerr<<"Q:"<<u<<" "<<k<<"|"<<Dep[u]<<endl;
        if (Dep[u]<=k) return 0;
        u=Fa[Hb[k]][u];k-=(1<<Hb[k]);
        int t=Top[u];
        if (Dep[u]-Dep[t]>=k) return Down[t][Dep[u]-Dep[t]-k];
        return Up[t][k-(Dep[u]-Dep[t])];
    }
}