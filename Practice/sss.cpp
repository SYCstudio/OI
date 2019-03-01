#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define MAX 300300
#define pi pair<ll,int>
#define fr first
#define sd second
#define mp make_pair
#define pb push_back
inline ll read()
{
	ll x=0;bool t=false;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')t=true,ch=getchar();
	while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
	return t?-x:x;
}
vector<pi> E[MAX];
int n,m,Q;
int id[MAX][3],tot;
int lb(int x){return x&(-x);}
struct SPT
{
	ll dis[MAX],c[MAX];int fa[MAX],dfn[MAX],low[MAX],tim;
	bool vis[MAX];
	vector<int> son[MAX];
	priority_queue<pi,vector<pi>,greater<pi> >Q;
	void dfs(int u){dfn[u]=++tim;for(int v:son[u])dfs(v);low[u]=tim;}
	void Modify(int x,ll w){x=dfn[x];while(x<=tim)c[x]+=w,x+=lb(x);}
	ll Query(int x)
	{
		ll ret=0;int X;
		X=low[x];while(X)ret+=c[X],X-=lb(X);
		X=dfn[x]-1;while(X)ret-=c[X],X-=lb(X);
		return ret;
	}
	void Dijkstra(int l,int r,int S)
	{
		for(int i=l;i<=r;++i)dis[i]=1e18,vis[i]=false;
		dis[S]=0;Q.push(mp(dis[S],S));
		while(!Q.empty())
		{
			int u=Q.top().sd;Q.pop();
			if(vis[u])continue;vis[u]=true;
			for(pi x:E[u])
			{
				int v=x.sd;ll w=x.fr;
				if(v<l||v>r||dis[v]<=dis[u]+w)continue;
				dis[v]=dis[u]+w;fa[v]=u;Q.push(mp(dis[v],v));
			}
		}
		for(int i=l;i<=r;++i)if(i!=S)son[fa[i]].pb(i);
		dfs(S);
	}
}T[18][3];
void Build(int l,int r,int dep)
{
	int mid=(l+r)>>1;
	for(int i=0;i<n;++i)
		T[dep][i].Dijkstra(id[l][0],id[r][n-1],id[mid][i]);
	if(l<mid)Build(l,mid-1,dep+1);
	if(r>mid)Build(mid+1,r,dep+1);
}
ll mx;
void Calc(int l,int r,int dep,int x,int y)
{
	int mid=(l+r)>>1;
	for(int i=0;i<n;++i)
		mx=min(mx,T[dep][i].dis[x]+T[dep][i].dis[y]);
	if(x<=id[mid][n-1]&&y>=id[mid][0])return;
	if(y<id[mid][0])Calc(l,mid-1,dep+1,x,y);
	else Calc(mid+1,r,dep+1,x,y);
}
void Modify(int l,int r,int dep,int x,int y,ll w)
{
	int mid=(l+r)>>1;
	for(int i=0;i<n;++i)
		if(T[dep][i].dis[x]+T[dep][i].dis[y]==mx)
		{
			T[dep][i].Modify(x,w),T[dep][i].Modify(y,w);
			return;
		}
	if(y<id[mid][0])Modify(l,mid-1,dep+1,x,y,w);
	else Modify(mid+1,r,dep+1,x,y,w);
}
ll Query(int l,int r,int dep,int u)
{
	int mid=(l+r)>>1;ll ret=0;
	for(int i=0;i<n;++i)
	{
		ll s=T[dep][i].Query(u);
		if(id[mid][i]==u)s>>=1;
		ret+=s;
	}
	if(u<id[mid][0])ret+=Query(l,mid-1,dep+1,u);
	if(u>id[mid][n-1])ret+=Query(mid+1,r,dep+1,u);
	return ret;
}
int main()
{
	n=read();m=read();Q=read();
	for(int i=0;i<m;++i)
		for(int j=0;j<n;++j)id[i][j]=++tot;
	for(int i=0;i<n-1;++i)
		for(int j=0;j<m;++j)
		{
			int u=id[j][i],v=id[j][i+1];ll w=read();
			E[u].pb(mp(w,v));E[v].pb(mp(w,u));
		}
	for(int i=0;i<n;++i)
		for(int j=0;j<m-1;++j)
		{
			int u=id[j][i],v=id[j+1][i];ll w=read();
			E[u].pb(mp(w,v));E[v].pb(mp(w,u));
		}
	Build(0,m-1,0);
	while(Q--)
	{
		int opt=read();
		if(opt==1)
		{
			int x1=read()-1,y1=read()-1,x2=read()-1,y2=read()-1;ll w=read();
			int u=id[y1][x1],v=id[y2][x2];if(u>v)swap(u,v);
			mx=1e18;Calc(0,m-1,0,u,v);
            cout<<"m:"<<mx<<endl;
			Modify(0,m-1,0,u,v,w);
		}
		else
		{
			int x=read()-1,y=read()-1,u=id[y][x];
			printf("%lld\n",Query(0,m-1,0,u));
		}
	}
	return 0;
}
