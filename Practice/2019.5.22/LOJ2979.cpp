#include<bits/stdc++.h>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)
const int maxN=310;
const int maxM=11;
const int maxNN=maxN*maxM*9;
const int maxMM=maxNN*8;
const int inf=1000000000;

class Edge{
public:
    int v,flow,w;
};

int n,m;
int ecnt=-1,Hd[maxNN],Nt[maxMM],idcnt=2,S=1,T=2;
Edge E[maxMM];
int Id[2][maxN<<2][maxM],L[maxN][maxM],R[maxN][maxM];
queue<int> Qu;
int vis[maxNN],Dst[maxNN],viscnt;

void Add_Edge(int u,int v,int flow,int w);
void Build(int x,int l,int r,int k0,int k1);
void Query(int x,int l,int r,int ql,int qr,int b,int j,int p);
bool SPFA();
int dfs(int u);
int main(){
    memset(Hd,-1,sizeof(Hd));
    scanf("%d%d",&n,&m);
    Build(1,1,n,0,0);
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&L[i][j]),++L[i][j];
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&R[i][j]),++R[i][j];
    for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++){
	    ++idcnt;Add_Edge(S,idcnt,1,0);
	    if (L[i][j]<=i) Query(1,1,n,L[i][j],min(R[i][j],i),0,j,i);
	    if (R[i][j]>=i+1) Query(1,1,n,max(L[i][j],i+1),R[i][j],1,j,i);
	}
    int Ans=0,flow=0;
    while (SPFA()){
	while (1){
	    ++viscnt;
	    if (!dfs(S)) break;
	    ++flow;Ans+=Dst[T];
	}
    }
    flow==n*m?printf("%d\n",Ans):puts("no solution");
    return 0;
}
void Add_Edge(int u,int v,int flow,int w){
    Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow,w});
    Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0,-w});
    return;
}
void Build(int x,int l,int r,int k0,int k1){
    for (int b=0;b<=1;b++) for (int i=1;i<=m;i++) Id[b][x][i]=++idcnt;
    int fa=x>>1;
    if (fa) for (int i=1;i<=m;i++) Add_Edge(Id[0][fa][i],Id[0][x][i],inf,k0),Add_Edge(Id[1][fa][i],Id[1][x][i],inf,k1);
    if (l==r){
	Add_Edge(Id[0][x][m],Id[0][x][1],inf,1);Add_Edge(Id[0][x][1],Id[0][x][m],inf,1);
	Add_Edge(Id[1][x][m],Id[1][x][1],inf,1);Add_Edge(Id[1][x][1],Id[1][x][m],inf,1);
	for (int i=1;i<m;i++){
	    Add_Edge(Id[0][x][i],Id[0][x][i+1],inf,1);Add_Edge(Id[0][x][i+1],Id[0][x][i],inf,1);
	    Add_Edge(Id[1][x][i],Id[1][x][i+1],inf,1);Add_Edge(Id[1][x][i+1],Id[1][x][i],inf,1);
	}
	for (int i=1;i<=m;i++){
	    ++idcnt;Add_Edge(idcnt,T,1,0);
	    Add_Edge(Id[0][x][i],idcnt,1,0);Add_Edge(Id[1][x][i],idcnt,1,0);
	}
	return;
    }
    int mid=(l+r)>>1;
    Build(ls,l,mid,(r-mid)*2,0);Build(rs,mid+1,r,0,(mid-l+1)*2);
    return;
}
void Query(int x,int l,int r,int ql,int qr,int b,int j,int p){
    if (l==ql&&r==qr){
	if (b==0) Add_Edge(idcnt,Id[b][x][j],1,(p-qr)*2);
	else Add_Edge(idcnt,Id[b][x][j],1,(ql-p)*2);
	return;
    }
    int mid=(l+r)>>1;
    if (qr<=mid) Query(ls,l,mid,ql,qr,b,j,p);
    else if (ql>=mid+1) Query(rs,mid+1,r,ql,qr,b,j,p);
    else Query(ls,l,mid,ql,mid,b,j,p),Query(rs,mid+1,r,mid+1,qr,b,j,p);
    return;
}
bool SPFA(){
    memset(Dst,63,sizeof(Dst));memset(vis,0,sizeof(vis));Dst[S]=0;Qu.push(S);vis[S]=1;
    while (!Qu.empty()){
	int u=Qu.front();Qu.pop();
	for (int i=Hd[u];i!=-1;i=Nt[i])
	    if (E[i].flow&&Dst[E[i].v]>Dst[u]+E[i].w){
		Dst[E[i].v]=Dst[u]+E[i].w;
		if (!vis[E[i].v]){
		    Qu.push(E[i].v);vis[E[i].v]=1;
		}
	    }
	vis[u]=0;
    }
    return Dst[T]!=Dst[0];
}
int dfs(int u){
    //cout<<"d at:"<<u<<endl;
    if (u==T) return 1;vis[u]=viscnt;
    for (int i=Hd[u];i!=-1;i=Nt[i])
	if (E[i].flow&&Dst[E[i].v]==Dst[u]+E[i].w&&vis[E[i].v]!=viscnt)
	    if (dfs(E[i].v)){
		--E[i].flow;++E[i^1].flow;return 1;
	    }
    return 0;
}
