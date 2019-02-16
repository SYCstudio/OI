#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y) ((x-1)*Q+y)

const int maxMap=40;
const int maxN=maxMap*maxMap*2;
const int maxM=maxN*3*2;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w,initflow;
};

int Car,P,Q,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Queue[maxN],Dist[maxN],Path[maxN],Flow[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,int w);
void _Add(int u,int v,int flow,int w);
bool Spfa();
void Outp(int x,int y);

int main()
{
    //freopen("outp.out","w",stdout);
    mem(Head,-1);
    scanf("%d%d%d",&Car,&Q,&P);S=P*Q*2+1;T=P*Q*2+2;
    for (int i=1;i<=P;i++)
	for (int j=1;j<=Q;j++)
	{
	    int opt;scanf("%d",&opt);
	    if (opt==1) continue;
	    Add_Edge(Id(i,j),Id(i,j)+P*Q,inf,0);
	    if (opt==2)	Add_Edge(Id(i,j),Id(i,j)+P*Q,1,1);
	    if (i!=P) Add_Edge(Id(i,j)+P*Q,Id(i+1,j),inf,0);
	    if (j!=Q) Add_Edge(Id(i,j)+P*Q,Id(i,j+1),inf,0);
	}
    Add_Edge(S,Id(1,1),Car,0);
    Add_Edge(Id(P,Q)+P*Q,T,Car,0);
    int Ans=0;
    while (Spfa())
    {
	int now=T;
	while (now!=S)
	{
	    E[Path[now]].flow-=Flow[T];
	    E[Path[now]^1].flow+=Flow[T];
	    now=E[Path[now]].u;
	}
	Ans+=Dist[T]*Flow[T];
    }
    for (int i=1;i<=Car;i++)
    {
	int h=0;
	int nowx=1,nowy=1;
	do
	{
	    int d0=Id(nowx+1,nowy),d1=Id(nowx,nowy+1);
	    for (int j=Head[Id(nowx,nowy)+P*Q];j!=-1;j=Next[j])
		if ((E[j].initflow-E[j].flow>0)&&(E[j].v<=Q*P))
		{
		    E[j].flow++;
		    if (E[j].v==d0)
		    {
			Queue[++h]=0;nowx++;
		    }
		    else
		    {
			Queue[++h]=1;nowy++;
		    }
		    //cout<<"("<<nowx<<","<<nowy<<") ";
		    break;
		}
	}
	while ((nowx!=P)||(nowy!=Q));
	//cout<<endl;
	for (int j=1;j<=h;j++) printf("%d %d\n",i,Queue[j]);
    }
}

void Add_Edge(int u,int v,int flow,int w)
{
    _Add(u,v,flow,w);_Add(v,u,0,-w);
    return;
}

void _Add(int u,int v,int flow,int w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].w=w;E[edgecnt].flow=flow;E[edgecnt].initflow=flow;
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(inqueue,0);
    int h=1,t=0;
    Queue[1]=S;Dist[S]=0;inqueue[S]=1;Flow[S]=inf;
    do
    {
	t++;if (t==maxN) t=0;int u=Queue[t];inqueue[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	    if ((E[i].flow)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]<Dist[u]+E[i].w)))
	    {
		Dist[E[i].v]=Dist[u]+E[i].w;Path[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
		if (inqueue[E[i].v]==0)
		{
		    h++;if (h==maxN) h=0;
		    inqueue[Queue[h]=E[i].v]=1;
		}
	    }
    }
    while (h!=t);
    if (Dist[T]==-1) return 0;
    return 1;
}
