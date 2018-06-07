#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define ll long long

const int maxN=1000001;
const int maxM=1000001;
const int inf=2147483647;

class Edge
{
public:
	int v;
	long long w;
};

class Graph
{
public:
	int Head[maxN];
	ll Dist[maxN];
	int Next[maxM];
	int V[maxM];
	ll W[maxM];
private:
	int cnt;
	bool inqueue[maxN];
	queue<int> Q;
public:
	void init()
	{
		cnt=0;
		memset(Head,-1,sizeof(Head));
		memset(Next,-1,sizeof(Next));
		return;
	}
	void Add(int u,int v,int w)
	{
		cnt++;
		V[cnt]=v;
		W[cnt]=w;
		Next[cnt]=Head[u];
		Head[u]=cnt;
		return;
	}
	void spfa(int S)
	{
		memset(Dist,127,sizeof(Dist));
		Dist[S]=0;
		memset(inqueue,0,sizeof(inqueue));
		while (!Q.empty())
		    Q.pop();
		Q.push(1);
		inqueue[1]=1;
		do
		{
			int u=Q.front();
			Q.pop();
			inqueue[u]=0;
			for (int i=Head[u];i!=-1;i=Next[i])
			{
				if (Dist[V[i]]>Dist[u]+W[i])
				{
					Dist[V[i]]=Dist[u]+W[i];
					if (inqueue[V[i]]==0)
					{
						Q.push(V[i]);
						inqueue[V[i]]=1;
					}
				}
			}
		}
		while (!Q.empty());
		return;
	}
};


int n,m;
Graph G1,G2;

int read();

int main()
{
	int T=read();
	for (int ti=1;ti<=T;ti++)
	{
		n=read();m=read();
		G1.init();
		G2.init();
		for (int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			G1.Add(u,v,w);
			G2.Add(v,u,w);
		}
		//spfa-1
		G1.spfa(1);
		G2.spfa(1);
		ll Sum=0;
		for (int i=1;i<=n;i++)
		    Sum+=G1.Dist[i]+G2.Dist[i];
		cout<<Sum<<endl;
	}
	return 0;
}

int read()
{
	int x=0;
	int k=1;
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!='-'))
	    ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch<='9')&&(ch>='0'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}
