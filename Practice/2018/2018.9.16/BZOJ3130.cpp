#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int maxM=1010*2;
const ld eps=1e-8;
const int inf=2147483647;

class Edge
{
public:
	int v;
	ld flow,mx;
};

int n,m,P;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
ld Calc(ld limit);
bool Bfs();
ld dfs(int u,ld flow);

int main(){
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&P);
	int mxf=0;
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);mxf=max(mxf,w);
	}

	ld flow=Calc(inf);

	ld L=0,R=mxf,ans=mxf;
	do{
		ld mid=(L+R)/2;
		//cout<<mid<<" "<<Calc(mid)<<" "<<flow<<endl;
		if (fabs(Calc(mid)-flow)<eps) ans=mid,R=mid-eps;
		else L=mid+eps;
	}
	while (L+eps<=R);

	//cout<<ans<<endl;
	printf("%.0lf\n%.4lf\n",flow,ans*P);

	return 0;
}

void Add_Edge(int u,int v,int flow){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,0});
	return;
}

ld Calc(ld limit){
	for (int i=0;i<=edgecnt;i++) E[i].flow=min(E[i].mx,limit);
	ld flow=0;
	while (Bfs()){
		for (int i=1;i<=n;i++) cur[i]=Head[i];
		do{
			ld di=dfs(1,inf);
			if (di<eps) break;
			flow+=di;
		}
		while (1);
	}
	return flow;
}

bool Bfs(){
	mem(Depth,-1);
	Q[1]=1;Depth[1]=1;int h=1,t=0;
	do for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
		   if ((E[i].flow>eps)&&(Depth[E[i].v]==-1))
			   Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[n]!=-1;
}

ld dfs(int u,ld flow){
	if (u==n) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>eps)&&(Depth[E[i].v]==Depth[u]+1)){
			ld di=dfs(E[i].v,min(flow,E[i].flow));
			if (di>eps){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
