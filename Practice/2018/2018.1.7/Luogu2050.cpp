#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxPeople=41;
const int maxCook=101;
const int maxP=810;
const int maxN=maxP+maxP*maxCook;
const int maxM=(maxP+maxCook+maxP*maxCook)*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

int n,m,S,T;
int Pi[maxPeople];
int Tim[maxPeople][maxCook];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN],Queue[maxN],Flow[maxN],Path[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,int w);
void _Add(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&m);
    int sump=0;
    for (int i=1;i<=n;i++)
    {
		scanf("%d",&Pi[i]);sump+=Pi[i];
    }
    S=sump+sump*m+1;T=sump+sump*m+2;
    for (int i=1;i<=n;i++) Add_Edge(S,i,Pi[i],0);//源点到菜的边
    for (int i=1;i<=m;i++) Add_Edge(n+(i-1)*sump+1,T,1,0);//厨师的倒数第一道菜到汇点的边
    for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&Tim[i][j]);
			Add_Edge(i,n+(j-1)*sump+1,1,Tim[i][j]);//菜到厨师的倒数第一道菜
		}
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
		Ans=Ans+Dist[T]*Flow[T];
		int k=E[Path[T]].u-n;//这一次的厨师及其在做倒数第几道菜
		int cook=(k+sump-1)/sump,dish=(k-1)%sump+1;//厨师编号及当前做的是倒数第几道菜
		Add_Edge(n+(cook-1)*sump+dish+1,T,1,0);
		for (int i=1;i<=n;i++)
			Add_Edge(i,n+(cook-1)*sump+dish+1,1,Tim[i][cook]*(dish+1));
    }
    printf("%d\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
    _Add(u,v,flow,w);_Add(v,u,0,-w);
    return;
}

void _Add(int u,int v,int flow,int w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].flow=flow;E[edgecnt].w=w;
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(inqueue,0);
    int h=1,t=0;Queue[1]=S;Dist[S]=0;Flow[S]=inf;inqueue[S]=0;
    do
    {
		t++;if (t>=maxN) t=0;
		int u=Queue[t];inqueue[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				if (inqueue[E[i].v]==0)
				{
					inqueue[E[i].v]=1;
					h++;if (h>=maxN) h=0;
					Queue[h]=E[i].v;
				}
			}
    }
    while (h!=t);
    if (Dist[T]==-1) return 0;
    return 1;
}
