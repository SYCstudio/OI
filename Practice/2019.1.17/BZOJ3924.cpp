#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int maxD=21;
const int inf=2000000000;
const ll INF=1e18;

int n,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int root,nowsize,Sz[maxN],Mx[maxN],Id[maxD][maxN];
bool vis[maxN];
vector<pair<int,int> > To[maxN];
pair<ll,ll> Gc[maxN][maxD],Bl[maxD][maxN],Sm[maxN];

void Add_Edge(int u,int v,int w);
void dfs_root(int u,int fa);
void solve_init(int u,int d);
void dfs_init(int u,int fa,ll dist,int anc,int d,int id);
void modify(int u,int d,int x,ll val);
ll get_dist(int u,int d);
ll get_val(int u);

int main(){
    //freopen("11.in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d",&n,&Q);mem(Head,-1);
    for (int i=1;i<n;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    Mx[root=0]=inf;nowsize=n;dfs_root(1,1);
    int rt=root;solve_init(root,0);
    //cout<<"Init finish"<<endl;
    while (Q--){
	int u,e;scanf("%d%d",&u,&e);
	modify(rt,0,u,e);
	/*
	ll Ans=INF;
	for (int i=1;i<=n;i++){
	    ll r=get_dist(rt,0,i);//cout<<i<<" "<<r<<endl;
	    Ans=min(Ans,r);
	}
	printf("%lld\n",Ans);
	//*/
	printf("%lld\n",get_dist(rt,0));
    }
    return 0;
}
void Add_Edge(int u,int v,int w){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
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
void solve_init(int u,int d){
    //cout<<"solve init:"<<u<<" "<<d<<endl;
    vis[u]=1;Bl[d][u]=make_pair(u,0);
    for (int i=Head[u];i!=-1;i=Next[i])
	if (vis[V[i]]==0) To[u].push_back(make_pair(V[i],W[i]));
    for (int i=0,sz=To[u].size();i<sz;i++){
	int v=To[u][i].first;dfs_init(v,u,To[u][i].second,u,d,i);
	root=0;nowsize=Sz[v];
	dfs_root(v,v);solve_init(root,d+1);
    }
    return;
}
void dfs_init(int u,int fa,ll dist,int anc,int d,int id){
    Bl[d][u]=make_pair(anc,dist);Id[d][u]=id;
    for (int i=Head[u];i!=-1;i=Next[i])
	if ((vis[V[i]]==0)&&(V[i]!=fa)) dfs_init(V[i],u,dist+W[i],anc,d,id);
    return;
}
void modify(int u,int d,int x,ll val){
    //cout<<"modify:"<<u<<" "<<d<<" "<<x<<" "<<val<<endl;
    Sm[u].second+=val*Bl[d][x].second;
    if (u==x){
	Sm[u].first+=val;return;
    }
    for (int i=0,sz=To[u].size();i<sz;i++)
	if (i!=Id[d][x]){
	    Gc[u][i].first+=val;Gc[u][i].second+=val*Bl[d][x].second;
	}
    modify(Bl[d+1][To[u][Id[d][x]].first].first,d+1,x,val);
}
ll get_dist(int u,int d){
    ll ret=get_val(u);
    ll mn=INF;int id=0;
    for (int i=0,sz=To[u].size();i<sz;i++){
	ll val=get_val(To[u][i].first);
	if (val<mn) mn=val,id=To[u][i].first;
    }
    if (ret>mn) return get_dist(Bl[d+1][id].first,d+1);
    return ret;
}
ll get_val(int u){
    //cout<<"get_val:"<<u<<endl;
    ll ret=Sm[u].second;
    for (int d=0;;d++){
	int nrt=Bl[d][u].first,id=Id[d][u];
	//cout<<d<<" "<<nrt<<" "<<id<<endl;
	if (nrt==u) break;
	//cout<<Gc[nrt][id].second+Bl[d][u].second*(Gc[nrt][id].first+Sm[nrt].first)<<endl;
	ret=ret+Gc[nrt][id].second+Bl[d][u].second*(Gc[nrt][id].first+Sm[nrt].first);
    }
    //cout<<"ret:"<<ret<<endl;
    return ret;
}
