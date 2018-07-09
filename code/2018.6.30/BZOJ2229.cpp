#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=151;
const int maxM=6010;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m;
int S,T,Ans[maxN][maxN],Node[maxN],Tmp[maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Q[maxN],cur[maxN];
bool mark[maxN];

void Add_Edge(int u,int v,int w);
bool Bfs();
int dfs(int u,int flow);
void Divide(int l,int r);
void dfs_mark(int u);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		scanf("%d%d",&n,&m);
		//cout<<n<<" "<<m<<endl;
		edgecnt=-1;mem(Head,-1);
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Ans[i][j]=inf;
		for (int i=1;i<=n;i++) Ans[i][i]=0;

		for (int i=1;i<=m;i++)
		{
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			Add_Edge(u,v,w);
		}

		for (int i=1;i<=n;i++) Node[i]=i;
		Divide(1,n);

		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
				cout<<Ans[i][j]<<" ";
			cout<<endl;
		}
		//*/

		int QQQ;scanf("%d",&QQQ);
		while (QQQ--)
		{
			int x;scanf("%d",&x);
			int cnt=0;
			for (int i=1;i<=n;i++)
				for (int j=i+1;j<=n;j++)
					if (Ans[i][j]<=x) cnt++;
			printf("%d\n",cnt);
		}
		if (TTT) printf("\n");
	}
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,flow});
	return;
}

bool Bfs()
{
	mem(Depth,-1);Q[1]=S;Depth[S]=1;
	int h=1,t=0;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

int dfs(int u,int flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow))){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}

void Divide(int l,int r)
{
	//cout<<"Divide:"<<l<<" "<<r<<endl;
	//for (int i=l;i<=r;i++) cout<<Node[i]<<" ";cout<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	S=Node[l];T=Node[r];
	for (int i=0;i<=edgecnt;i+=2) E[i].flow=E[i^1].flow=(E[i].flow+E[i^1].flow)/2;
	int mxflow=0;
	mem(cur,-1);
	while (Bfs())
	{
		for (int i=1;i<=n;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) mxflow+=di;
	}

	mem(mark,0);
	dfs_mark(S);

	//cout<<mxflow<<endl;
	//for (int i=1;i<=n;i++) cout<<mark[i]<<" ";cout<<endl;
	
	for (int i=1;i<=n;i++)
		if (mark[i]==1)
			for (int j=1;j<=n;j++)
				if (mark[j]==0)
				{
					//cout<<"("<<i<<","<<j<<") ";
					Ans[i][j]=Ans[j][i]=min(Ans[i][j],mxflow);
				}
	//cout<<endl;
	
	int ql=l-1,qr=r+1;
	for (int i=l;i<=r;i++)
		if (mark[Node[i]]) Tmp[++ql]=Node[i];
		else Tmp[--qr]=Node[i];
	for (int i=l;i<=r;i++) Node[i]=Tmp[i];
	Divide(l,ql);Divide(qr,r);
	return;
}

void dfs_mark(int u)
{
	mark[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(mark[E[i].v]==0)) dfs_mark(E[i].v);
	return;
}
/*
1
5 3
1 2 2
1 3 3
2 3 3
4
10
5
9
2
*/
