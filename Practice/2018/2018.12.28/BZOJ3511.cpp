#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100+40400*2;
const int maxM=(10100*2+40400*7)*2;
const int inf=1000000000;

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],Flow[maxM];
int Dph[maxN],cur[maxN],Q[maxN];

void Add_Edge(int u,int v,int flow,int opt);
bool Bfs();
int dfs(int u,int flow);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);S=n+2*m+1;T=S+1;
	Add_Edge(S,1,inf,0);Add_Edge(n,T,inf,0);
	int sum=0;
	for (int i=2;i<n;i++){
		int key;scanf("%d",&key);
		Add_Edge(S,i,key,0);sum+=key;
	}
	for (int i=2;i<n;i++){
		int key;scanf("%d",&key);
		Add_Edge(i,T,key,0);sum+=key;
	}
	for (int i=1;i<=m;i++){
		int u,v,a,b,c;scanf("%d%d%d%d%d",&u,&v,&a,&b,&c);sum+=a+b;
		int id1=i+n,id2=i+n+m;
		Add_Edge(u,v,c,1);Add_Edge(S,id1,a,0);Add_Edge(id2,T,b,0);
		Add_Edge(id1,u,inf,0);Add_Edge(id1,v,inf,0);
		Add_Edge(u,id2,inf,0);Add_Edge(v,id2,inf,0);
	}
	int flow=0;
	while (Bfs()){
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) flow+=di;
	}
	printf("%d\n",sum-flow);return 0;
}

void Add_Edge(int u,int v,int flow,int opt){
	if (flow==0) return;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Flow[edgecnt]=flow;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;Flow[edgecnt]=opt?flow:0;
	return;
}

bool Bfs(){
	mem(Dph,-1);Dph[S]=1;Q[1]=S;int h=1,t=0;
	do for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
		   if ((Dph[V[i]]==-1)&&(Flow[i]))
			   Dph[Q[++h]=V[i]]=Dph[u]+1;
	while (t!=h);
	return Dph[T]!=-1;
}

int dfs(int u,int flow){
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((Dph[V[i]]==Dph[u]+1)&&(Flow[i]))
			if (int di=dfs(V[i],min(flow,Flow[i]))){
				Flow[i]-=di;Flow[i^1]+=di;
				return di;
			}
	return 0;
}
/*
3 3 
8 
9 
1 2 2 6 2 
2 3 8 5 7 
1 3 9 4 1
//*/
