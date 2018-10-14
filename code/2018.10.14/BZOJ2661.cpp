#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int maxM=maxN*50;
const int inf=2147483647;

class Edge
{
public:
	int v,flow,w;
};

int n,a,b;
int S,T;
int idcnt,Id[maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN],Flow[maxN],Path[maxN];
queue<int> Q;
bool inq[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main(){
	mem(Head,-1);
	scanf("%d%d",&a,&b);
	for (int i=a;i<=b;i++) Id[i]=++idcnt,++idcnt;
	S=idcnt+1;T=idcnt+2;
	for (int i=a;i<=b;i++) Add_Edge(S,Id[i],1,0),Add_Edge(Id[i]+1,T,1,0);
	for (int i=a;i<=b;i++)
		for (int j=a;j<i;j++){
			int x=sqrt(i*i-j*j);
			if ((x*x==i*i-j*j)&&(__gcd(x,j)==1)){
				Add_Edge(Id[i],Id[j]+1,1,i+j);
				Add_Edge(Id[j],Id[i]+1,1,i+j);
			}
		}

	int Ans=0,flow=0;
	while (Spfa()){
		Ans+=Flow[T]*Dist[T];flow+=Flow[T];
		int now=T;
		while (now!=S){
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]^1].v;
		}
	}
	printf("%d %d\n",flow/2,Ans/2);return 0;
}

void Add_Edge(int u,int v,int flow,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,-w});
	return;
}

bool Spfa(){
	for (int i=1;i<=T;i++) Dist[i]=-inf;mem(inq,0);while (!Q.empty()) Q.pop();
	Dist[S]=0;inq[S]=1;Q.push(S);Flow[S]=inf;
	do{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow)&&(Dist[E[i].v]<Dist[u]+E[i].w)){
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				if (inq[E[i].v]==0){
					inq[E[i].v]=1;Q.push(E[i].v);
				}
			}
		inq[u]=0;
	}
	while (!Q.empty());
	return Dist[T]!=-inf;
}
