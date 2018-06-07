#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxN=101;
const int maxM=maxN*maxN;
const int inf=2147483647;

int n,M;
class Graph
{
private:
	int cnt;
	int Head[maxN];
	int Next[maxM];
	int V[maxM];
	int W[maxM];
	bool vis[maxN];
public:
	int n;
	int Dist[maxN];
	int Value[maxN];
	int Status[maxN];
	void init()
	{
		cnt=0;
		memset(Head,-1,sizeof(Head));
		memset(Next,-1,sizeof(Next));
		memset(Dist,127,sizeof(Dist));
	}
	void Add_Edge(int u,int v,int w)
	{
		cnt++;
		Next[cnt]=Head[u];
		Head[u]=cnt;
		V[cnt]=v;
		W[cnt]=w;
	}
	int Dijkstra()
	{
		for (int i=1;i<=n;i++)
		    Dist[i]=Value[i];
		for (int i=1;i<n;i++)
		{
			int id=-1,mi=inf;
			for (int j=1;j<=n;j++)
                if ((vis[j]==0)&&(Dist[j]<mi))
                {
                    mi=Dist[j];
                    id=j;
                }
            if (id==-1)
                break;
            vis[id]=1;
            for (int i=Head[id];i!=-1;i=Next[i])
            {
                if ((vis[V[i]]==0)&&(Dist[V[i]]>Dist[id]+W[i]))
                {
                    Dist[V[i]]=Dist[id]+W[i];
                }
            }
		}
		return Dist[1];
	}
	int work()
	{
	    int Ans=inf;
	    for (int i=1;i<=n;i++)
        {
            int maxlv=Status[i];
            memset(vis,0,sizeof(vis));
            for (int j=1;j<=n;j++)
                if ((Status[j]>maxlv)||(maxlv-Status[j]>M))
                    vis[j]=1;
            Ans=min(Ans,Dijkstra());
        }
        return Ans;
	}
};

Graph G;

int main()
{
	G.init();
	cin>>M>>n;
	G.n=n;
	for (int i=1;i<=n;i++)
	{
		cin>>G.Value[i]>>G.Status[i];
		int tot;
		cin>>tot;
		for (int j=1;j<=tot;j++)
		{
			int u,w;
			cin>>u>>w;
			G.Add_Edge(u,i,w);
		}
	}
	cout<<G.work()<<endl;
	return 0;
}
