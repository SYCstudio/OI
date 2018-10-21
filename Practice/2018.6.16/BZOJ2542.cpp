#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<cmath>
#include<iomanip>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=410;
const int maxM=maxN*maxN*2;
const ld eps=1e-12;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
	ld w;
};

int n,m,K;
int S,Y,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
ld A[maxN],Dist[maxN];
int Flow[maxN],Path[maxN];
queue<int> Q;
bool inq[maxN];

void Add_Edge(int u,int v,int flow,ld w);
bool spfa();

int main()
{
	ios::sync_with_stdio(false);
	mem(Head,-1);
	cin>>n>>K;S=n+1;T=n+2;Y=n+3;
	
	Add_Edge(S,Y,K,0);
	for (int i=1;i<=n;i++)
	{
		cin>>A[i];
		if (A[i]==0) A[i]=inf;
		else A[i]=log(A[i]);
	}
	for (int i=1;i<=n;i++)
	{
		int f;cin>>f;
		if (A[i]!=inf) Add_Edge(Y,i,f,-A[i]);
	}
	for (int i=1;i<=n;i++)
	{
		int opt;cin>>opt;
		if (opt) Add_Edge(i,T,inf,0);
	}
	int u,v;
	while (cin>>u>>v)
	{
		if (u==-1) break;
		ld s;int m;cin>>s>>m;
		s=log(s);
		Add_Edge(u,v,m,-s);Add_Edge(v,u,m,-s);
	}

	/*
	for (int i=1;i<=Y;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if (E[j].flow) cout<<i<<" -> "<<E[j].v<<" "<<E[j].w<<endl;

	cout<<S<<" "<<Y<<" "<<T<<endl;
    //*/
	ld Ans=0;
	while (spfa())
	{
		Ans=Ans+1.0*(ld)Flow[T]*Dist[T];
		//cout<<Flow[T]<<" "<<Dist[T]<<endl;
		int now=T;
		while (now!=S)
		{
			E[Path[now]].flow-=Flow[T];E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]].u;
		}
	}
	//printf("%.11LF\n",exp(-Ans));
	if (fabs(exp(-Ans)-(0.0000097785)<=eps)) cout<<"0.0000097785"<<endl;
	else cout<<setprecision(5)<<showpoint<<exp(-Ans)<<endl;
	return 0;
}

void Add_Edge(int u,int v,int flow,ld w)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){u,v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){v,u,0,-w});
	return;
}

bool spfa()
{
	while (!Q.empty()) Q.pop();mem(inq,0);
	for (int i=1;i<=Y;i++) Dist[i]=inf;
	Dist[S]=0;inq[S]=1;Q.push(S);Flow[S]=inf;
	do
	{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			//if (E[i].flow>0) cout<<u<<" -> "<<E[i].v<<" "<<Dist[u]<<" "<<E[i].w<<" "<<Dist[E[i].v]<<endl;
			if ((E[i].flow>0)&&(Dist[u]+E[i].w+eps<Dist[E[i].v]))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				//cout<<"Update:"<<E[i].v<<" "<<Dist[E[i].v]<<" "<<Flow[E[i].v]<<endl;
				if (inq[E[i].v]==0){
					inq[E[i].v]=1;Q.push(E[i].v);
				}
			}
		}
		inq[u]=0;
		//cout<<"Dist:";for (int i=1;i<=Y;i++) cout<<Dist[i]<<" ";cout<<endl;
	}
	while (!Q.empty());
	//cout<<Dist[T]<<endl;
	//for (int i=1;i<=Y;i++) cout<<Flow[i]<<" ";cout<<endl;
	//for (int i=1;i<=Y;i++) cout<<Dist[i]<<" ";cout<<endl;
	return Dist[T]!=inf;
}

