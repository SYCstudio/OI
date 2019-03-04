#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

typedef long long ll;
using namespace std;

class Matrix{
    public:
    ll a00,a01,a10,a11;
    Matrix(){
        a00=1;a01=a10=a11=0;return;
    }
};

const int maxN=1010000;
const int maxM=maxN<<1;

int n,I,Ip[maxN];
ll K,F[maxN],G[maxN];
int edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM];
int Sz[maxN],Hs[maxN],Top[maxN],Fa[maxN],Dep[maxN],dfncnt,dfn[maxN],rht[maxN],idfn[maxN];

ll Mul(ll a,ll b);
void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
namespace DC{
    class SegmentData{
        public:
        int ls,rs;Matrix M;
    };
    int nodecnt,rt[maxN];
    SegmentData S[maxN*20];
}
namespace DS{
    class SegmentData{
        public:
        int ls,rs;ll m1,m2;
    };
    int nodecnt,rt[maxN],scnt=0,sonseq[maxN],lft[maxN],rht[maxN];
    SegmentData S[maxN*20];
    void Build(int &x,int l,int r);
}
int main(){
    scanf("%d%lld",&n,&K);memset(Hd,-1,sizeof(Hd));
    for (int i=1;i<n;i++) scanf("%d",&Ip[i]);
    for (int i=1;i<n;i++){
        int y;scanf("%d",&y);Add_Edge(y,Ip[i]);Add_Edge(Ip[i],y);
    }
    dfs1(1,0);dfs2(1,1);
}
ll Mul(ll a,ll b){
    if (!a||!b) return 0;
    if (a>=K||b>=K) return K;
    if (__builtin_clzll(a)+__builtin_clzll(b)<66||a*b>=K) return K;
    return a*b;
}
void Add_Edge(int u,int v){
    Nt[++edgecnt]=Hd[u];Hd[u]=edgecnt;V[edgecnt]=v;
    return;
}
void dfs1(int u,int fa){
    Fa[u]=fa;Dep[u]=Dep[fa]+1;Sz[u]=1;
    for (int i=Hd[u];i!=-1;i=Nt[i])
        if (V[i]!=fa){
            dfs1(V[i],u);Sz[u]+=Sz[V[i]];
            if (Sz[V[i]]>Sz[Hs[u]]) Hs[u]=V[i];
        }
    return;
}
void dfs2(int u,int top){
    Top[u]=top;idfn[dfn[u]=++dfncnt]=u;F[u]=G[u]=1;
    if (Hs[u]){
        dfs2(Hs[u],top);
        for (int i=Hd[u];i!=-1;i=Nt[i]) if (V[i]!=Fa[u]&&V[i]!=Top[u]) dfs2(V[i],V[i]);
        DS::lft[u]=DS::scnt+1;
        for (int i=Hd[u];i!=-1;i=Nt[i]) if (V[i]!=Fa[u]&&V[i]!=Top[u]) DS::sonseq[++DS::scnt]=V[i];
        DS::rht[u]=DS::scnt;
        DS::Build(DS::rt[u],DS::lft[u],DS::rht[u]);
    }
}