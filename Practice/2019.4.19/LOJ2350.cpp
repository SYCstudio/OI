#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int maxN=101000;
const ll INF=1e18;

int n,m,S,T,U,V;
vector<pair<int,ll> > E[maxN];
vector<int> ME[maxN],uME[maxN];
ll D[maxN],DU[maxN],DV[maxN],Mu[maxN],Mv[maxN];
int Dg[maxN],Tst[maxN],Mark[maxN];
int vis[maxN];
priority_queue<pair<ll,int> > H;

void Dijkstra(int S,ll *Dst);

int main(){
    scanf("%d%d%d%d%d%d",&n,&m,&S,&T,&U,&V);
    for (int i=1;i<=m;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	E[u].push_back(make_pair(v,w));
	E[v].push_back(make_pair(u,w));
    }
    Dijkstra(S,D);Dijkstra(U,DU);Dijkstra(V,DV);

    for (int i=1;i<=n;i++)
	for (int j=0,sz=E[i].size();j<sz;j++)
	    if (D[E[i][j].first]==D[i]+E[i][j].second){
		++Dg[i];
		ME[i].push_back(E[i][j].first);
		uME[E[i][j].first].push_back(i);
	    }
    int ql=1,qr=0;Mark[T]=1;for (int i=1;i<=n;i++) if (!Dg[i]) Tst[++qr]=i;
    while (ql<=qr)
	for (int u=Tst[ql++],i=0,sz=uME[u].size();i<sz;i++){
	    Mark[uME[u][i]]|=Mark[u];
	    if ((--Dg[uME[u][i]])==0) Tst[++qr]=uME[u][i];
	}
    
    for (int i=1;i<=n;i++) Mu[i]=DU[i],Mv[i]=DV[i],Dg[i]=uME[i].size();
    
    ql=1;qr=1;Tst[1]=S;
    ll Ans=DU[V];
    while (ql<=qr){
	int u=Tst[ql++];Ans=min(Ans,Mu[u]+DV[u]);Ans=min(Ans,Mv[u]+DU[u]);
	for (int i=0,sz=ME[u].size();i<sz;i++)
	    if (Mark[ME[u][i]]){
		int v=ME[u][i];
		Mu[v]=min(Mu[v],Mu[u]);Mv[v]=min(Mv[v],Mv[u]);
		if ((--Dg[v])==0) Tst[++qr]=v;
	    }
    }
    printf("%lld\n",Ans);return 0;
}
void Dijkstra(int S,ll *Dst){
    memset(vis,0,sizeof(vis));for (int i=1;i<=n;i++) Dst[i]=INF;
    Dst[S]=0;
    while (!H.empty()) H.pop();
    H.push(make_pair(0,S));
    while (!H.empty()){
	int u=H.top().second;H.pop();if (vis[u]) continue;
	vis[u]=1;
	for (int i=0,sz=E[u].size();i<sz;i++){
	    int v=E[u][i].first,w=E[u][i].second;
	    if (Dst[v]>Dst[u]+w) H.push(make_pair(-(Dst[v]=Dst[u]+w),v));
	}
    }
    return;
}
