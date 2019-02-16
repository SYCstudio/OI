#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=105*2;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

class Mystring
{
public:
    char name[20];
};

bool operator < (Mystring A,Mystring B)
{
    return strcmp(A.name,B.name)>0;
}

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
map<Mystring,int> Map;
Mystring Name[maxN];
int Dist[maxN],Queue[maxM],Path[maxN],Flow[maxN];
bool vis[maxN];
int Stack[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&m);
    S=1,T=n+n;
    Mystring In1,In2;
    for (int i=1;i<=n;i++)
    {
	scanf("%s",Name[i].name);
	Map[Name[i]]=i;
    }
    for (int i=1;i<=m;i++)
    {
	scanf("%s %s",In1.name,In2.name);
	int id1=Map[In1],id2=Map[In2];
	if (id1>id2) swap(id1,id2);
	if (!((id1==1)&&(id2==n))) Add_Edge(id1+n,id2,1,1),Add_Edge(id2,id1+n,0,-1);
	else Add_Edge(id1+n,id2,2,1),Add_Edge(id2,id1+n,0,-1);
    }
    Add_Edge(1,1+n,2,0);Add_Edge(n+1,1,0,0);Add_Edge(n,n+n,2,0);Add_Edge(n+n,n,0,0);
    for (int i=2;i<n;i++) Add_Edge(i,i+n,1,0),Add_Edge(i+n,i,0,0);
    /*
    for (int i=0;i<=n;i++)
    {
	for (int j=Head[i];j!=-1;j=Next[j])
	    cout<<E[j].u<<" "<<E[j].v<<" "<<E[j].w<<" "<<E[i].flow<<endl;
	cout<<endl;
    }
    //*/
    int Ans=0,flowsum=0;
    while (Spfa())
    {
	int now=T;
	while (now!=S)
	{
	    E[Path[now]].flow-=Flow[T];
	    E[Path[now]^1].flow+=Flow[T];
	    now=E[Path[now]].u;
	}
	Ans+=Flow[T]*Dist[T];
	flowsum+=Flow[T];
    }
    if (flowsum<2) {printf("No Solution!\n");return 0;}
    else printf("%d\n",Ans);
    int st1=0,st2=0;
    for (int i=Head[1+n];i!=-1;i=Next[i])
	if ((E[i].v<=n)&&(E[i].flow==0)&&(E[i].w>0))
	{
	    if (st1==0) st1=E[i].v;
	    else {st2=E[i].v;break;}
	}
    //cout<<st1<<" "<<st2<<endl;
    int now=st1;
    printf("%s\n",Name[1].name);
    while (now!=n)
    {
	printf("%s\n",Name[now].name);
	now=now+n;
	for (int i=Head[now];i!=-1;i=Next[i])
	    if ((E[i].v<=n)&&(E[i].flow==0)&&(E[i].w>0))
	    {
		now=E[i].v;break;
	    }
    }
    printf("%s\n",Name[n].name);
    int stacktop=0;
    now=st2;
    while (now!=n)
    {
	Stack[++stacktop]=now;
	now=now+n;
	for (int i=Head[now];i!=-1;i=Next[i])
	    if ((E[i].v<=n)&&(E[i].flow==0)&&(E[i].w>0))
	    {
		now=E[i].v;break;
	    }
    }
    while (stacktop) printf("%s\n",Name[Stack[stacktop--]].name);
    printf("%s\n",Name[1].name);
    return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt]=((Edge){u,v,flow,w});
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(vis,0);
    int h=1,t=0;Queue[1]=S;Dist[S]=0;vis[S]=0;Flow[S]=inf;
    do
    {
	int u=Queue[++t];vis[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((E[i].flow>0)&&((Dist[v]==-1)||(Dist[v]<Dist[u]+E[i].w)))
	    {
		Dist[v]=Dist[u]+E[i].w;Path[v]=i;Flow[v]=min(Flow[u],E[i].flow);
		if (vis[v]==0) vis[Queue[++h]=v]=1;
	    }
	}
    }
    while (t!=h);
    if (Dist[T]==-1) return 0;
    return 1;
}
