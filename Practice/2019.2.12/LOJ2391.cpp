#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<set>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=1010000*2;
const int maxM=maxN<<1;
const int Mod=1e9+7;
int n;
pair<int,int> P[maxN];
set<pair<int,int> > S;
int Nxt[maxN],St[maxN],vis[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];

void Add_Edge(int u,int v);
void dfs(int u,int w);
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%d%d",&P[i].first,&P[i].second);
	sort(&P[1],&P[n+1]);
	mem(Head,-1);
	for (int i=1; i<=n; i++) {
		while (!S.empty()&&(*S.begin()).first<P[i].first) {
			int id=(*S.begin()).second;
			S.erase(S.begin());
			if (Nxt[id]) S.insert(make_pair(P[Nxt[id]].second,Nxt[id]));
		}
		int top=0;
		while (!S.empty()&&(*S.begin()).first<P[i].second) {
			St[++top]=(*S.begin()).second;
			S.erase(S.begin());
		}
		for (int j=1; j<=top; j++) Add_Edge(i,St[j]);
		for (int j=1; j<top; j++) Nxt[St[j]]=St[j+1];
		S.insert(make_pair(P[St[1]].second,St[1]));
		S.insert(make_pair(P[i].second,i));
	}
	int Ans=1;
	mem(vis,-1);
	for (int i=1; i<=n; i++) if (vis[i]==-1) dfs(i,0),Ans=2ll*Ans%Mod;
	printf("%d\n",Ans);
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	Next[++edgecnt]=Head[v];
	Head[v]=edgecnt;
	V[edgecnt]=u;
	return;
}
void dfs(int u,int w)
{
	if (vis[u]!=-1) {
		if (vis[u]!=w) {
			puts("0");
			exit(0);
		}
		return;
	}
	vis[u]=w;
	for (int i=Head[u]; i!=-1; i=Next[i]) dfs(V[i],w^1);
	if (Nxt[u]) dfs(Nxt[u],w);
	return;
}