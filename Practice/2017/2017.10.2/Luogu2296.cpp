#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int maxN=10100;
const int maxM=201000;
const int inf=2147483647;
const int meminf=2139062143;

int n,m;
int Q[maxM*4];
bool vis[maxN];

class Graph
{
public:
	int cnt;
	int Head[maxN];
	int V[maxM];
	int Next[maxM];
	int Dist[maxN];
	Graph()
		{
			cnt=0;
			memset(Head,-1,sizeof(Head));
			return;
		}
	void Add(int u,int v)
		{
			cnt++;
			Next[cnt]=Head[u];
			Head[u]=cnt;
			V[cnt]=v;
			return;
		}
	void spfa(int s)
		{
			memset(Dist,127,sizeof(Dist));
			memset(vis,0,sizeof(vis));
			int h=1,t=0;
			Q[1]=s;
			Dist[s]=0;
			vis[s]=1;
			do
			{
				t++;
				int u=Q[t];
				for (int i=Head[u];i!=-1;i=Next[i])
				{
					int v=V[i];
					if (Dist[v]>Dist[u]+1)
					{
						Dist[v]=Dist[u]+1;
						if (vis[v]==0)
						{
							h++;
							Q[h]=v;
							vis[v]=1;
						}
					}
				}
				vis[u]=0;
			}
			while (h>t);
			return;
		}
};

int S,T;
Graph G,unG,G2;
bool is_to_t[maxN];

int main()
{
	freopen("roadb.in","r",stdin);
	freopen("roadb.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G2.Add(u,v);
		unG.Add(v,u);
	}
	
	scanf("%d%d",&S,&T);
	unG.spfa(T);
	
	memset(is_to_t,0,sizeof(is_to_t));
	for (int i=1;i<=n;i++)
	{
		is_to_t[i]=1;
		if (unG.Dist[i]==meminf)
		{
			is_to_t[i]=0;
			continue;
		}
		for (int j=G2.Head[i];j!=-1;j=G2.Next[j])
		{
			int v=G2.V[j];
			if (unG.Dist[v]==meminf)
			{
				is_to_t[i]=0;
				break;
			}
		}
	}

	/*
	for (int i=1;i<=n;i++)
		cout<<is_to_t[i]<<" ";
	cout<<endl;
	//*/
	
	for (int i=1;i<=n;i++)
		if (is_to_t[i]==1)
		    for (int j=unG.Head[i];j!=-1;j=unG.Next[j])
			{
				int v=unG.V[j];
				if (is_to_t[v]==1)
					G.Add(v,i);
			}

	G.spfa(S);
	if ((G.Dist[T]==meminf)||(is_to_t[S]==0))
		printf("-1\n");
	else
		printf("%d\n",G.Dist[T]);
	return 0;
}
