#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define pos(x,y) ((x-1)*m+y)
#define inpos(x) '['<<x<<']'<<'('<<(x/m)+(int)(!(x%m==0))<<','<<(x-1)%m+1<<')'

const int maxN=2001;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int D;
int Lizards;
int cnt;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxN];
char str1[maxN][maxN];
char str[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	int T;
	scanf("%d",&T);
	for (int ti=1;ti<=T;ti++)
	{
		Lizards=0;
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		scanf("%d%d",&n,&D);
		cin>>str1[1];
		m=strlen(str1[1]);
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<m;j++)
				if (str1[i][j]!='0')
					Add_Edge(pos(i,j+1),pos(i,j+1)+n*m,str1[i][j]-'0');
			if (i!=n)
				cin>>str1[i+1];
		}
		for (int i=1;i<=n;i++)
		{
			cin>>str;
			for (int j=0;j<m;j++)
				if (str[j]=='L')
				{
					Lizards++;
					Add_Edge(0,pos(i,j+1),1);
				}
		}
		/*
		for (int i=1;i<=n*m*2;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
				if (E[j].v!=flow)
					cout<<inpos(i)<<"->"<<inpos(E[j].v)<<" "<<E[j].flow<<endl;
		}
		//*/
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (str1[i][j-1]!='0')
				{
					if ((i<=D)||(j<=D)||(n-i+1<=D)||(m-j+1<=D))
					{
						Add_Edge(pos(i,j)+n*m,n*m*2+1,inf);
						//continue;
					}
					for (int x=max(i-D,1);x<=min(i+D,n);x++)
						for (int y=max(j-D,1);y<=min(j+D,m);y++)
						{
							if ((x==i)&&(j==y))
								continue;
							if (str1[x][y-1]=='0')
								continue;
							if (abs(x-i)+abs(y-j)<=D)
								Add_Edge(pos(i,j)+n*m,pos(x,y),inf);
						}
				}
		/*
		for (int i=0;i<=n*m*2;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
				if (E[j].flow!=0)
					cout<<inpos(i)<<"->"<<inpos(E[j].v)<<" "<<E[j].flow<<endl;
		}
		//*/
		int Ans=0;
		while (bfs())
		{
			for (int i=0;i<=n*m*2+1;i++)
				cur[i]=Head[i];
			while (int di=dfs(0,inf))
				Ans+=di;
		}
		Ans=Lizards-Ans;
		printf("Case #%d: ",ti);
		if (Ans==0)
			printf("no lizard was left behind.\n");
		else
			if (Ans==1)
				printf("1 lizard was left behind.\n");
			else
				printf("%d lizards were left behind.\n",Ans);
		//printf("%d\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].flow=flow;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].u=v;
	E[cnt].v=u;
	E[cnt].flow=0;
}

bool bfs()
{
	memset(depth,-1,sizeof(depth));
	int h=1,t=0;
	Q[1]=0;
	depth[0]=1;
	do
	{
		t++;
		int u=Q[t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((depth[v]==-1)&&(E[i].flow>0))
			{
				depth[v]=depth[u]+1;
				h++;
				Q[h]=v;
			}
		}
	}
	while (t!=h);
	if (depth[n*m*2+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==n*m*2+1)
		return flow;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if ((depth[v]==depth[u]+1)&&(E[i].flow>0))
		{
			int di=dfs(v,min(flow,E[i].flow));
			if (di>0)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	}
	return 0;
}
