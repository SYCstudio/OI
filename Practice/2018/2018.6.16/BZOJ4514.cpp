#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int maxM=maxN*maxN*30;
const int inf=2147483647;
const ll INF=1e17;

class Edge
{
public:
	int u,v,flow;
	ll w;
};

int n;
int A[maxN],B[maxN];
ll C[maxN];
int Cnt[maxN];
int S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
ll Dist[maxN],Flow[maxN],Path[maxN];
bool inq[maxN];
queue<int> Q;

int Frac(int x);
void Add_Edge(int u,int v,int flow,ll w);
bool spfa();

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]),Cnt[i]=Frac(A[i]);
	for (int i=1;i<=n;i++) scanf("%d",&B[i]);
	for (int i=1;i<=n;i++) scanf("%lld",&C[i]);

	//for (int i=1;i<=n;i++) cout<<Cnt[i]<<" ";cout<<endl;

	S=n+1;T=n+2;
	for (int i=1;i<=n;i++)
		if (Cnt[i]&1) Add_Edge(S,i,B[i],0);
		else Add_Edge(i,T,B[i],0);
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if ((A[i]%A[j]==0)&&(Cnt[i]==Cnt[j]+1)){
				if (Cnt[i]&1) Add_Edge(i,j,inf,C[i]*C[j]);
				else Add_Edge(j,i,inf,C[i]*C[j]);
			}

	/*
	for (int i=1;i<=T;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if (E[j].flow)
				cout<<i<<" -> "<<E[j].v<<" "<<E[j].w<<endl;
	//*/

	ll flow=0,sum=0;
	while (spfa())
	{
		if (sum+Flow[T]*Dist[T]<0)
		{
			flow+=(ll)(sum/(-Dist[T]));
			break;
		}
		flow+=Flow[T];sum+=Flow[T]*Dist[T];
		int now=T;
		while (now!=S)
		{
			E[Path[now]].flow-=Flow[T];E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]].u;
		}
	}

	printf("%lld\n",flow);
	
	return 0;
}

int Frac(int x)
{
	int ret=0;
	for (int i=2;i<=sqrt(x);i++)
		while (x%i==0) x/=i,ret++;
	if (x!=1) ret++;
	return ret;
}

void Add_Edge(int u,int v,int flow,ll w)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){u,v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){v,u,0,-w});
	return;
}

bool spfa()
{
	while (!Q.empty()) Q.pop();mem(inq,0);
	for (int i=1;i<=T;i++) Dist[i]=-INF;
	Dist[S]=0;Flow[S]=inf;Q.push(S);inq[S]=1;
	do
	{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Dist[E[i].v]<Dist[u]+E[i].w))
			{
				//cout<<"Update:"<<u<<" -> "<<E[i].v<<" "<<Dist[u]<<" "<<E[i].w<<" "<<Dist[E[i].v]<<endl;
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],(ll)E[i].flow);Path[E[i].v]=i;
				if (inq[E[i].v]==0){
					inq[E[i].v]=1;Q.push(E[i].v);
				}
			}
		inq[u]=0;
	}
	while (!Q.empty());
	//for (int i=1;i<=T;i++) cout<<Dist[i]<<" ";cout<<endl;
	return Dist[T]!=-INF;
}
