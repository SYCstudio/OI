#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=505000;
const int maxB=21;

class Edge{
public:
    int u,v,w;
};

int n,m,K;
Edge Ek[maxN],Em[maxN];
int ufs[maxN],Dep[maxN];
vector<pair<int,int> > T[maxN];
pair<int,int> Fa[maxN];

int find(int x);
void Add_Edge(int u,int v,int o);
void dfs(int u,int fa,int o);
int main(){
    scanf("%d%d%d",&n,&K,&m);int ncnt=n;
    for (int i=1;i<=K;i++) scanf("%d%d",&Ek[i].u,&Ek[i].v);
    for (int i=1;i<=n;i++) ufs[i]=i;
    for (int i=1;i<=m;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);Em[i]=((Edge){u,v,w});
	if (find(u)==find(v)) continue;
	ufs[find(u)]=find(v);
    }
    for (int i=1;i<=n;i++) ufs[i]=i;
    for (int i=1;i<=K;i++) Add_Edge(Ek[i].u,Ek[i].v,1),ufs[find(Ek[i].u)]=find(Ek[i].v);
    for (int i=1;i<=m;i++){
	int u=Em[i].u,v=Em[i].v;
	if (find(u)==find(v)) continue;
	Add_Edge(u,v,0);Em[i].w=-Em[i].w;ufs[find(u)]=find(v);
    }
    dfs(1,0,0);ll Ans=0;
    for (int i=1;i<=m;i++)
	if (Em[i].w>0){
	    int u=Em[i].u,v=Em[i].v;u=find(u);v=find(v);
	    //cout<<u<<" "<<v<<" "<<Em[i].w<<endl;
	    while (u!=v){
		if (Dep[u]<Dep[v]) swap(u,v);
		if (Fa[u].second) Ans=Ans+Em[i].w;
		int fa=Fa[u].first;ufs[u]=fa;u=find(fa);
	    }
	}
    for (int i=2;i<=n;i++)
	if (Fa[i].second&&find(i)!=find(Fa[i].first)){
	    puts("-1");return 0;
	}
    printf("%lld\n",Ans);return 0;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
void Add_Edge(int u,int v,int o){
    T[u].push_back(make_pair(v,o));
    T[v].push_back(make_pair(u,o));
    return;
}
void dfs(int u,int fa,int o){
    Fa[u]=make_pair(fa,o);Dep[u]=Dep[fa]+1;ufs[u]=u;
    for (int i=0,sz=T[u].size();i<sz;i++) if (T[u][i].first!=fa) dfs(T[u][i].first,u,T[u][i].second);
    return;
}
