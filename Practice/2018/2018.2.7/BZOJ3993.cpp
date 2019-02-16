#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=120;
const int maxM=maxN/2*maxN/2*10;
const ld eps=1e-5;
const int inf=500000;

class Edge
{
public:
	int v;ld flow;
};

int n,m,S,T;
int A[maxN],B[maxN];
int sumA;
int Atta[51][51];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Queue[maxN],cur[maxN];

void Add_Edge(int u,int v,ld flow);
bool Check(ld tim);
bool Bfs();
ld dfs(int u,ld flow);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]),sumA+=A[i];
	for (int i=1;i<=m;i++) scanf("%d",&B[i]);
	S=n+m+1;T=n+m+2;
	for (int i=1;i<=m;i++) for (int j=1;j<=n;j++) scanf("%d",&Atta[i][j]);
	ld l=0,r=50100;
	ld Ans=0;
	do
	{
		ld mid=(l+r)/(ld)2;
		if (Check(mid)) Ans=mid,r=mid-eps;
		else l=mid+eps;
	}
	while (fabs(r-l)>=eps);
	printf("%.6LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,ld flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].flow=0;
	return;
}

bool Check(ld tim)
{
	edgecnt=-1;mem(Head,-1);
	for (int i=1;i<=n;i++) Add_Edge(i+m,T,(ld)A[i]);
	for (int i=1;i<=m;i++) Add_Edge(S,i,(ld)B[i]*tim);
	for (int i=1;i<=m;i++) for (int j=1;j<=n;j++) if (Atta[i][j]) Add_Edge(i,j+m,inf);
	ld mxflow=0;
	//cout<<edgecnt<<" "<<S<<" "<<T<<endl;
	/*
	for (int i=1;i<=T;i++)
	{
		cout<<i<<":"<<endl;
		for (int j=Head[i];j!=-1;j=Next[j]) cout<<i<<" "<<E[j].v<<" "<<E[j].flow<<endl;
		cout<<endl;
	}
	cout<<endl;
	//*/
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (1)
		{
			ld di=dfs(S,inf);
			mxflow+=di;
			if (fabs(di)<=eps) break;
		}
	}
	//cout<<"tim:"<<tim<<" mxflow:"<<mxflow<<endl;
	if (fabs(mxflow-sumA)<=eps) return 1;
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
		{
			if ((fabs(E[i].flow)>=eps)&&(Depth[E[i].v]==-1))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
		}
	}
	while (h!=t);
	//for (int i=1;i<=T;i++) cout<<Depth[i]<<" ";cout<<endl;
	if (Depth[T]==-1) return 0;
	return 1;
}

ld dfs(int u,ld flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((Depth[E[i].v]==Depth[u]+1)&&(fabs(E[i].flow)>eps))
		{
			ld di=dfs(E[i].v,min(flow,E[i].flow));
			if (fabs(di)>eps)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
