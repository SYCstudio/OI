#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=800;
const int maxM=800;
const int inf=2147483647;

class Graph
{
private:
	int s,t;
	int cnt;
	int Head[maxN];
	int Next[maxM];
	int V[maxM];
	int W[maxM];
	int Depth[maxN];
	int cur[maxN];//当前流优化
public:
	int n;
	void init(int ss,int tt)
		{
			n=26*2;
			s=ss;
			t=tt;
			cnt=0;
			memset(Head,-1,sizeof(Head));
			memset(Next,-1,sizeof(Next));
			return;
		}
	void _Add(int u,int v,int w)
		{
			cnt++;
			Next[cnt]=Head[u];
			V[cnt]=v;
			W[cnt]=w;
			Head[u]=cnt;
		}
	void Add_Edge(int u,int v,int w)
		{
			_Add(u,v,w);
			_Add(v,u,0);
		}
	int dfs(int u,int dist)
		{
			//cout<<"Dfs:"<<u<<' '<<dist<<endl;
			if (u==t)
				return dist;
			for (int i=Head[u];i!=-1;i=Next[i])
			{
				if ((Depth[V[i]]==Depth[u]+1)&&(W[i]!=0))
				{
					int di=dfs(V[i],min(dist,W[i]));
					if (di>0)
					{
						W[i]-=di;
						W[(i%2==0)?(i-1):(i+1)]+=di;
						return di;
					}
				}
			}
			return 0;
		}
	int bfs()
		{
			//cout<<"Bfs.begin:"<<endl;
			queue<int> Q;
			while (!Q.empty())
				Q.pop();
			memset(Depth,0,sizeof(Depth));
			Depth[s]=1;
			Q.push(s);
			do
			{
				int u=Q.front();
				//cout<<u<<endl;
				Q.pop();
				for (int i=Head[u];i!=-1;i=Next[i])
				{
					if ((W[i]>0)&&(Depth[V[i]]==0))
					{
						Depth[V[i]]=Depth[u]+1;
						Q.push(V[i]);
					}
				}
			}
			while (!Q.empty());
			//cout<<"Bfs.end"<<endl;
			if (Depth[t]>0)
				return 1;
			return 0;
		}
	int Dinic()
		{
			int Ans=0;
			while (bfs())
			{
				while (int d=dfs(s,inf))
					Ans+=d;
			}
			return Ans;
		}
};

Graph G;

int main()
{
	G.init(1,26);
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		char A,B;
		int w;
		cin>>A>>B>>w;
		if ((A>='A')&&(A<='Z'))
			A=A-'A'+1;
		else
			A=A-'a'+27;
		if ((B>='A')&&(B<='Z'))
			B=B-'A'+1;
		else
			B=B-'a'+27;
		//cout<<(int)(A)<<' '<<(int)(B)<<endl;
		G.Add_Edge(A,B,w);
	}
	//G.Outp();
	cout<<G.Dinic()<<endl;
	return 0;
}
