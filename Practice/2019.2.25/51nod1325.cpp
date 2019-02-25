#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=60;
const int maxM=1001000;
const int inf=1000000000;

class Edge{
    public:
    int v,flow;
};

int n,Val[maxN],S,T;
vector<int> T1[maxN],T2[maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int cur[maxN],Dep[maxN],Qu[maxN];

int Calc(int root);
void Add_Edge(int u,int v,int flow);
void dfs1(int u,int fa);
void dfs2(int u,int fa);
bool Bfs();
int dfs(int u,int fa);
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Val[i]);S=n+1;T=S+1;
    for (int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);++u;++v;T1[u].push_back(v);T1[v].push_back(u);
    }
    for (int i=1;i<n;i++){
        int u,v;scanf("%d%d",&u,&v);++u;++v;T2[u].push_back(v);T2[v].push_back(u);
    }
    int Ans=-inf;
    for (int i=1;i<=n;i++) Ans=max(Ans,Calc(i));
    printf("%d\n",Ans);return 0;
}
int Calc(int root){
    edgecnt=-1;memset(Head,-1,sizeof(Head));
    dfs1(root,0);dfs2(root,0);
    int sum=0;for (int i=1;i<=n;i++) Val[i]>0?(sum+=Val[i],Add_Edge(S,i,Val[i])):Add_Edge(i,T,-Val[i]);
    while (Bfs()){
        memcpy(cur,Head,sizeof(Head));
        while (int di=dfs(S,inf)) sum-=di;
    }
    return sum;
}
void Add_Edge(int u,int v,int flow){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
    return;
}
void dfs1(int u,int fa){
    if (fa) Add_Edge(u,fa,inf);
    for (int i=0,sz=T1[u].size();i<sz;i++) if (T1[u][i]!=fa) dfs1(T1[u][i],u);
}
void dfs2(int u,int fa){
    if (fa) Add_Edge(u,fa,inf);
    for (int i=0,sz=T2[u].size();i<sz;i++) if (T2[u][i]!=fa) dfs2(T2[u][i],u);
}
bool Bfs(){
    memset(Dep,-1,sizeof(Dep));int ql=1,qr=1;Dep[Qu[1]=S]=1;
    while (ql<=qr) for (int u=Qu[ql++],i=Head[u];i!=-1;i=Next[i]) if (Dep[E[i].v]==-1&&E[i].flow) Dep[Qu[++qr]=E[i].v]=Dep[u]+1;
    return Dep[T]!=-1;
}
int dfs(int u,int flow){
    if (u==T) return flow;
    for (int &i=cur[u],di;i!=-1;i=Next[i])
        if (E[i].flow&&Dep[E[i].v]==Dep[u]+1)
            if (di=dfs(E[i].v,min(flow,E[i].flow))){
                E[i].flow-=di;E[i^1].flow+=di;return di;
            }
    return 0;
}