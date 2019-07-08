#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
#define ft first
#define sd second
const int maxN=101000;
const int maxM=303000<<1;
const ll INF=1e18;

int n,m;
int edgecnt=-1,Hd[maxN],Nt[maxM],V[maxM],W[maxM];
ll D1[maxN],D2[maxN];
double X[maxN],Y[maxN];
bool vis[maxN];
priority_queue<pair<ll,int> > H;

void Add_Edge(int u,int v,int w);
void Dijkstra(int S,ll *D);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d%d",&n,&m);
		memset(Hd,-1,sizeof(Hd));
		edgecnt=-1;
		for (int i=1; i<=m; i++) {
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			Add_Edge(u,v,w);
			Add_Edge(v,u,w);
		}
		Dijkstra(1,D1);
		Dijkstra(2,D2);
		for (int i=1; i<=n; i++) X[i]=0.5*(D1[i]+D2[i]),Y[i]=0.5*(D1[i]-D2[i]);
		sort(&X[1],&X[n+1]);
		sort(&Y[1],&Y[n+1]);
		double Ans=0;
		int mid=(n+1)/2;
		for (int i=1; i<=n; i++) Ans+=fabs(X[mid]-X[i])+fabs(Y[mid]-Y[i]);
		printf("%.10lf\n",Ans/n);
	}
	return 0;
}
void Add_Edge(int u,int v,int w)
{
	Nt[++edgecnt]=Hd[u];
	Hd[u]=edgecnt;
	V[edgecnt]=v;
	W[edgecnt]=w;
	return;
}
void Dijkstra(int S,ll *D)
{
	for (int i=1; i<=n; i++) D[i]=INF,vis[i]=0;
	while (!H.empty()) H.pop();
	D[S]=0;
	H.push(make_pair(0,S));
	while (!H.empty()) {
		int u=H.top().sd;
		H.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=Hd[u]; i!=-1; i=Nt[i]) if (D[V[i]]>D[u]+W[i]) H.push(make_pair(-(D[V[i]]=D[u]+W[i]),V[i]));
	}
	return;
}