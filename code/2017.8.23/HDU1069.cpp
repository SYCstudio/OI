#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=40*4;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

class Queue_Data
{
public:
	int u,dist;
};

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.dist<B.dist;
}

class Edge
{
public:
	int u,v,w;
};

int n,m;
int cnt;
int Node[maxN];
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Dist[maxN];
bool vis[maxN];
int Cube[maxN][4];
priority_queue<Queue_Data> Q;

void Add_Edge(int u,int v,int w);

int main()
{
	int cas=0;
	while (cin>>n)
	{
		if (n==0)
			break;
		cnt=0;
		memset(Head,-1,sizeof(Head));
		for (int i=1;i<=n;i++)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			if (b<a)
				swap(a,b);
			if (c<a)
				swap(a,c);
			if (c<b)
				swap(b,c);
			Cube[i][1]=a;
			Cube[i][2]=b;
			Cube[i][3]=c;

			Cube[i+n][1]=b;
			Cube[i+n][2]=c;
			Cube[i+n][3]=a;

			Cube[i+n+n][1]=a;
			Cube[i+n+n][2]=c;
			Cube[i+n+n][3]=b;
		}
		/*
		for (int i=1;i<=n*3;i++)
			cout<<Cube[i][1]<<" "<<Cube[i][2]<<endl;
		cout<<endl;
		//*/
		for (int i=1;i<=n*3;i++)
			for (int j=1;j<=n*3;j++)
				if ((Cube[i][1]>Cube[j][1])&&(Cube[i][2]>Cube[j][2]))
					Add_Edge(i,j,Cube[j][3]);
		for (int i=1;i<=n*3;i++)
			Add_Edge(0,i,Cube[i][3]);
		/*
		for (int i=1;i<=cnt;i++)
			cout<<E[i].u<<" "<<E[i].v<<" "<<E[i].w<<endl;
		//*/
		memset(vis,0,sizeof(vis));
		memset(Dist,0,sizeof(Dist));
		Q.push((Queue_Data){0,0});
		int Ans=0;
		do
		{
			int u=Q.top().u;
			int di=Q.top().dist;
			Q.pop();
			if (vis[u]==1)
				continue;
			vis[u]=1;
			//cout<<"take:"<<u<<" "<<di<<endl;
			Ans=max(Ans,di);
			for (int i=Head[u];i!=-1;i=Next[i])
			{
				int v=E[i].v;
				if (di+E[i].w>Dist[v])
				{
					vis[v]=0;
					Dist[v]=di+E[i].w;
					Q.push((Queue_Data){v,Dist[v]});
				}
			}
		}
		while (!Q.empty());
		/*
		for (int i=1;i<=n*3;i++)
			cout<<Dist[i]<<" ";
		cout<<endl;
		//*/
		printf("Case %d: maximum height = %d\n",++cas,Ans); 
	}
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].w=w;
	return;
}
