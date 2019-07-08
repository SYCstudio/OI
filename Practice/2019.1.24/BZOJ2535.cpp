#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

#define PI pair<int,int>
#define mp make_pair
#define ft first
#define sd second

const int maxN=2010;

int n,m;
int Limit[maxN],D[maxN],BD[maxN],Ans[maxN];
vector<int> T[maxN];
priority_queue<PI,vector<PI>,greater<PI> > H;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&Limit[i]),Limit[i]=n-Limit[i];
	for (int i=1; i<=m; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		T[y].push_back(x);
		++D[x];
	}
	for (int i=1; i<=n; i++) BD[i]=D[i];

	for (int i=1; i<=n; i++) if (D[i]==0) H.push(mp(Limit[i],i));
	int cnt=n;
	while (!H.empty()) {
		int u=H.top().sd;
		H.pop();
		Ans[cnt--]=u;
		for (int i=0,sz=T[u].size(); i<sz; i++)
			if ((--D[T[u][i]])==0) H.push(mp(Limit[T[u][i]],T[u][i]));
	}
	for (int i=1; i<=n; i++) printf("%d ",Ans[i]);
	printf("\n");

	for (int x=1; x<=n; x++) {
		cnt=n;
		for (int i=1; i<=n; i++) D[i]=BD[i];
		while (!H.empty()) H.pop();
		for (int i=1; i<=n; i++) if (D[i]==0) H.push(mp(Limit[i],i));
		while (!H.empty()) {
			int u=H.top().sd;
			H.pop();
			if (u==x) continue;
			if (cnt>n-Limit[u]) break;
			--cnt;
			for (int i=0,sz=T[u].size(); i<sz; i++)
				if ((--D[T[u][i]])==0) H.push(mp(Limit[T[u][i]],T[u][i]));
		}
		printf("%d ",cnt);
	}
	printf("\n");
	return 0;
}
