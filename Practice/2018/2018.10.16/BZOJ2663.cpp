#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

const int maxN=51;
const int maxNode=maxN*maxN;
const ld eps=1e-7;
const int maxM=maxN*maxN*8;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

class Pos
{
public:
	int x,y;
};

int n,K,S,T;
Pos P1[maxN],P2[maxN];
ld ED[maxN][maxN];
int edgecnt=-1,Head[maxNode],Next[maxM];
Edge E[maxM];
int Dph[maxNode],cur[maxNode],Q[maxNode];

void Solve1();
void Solve2();
void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d%d",&P1[i].x,&P1[i].y);
	for (int i=1;i<=n;i++) scanf("%d%d",&P2[i].x,&P2[i].y);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) ED[i][j]=sqrt(sqr(P1[i].x-P2[j].x)+sqr(P1[i].y-P2[j].y));

	Solve1();
	Solve2();

	return 0;
}

void Solve1(){
	ld l=0,r=1e9,Ans;
	do{
		ld mid=(l+r)/2.0;
		edgecnt=-1;mem(Head,-1);
		S=n+n+1;T=S+1;
		for (int i=1;i<=n;i++) Add_Edge(S,i,1),Add_Edge(i+n,T,1);
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (ED[i][j]<=mid) Add_Edge(i,j+n,1);
		int flow=0;
		while (Bfs()){
			for (int i=1;i<=T;i++) cur[i]=Head[i];
			while (int di=dfs(S,inf)) flow+=di;
		}
		if (flow>=K) Ans=mid,r=mid-eps;
		else l=mid+eps;
	}
	while (l+eps<r);
	printf("%.2LF ",Ans);return;
}

void Solve2(){
	if (n==K){
		printf("+INF\n");return;
	}
	ld l=0,r=1e9,Ans;
	do{
		ld mid=(l+r)/2.0;
		edgecnt=-1;mem(Head,-1);
		S=n+n+1;T=S+1;
		for (int i=1;i<=n;i++) Add_Edge(S,i,1),Add_Edge(i+n,T,1);
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (ED[i][j]>=mid) Add_Edge(i,j+n,1);
		int flow=0;
		while (Bfs()){
			for (int i=1;i<=T;i++) cur[i]=Head[i];
			while (int di=dfs(S,inf)) flow+=di;
		}
		if (flow>=n-K) Ans=mid,l=mid+eps;
		else r=mid-eps;
	}
	while (l+eps<r);
	printf("%.2LF\n",Ans);return;
}

void Add_Edge(int u,int v,int flow){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

bool Bfs(){
	mem(Dph,-1);int h=1,t=0;
	Dph[Q[1]=S]=1;
	do for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
		   if ((E[i].flow)&&(Dph[E[i].v]==-1))
			   Dph[Q[++h]=E[i].v]=Dph[u]+1;
	while (h!=t);
	return Dph[T]!=-1;
}

int dfs(int u,int flow){
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow)&&(Dph[E[i].v]==Dph[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow))){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}
