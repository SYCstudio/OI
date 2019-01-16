#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define IMPOSSBLE {printf("No\n");return 0;}
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMp=110;
const int maxN=maxMp*maxMp;
const int maxM=maxN*20;
const int inf=100000000;

class Edge{
public:
    int v,flow;
};

int n;
int Dfl[maxN],Up[maxMp][maxMp],Down[maxMp][maxMp],idcnt=0,Id[maxMp][maxMp],X[maxN],Y[maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Lal[maxN],cur[maxN],Q[maxN];

void Add_Edge(int u,int v,int flow);
int Dinic(int S,int T);
bool Bfs(int S,int T);
int dfs(int u,int flow,int T);

int main(){
    int S,T,SS,TT;
    scanf("%d",&n);mem(Head,-1);
    for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++){
	    double key;scanf("%lf",&key);
	    Up[i][j]=ceil(key);Down[i][j]=(int)key;
	    Id[i][j]=++idcnt;
	}
    for (int i=1;i<=n;i++) X[i]=Id[i][n];
    for (int i=1;i<=n;i++) Y[i]=Id[n][i];
    if ((Up[n][n]!=0)&&(Down[n][n]!=0)) IMPOSSBLE;
    S=idcnt+1;T=S+1;SS=T+1;TT=SS+1;

    for (int i=1;i<n;i++)
	for (int j=1;j<n;j++){
	    Dfl[X[i]]-=Down[i][j];Dfl[Y[j]]+=Down[i][j];
	    Add_Edge(X[i],Id[i][j],Up[i][j]-Down[i][j]);
	    Add_Edge(Id[i][j],Y[j],Up[i][j]-Down[i][j]);
	}
    for (int i=1;i<=n;i++){
	Dfl[S]-=Down[i][n];Dfl[X[i]]+=Down[i][n];
	Add_Edge(S,X[i],Up[i][n]-Down[i][n]);

	Dfl[Y[i]]-=Down[n][i];Dfl[T]+=Down[n][i];
	Add_Edge(Y[i],T,Up[n][i]-Down[n][i]);
    }
    
    Add_Edge(T,S,inf);

    int sumdown=0,sumup;
    for (int i=1;i<=T;i++)
	if (Dfl[i]>0) Add_Edge(SS,i,Dfl[i]),sumdown+=Dfl[i];
	else if (Dfl[i]<0) Add_Edge(i,TT,-Dfl[i]),sumup-=Dfl[i];

    if (Dinic(SS,TT)!=sumdown) IMPOSSBLE;
    printf("%d\n",Dinic(S,T)*3);return 0;
}
void Add_Edge(int u,int v,int flow){
    if (flow==0) return;
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
    return;
}
int Dinic(int S,int T){
    int ret=0,di;
    while (Bfs(S,T)){
	memcpy(cur,Head,sizeof(cur));
	while (di=dfs(S,inf,T)) ret+=di;
    }
    return ret;
}
bool Bfs(int S,int T){
    mem(Lal,-1);Lal[S]=1;Q[1]=S;int ql=1,qr=1;
    while (ql<=qr)
	for (int u=Q[ql++],i=Head[u];i!=-1;i=Next[i])
	    if ((E[i].flow)&&(Lal[E[i].v]==-1)){
		Lal[E[i].v]=Lal[u]+1;
		if (E[i].v==T) return 1;
		Q[++qr]=E[i].v;
	    }
    return 0;
}
int dfs(int u,int flow,int T){
    if (u==T) return flow;
    for (int &i=cur[u];i!=-1;i=Next[i])
	if ((Lal[E[i].v]==Lal[u]+1)&&(E[i].flow))
	    if (int di=dfs(E[i].v,min(flow,E[i].flow),T)){
		E[i].flow-=di;E[i^1].flow+=di;return di;
	    }
    return 0;
}
/*
4
3.1 6.8 7.3 17.2
9.6 2.4 0.7 12.7
3.6 1.2 6.5 11.3
16.3 10.4 14.5 0
//*/
