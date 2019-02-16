#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=100100*2;
const int inf=2147483647;

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],Flow[maxM];
int cur[maxN],Dph[maxN],Q[maxN];
int Seq[maxN],acnt,Ans[maxN],Bp[maxN];
bool mark[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);
void Divide(int l,int r);
void dfs_mark(int u);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
	}
	for (int i=1;i<=n;i++) Seq[i]=i;
	Divide(1,n);
	sort(&Ans[1],&Ans[acnt+1]);acnt=unique(&Ans[1],&Ans[acnt+1])-Ans-1;
	printf("%d\n",acnt);return 0;
}

void Add_Edge(int u,int v,int flow){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Flow[edgecnt]=flow;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;Flow[edgecnt]=flow;
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

void Divide(int l,int r){
	if (l==r) return;
	if (l>r) return;
	for (int i=0;i<=edgecnt;i+=2) Flow[i]=Flow[i^1]=(Flow[i]+Flow[i^1])/2;
	S=Seq[l];T=Seq[r];int flow=0;
	while (Bfs()){
		for (int i=1;i<=n;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) flow+=di;
	}
	Ans[++acnt]=flow;
	mem(mark,0);dfs_mark(S);
	int nl=l,nr=r;
	for (int i=l;i<=r;i++)
		if (mark[Seq[i]]) Bp[nl++]=Seq[i];
		else Bp[nr--]=Seq[i];
	for (int i=l;i<=r;i++) Seq[i]=Bp[i];
	Divide(l,nl-1);Divide(nr+1,r);
}

void dfs_mark(int u){
	mark[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((Flow[i])&&(mark[V[i]]==0)) dfs_mark(V[i]);
	return;
}
/*
4 4
1 2 3
1 3 6
2 4 5
3 4 4
//*/
