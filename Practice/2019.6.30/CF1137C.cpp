#include<bits/stdc++.h>
using namespace std;

const int maxN=100001*50;
const int maxD=55;
const int maxM=maxN;

class Graph
{
public:
	int ecnt,Hd[maxN],Nt[maxM],V[maxM];
	Graph()
	{
		ecnt=-1;
		memset(Hd,-1,sizeof(Hd));
	}
	void Add_Edge(int u,int v)
	{
		Nt[++ecnt]=Hd[u];
		Hd[u]=ecnt;
		V[ecnt]=v;
		return;
	}
};

int n,m,D;
int Id[101000][maxD];
int dfncnt,dfn[maxN],low[maxN],Bcc[maxN],bcccnt,St[maxN],top,inq[maxN];
Graph G1,G2;
char In[maxD];
int Dp[maxN],Sz[maxN],Dg[maxN];
queue<int> Qu;

void Add_Edge(int u,int v);
void tarjan(int u);
int main()
{
	scanf("%d%d%d",&n,&m,&D);
	for (int i=1,idcnt=0; i<=n; i++) for (int j=0; j<D; j++) Id[i][j]=++idcnt;
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		for (int j=0; j<D; j++) G1.Add_Edge(Id[u][j],Id[v][(j+1)%D]);
	}
	for (int i=1; i<=n*D; i++) if (!dfn[i]) tarjan(i);

	/*
	  for (int i=1;i<=n;i++){
	  for (int j=0;j<D;j++) cout<<Bcc[Id[i][j]]<<" ";cout<<endl;
	  }
	//*/

	for (int i=1; i<=n*D; i++) for (int j=G1.Hd[i]; j!=-1; j=G1.Nt[j]) if (Bcc[i]!=Bcc[G1.V[j]]) G2.Add_Edge(Bcc[G1.V[j]],Bcc[i]);

	for (int i=1; i<=n; i++) {
		scanf("%s",In);
		set<int> S;
		for (int j=0; j<D; j++)
			if (In[j]=='1'&&S.count(Bcc[Id[i][j]])==0) {
				++Sz[Bcc[Id[i][j]]];
				S.insert(Bcc[Id[i][j]]);
			}
	}

	for (int i=1; i<=bcccnt; i++) for (int j=G2.Hd[i]; j!=-1; j=G2.Nt[j]) ++Dg[G2.V[j]];
	for (int i=1; i<=bcccnt; i++) if (!Dg[i]) Qu.push(i);
	while (!Qu.empty()) {
		int u=Qu.front();
		Qu.pop();
		Dp[u]+=Sz[u];
		for (int i=G2.Hd[u]; i!=-1; i=G2.Nt[i]) {
			Dp[G2.V[i]]=max(Dp[G2.V[i]],Dp[u]);
			if ((--Dg[G2.V[i]])==0) Qu.push(G2.V[i]);
		}
	}
	printf("%d\n",Dp[Bcc[Id[1][0]]]);
	return 0;
}
void tarjan(int u)
{
	dfn[u]=low[u]=++dfncnt;
	St[++top]=u;
	inq[u]=1;
	for (int i=G1.Hd[u]; i!=-1; i=G1.Nt[i]) {
		int v=G1.V[i];
		if (!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		} else if (inq[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u]) {
		++bcccnt;
		int v;
		do inq[v=St[top--]]=0,Bcc[v]=bcccnt;
		while (u!=v);
	}
	return;
}
