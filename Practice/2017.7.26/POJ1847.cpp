#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=201;
const int maxM=maxN*maxN;
const int inf=2147483647;

int n;

class Graph
{
private:
	int cnt;
	int Head[maxN];
	int W[maxM];
	int Next[maxM];
	int V[maxM];
	//priority_queue<Data,vector<Data>,greater<Data> > Q;
	queue<int> Q;
	bool inqueue[maxN];
public:
	int s,t;
	int Dist[maxN];
	void init()
		{
			cnt=0;
			memset(Head,-1,sizeof(Head));
			memset(Next,-1,sizeof(Next));
		}
	void Add_Edge(int u,int v,int w)
		{
			cnt++;
			Next[cnt]=Head[u];
			Head[u]=cnt;
			V[cnt]=v;
			W[cnt]=w;
		}
	void spfa()
		{
			while (!Q.empty())
				Q.pop();
			for (int i=1;i<=n;i++)
				Dist[i]=inf;
			memset(inqueue,0,sizeof(inqueue));
			Dist[s]=0;
			Q.push(s);
			inqueue[s]=1;
			do
			{
				int u=Q.front();
				Q.pop();
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
				inqueue[u]=0;
			}
			while (!Q.empty());
			return;
		}
	void Outp()
		{
			for (int i=1;i<=n;i++)
			{
				for (int j=Head[i];j!=-1;j=Next[j])
				{
					cout<<"("<<i<<","<<V[j]<<") "<<W[j]<<endl;
				}
				cout<<endl;
			}
		}
};

Graph G;

int main()
{
	G.init();
	cin>>n>>G.s>>G.t;
	for (int i=1;i<=n;i++)
	{
		int T;
		cin>>T;
		int v;
		cin>>v;
		G.Add_Edge(i,v,0);
		if (T<2)
			continue;
		for (int j=2;j<=T;j++)
		{
			cin>>v;
			G.Add_Edge(i,v,1);
		}
	}
	//G.Outp();
	G.spfa();
	if (G.Dist[G.t]==inf)
		cout<<-1<<endl;
	else
		cout<<G.Dist[G.t]<<endl;
	return 0;
}
