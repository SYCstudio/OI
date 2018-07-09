#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=4050;
const int maxM=maxN*100;
const int inf=2147483647;

class Pos
{
public:
	int x,y;
};

class Edge
{
public:
	int u,v,flow,w;
};

int n;
Pos P[maxN];
int S,T,Y;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN],Path[maxN],Flow[maxN];
bool inq[maxN];
queue<int> Q;

bool cmp(Pos A,Pos B);
void Add_Edge(int u,int v,int flow,int w);
bool spfa();

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&P[i].x,&P[i].y);
	sort(&P[1],&P[n+1],cmp);

	S=n+n+1;T=n+n+2;Y=n+n+3;
	for (int i=1;i<=n;i++) Add_Edge(i,i+n,1,1),Add_Edge(i,i+n,2,0),Add_Edge(Y,i,2,0),Add_Edge(i+n,T,2,0);

	for (int i=1;i<=n;i++)
	{
		int Mx=0;
		for (int j=i-1;j>=1;j--)
		{
			if ((P[j].y>P[i].y)||(Mx>=P[j].y)) continue;
			Mx=max(Mx,P[j].y);Add_Edge(j+n,i,2,0);
		}
	}

	Add_Edge(S,Y,2,0);

	/*
	for (int i=1;i<=Y;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if (E[j].flow) cout<<i<<" -> "<<E[j].v<<endl;
	//*/

	int Ans=0;
	while (spfa())
	{
		//cout<<Dist[T]<<" "<<Flow[T]<<endl;
		int now=T;Ans=Ans+Dist[T]*Flow[T];
		while (now!=S)
		{
			E[Path[now]].flow-=Flow[T];E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]].u;
		}
	}

	printf("%d\n",Ans);
	return 0;
}

bool cmp(Pos A,Pos B){
	if (A.x!=B.x) return A.x<B.x;
	else return A.y<B.y;
}

void Add_Edge(int u,int v,int flow,int w)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){u,v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){v,u,0,-w});
	return;
}

bool spfa()
{
	while (!Q.empty()) Q.pop();mem(inq,0);
	for (int i=1;i<=Y;i++) Dist[i]=-inf;
	Dist[S]=0;Flow[S]=inf;Q.push(S);inq[S]=1;
	do
	{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			if ((E[i].flow>0)&&(Dist[u]+E[i].w>Dist[E[i].v]))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				if (inq[E[i].v]==0){
					inq[E[i].v]=1;Q.push(E[i].v);
				}
			}
		}
		inq[u]=0;
	}
	while (!Q.empty());
	//for (int i=1;i<=Y;i++) cout<<Dist[i]<<" ";cout<<endl;
	return Dist[T]!=-inf;
}
