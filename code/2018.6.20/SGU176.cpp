#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=120;
const int maxM=maxN*maxN*8;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m;
int edgecnt=-1,ecnt=-1,Head[maxN],Next[maxM],Low[maxM],Sum[maxN];
Edge E[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
int Dinic(int S,int T);
bool Bfs(int S,int T);
int dfs(int u,int flow,int T);
//void OutpMap();

int main()
{
	int S,T;mem(Head,-1);
	scanf("%d%d",&n,&m);S=n+1;T=S+1;
	for (int i=1;i<=m;i++)
	{
		int u,v,flow,opt;scanf("%d%d%d%d",&u,&v,&flow,&opt);
		if (opt==1)
		{
			Sum[v]+=flow;Sum[u]-=flow;
			Low[++ecnt]=flow;Add_Edge(u,v,0);
		}
		else{
			Low[++ecnt]=0;Add_Edge(u,v,flow);
		}
	}
	int sum=0;
	for (int i=1;i<=n;i++)
		if (Sum[i]>0) Add_Edge(S,i,Sum[i]),sum+=Sum[i];
		else if (Sum[i]<0) Add_Edge(i,T,-Sum[i]);

	//OutpMap();
	
	int ret=Dinic(S,T);

	if (ret!=sum){
		Add_Edge(n,1,inf);
		ret+=Dinic(S,T);
	}

	if (ret!=sum){
		printf("Impossible\n");return 0;
	}
	int Ans=0;
	for (int i=Head[1];i!=-1;i=Next[i])
		if (E[i].v==n){
			Ans=E[i].flow,E[i].flow=E[i^1].flow=0;break;
		}

	//OutpMap();

	//Ans+=Dinic(n,1);

	//OutpMap();

	printf("%d\n",Ans);
	for (int i=0;i<m;i++) printf("%d ",E[(i<<1)^1].flow+Low[i]);
	printf("\n");
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

int Dinic(int S,int T)
{
	int mxflow=0;
	while (Bfs(S,T))
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf,T)) mxflow+=di;
	}
	return mxflow;
}

bool Bfs(int S,int T)
{
	mem(Depth,-1);Depth[S]=1;Q[1]=S;
	int h=1,t=0;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

int dfs(int u,int flow,int T)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow),T)){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}

/*
void OutpMap()
{
	for (int i=1;i<=n+2;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			cout<<i<<" -> "<<E[j].v<<" "<<E[j].flow<<endl;
	cout<<endl;
	return;
}
//*/
