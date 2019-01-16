#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;

class Array{
public:
    int tim,Tim[maxN],Key[maxN];
    void clear(){
	++tim;return;
    }
    void reset(int p){
	Tim[p]=0;return;
    }
    void use(int p){
	Tim[p]=tim;return;
    }
    bool check(int p){
	return Tim[p]==tim;
    }
    void plus(int p,int k){
	if (Tim[p]!=tim) Tim[p]=tim,Key[p]=0;
	Key[p]+=k;return;
    }
    int get(int p){
	return (Tim[p]==tim)?Key[p]:0;
    }
};

int n,Col[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int root,nowsize,Sz[maxN],Mx[maxN];
ll Ans[maxN],sum;
bool vis[maxN];
Array T,A;

void Add_Edge(int u,int v);
void dfs_root(int u,int fa);
void solve(int u);
void dfs_inc(int u,int fa);
void dfs_exc(int u,int fa);
void dfs_calc(int u,int fa,int sz,ll ans);

int main(){
    scanf("%d",&n);mem(Head,-1);
    for (int i=1;i<=n;i++) scanf("%d",&Col[i]);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	Add_Edge(u,v);Add_Edge(v,u);
    }
    Mx[root=0]=inf;nowsize=n;
    dfs_root(1,1);solve(root);
    for (int i=1;i<=n;i++) printf("%lld\n",Ans[i]);return 0;
}
void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
    return;
}
void dfs_root(int u,int fa){
    Sz[u]=1;Mx[u]=0;
    for (int i=Head[u];i!=-1;i=Next[i])
	if ((vis[V[i]]==0)&&(V[i]!=fa)){
	    dfs_root(V[i],u);Sz[u]+=Sz[V[i]];
	    Mx[u]=max(Mx[u],Sz[V[i]]);
	}
    Mx[u]=max(Mx[u],nowsize-Sz[u]);
    if (Mx[u]<Mx[root]) root=u;return;
}
void solve(int u){
    vis[u]=1;int sumsize=1;
    for (int i=Head[u];i!=-1;i=Next[i])
	if (vis[V[i]]==0) dfs_root(V[i]),sumsize+=Sz[V[i]];
    sum=0;A.clear();A.plus(Col[u],1);
    for (int i=Head[u];i!=-1;i=Next[i])
	if (vis[V[i]]==0) T.clear(),T.use(Col[u]),dfs_inc(V[i],u);
    for (int i=Head[u];i!=-1;i=Next[i])
	if (vis[V[i]]==0){
	    T.clear();T.use(Col[u]);dfs_exc(V[i],u);
	    dfs_calc(V[i],u,sumsize-Sz[V[i]],sum+sumsize-Sz[V[i]]);
	    T.clear();T.use(Col[u]);dfs_inc(V[i],u);
	}
    for (int i=Head[u];i!=-1;i=Next[i])
	if (vis[V[i]]==0){
	    root=0;nowsize=Sz[V[i]];
	    dfs_root(V[i],V[i]);solve(root);
	}
    return;
}
void dfs_inc(int u,int fa){
    A.plus(Col[u],1);bool flag=0;
    if (T.check(Col[u])==0) sum+=Sz[u],T.use(Col[u]),flag=1;
    for (int i=Head[u];i!=-1;i=Next[i])
	if ((vis[V[i]]==0)&&(V[i]!=fa)) dfs_inc(V[i],u);
    if (flag) T.reset(Col[u]);
    return;
}
void dfs_exc(int u,int fa,){
    A.plus(Col[u],-1);bool flag=0;
    if (T.check(Col[u])==0) sum-=Sz[u],T.use(Col[u]),flag=1;
    for (int i=Head[u];i!=-1;i=Next[i])
	if ((vis[V[i]]==0)&&(V[i]!=fa)) dfs_exc(V[i],u);
    if (flag) T.reset(Col[u]);
    return;
}
void dfs_calc(int u,int fa,int sz,ll ans){
    if (A.get(Col[u])==0) ans+=sz;
    A.plus(Col[u],1);
    Ans[u]+=ans;
    for (int i=Head[u];i!=-1;i=Next[i])
	if ((vis[V[i]]==0)&&(V[i]!=fa)) dfs_calc(V[i],u,sz,ans);
    A.plus(Col[u],-1);
    return;
}
