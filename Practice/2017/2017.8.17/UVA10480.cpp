#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=60;
const int maxM=2000;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
	bool edge;
};

int n,m;
int cnt;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxM];
bool is_outp[maxN][maxN];
bool setS[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);
void outp(int u);

int main()
{
	bool op=0;
	while (cin>>n>>m)
	{
		if ((n==0)&&(m==0))
			break;
		if (op)
			printf("\n");
		op=1;
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		for (int i=1;i<=m;i++)
		{
			int u,w,v;
			scanf("%d%d%d",&u,&v,&w);
			Add_Edge(u,v,w);
			Add_Edge(v,u,w);
		}
		/*for (int i=1;i<=n;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
				cout<<E[j].u<<" "<<E[j].v<<" "<<E[j].flow<<endl;
			cout<<endl;
		}
		//*/
		while (bfs())
		{
			for (int i=1;i<=n;i++)
				cur[i]=Head[i];
			while (dfs(1,inf));
		}
		memset(is_outp,0,sizeof(is_outp));
		memset(setS,0,sizeof(setS));
		outp(1);
		for (int i=1;i<=n;i++)
			if (setS[i]==1)
			{
				for (int j=Head[i];j!=-1;j=Next[j])
				{
					int v=E[j].v;
					if ((setS[v]==0)&&(is_outp[i][v]==0))
					{
						printf("%d %d\n",i,v);
						is_outp[i][v]=1;
					}
				}
			}
		/*
		for (int i=0;i<=cnt;i++)
			if ((E[i].flow==0)&&(E[i].edge==1))
				printf("%d %d\n",E[i].u,E[i].v);
		//*/
	}
}

void Add_Edge(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].flow=flow;
	E[cnt].edge=1;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].v=u;
	E[cnt].u=v;
	E[cnt].flow=0;
	E[cnt].edge=0;
}

bool bfs()
{
	memset(depth,-1,sizeof(depth));
	int h=1,t=0;
	Q[1]=1;
	depth[1]=1;
	do
	{
		t++;
		int u=Q[t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((depth[v]==-1)&&(E[i].flow>0))
			{
				depth[v]=depth[u]+1;
				h++;
				Q[h]=v;
			}
		}
	}
	while (h!=t);
	if (depth[2]==-1)
		return 0;
	/*for (int i=1;i<=n;i++)
		cout<<depth[i]<<" ";
	cout<<endl;
	getchar();*/
	return 1;
}

int dfs(int u,int flow)
{
	//cout<<u<<endl;
	if (u==2)
		return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if ((depth[v]==depth[u]+1)&&(E[i].flow>0))
		{
			//cout<<i<<" "<<u<<' '<<v<<endl;
			//cout<<"E:"<<E[i].u<<" "<<E[i].v<<" "<<E[i].flow<<endl;
			//getchar();
			int di=dfs(v,min(flow,E[i].flow));
			if (di>0)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	}
	return 0;
}

void outp(int u)
{
	setS[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((setS[E[i].v]==0)&&(E[i].flow>0))
			outp(E[i].v);
	return;
}
