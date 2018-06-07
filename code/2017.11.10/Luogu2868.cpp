#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1011;
const int maxM=5011;
const int inf=2147483647;
const ld eps=1e-4;

class Edge
{
public:
    int v,ww,nex;
    ld w;
};
    
class Graph
{
public:
    int cnt;
    int n;
    int Head[maxN],Happy[maxN];
    Edge E[maxM];
    int Stack[maxN];
    ld Dist[maxN];
    bool instack[maxN];
    bool chk;
    Graph()
		{
			cnt=0;
			mem(Head,-1);
		}
    void ReSet(ld mid)//把每一条边都变成原来的边权*mid-它指向的点的Happy值，这样走如果图中还有负环则说明答案还可以更优
	                  //因为知道答案=(总快乐值)/(总时间)，即 总时间*答案=总快乐值 ，即 总时间*答案-总快乐值=0
	                  //所以如果 总时间*答案-总快乐值<0 则说明此时的答案不是最优的
	                  //而为了方便处理第一个景点的总快乐值，可以第一个不算，然后每一条边计算其到达的点得，这样就可以把点权放到边上
		{
			for (int i=1;i<=n;i++)
				for (int j=Head[i];j!=-1;j=E[j].nex)
					E[j].w=(ld)E[j].ww*mid-Happy[E[j].v];
		}
    void Spfa(int S)
		{
			instack[S]=1;
			for (int i=Head[S];i!=-1;i=E[i].nex)
			{
				int v=E[i].v;
				if (Dist[v]>Dist[S]+E[i].w)
				{
					if (instack[v])
					{
						chk=1;
						return;
					}
					Dist[v]=Dist[S]+E[i].w;
					Spfa(v);
				}
			}
			instack[S]=0;
		}
    void Add_Edge(int u,int v,int w)
		{
			cnt++;E[cnt].nex=Head[u];Head[u]=cnt;
			E[cnt].v=v;E[cnt].ww=w;
			return;
		}
    bool Check()
		{
			for (int i=1;i<=n;i++) Dist[i]=instack[i]=0;
			chk=0;
			for (int i=1;i<=n;i++)
			{
				Spfa(i);
				if (chk) return 1;
			}
			return 0;
		}
};

int m;
Graph G;

int main()
{
    scanf("%d%d",&G.n,&m);
    for (int i=1;i<=G.n;i++) scanf("%d",&G.Happy[i]);
    for (int i=1;i<=m;i++)
    {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G.Add_Edge(u,v,w);
    }
    ld l=0,r=1000000;
    ld Ans=0;
    do
    {
		//cout<<l<<" "<<r<<endl;
		ld mid=(l+r)/2;
		G.ReSet(mid);
		if (G.Check())
		{
			Ans=mid;
			l=mid+eps;
		}
		else r=mid-eps;
    }
    while (l<=r-eps);
    printf("%.2LF\n",Ans);
    return 0;
}
