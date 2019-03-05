#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxI=51;
const int maxK=210;
const int Num=100;
const int maxN=maxI*maxK;
const int maxM=maxN*10;
const int inf=1000000000;
const ll INF=1e18;

class Edge{
    public:
    int v;
    ll flow;
};

int n,m,S,T;
int A[maxI],B[maxI],C[maxI];
ll Key[maxK];
int Id[maxI][maxK];
int ecnt=-1,Hd[maxN],Nt[maxM];
Edge E[maxM];
int cur[maxN],Qu[maxN],label[maxN];

void Add_Edge(int u,int v,ll flow);
bool Bfs();
ll dfs(int u,ll flow);
int main(){
    scanf("%d%d",&n,&m);memset(Hd,-1,sizeof(Hd));
    for (int i=1;i<=n;i++) scanf("%d%d%d",&A[i],&B[i],&C[i]);
    int idcnt=0;
    for (int i=1;i<=n;i++) for (int j=-100;j<100;j++) Id[i][j+Num]=++idcnt;S=++idcnt;T=++idcnt;
    for (int i=1;i<=n;i++) Id[i][-101+Num]=S,Id[i][100+Num]=T;
    ll Ans=0;
    for (int i=1;i<=n;i++){
        int l,r;ll sum=0;scanf("%d%d",&l,&r);
        for (int j=-100;j<=100;j++)
            if (j<l||j>r) Key[j+Num]=0;
            else Key[j+Num]=j*j*A[i]+B[i]*j+C[i]+inf,sum+=Key[j+Num];
        Ans+=sum;
        for (int j=-100;j<=100;j++) Add_Edge(Id[i][j+Num-1],Id[i][j+Num],sum-Key[j+Num]);
    }
    for (int i=1;i<=m;i++){
        int u,v,d;scanf("%d%d%d",&u,&v,&d);
        for (int j=d-100;j<=100;j++) Add_Edge(Id[u][j+Num],Id[v][j-d+Num],INF);
    }
    while (Bfs()){
        memcpy(cur,Hd,sizeof(cur));
        while (ll di=dfs(S,INF)) Ans-=di;
    }
    printf("%lld\n",Ans-1ll*n*inf);return 0;
}
void Add_Edge(int u,int v,ll flow){
    Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow});
    Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0});
    return;
}
bool Bfs(){
    memset(label,-1,sizeof(label));int ql=1,qr=1;Qu[1]=S;label[S]=1;
    while (ql<=qr) for (int u=Qu[ql++],i=Hd[u];i!=-1;i=Nt[i]) if (E[i].flow&&label[E[i].v]==-1) label[Qu[++qr]=E[i].v]=label[u]+1;
    return label[T]!=-1;
}
ll dfs(int u,ll flow){
    if (u==T) return flow;
    for (int &i=cur[u];i!=-1;i=Nt[i]) if (E[i].flow&&label[E[i].v]==label[u]+1) if (ll di=dfs(E[i].v,min(flow,E[i].flow))) return E[i].flow-=di,E[i^1].flow+=di,di;
    return 0;
}