#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxP=10;
const int maxM=3010<<1;
const int inf=2147483647;

int n,m,P;
int edgecnt=0,Head[maxN],Next[maxM];
pair<int,int> E[maxM];
pair<int,int> Data[maxN];
int viscnt,vis[maxN];
int F[maxN][1<<maxP],G[1<<maxP];
int pcnt=0,pS[maxN];
priority_queue<pair<int,int> > H;

void Add_Edge(int u,int v,int w);

int main(){
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&P);
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	mem(F,63);
	for (int i=1;i<=P;i++) scanf("%d%d",&Data[i].first,&Data[i].second);
	sort(&Data[1],&Data[P+1]);
	for (int i=1;i<=P;i++) F[Data[i].second][1<<(i-1)]=0;

	for (int S=0;S<(1<<P);S++){
		for (int i=1;i<=n;i++){
			for (int s=S;s;s=(s-1)&S)
				F[i][S]=min(F[i][S],F[i][s]+F[i][S^s]);
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

	for (int i=1,j;i<=P;i=j+1){
		j=i;pS[pcnt]|=(1<<(i-1));
		while ((j<P)&&(Data[j+1].first==Data[i].first)) pS[pcnt]|=(1<<(j++));
		pcnt++;
	}

	mem(G,63);
	for (int S=1;S<(1<<pcnt);S++){
		int nowS=0;
		for (int i=0;i<pcnt;i++) if (S&(1<<i)) nowS|=pS[i];
		for (int i=1;i<=n;i++) G[S]=min(G[S],F[i][nowS]);
	}

	for (int S=1;S<(1<<pcnt);S++)
		for (int s=S;s;s=(s-1)&S)
			G[S]=min(G[S],G[s]+G[s^S]);
	printf("%d\n",G[(1<<pcnt)-1]);
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=make_pair(v,w);
	return;
}
