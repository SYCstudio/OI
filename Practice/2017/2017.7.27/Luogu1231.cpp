#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=10010*10;
const int maxM=20010*10;
const int inf=2147483647;

int n1,n2,n3,m1,m2;

class Graph
{
private:
	int cnt;
	int Head[maxN];
	int Next[maxM];
	int W[maxM];
	int V[maxM];
	int Depth[maxN];
	int cur[maxN];
public:
	int s,t;
	void init()
		{
			cnt=-1;
			memset(Head,-1,sizeof(Head));
			memset(Next,-1,sizeof(Next));
		}
	void _Add(int u,int v,int w)
		{
			cnt++;
			Next[cnt]=Head[u];
			Head[u]=cnt;
			V[cnt]=v;
			W[cnt]=w;
		}
	void Add_Edge(int u,int v,int w)
		{
			_Add(u,v,w);
			_Add(v,u,0);
		}
	int dfs(int u,int flow)
		{
			if (u==t)
				return flow;
			for (int& i=cur[u];i!=-1;i=Next[i])
			{
				if ((Depth[V[i]]==Depth[u]+1)&&(W[i]!=0))
				{
					int di=dfs(V[i],min(flow,W[i]));
					if (di>0)
					{
						W[i]-=di;
						W[i^1]+=di;
						return di;
					}
				}
			}
			return 0;
		}
	int bfs()
		{
			queue<int> Q;
			while (!Q.empty())
				Q.pop();
			memset(Depth,0,sizeof(Depth));
			Depth[s]=1;
			Q.push(s);
			do
			{
				int u=Q.front();
				Q.pop();
				for (int i=Head[u];i!=-1;i=Next[i])
					if ((Depth[V[i]]==0)&&(W[i]>0))
					{
						Depth[V[i]]=Depth[u]+1;
						Q.push(V[i]);
					}
			}
			while (!Q.empty());
			if (Depth[t]>0)
				return 1;
			return 0;
		}
	int Dinic()
		{
			int Ans=0;
			while (bfs())
			{
				for (int i=1;i<=n2+n1*2+n3+2;i++)
					cur[i]=Head[i];
				while (int d=dfs(s,inf))
				{
					Ans+=d;
					//cout<<d<<endl;
				}
			}
			return Ans;
		}
	void Outp()
		{
			for (int i=1;i<=n2+n1*2+n3+2;i++)
			{
				for (int j=Head[i];j!=-1;j=Next[j])
					cout<<"("<<i<<","<<V[j]<<") "<<W[j]<<endl;
				cout<<endl;
			}
		}
};

Graph G;

int read();

int main()
{
	G.init();
	n1=read();
	n2=read();
	n3=read();
	for (int i=1;i<=n1;i++)
		G.Add_Edge(n2+i,n2+n1+i,1);
	for (int i=1;i<=n2;i++)
		G.Add_Edge(n2+2*n1+n3+1,i,1);
	for (int i=1;i<=n3;i++)
		G.Add_Edge(n2+2*n1+i,n2+2*n1+n3+2,1);
	G.s=n2+2*n1+n3+1;
	G.t=n2+2*n1+n3+2;
	m1=read();
	for (int i=1;i<=m1;i++)
	{
		int u=read(),v=read();
		G.Add_Edge(v,n2+u,1);
	}
	m2=read();
	for (int i=1;i<=m2;i++)
	{
		int u=read(),v=read();
		G.Add_Edge(n2+n1+u,n2+2*n1+v,1);
	}
	//G.Outp();
	cout<<G.Dinic()<<endl;
	return 0;
}

int read()
{
	int x=0;
	int k=1;
	char ch=getchar();
	while (((ch<'0')||(ch>'9'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}
