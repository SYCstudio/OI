#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxM=maxN*4;
const int inf=2147483647;

int n,m;
int S1[maxN],S2[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int dfncnt=0,dfn[maxN],low[maxN],Fa[maxN];

int Find(int *F,int x);
void Add_Edge(int u,int v);
void Tarjan(int u,int edge);

int main()
{
   mem(Head,-1);
   scanf("%d%d",&n,&m);
   for (int i=1;i<=n;i++) S1[i]=S2[i]=i;
   for (int i=1;i<=m;i++)
   {
	  int u,v;scanf("%d%d",&u,&v);
	  if (Find(S1,u)!=Find(S1,v))
	  {
		 Add_Edge(u,v);S1[Find(S1,u)]=Find(S1,v);
	  }
	  else if (Find(S2,u)!=Find(S2,v))
	  {
		 Add_Edge(u,v);S2[Find(S2,u)]=Find(S2,v);
	  }
   }
   for (int i=1;i<=n;i++) if (dfn[i]==0) Tarjan(i,edgecnt+10),Fa[i]=i;
   for (int i=1;i<=n;i++) if ((dfn[i]==low[i])&&(i!=Fa[i])) printf("%d %d\n",i,Fa[i]);
   return 0;
}

int Find(int *F,int x)
{
   if (F[x]!=x) F[x]=Find(F,F[x]);
   return F[x];
}

void Add_Edge(int u,int v)
{
   edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
   edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
   return;
}

void Tarjan(int u,int edge)
{
   dfn[u]=low[u]=++dfncnt;
   for (int i=Head[u];i!=-1;i=Next[i])
	  if (i!=(edge^1))
	  {
		 if (dfn[V[i]]==0)
		 {
			Fa[V[i]]=u;
			Tarjan(V[i],i);
			low[u]=min(low[u],low[V[i]]);
		 }
		 else low[u]=min(low[u],dfn[V[i]]);
	  }
   return;
}
