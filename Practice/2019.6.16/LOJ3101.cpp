#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=50010;
const int maxM=100010;
const int maxP=maxM*2+maxN*4;
const int maxB=17000;

int T,n,m,tcnt=0;
int Ic[maxM],It[maxM],Ix[maxM],Iy[maxM];
vector<int> Id[maxN],G[maxP];
map<int,int> Mp[maxN];
bitset<maxB> GET[maxP],fob;
int tpscnt,Tps[maxP],Dg[maxP];
int Ans[maxN],mark[maxN];

int main()
{
	scanf("%d%d%d",&T,&n,&m);
	for (int i=1; i<=n; i++) Mp[i][1]=++tcnt,Id[i].pb(1),++tcnt;
	for (int i=1; i<=n; i++) Mp[i][T+1]=++tcnt,Id[i].pb(T+1),++tcnt;
	for (int i=1; i<=m; i++) {
		scanf("%d%d%d%d",&Ic[i],&It[i],&Ix[i],&Iy[i]);
		if (Mp[Ix[i]].count(It[i])==0) Mp[Ix[i]][It[i]]=++tcnt,Id[Ix[i]].pb(It[i]),++tcnt;
	}
	for (int i=1; i<=n; i++) {
		sort(Id[i].begin(),Id[i].end());
		for (int j=0; j+1<Id[i].size(); j++) {
			G[Mp[i][Id[i][j]]+1].pb(Mp[i][Id[i][j+1]]+1);
			G[Mp[i][Id[i][j+1]]].pb(Mp[i][Id[i][j]]);
		}
	}
	for (int i=1; i<=m; i++) {
		int c=Ic[i],t=It[i],x=Ix[i],y=Iy[i];
		if (c==0) {
			int yt=Mp[y][*lower_bound(Id[y].begin(),Id[y].end(),t+1)];
			assert(Mp[x][t]);
			assert(yt);
			G[Mp[x][t]+1].pb(yt+1);
			G[yt].pb(Mp[x][t]);
		} else {
			int yt=Mp[y][*lower_bound(Id[y].begin(),Id[y].end(),t)];
			assert(Mp[x][t]);
			assert(yt);
			G[Mp[x][t]].pb(yt+1);
			G[yt].pb(Mp[x][t]+1);
		}
	}

	for (int i=1; i<=tcnt; i++) for (int j=0; j<G[i].size(); j++) ++Dg[G[i][j]];

	queue<int> Qu;
	for (int i=1; i<=tcnt; i++) if (!Dg[i]) Qu.push(i);
	while (!Qu.empty()) {
		int u=Qu.front();
		Qu.pop();
		Tps[++tpscnt]=u;
		for (int i=0; i<G[u].size(); i++) if ((--Dg[G[u][i]])==0) Qu.push(G[u][i]);
	}
	for (int l=1,r; l<=n; l=r+1) {
		r=min(n,l+maxB-1);
		for (int i=1; i<=tcnt; i++) GET[i].reset();
		fob.reset();
		for (int i=l; i<=r; i++) GET[Mp[i][T+1]+1][i-l]=1;
		for (int i=tcnt; i>=1; i--) for (int j=0; j<G[Tps[i]].size(); j++) GET[Tps[i]]|=GET[G[Tps[i]][j]];
		for (int i=l; i<=r; i++) if (GET[Mp[i][T+1]][i-l]) fob[i-l]=mark[i]=1;
		for (int i=1; i<=n; i++) Ans[i]+=(GET[Mp[i][T+1]]|fob).count();
	}

	for (int i=1; i<=n; i++) printf("%d ",(mark[i]^1)*(n-1-Ans[i]));
	return 0;
}
