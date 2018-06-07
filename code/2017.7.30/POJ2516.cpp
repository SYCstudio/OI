#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=300;
const int inf=2147483647;

int n,m,K;
int Path[maxN];
int Flow[maxN];
int Dist[maxN];
int ques[maxN][maxN];
int prov[maxN][maxN];
int G[maxN][maxN];
int C[maxN][maxN];
bool inqueue[maxN];

bool spfa();

int main()
{
	while (cin>>n>>m>>K)
	{
		if ((n==0)&&(m==0)&&(K==0))
			break;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=K;j++)
				scanf("%d",&ques[i][j]);
		for (int i=1;i<=m;i++)
			for (int j=1;j<=K;j++)
				scanf("%d",&prov[i][j]);
		int Ans=0;
		bool had_ans=1;
		for (int i=1;i<=K;i++)
		{
			int sum1=0;
			for (int j=1;j<=n;j++)
				sum1+=ques[j][i];
			int sum2=0;
			for (int j=1;j<=m;j++)
				sum2+=prov[j][i];
			if (sum2<sum1)
			{
				had_ans=0;
				break;
			}
		}
		for (int ki=1;ki<=K;ki++)
		{
			memset(G,0,sizeof(G));
			memset(C,0,sizeof(C));
			for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
				{
					scanf("%d",&C[i][j+n]);
					C[j+n][i]=-C[i][j+n];
					G[i][j+n]=inf;
				}
			if (had_ans==0)
				continue;
			for (int i=1;i<=n;i++)
				G[0][i]=ques[i][ki];
			for (int i=1;i<=m;i++)
				G[i+n][n+m+1]=prov[i][ki];
			/*for (int i=0;i<=n+m+1;i++)
			{
				for (int j=0;j<=n+m+1;j++)
					cout<<G[i][j]<<' ';
				cout<<endl;
			}
			cout<<endl;
			for (int i=0;i<=n+m;i++)
			{
				for (int j=0;j<=n+m;j++)
					cout<<C[i][j]<<' ';
				cout<<endl;
			}
			cout<<endl<<endl;*/
			int cost=0;
			int flow_ans=0;
			while (spfa())
			{
				int now=n+m+1;
				int last=Path[now];
				cost+=Flow[n+m+1]*Dist[n+m+1];
				while (now!=0)
				{
					G[last][now]-=Flow[n+m+1];
					G[now][last]+=Flow[n+m+1];
					now=last;
					last=Path[now];
				}
			}
			Ans+=cost;
		}
		if (had_ans)
		    cout<<Ans<<endl;
		else
			cout<<-1<<endl;
	}
	return 0;
}

bool spfa()
{
	memset(Dist,127,sizeof(Dist));
	memset(Path,-1,sizeof(Path));
	memset(Flow,0,sizeof(Flow));
	memset(inqueue,0,sizeof(inqueue));
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	Q.push(0);
	Dist[0]=0;
	Flow[0]=inf;
	do
	{
		int u=Q.front();
		inqueue[u]=0;
		Q.pop();
		for (int i=0;i<=n+m+1;i++)
		    if ((G[u][i]>0)&&(Dist[i]>Dist[u]+C[u][i]))
			{
				Dist[i]=Dist[u]+C[u][i];
				Path[i]=u;
				Flow[i]=min(Flow[u],G[u][i]);
				if (inqueue[i]==0)
				{
					Q.push(i);
					inqueue[i]=1;
				}
			}
	}
	while (!Q.empty());
	if (Path[n+m+1]==-1)
		return 0;
	return 1;
}
