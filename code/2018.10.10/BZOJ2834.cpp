#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN*20;
const int inf=2147483647;

class Pos
{
public:
	int x,y,id;
};

class HData
{
public:
	int u,key;
};

int n,m;
Pos P[maxN];
int Sx,Sy,Tx,Ty;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM],Dist[maxN];
priority_queue<HData> H;
bool vis[maxN];

void Add_Edge(int u,int v,int w);
bool cmpx(Pos A,Pos B);
bool cmpy(Pos A,Pos B);
bool operator < (HData A,HData B);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d%d",&P[i].x,&P[i].y),P[i].id=i;
	scanf("%d%d%d%d",&Sx,&Sy,&Tx,&Ty);P[++m]=((Pos){Sx,Sy,m});P[++m]=((Pos){Tx,Ty,m});
	sort(&P[1],&P[m+1],cmpx);
	for (int i=1,j;i<=m;i=j+1){
		j=i;
		while (P[j+1].x==P[i].x) j++,Add_Edge(2*P[j].id-1,2*P[j-1].id-1,2*(P[j].y-P[j-1].y));
	}
	sort(&P[1],&P[m+1],cmpy);
	for (int i=1,j;i<=m;i=j+1){
		j=i;
		while (P[j+1].y==P[i].y) j++,Add_Edge(2*P[j].id,2*P[j-1].id,2*(P[j].x-P[j-1].x));
	}
	for (int i=1;i<=m-2;i++) Add_Edge(2*i-1,2*i,1);
	for (int i=m-1;i<=m;i++) Add_Edge(2*i-1,2*i,0);
	int S=2*(m-1),T=2*m;
	for (int i=1;i<=2*m;i++) Dist[i]=inf;
	Dist[S]=0;H.push((HData){S,0});
	do{
		int u=H.top().u;H.pop();
		if (vis[u]) continue;vis[u]=1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Dist[V[i]]>Dist[u]+W[i]) H.push((HData){V[i],Dist[V[i]]=Dist[u]+W[i]});
	}
	while (!H.empty());
	if (Dist[T]==inf) printf("-1\n");
	else printf("%d\n",Dist[T]);return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

bool cmpx(Pos A,Pos B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}

bool cmpy(Pos A,Pos B){
	if (A.y!=B.y) return A.y<B.y;
	return A.x<B.x;
}

bool operator < (HData A,HData B){
	return A.key>B.key;
}
