#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMp=210;
const int maxN=maxMp*maxMp;
const int maxM=maxN*20;
const int inf=2000000000;

class Edge
{
public:
	int v,flow;
};

int n,m,BL,BR;
int A[maxMp][maxMp],X[maxMp],Y[maxMp],Id[maxMp][maxMp],idcnt;
int Dfl[maxN],SX[maxMp],SY[maxMp];
int edgecnt,Head[maxN],Next[maxM];
Edge E[maxM];
int Lal[maxN],cur[maxN],Q[maxN];

bool check(int limit);
void Add_Edge(int u,int v,int flow);
bool Bfs(int S,int T);
int dfs(int u,int flow,int T);

int main()
{
	scanf("%d%d",&n,&m);
	int sum=0;
	for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) scanf("%d",&A[i][j]),Id[i][j]=++idcnt,SX[i]+=A[i][j],SY[j]+=A[i][j],sum+=A[i][j];
	for (int i=1; i<=n; i++) X[i]=++idcnt;
	for (int i=1; i<=m; i++) Y[i]=++idcnt;
	scanf("%d%d",&BL,&BR);

	int l=0,r=sum,Ans=sum;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (check(mid)) Ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",Ans);
	return 0;
}
bool check(int limit)
{
	//cout<<"check limit:"<<limit<<endl;
	edgecnt=-1;
	mem(Head,-1);
	mem(Dfl,0);
	int S=idcnt+1,T=S+1,SS=T+1,TT=SS+1;

	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++) {
			Dfl[X[i]]-=BL;
			Dfl[Y[j]]+=BL;
			Add_Edge(X[i],Id[i][j],BR-BL);
			Add_Edge(Id[i][j],Y[j],BR-BL);
		}
	for (int i=1; i<=n; i++) {
		int up=SX[i]+limit,down=max(0,SX[i]-limit);
		Dfl[S]-=down;
		Dfl[X[i]]+=down;
		Add_Edge(S,X[i],up-down);
	}
	for (int i=1; i<=m; i++) {
		int up=SY[i]+limit,down=max(0,SY[i]-limit);
		Dfl[Y[i]]-=down;
		Dfl[T]+=down;
		Add_Edge(Y[i],T,up-down);
	}
	Add_Edge(T,S,inf);

	//for (int i=1;i<=T;i++) cout<<Dfl[i]<<" ";cout<<endl;

	int sumdown=0,di;
	for (int i=1; i<=T; i++)
		if (Dfl[i]>0) Add_Edge(SS,i,Dfl[i]),sumdown+=Dfl[i];
		else if (Dfl[i]<0) Add_Edge(i,TT,-Dfl[i]);
	while (Bfs(SS,TT)) {
		memcpy(cur,Head,sizeof(Head));
		while (di=dfs(SS,inf,TT)) sumdown-=di;
	}
	return sumdown==0;
}
void Add_Edge(int u,int v,int flow)
{
	if (flow==0) return;
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	E[edgecnt]=((Edge) {
		v,flow
	});
	Next[++edgecnt]=Head[v];
	Head[v]=edgecnt;
	E[edgecnt]=((Edge) {
		u,0
	});
	return;
}
bool Bfs(int S,int T)
{
	mem(Lal,-1);
	Lal[S]=1;
	Q[1]=S;
	int ql=1,qr=1;
	while (ql<=qr)
		for (int u=Q[ql++],i=Head[u]; i!=-1; i=Next[i])
			if ((E[i].flow)&&(Lal[E[i].v]==-1)) {
				Lal[E[i].v]=Lal[u]+1;
				if (E[i].v==T) return 1;
				Q[++qr]=E[i].v;
			}
	return 0;
}
int dfs(int u,int flow,int T)
{
	if (u==T) return flow;
	for (int &i=cur[u]; i!=-1; i=Next[i])
		if ((E[i].flow)&&(Lal[E[i].v]==Lal[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow),T)) {
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
	return 0;
}
/*
2 2
0 1
2 1
0 1
//*/
