#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=70;
const int maxM=maxN*maxN*4;
const int inf=1000000000;

class Edge{
public:
    int v,flow;
};

int n,a1,a2,b1,b2,at,bt,S,T;
char Mp[maxN][maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Q[maxN],Dph[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
int Dinic();
bool Bfs();
int dfs(int u,int flow);

int main(){
    while (scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&at,&b1,&b2,&bt)!=EOF){
	++a1;++a2;++b1;++b2;
	for (int i=1;i<=n;i++) scanf("%s",Mp[i]+1);

	edgecnt=-1;mem(Head,-1);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<i;j++)
		if (Mp[i][j]=='O') Add_Edge(i,j,1);
		else if (Mp[i][j]=='N') Add_Edge(i,j,inf);
	S=n+1;T=n+2;
	Add_Edge(S,a1,at);Add_Edge(S,b1,bt);Add_Edge(a2,T,at);Add_Edge(b2,T,bt);
	if (Dinic()!=at+bt){
	    printf("No\n");continue;
	}

	swap(b1,b2);
	edgecnt=-1;mem(Head,-1);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<i;j++)
		if (Mp[i][j]=='O') Add_Edge(i,j,1);
		else if (Mp[i][j]=='N') Add_Edge(i,j,inf);
	S=n+1;T=n+2;
	Add_Edge(S,a1,at);Add_Edge(S,b1,bt);Add_Edge(a2,T,at);Add_Edge(b2,T,bt);
	if (Dinic()!=at+bt){
	    printf("No\n");continue;
	}
	printf("Yes\n");
    }
    return 0;
}

void Add_Edge(int u,int v,int flow){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,flow});
    return;
}
int Dinic(){
    int ret=0;
    while (Bfs()){
	for (int i=1;i<=T;i++) cur[i]=Head[i];
	while (int di=dfs(S,inf)) ret+=di;
    }
    return ret;
}
bool Bfs(){
    mem(Dph,-1);Dph[S]=1;int ql=0,qr=1;Q[1]=S;
    while (ql<qr) for (int u=Q[++ql],i=Head[u];i!=-1;i=Next[i]) if ((Dph[E[i].v]==-1)&&(E[i].flow)) Dph[Q[++qr]=E[i].v]=Dph[u]+1;
    return Dph[T]!=-1;
}
int dfs(int u,int flow){
    if (u==T) return flow;
    for (int i=cur[u];i!=-1;i=Next[i])
	if ((E[i].flow)&&(Dph[E[i].v]==Dph[u]+1)){
	    int di=dfs(E[i].v,min(flow,E[i].flow));
	    if (di){
		E[i].flow-=di;E[i^1].flow+=di;return di;
	    }
	}
    return 0;
}
