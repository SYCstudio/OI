#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=10100<<1;
const int maxD=8;
const int inf=2147483647;

int n,m,D;
int edgecnt=0,Head[maxN],Next[maxM];
pair<int,int> E[maxM];
int F[maxN][1<<maxD],G[1<<maxD];
priority_queue<pair<int,int> > H;
int viscnt,vis[maxN];

void Add_Edge(int u,int v,int w);

int main(){
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&D);
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	mem(F,63);
	for (int i=1;i<=D;i++){
		F[i][1<<(i-1)]=0;
		F[n-i+1][1<<(D+i-1)]=0;
	}
	for (int S=0;S<(1<<(D+D));S++){
		for (int i=1;i<=n;i++){
			for (int s=(S-1)&S;s;s=(s-1)&S) F[i][S]=min(F[i][S],F[i][s]+F[i][S^s]);
			if (F[i][S]!=F[0][0]) H.push(make_pair(-F[i][S],i));
		}
		++viscnt;
		while (!H.empty()){
			int u=H.top().second;H.pop();
			if (vis[u]==viscnt) continue;vis[u]=viscnt;
			for (int i=Head[u];i!=-1;i=Next[i])
				if (F[E[i].first][S]>F[u][S]+E[i].second)
					H.push(make_pair(-(F[E[i].first][S]=F[u][S]+E[i].second),E[i].first));
		}
	}
	mem(G,63);
	for (int S=1;S<(1<<D);S++) for (int i=1;i<=n;i++) G[S]=min(G[S],F[i][S^(S<<D)]);
	for (int S=1;S<(1<<D);S++)
		for (int s=(S-1)&S;s;s=(s-1)&S)
			G[S]=min(G[S],G[s]+G[S^s]);
	if (G[(1<<D)-1]==F[0][0]) printf("-1\n");
	else printf("%d\n",G[(1<<D)-1]);
	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=make_pair(v,w);
	return;
}
/*
10 20 1
6 5 1
6 9 4
9 4 2
9 4 10
6 1 2
2 3 6
7 6 10
5 7 1
9 7 2
5 9 10
1 6 8
4 7 4
5 7 1
2 6 9
10 10 6
8 7 2
10 9 10
1 2 4
10 1 8
9 9 7
//*/
