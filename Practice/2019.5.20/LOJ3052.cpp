#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define pb push_back
const int maxN=202000;

int n,Val[maxN],Mx[maxN],Len[maxN];
vector<int> T[maxN],V;
priority_queue<int> H[maxN];

void dfs1(int u);
void dfs2(int u);
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%d",&Val[i]);
	for (int i=2; i<=n; i++) {
		int fa;
		scanf("%d",&fa);
		T[fa].pb(i);
	}
	dfs1(1);
	dfs2(1);
	long long Ans=0;
	while (!H[1].empty()) Ans=Ans+H[1].top(),H[1].pop();
	printf("%lld\n",Ans);
	return 0;
}
void dfs1(int u)
{
	for (int i=0,sz=T[u].size(); i<sz; i++) {
		dfs1(T[u][i]);
		if (Len[T[u][i]]>Len[Mx[u]]) Mx[u]=T[u][i];
	}
	Len[u]=Len[Mx[u]]+1;
	return;
}
void dfs2(int u)
{
	if (Mx[u]) {
		for (int i=0,sz=T[u].size(); i<sz; i++) dfs2(T[u][i]);
		H[u].swap(H[Mx[u]]);
		for (int i=0,sz=T[u].size(); i<sz; i++)
			if (T[u][i]!=Mx[u]) {
				while (!H[T[u][i]].empty()) V.pb(max(H[T[u][i]].top(),H[u].top())),H[T[u][i]].pop(),H[u].pop();
				for (vector<int>::iterator it=V.begin(); it!=V.end(); it++) H[u].push(*it);
				V.clear();
			}
	}
	H[u].push(Val[u]);
	return;
}
