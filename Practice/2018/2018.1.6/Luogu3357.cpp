#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (((ll)x)*((ll)x))

const int maxLine=511;
const int maxNode=maxLine*2;
const int maxN=maxNode*2;
const int maxM=(maxN+maxLine)*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow;
    ll w;
};

class Line
{
public:
    int x1,y1,x2,y2;
    void check()
    {
	if (x1>x2) swap(x1,x2),swap(y1,y2);
	return;
    }
};

int n,K,S,T;
Line L[maxLine];
map<int,int> Map;
int numcnt=0,Num[maxNode];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
ll Dist[maxN];
int Queue[maxN],Flow[maxN],Path[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,ll w);
void _Add(int u,int v,int flow,ll w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&K);
    for (int i=1;i<=n;i++)
    {
	scanf("%d%d%d%d",&L[i].x1,&L[i].y1,&L[i].x2,&L[i].y2);L[i].check();
	if (Map[L[i].x1]==0) Map[L[i].x1]=1,Num[++numcnt]=L[i].x1;
	if (Map[L[i].x2]==0) Map[L[i].x2]=1,Num[++numcnt]=L[i].x2;
    }
    sort(&Num[1],&Num[numcnt+1]);S=numcnt*2+1;T=numcnt*2+2;
    for (int i=1;i<=numcnt;i++) Map[Num[i]]=i;
    for (int i=1;i<numcnt;i++) Add_Edge(i+numcnt,i+1,K,0);
    for (int i=1;i<=numcnt;i++) Add_Edge(i,i+numcnt,K,0);
    ll Ans=0;
    for (int i=1;i<=n;i++)
    {
	if (L[i].x1!=L[i].x2) Add_Edge(Map[L[i].x1]+numcnt,Map[L[i].x2],1,sqrt(sqr(L[i].x1-L[i].x2)+sqr(L[i].y1-L[i].y2)));
	else Add_Edge(Map[L[i].x1],Map[L[i].x2]+numcnt,1,sqrt(sqr(L[i].x1-L[i].x2)+sqr(L[i].y1-L[i].y2)));
	//cout<<sqrt(sqr(L[i].x1-L[i].x2)+sqr(L[i].y1-L[i].y2))<<endl;
    }
    Add_Edge(S,1,K,0);Add_Edge(numcnt*2,T,K,0);
    while (Spfa())
    {
	int now=T;
	//cout<<Flow[T]<<" "<<Dist[T]<<endl;
	while (now!=S)
	{
	    E[Path[now]].flow-=Flow[T];
	    E[Path[now]^1].flow+=Flow[T];
	    now=E[Path[now]].u;
	}
	Ans=Ans+(ll)Dist[T]*Flow[T];
    }
    printf("%lld\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int flow,ll w)
{
    _Add(u,v,flow,w);_Add(v,u,0,-w);
    return;
}

void _Add(int u,int v,int flow,ll w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].flow=flow;E[edgecnt].w=w;
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(inqueue,0);
    int h=1,t=0;Dist[S]=0;Queue[1]=S;inqueue[S]=1;Flow[S]=inf;
    do
    {
	t++;if (t>=maxN) t=0;
	int u=Queue[t];inqueue[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	    if ((E[i].flow>0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]<Dist[u]+E[i].w)))
	    {
		Dist[E[i].v]=Dist[u]+E[i].w;Path[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
		if (inqueue[E[i].v]==0)
		{
		    ++h;if (h>=maxN) h=0;
		    inqueue[Queue[h]=E[i].v]=1;
		}
	    }
    }
    while (t!=h);
    if (Dist[T]==-1) return 0;
    return 1;
}
