#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<string>
#include<vector>
#include<queue>
using namespace std;

const int maxN=2000;
const int inf=2147483647;

class Edge
{
public:
	int v,w;
};

int n1,n2,n3;//插座，转换器，电器
int n12;
int R1[maxN];
int R2[maxN];
int R3[maxN][3];
int G[maxN][maxN];
map<string,int> Map;
int Path[maxN];
int Flow[maxN];

bool bfs();

int main()
{
	int T;
	cin>>T;
	for (int ti=1;ti<=T;ti++)
	{
		Map.clear();
		memset(G,0,sizeof(G));
		scanf("%d",&n1);
		for (int i=1;i<=n1;i++)
		{
			string str;
			cin>>str;
			Map[str]=i;
			R1[i]=i;
		}
		n12=n1;
		scanf("%d",&n2);
		for (int i=1;i<=n2;i++)
		{
			string str;
			cin>>str;
			cin>>str;
			int k;
			if (Map[str]==0)
				k=Map[str]=++n1;
			else
				k=Map[str];
			R2[i]=k;
		}
		scanf("%d",&n3);
		for (int i=1;i<=n3;i++)
		{
			string str;
			cin>>str;
			if (Map[str]==0)
				Map[str]=++n1;
			R3[i][1]=Map[str];
			cin>>str;
			if (Map[str]==0)
				Map[str]=++n1;
			R3[i][2]=Map[str];
		}
		//cout<<n1<<' '<<n2<<' '<<n3<<endl;
		for (int i=1;i<=n12;i++)
			G[0][i]=1;
		for (int i=1;i<=n12;i++)
			for (int j=1;j<=n2;j++)
				if (R1[i]==R2[j])
				{
					G[i][j+n1]=inf;
				}
		for (int i=n12+1;i<=n1;i++)
			for (int j=1;j<=n2;j++)
				if (i==R2[j])
				{
					G[i][j+n1]=inf;
				}
		for (int i=1;i<=n3;i++)
			G[R3[i][2]][R3[i][1]]=inf;
		for (int i=1;i<=n2;i++)
			G[i+n1][n1+n2+1]=1;
		//for (int i=0;i<=n1+n2+1;i++)
		//{
		//		for (int j=0;j<=n1+n2+1;j++)
		//		cout<<G[i][j]<<' ';
		//	cout<<endl;
		//	}
		int Ans=0;
		while (bfs())
		{
			int di=Flow[n1+n2+1];
			int now=n1+n2+1;
			int last=Path[now];
			while (now!=0)
			{
				G[last][now]-=di;
				G[now][last]+=di;
				now=last;
				last=Path[now];
			}
			Ans+=di;
		}
		cout<<n2-Ans<<endl;
		if (ti!=T)
			cout<<endl;
	}
	return 0;
}

bool bfs()
{
	memset(Path,-1,sizeof(Path));
	memset(Flow,0,sizeof(Flow));
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	Q.push(0);
	Flow[0]=inf;
	Path[0]=0;
	do
	{
		int u=Q.front();
		Q.pop();
		for (int i=0;i<=n1+n2+1;i++)
			if ((Path[i]==-1)&&(G[u][i]>0))
			{
				Path[i]=u;
				Flow[i]=min(Flow[u],G[u][i]);
				Q.push(i);
			}
	}
	while (!Q.empty());
	if (Flow[n1+n2+1]==0)
		return 0;
	return 1;
}
