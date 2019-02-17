#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define pw(x) (1<<(x))
const int maxN=100100;
const int maxM=maxN<<1;
const int maxB=17;

int n,Q,Log[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],W[maxM],Dst[maxN];

class Tree{
    public:
    int root,Dep[maxN],Fa[maxN],Dst[maxN],Mx[maxN],ST[maxB][maxN],Mxd[maxB][maxN],dfncnt,dfn[maxN],lst[maxN];
    int lcnt,Mark[maxN];
    pair<int,int> Leaf[maxN];
    void dfs_init(int u,int fa){
        Dep[u]=0;ST[0][u]=fa;
        for (int i=Head[u];i!=-1;i=Next[i])
            if (V[i]!=fa){
                dfs_init(V[i],u);
                if (Dep[V[i]]+W[i]>Dep[u]) Mx[u]=V[i],Dep[u]=Dep[V[i]]+W[i];
            }
        return;
    }
    void dfs_push(int u,int fa,int w){
        Dep[u]=Dep[fa]+1;dfn[u]=++dfncnt;Mxd[0][dfncnt]=Dst[u];
        if (Mx[u]==0) Leaf[++lcnt]=make_pair(w,u);
        else{
            Fa[Mx[u]]=u;
            for (int i=Head[u];i!=-1;i=Next[i])
                if (V[i]!=fa) Dst[V[i]]=Dst[u]+W[i],dfs_push(V[i],u,(V[i]==Mx[u])?w+W[i]:W[i]);
        }
        lst[u]=dfncnt;
        return;
    }
    void Init(int r){
        root=r;dfs_init(root,0);Dep[root]=1;Dst[root]=0;dfs_push(root,0,0);
        for (int i=1;i<maxB;i++) for (int j=1;j<=n;j++) ST[i][j]=ST[i-1][ST[i-1][j]];
        sort(&Leaf[1],&Leaf[lcnt+1]);reverse(&Leaf[1],&Leaf[lcnt+1]);for (int i=1;i<=lcnt;i++) Leaf[i].first+=Leaf[i-1].first;
        for (int i=1;i<=lcnt;i++){
            int now=Leaf[i].second;
            while (now) Mark[now]=i,now=Fa[now];
        }
        for (int i=1;i<maxB;i++) for (int j=1;j+pw(i)-1<=n;j++) Mxd[i][j]=max(Mxd[i-1][j],Mxd[i-1][j+pw(i-1)]);
        //cout<<"init on:"<<root<<endl;
        //for (int i=1;i<=lcnt;i++) cout<<"("<<Leaf[i].first-Leaf[i-1].first<<","<<Leaf[i].second<<")"<<endl;
        return;
    }
    int LCA(int u,int v){
        if (Dep[u]<Dep[v]) swap(u,v);for (int i=maxB-1;i>=0;i--) if (ST[i][u]&&Dep[ST[i][u]]>=Dep[v]) u=ST[i][u];
        if (u==v) return u;for (int i=maxB-1;i>=0;i--) if (ST[i][u]&&ST[i][v]&&ST[i][u]!=ST[i][v]) u=ST[i][u],v=ST[i][v];
        return ST[0][u];
    }
    int GET(int u,int cnt){
        cnt=min(cnt*2-1,lcnt);
        if (Mark[u]<=cnt) return Leaf[cnt].first;
        int ret=Leaf[cnt-1].first;
        int now=u;for (int i=maxB-1;i>=0;i--) if (ST[i][now]&&Mark[ST[i][now]]>cnt) now=ST[i][now];now=ST[0][now];
        //cout<<"root:"<<root<<" "<<u<<" "<<cnt<<endl;
        //cout<<now<<" "<<ret<<endl;
        int l=dfn[u],r=lst[u],lg=Log[r-l+1];
        int mxd=max(Mxd[lg][l],Mxd[lg][r-pw(lg)+1]);
        //cout<<"mxd:"<<mxd<<endl;
        ret=ret+mxd-Dst[now];
        //cout<<"RET:"<<ret<<" "<<Leaf[cnt].first+Dst[u]-Dst[Leaf[Mark[now]].second]<<endl;
        return max(ret,Leaf[cnt].first+mxd-Dst[Leaf[Mark[now]].second]);
    }
};

Tree T1,T2;

void Add_Edge(int u,int v,int w);
void Bfs(int S);
int main(){
    for (int i=2;i<maxN;i++) Log[i]=Log[i>>1]+1;
    //freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d",&n,&Q);mem(Head,-1);
    for (int i=1;i<n;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    int S,T;
    Bfs(1);S=1;for (int i=1;i<=n;i++) if (Dst[S]<Dst[i]) S=i;
    Bfs(S);T=1;for (int i=1;i<=n;i++) if (Dst[T]<Dst[i]) T=i;
    //cout<<S<<" "<<T<<endl;
    T1.Init(S);T2.Init(T);int lstans=0;
    while (Q--){
        //cout<<"running on :"<<Q<<endl;
        int x,y;scanf("%d%d",&x,&y);
        x=(x+lstans-1)%n+1;y=(y+lstans-1)%n+1;
        printf("%d\n",lstans=max(T1.GET(x,y),T2.GET(x,y)));
    }
    return 0;
}
void Add_Edge(int u,int v,int w){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
    return;
}
void Bfs(int S){
    static int vis[maxN],Qu[maxN];mem(vis,0);int l=1,r=1;Qu[1]=S;Dst[S]=0;vis[S]=1;
    while (l<=r) for (int u=Qu[l++],i=Head[u];i!=-1;i=Next[i]) if (vis[V[i]]==0) Dst[Qu[++r]=V[i]]=Dst[u]+W[i],vis[V[i]]=1;
    return;
}