#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=23;
const int maxN=maxMap*maxMap*maxMap;
const int maxM=maxN*10*2;
const int F1[4]={0,0,1,-1};
const int F2[4]={1,-1,0,0};
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m,S,T,doorcnt,pcnt;
char Input[maxMap][maxMap];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Queue[maxN],Id[maxMap][maxMap],cur[maxN];

bool Check(int mid);
void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) {if (Input[i][j]=='D') doorcnt++;if (Input[i][j]=='.') pcnt++;}
	int idcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt;
	int l=1,r=n*m+2;
	int Ans=-1;
	do
	{
		int mid=(l+r)/2;
		if (Check(mid)) Ans=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	if (Ans!=-1) printf("%d\n",Ans);
	else printf("impossible\n");
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].flow=0;
	return;
}

int Queue1[maxN],Queue2[maxN],Len[maxMap][maxMap],Tag[maxMap][maxMap];

bool Check(int mid)
{
	edgecnt=-1;mem(Head,-1);mem(Tag,0);
	int nodecnt=n*m;
	S=n*m+mid*doorcnt+1;
	T=n*m+mid*doorcnt+2;
	int dcnt=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (Input[i][j]=='X') continue;
			if (Input[i][j]=='.') Add_Edge(S,Id[i][j],1);
			if (Input[i][j]=='D')
			{
				int h=1,t=0;
				Queue1[1]=i;Queue2[1]=j;Len[i][j]=0;
				dcnt++;
				Tag[i][j]=dcnt;
				for (int de=1;de<=mid;de++)
				{
					Add_Edge(nodecnt+de,T,1);
					if (de!=mid) Add_Edge(nodecnt+de,nodecnt+de+1,inf);
				}
				do
				{
					t++;int x=Queue1[t],y=Queue2[t];
					if (Len[x][y]>mid) continue;
					Add_Edge(Id[x][y],nodecnt+Len[x][y],1);
					for (int o=0;o<4;o++)
						if ((Input[x+F1[o]][y+F2[o]]=='.')&&(Tag[x+F1[o]][y+F2[o]]!=dcnt))
						{
							Tag[x+F1[o]][y+F2[o]]=dcnt;
							Len[x+F1[o]][y+F2[o]]=Len[x][y]+1;
							h++;Queue1[h]=x+F1[o];Queue2[h]=y+F2[o];
						}
				}
				while (t!=h);
				nodecnt+=mid;
			}
		}
	int ret=0;
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) ret+=di;
	}
	if (ret==pcnt) return 1;
	return 0;
}

bool Bfs()
{
	mem(Depth,-1);
	int h=1,t=0;Queue[1]=S;Depth[S]=1;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
	}
	while (t!=h);
	if (Depth[T]==-1) return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
		{
			int di=dfs(E[i].v,min(flow,E[i].flow));
			if (di)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
