#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101*4;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int top=0,Stack[maxN];
bool instack[maxN];
int idcnt=0,Id[maxN];
int dfncnt,dfn[maxN],low[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		scanf("%d%d",&n,&m);
		edgecnt=0;mem(Head,-1);dfncnt=0;mem(dfn,0);top=0;mem(instack,0);
		for (int i=1;i<=n;i++) Add_Edge(i,i+n*3),Add_Edge(i+n*3,i),Add_Edge(i+n,i+n*2),Add_Edge(i+n*2,i+n);
		for (int i=1;i<=m;i++)
		{
			int id1,id2;
			char opt1,opt2;
			scanf("\n%c%d %c%d",&opt1,&id1,&opt2,&id2);
			//cout<<opt1<<" "<<id1<<" "<<opt2<<" "<<id2<<endl;
			int d1=((opt1=='h')?(0):(n)),d2=((opt2=='h')?(0):(n));
			Add_Edge(id1+2*n+d1,id2+d2);Add_Edge(id2+2*n+d2,id1+d1);
		}
		for (int i=1;i<=n*4;i++)
			if (dfn[i]==0) tarjan(i,0);

		bool flag=1;
		for (int i=1;i<=2*n;i++) if (Id[i]==Id[i+2*n]) flag=0;
		printf("%s\n",(flag)?("GOOD"):("BAD"));
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;
	instack[u]=1;Stack[++top]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (dfn[V[i]]==0)
		{
			tarjan(V[i],u);
			low[u]=min(low[u],low[V[i]]);
		}
		else if (instack[V[i]]) low[u]=min(low[u],dfn[V[i]]);
	if (dfn[u]==low[u])
	{
		int v;idcnt++;
		do v=Stack[top--],instack[v]=0,Id[v]=idcnt;
		while (u!=v);
	}
	return;
}
