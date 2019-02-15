#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const int maxM=1010<<2;
const int inf=2147483647;

class HData
{
public:
	int u,id,key;
};

int n,m,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN][maxN];
bool vis[maxN][maxN];
priority_queue<HData> H;

void Add_Edge(int u,int v,int w);
bool operator < (HData A,HData B);

int main(){
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	for (int i=1;i<=n;i++) for (int j=0;j<=K;j++) Dist[i][j]=inf;
	Dist[1][0]=0;H.push((HData){1,0,0});
	do{
		int u=H.top().u,d=H.top().id;H.pop();
		if (vis[u][d]) continue;vis[u][d]=1;
		for (int i=Head[u];i!=-1;i=Next[i]){
			if (Dist[V[i]][d]>Dist[u][d]+W[i])
				H.push((HData){V[i],d,Dist[V[i]][d]=Dist[u][d]+W[i]});
			if ((d<K)&&(Dist[V[i]][d+1]>Dist[u][d]+W[i]/2))
				H.push((HData){V[i],d+1,Dist[V[i]][d+1]=Dist[u][d]+W[i]/2});
		}
	}
	while (!H.empty());
	int Ans=inf;
	for (int i=0;i<=K;i++) Ans=min(Ans,Dist[n][i]);
	printf("%d\n",Ans);return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

bool operator < (HData A,HData B){
	return A.key>B.key;
}
