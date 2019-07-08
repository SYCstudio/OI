#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define ft first
#define sd second
#define mp make_pair
const int maxN=1100;
const int maxM=5050;

int n,m;
int U[maxM],V[maxM];
vector<int> T1[maxN],T2[maxN];
int M1[maxN],M2[maxN];
vector<pair<int,int> > G[maxN];
int Dst[maxN],inq[maxN],vis[maxN];
queue<int> Qu;

void dfs1(int u);
void dfs2(int u);
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) {
		scanf("%d%d",&U[i],&V[i]);
		T1[U[i]].pb(V[i]);
		T2[V[i]].pb(U[i]);
	}
	dfs1(1);
	dfs2(n);
	//for (int i=1;i<=n;i++) cout<<M1[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<M2[i]<<" ";cout<<endl;
	for (int i=1; i<=m; i++)
		if (M1[U[i]]&&M1[V[i]]&&M2[U[i]]&&M2[V[i]]) {
			G[U[i]].pb(mp(V[i],-1));
			G[V[i]].pb(mp(U[i],2));
		}

	memset(Dst,127,sizeof(Dst));
	Dst[n]=0;
	Qu.push(n);
	inq[n]=1;
	++vis[n];
	while (!Qu.empty()) {
		int u=Qu.front();
		Qu.pop();
		for (int i=0; i<G[u].size(); i++) {
			int v=G[u][i].ft;
			if (Dst[v]>Dst[u]+G[u][i].sd) {
				Dst[v]=Dst[u]+G[u][i].sd;
				++vis[v];
				if (v>=n) {
					puts("No");
					return 0;
				}
				if (!inq[v]) {
					Qu.push(v);
					inq[v]=1;
				}
			}
		}
		inq[u]=0;
	}

	puts("Yes");
	for (int i=1; i<=m; i++)
		if (M1[U[i]]&&M1[V[i]]&&M2[U[i]]&&M2[V[i]]) printf("%d\n",Dst[U[i]]-Dst[V[i]]);
		else puts("1");
	return 0;
}
void dfs1(int u)
{
	M1[u]=1;
	for (int i=0; i<T1[u].size(); i++) if (!M1[T1[u][i]]) dfs1(T1[u][i]);
	return;
}
void dfs2(int u)
{
	M2[u]=1;
	for (int i=0; i<T2[u].size(); i++) if (!M2[T2[u][i]]) dfs2(T2[u][i]);
	return;
}
