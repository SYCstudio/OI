#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;

const int maxN=30001;
const int maxM=150001;
const int inf=2147483647;

class Graph
{
private:
	int cnt;
	stack<int> S;
	int instack[maxN];
	int Head[maxN];
	int V[maxM];
	int W[maxM];
	int Next[maxM];
public:
	int Dist[maxN];
	void init()
	{
		memset(Head,-1,sizeof(Head));
		memset(Next,-1,sizeof(Next));
		cnt=0;
	}
	void Add_Edge(int u,int v,int w)
	{
		cnt++;
		Next[cnt]=Head[u];
		V[cnt]=v;
		W[cnt]=w;
		Head[u]=cnt;
	}
	void spfa()
	{
		memset(Dist,127,sizeof(Dist));
		memset(instack,0,sizeof(instack));
		while (!S.empty())
		    S.pop();
		Dist[1]=0;
		instack[1]=1;
		S.push(1);
		do
		{
			int u=S.top();
			S.pop();
			instack[u]=0;
			for (int i=Head[u];i!=-1;i=Next[i])
			{
				if (Dist[V[i]]>Dist[u]+W[i])
				{
					Dist[V[i]]=Dist[u]+W[i];
					if (instack[V[i]]==0)
					{
						S.push(V[i]);
						instack[V[i]]=1;
					}
				}
			}
		}
		while (!S.empty());
	}
};

int n,m;
Graph G;

int read();

int main()
{
	while (cin>>n>>m)
	{
		G.init();
		for (int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			G.Add_Edge(u,v,w);
		}
		G.spfa();
		cout<<G.Dist[n]<<endl;
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
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}
