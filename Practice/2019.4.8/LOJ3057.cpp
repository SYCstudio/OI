#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=5010;
const int maxM=505000;

int n,m,Q;
char Col[maxN];
vector<int> E[maxN],W[maxN],B[maxN];
int vis[maxN],Mark[maxN];
bool fob=0;
bool Ans[maxN][maxN];
queue<pair<int,int> > Qu;

void dfs_same(int u,int fa);
void dfs_unsame(int u,int fa);
void Add(int u,int v);
int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	scanf("%s",Col+1);
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	memset(Mark,-1,sizeof(Mark));
	for (int i=1; i<=n; i++) {
		if (Mark[i]==-1) {
			Mark[i]=0;
			fob=0;
			dfs_same(i,i);
			if (fob) Add(i,i);
		}
		if (!vis[i]) dfs_unsame(i,i);
	}
	for (int i=1; i<=n; i++) Ans[i][i]=1,Qu.push(make_pair(i,i));
	while (!Qu.empty()) {
		int u=Qu.front().first,v=Qu.front().second;
		Qu.pop();
		for (int i=0,sz1=W[u].size(); i<sz1; i++) for (int j=0,sz2=W[v].size(); j<sz2; j++) if (!Ans[W[u][i]][W[v][j]]) Ans[W[u][i]][W[v][j]]=Ans[W[v][j]][W[u][i]]=1,Qu.push(make_pair(W[u][i],W[v][j]));
		for (int i=0,sz1=B[u].size(); i<sz1; i++) for (int j=0,sz2=B[v].size(); j<sz2; j++) if (!Ans[B[u][i]][B[v][j]]) Ans[B[u][i]][B[v][j]]=Ans[B[v][j]][B[u][i]]=1,Qu.push(make_pair(B[u][i],B[v][j]));
	}
	while (Q--) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (Ans[u][v]) puts("YES");
		else puts("NO");
	}
	return 0;
}
void dfs_same(int u,int fa)
{
	for (int i=0,sz=E[u].size(); i<sz; i++) {
		int v=E[u][i];
		if (v==fa||Col[v]!=Col[u]) continue;
		if (Mark[v]==-1) {
			Add(u,v);
			Mark[v]=Mark[u]^1;
			dfs_same(v,u);
		} else if (Mark[v]==Mark[u]) fob=1;
	}
	return;
}
void dfs_unsame(int u,int fa)
{
	for (int i=0,sz=E[u].size(); i<sz; i++) {
		int v=E[u][i];
		if (v==fa||Col[v]==Col[u]) continue;
		if (!vis[v]) {
			vis[v]=1;
			Add(u,v);
			dfs_unsame(v,u);
		}
	}
	return;
}
void Add(int u,int v)
{
	if (Col[u]==Col[v]) Ans[u][v]=Ans[v][u]=1,Qu.push(make_pair(u,v));
	if (Col[v]=='1') W[u].push_back(v);
	else B[u].push_back(v);
	if (Col[u]=='1') W[v].push_back(u);
	else B[v].push_back(u);
	return;
}