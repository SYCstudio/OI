#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101*101*2;
const int maxM=maxN*100*2;
const int inf=2147483647;

#define pos(x,y) ((x-1)*m+(y-1)%m+1)
#define inpos(x) '['<<x/m+(int)(x%m!=0)<<','<<(x-1)%m+1<<']'

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int cnt;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Mat1[101][101];
int Mat2[101][101];
int Ans[101][101];
char str[10];
int cur[maxN];
int Q[maxN];
int depth[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	while (cin>>n>>m)
	{
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		memset(Mat1,-1,sizeof(Mat1));
		memset(Mat2,-1,sizeof(Mat2));
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				scanf("%s",str);
				if ((str[0]!='X')&&(str[0]!='.'))
					Mat1[i][j]=(str[0]-'0')*100+(str[1]-'0')*10+(str[2]-'0')*1;
				if ((str[4]!='X')&&(str[4]!='.'))
					Mat2[i][j]=(str[4]-'0')*100+(str[5]-'0')*10+(str[6]-'0')*1;
				if (str[0]=='.')
					Mat1[i][j]=0;
				if (str[4]=='.')
					Mat2[i][j]=0;
			}
		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				cout<<Mat1[i][j]<<'/'<<Mat2[i][j]<<" ";
			cout<<endl;
		}
		//*/
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (Mat1[i][j]>0)
				{
					int k=i+1;
					//cout<<'['<<i<<','<<j<<']'<<endl;
					while ((Mat1[k][j]==0)&&(k<=n))
					{
						//cout<<Mat1[k][j]<<endl;
						//cout<<"Add_Edge:"<<i<<" "<<j<<" "<<k<<" "<<j<<endl;
						Add_Edge(pos(i,j),pos(k,j),8);
						k=k+1;
					}
					Add_Edge(0,pos(i,j),Mat1[i][j]-(k-i)+1);
					//cout<<i<<" "<<j<<" "<<k<<" "<<Mat1[i][j]-(k-i)<<endl<<endl;
				}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (Mat2[i][j]>0)
				{
					int k=j+1;
					//cout<<'['<<i<<','<<j<<']'<<endl;
					while ((Mat2[i][k]==0)&&(k<=m))
					{
						Add_Edge(pos(i,k),pos(i,j)+n*m,8);
						//cout<<"Add_Edge:"<<i<<" "<<k<<" "<<i<<" "<<j<<endl;
						k=k+1;
					}
					Add_Edge(pos(i,j)+n*m,n*m*2+1,(Mat2[i][j]-(k-j)+1));
					//cout<<i<<" "<<j<<" "<<k<<" "<<Mat2[i][j]-(k-j)<<endl<<endl;
				}
		/*
		for (int i=0;i<=cnt;i++)
			if (E[i].flow>0)
				cout<<inpos(E[i].u)<<" -> "<<inpos(E[i].v)<<" "<<E[i].flow<<endl;
		//*/
		int Tot=0;
		while (bfs())
		{
			for (int i=0;i<=n*m*2+1;i++)
				cur[i]=Head[i];
			while (int di=dfs(0,inf))
				Tot+=di;
		}
		//cout<<Tot<<endl;
		for (int i=Head[0];i!=-1;i=Next[i])
		{
			int u=E[i].v;
			//cout<<inpos(u)<<" "<<E[i].flow<<endl;
			for (int j=Head[u];j!=-1;j=Next[j])
			{
				int v=E[j].v;
				int x=v/m+(int)(v%m!=0);
				int y=(v-1)%m+1;
				if ((v!=0)&&(E[j].flow<=8)&&(Mat1[x][y]==0))
				{
					//cout<<inpos(v)<<" "<<E[j].flow<<endl;
					Ans[x][y]=8-E[j].flow;
				}
			}
			//cout<<endl;
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				if (Mat1[i][j]!=0)
					printf("_ ");
				else
					printf("%d ",Ans[i][j]+1);
			printf("\n");
		}
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
	return;
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
	for (int &i=cur[u];i!=-1;i=Next[i])
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
