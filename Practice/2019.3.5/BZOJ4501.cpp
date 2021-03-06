#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

#define double long double
const int maxN=55;
const int maxM=510;
const int inf=1000000000;
const double eps=1e-10;

int n,m,K,D[maxN],Qu[maxN];
int ecnt,Hd[maxN],Nt[maxM],V[maxM];
vector<pair<int,int> > To[maxN],Lm[maxN];
double F[maxN];

void Add_Edge(int u,int v);
namespace MF
{
class Edge
{
public:
	int v;
	double flow;
};
int ecnt,S,T,Hd[maxM],Nt[maxM*10],Id[maxM];
Edge E[maxM*10];
int cur[maxM],Qu[maxM],label[maxM];
void Init(int u);
double Calc(int start,double limit);
void Add_Edge(int u,int v,double flow);
bool Bfs();
double dfs(int u,double flow);
}

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	memset(Hd,-1,sizeof(Hd));
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(v,u);
		To[u].push_back(make_pair(v,i));
	}
	for (int i=1; i<=K; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if (x==y) continue;
		Lm[V[x]].push_back(make_pair(x,y));
	}
	int ql=1,qr=0;
	for (int i=1; i<=n; i++) if (!D[i]) Qu[++qr]=i;
	while (ql<=qr) {
		int u=Qu[ql++];
		for (int i=Hd[u]; i!=-1; i=Nt[i]) if ((--D[V[i]])==0) Qu[++qr]=V[i],MF::Init(V[i]);
	}
	printf("%.10LF\n",F[1]);
	return 0;
}
void Add_Edge(int u,int v)
{
	++D[v];
	Nt[++ecnt]=Hd[u];
	Hd[u]=ecnt;
	V[ecnt]=v;
	return;
}
namespace MF
{
void Init(int u)
{
	double ret=0,l=0,r=1e7;
	while (l+eps<r) {
		double mid=(l+r)/2.0;
		if (Calc(u,mid)>eps) ret=mid,l=mid+eps;
		else r=mid-eps;
	}
	F[u]=ret+1;
	return;
}
double Calc(int start,double limit)
{
	ecnt=-1;
	memset(Hd,-1,sizeof(Hd));
	S=1;
	T=2;
	int cnt=2;
	double sum=0;
	for (int i=0,sz=To[start].size(); i<sz; i++) {
		int v=To[start][i].first;
		Id[To[start][i].second]=++cnt;
		double key=::F[v]-limit;
		if (key>=0) sum+=key,Add_Edge(S,cnt,key);
		else Add_Edge(cnt,T,-key);
	}
	for (int i=0,sz=Lm[start].size(); i<sz; i++)
		Add_Edge(Id[Lm[start][i].first],Id[Lm[start][i].second],inf);
	while (Bfs()) {
		memcpy(cur,Hd,sizeof(cur));
		double di;
		while (1) {
			di=dfs(S,inf);
			if (di<eps) break;
			sum-=di;
		}
	}
	return sum;
}
void Add_Edge(int u,int v,double flow)
{
	Nt[++ecnt]=Hd[u];
	Hd[u]=ecnt;
	E[ecnt]=((Edge) {
		v,flow
	});
	Nt[++ecnt]=Hd[v];
	Hd[v]=ecnt;
	E[ecnt]=((Edge) {
		u,0
	});
	return;
}
bool Bfs()
{
	memset(label,-1,sizeof(label));
	label[S]=1;
	int ql=1,qr=1;
	Qu[1]=S;
	while (ql<=qr) for (int u=Qu[ql++],i=Hd[u]; i!=-1; i=Nt[i]) if (E[i].flow>eps&&label[E[i].v]==-1) label[Qu[++qr]=E[i].v]=label[u]+1;
	return label[T]!=-1;
}
double dfs(int u,double flow)
{
	if (u==T) return flow;
	for (int &i=cur[u]; i!=-1; i=Nt[i])
		if (E[i].flow>eps&&label[E[i].v]==label[u]+1) {
			double di=dfs(E[i].v,min(flow,E[i].flow));
			if (di>eps) {
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
}