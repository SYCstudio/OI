#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int maxM=maxN*maxN*4;
const int maxW=2010;
const int maxL=201;
const int inf=47483647;

class Edge
{
public:
	int v,cnt;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],Degree[maxN];
Edge E[maxM];
int Limit[maxN],Cost[maxN],W[maxN];
bool Leaf[maxN];
int F[maxN][maxL][maxW];
int G[maxN][maxW],H[maxN][maxW];

void Add_Edge(int u,int v,int cnt);
void dfs(int u);

int main()
{
	ios::sync_with_stdio(false);
	mem(Head,-1);mem(F,-0x3f3f3f3f);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		char opt;cin>>W[i]>>opt;
		if (opt=='A')
		{
			int C;cin>>C;
			while (C--)
			{
				int v,cnt;cin>>v>>cnt;
				Add_Edge(i,v,cnt);
				Leaf[i]=0;
			}
		}
		if (opt=='B')
		{
			cin>>Cost[i]>>Limit[i];
			Limit[i]=min(Limit[i],m/Cost[i]);
			Leaf[i]=1;
		}
	}
	int tot=0;
	for (int node=1;node<=n;node++)
		if (Degree[node]==0)
		{
			dfs(node);
			tot++;
			for (int i=0;i<=m;i++)//枚举花多少钱
				for (int j=0;j<=i;j++)//枚举这i元钱中有多少从上一次转移过来
					for (int k=0;k<=Limit[node];k++)//枚举这一次node号选择合成多少个
						H[tot][i]=max(H[tot][i],H[tot-1][j]+F[node][k][i-j]);
		}
	int Ans=0;
	for (int i=0;i<=m;i++) Ans=max(Ans,H[tot][i]);
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int cnt)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].cnt=cnt;
	Degree[v]++;
	return;
}

void dfs(int u)
{
	//cout<<"u:"<<u<<endl;
	if (Leaf[u]==1)//叶子节点
	{
		//cout<<"Leaf:"<<u<<endl;
		for (int i=0;i<=Limit[u];i++)//枚向上贡献多少个
			for (int j=i;j<=Limit[u];j++)//枚举总共多少个，那么j-i就是自己保留的个数
				F[u][i][j*Cost[u]]=W[u]*(j-i);
		return;
	}
	Limit[u]=inf;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		dfs(E[i].v);
		Cost[u]+=Cost[E[i].v]*E[i].cnt;
		Limit[u]=min(Limit[u],Limit[E[i].v]/E[i].cnt);
	}
	Limit[u]=min(Limit[u],m/Cost[u]);
	//for (int i=0;i<maxN;i++) for (int j=0;j<maxW;j++) G[i][j]=-inf;
	mem(G,-0x3f3f3f3f);
	G[0][0]=0;
	for (int l=Limit[u];l>=0;l--)
	{
		int tot=0;
		for (int e=Head[u];e!=-1;e=Next[e])
		{
			tot++;
			for (int i=0;i<=m;i++)//枚举这一次总共花多少钱
				for (int j=0;j<=i;j++)//枚举从这一棵子树转移过来多少钱，那么i-j就是从前面的子树转移过来的
					G[tot][i]=max(G[tot][i],G[tot-1][i-j]+F[E[e].v][l*E[e].cnt][j]);
		}
		for (int i=0;i<=l;i++)
			for (int j=0;j<=m;j++)
				F[u][i][j]=max(F[u][i][j],G[tot][j]+(l-i)*W[u]);
	}
	return;
}
