#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=250;
const int maxM=maxN*maxN*5;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow,w;
};

int n,m;
int S,Y,T,SS,TT;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN],Sum[maxN],Flow[maxN],Path[maxN];
queue<int> Q;
bool inq[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool spfa();

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	S=n+n+1;Y=S+1;T=Y+1;SS=T+1;TT=SS+1;
	Sum[S]-=m;Sum[Y]+=m;
	
	for (int i=1;i<=n;i++)
	{
		int key;scanf("%d",&key);
		Add_Edge(Y,i,inf,0);Add_Edge(i+n,T,inf,0);
		Sum[i+n]+=key;Sum[i]-=key;
	}

	for (int i=1;i<n;i++)
		for (int j=i+1;j<=n;j++)
		{
			int key;scanf("%d",&key);
			if (key!=-1) Add_Edge(i+n,j,inf,key);
		}

	for (int i=1;i<=TT;i++)
		if (Sum[i]>0) Add_Edge(SS,i,Sum[i],0);
		else if (Sum[i]<0) Add_Edge(i,TT,-Sum[i],0);

	Add_Edge(T,S,inf,0);

	//cout<<"Init finish"<<endl;

	int Ans=0,mxflow=0;
	while (spfa())
	{
		Ans=Flow[TT]*Dist[TT];mxflow+=Flow[TT];
		int now=TT;
		while (now!=SS){
			E[Path[now]].flow-=Flow[TT];E[Path[now]^1].flow+=Flow[TT];now=E[Path[now]].u;
		}
	}

	cout<<mxflow<<endl;
	printf("%d\n",Ans);
	return 0;
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
	for (int i=1;i<=TT;i++) Dist[i]=inf;
	Dist[SS]=0;inq[SS]=1;Q.push(SS);Flow[SS]=inf;
	do
	{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			if ((E[i].flow>0)&&(Dist[u]+E[i].w<Dist[E[i].v]))
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
	return Dist[TT]!=inf;
}
