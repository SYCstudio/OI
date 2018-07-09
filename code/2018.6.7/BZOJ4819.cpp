#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101*2;
const int maxM=maxN*maxN*2;
const ld eps=1e-9;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
	ld w;
};

int n;
int S,T;
int A[maxN][maxN],B[maxN][maxN];
int edgecnt,Head[maxN],Next[maxM],Path[maxN],Flow[maxN];
Edge E[maxM];
ld Dist[maxN];
bool inqueue[maxN];
queue<int> Q;

ld Calc(ld k);
void Add_Edge(int u,int v,int flow,ld w);
bool Spfa();

int main()
{
	ld L=inf,R=0,Ans;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&A[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&B[i][j]),L=min(L,(ld)1.0*A[i][j]/(1.0*B[i][j])),R=max(R,(ld)1.0*A[i][j]/(1.0*B[i][j]));

	do
	{
		//cout<<"("<<L<<","<<R<<")"<<endl;
		ld mid=(L+R)/2.0;
		if (Calc(mid)>=eps) Ans=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);
	printf("%.6LF\n",Ans);
	return 0;
}

ld Calc(ld k)
{
	edgecnt=-1;mem(Head,-1);
	S=n+n+1;T=S+1;
	for (int i=1;i<=n;i++) Add_Edge(S,i,1,0),Add_Edge(i+n,T,1,0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) Add_Edge(i,j+n,1,1.0*A[i][j]-1.0*B[i][j]*k);
	/*
	for (int i=1;i<=T;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if (E[j].flow) cout<<i<<" -> "<<E[j].v<<" "<<E[j].flow<<" "<<E[j].w<<endl;
	//*/
	ld Ret=0;
	while (Spfa())
	{
		Ret+=1.0*Dist[T]*Flow[T];
		int now=T;
		while (now!=S)
		{
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]].u;
		}
	}
	return Ret;
}

void Add_Edge(int u,int v,int flow,ld w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){u,v,flow,w});
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){v,u,0,-w});
	return;
}

bool Spfa()
{
	for (int i=1;i<=T;i++) Dist[i]=-inf;
	while (!Q.empty()) Q.pop();
	Dist[S]=0;Q.push(S);inqueue[S]=1;Flow[S]=inf;
	do
	{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow)&&(Dist[E[i].v]<Dist[u]+E[i].w))
			{
				//cout<<u<<"->"<<E[i].v<<endl;
				Dist[E[i].v]=Dist[u]+E[i].w;
				Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				if (inqueue[E[i].v]==0){
					Q.push(E[i].v);inqueue[E[i].v]=1;
				}
			}
		inqueue[u]=0;
	}
	while (!Q.empty());
	return Dist[T]!=-inf;
}
