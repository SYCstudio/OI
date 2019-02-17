#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=100100;
const int maxM=maxN<<1;
const int maxB=17;

int n,Q;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],W[maxM],Dst[maxN];

class Tree{
    public:
    int root,Dep[maxN],Fa[maxN],Dst[maxN],Mx[maxN],ST[maxB][maxN];
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
        Dep[u]=Dep[fa]+1;
        if (Mx[u]==0) Leaf[++lcnt]=make_pair(w,u);
        else{
            Fa[Mx[u]]=u;
            for (int i=Head[u];i!=-1;i=Next[i])
                if (V[i]!=fa) Dst[V[i]]=Dst[u]+W[i],dfs_push(V[i],u,(V[i]==Mx[u])?Dst[u]+W[i]:W[i]);
        }
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
        cout<<"root:"<<root<<endl;
        for (int i=1;i<=n;i++) cout<<ST[0][i]<<" ";cout<<endl;
        for (int i=1;i<=n;i++) cout<<Mark[i]<<" ";cout<<endl;
        for (int i=1;i<=n;i++) cout<<Dst[i]<<" ";cout<<endl;
        for (int i=1;i<=n;i++) cout<<Dep[i]<<" ";cout<<endl;
        for (int i=1;i<=lcnt;i++) cout<<Leaf[i].first<<" "<<Leaf[i].second<<endl;
        return;
    }
    int LCA(int u,int v){
        if (Dep[u]<Dep[v]) swap(u,v);for (int i=maxB-1;i>=0;i--) if (ST[i][u]&&Dep[ST[i][u]]>=Dep[v]) u=ST[i][u];
        if (u==v) return u;for (int i=maxB-1;i>=0;i--) if (ST[i][u]&&ST[i][v]&&ST[i][u]!=ST[i][v]) u=ST[i][u],v=ST[i][v],cout<<"skip:"<<u<<" "<<v<<endl;
        cout<<"final:"<<u<<" "<<v<<" "<<ST[0][u]<<endl;
        return ST[0][u];
    }
    int GET(int u,int cnt){
        cnt=min(cnt*2-1,lcnt);
        if (Mark[u]<=cnt) return Leaf[cnt].first;
        int lca=LCA(u,Leaf[cnt].second);
        cout<<"GET:"<<u<<" "<<cnt<<endl;
        cout<<"lca:"<<u<<" "<<Leaf[cnt].second<<"|"<<lca<<endl;
        return Leaf[cnt].first-(Dst[Leaf[cnt].second]-Dst[lca])+(Dst[u]-Dst[lca]);
    }
};

Tree T1,T2;

void Add_Edge(int u,int v,int w);
void Bfs(int S);
int main(){
    freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d",&n,&Q);mem(Head,-1);
    for (int i=1;i<n;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    int S,T;
    Bfs(1);S=1;for (int i=1;i<=n;i++) if (Dst[S]<Dst[i]) S=i;
    Bfs(S);T=1;for (int i=1;i<=n;i++) if (Dst[T]<Dst[i]) T=i;
    cout<<S<<" "<<T<<endl;
    T1.Init(S);T2.Init(T);int lstans=0;
    while (Q--){
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