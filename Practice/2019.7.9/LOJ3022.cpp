#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;
const int maxM=maxN*4;
const int Col[2][4]={{1,2,3,4},{4,3,2,1}};
const int inf=2000000000;
const int F1[]={0,1,0,-1};
const int F2[]={1,0,-1,0};

class Edge{
public:
	int v,flow;
};

int n,m,C,X[maxN],Y[maxN],S,T;
map<int,int> Mp[maxN],Key[maxN],Mark[maxN];
int ecnt=-1,Hd[maxN],Nt[maxM];
Edge E[maxM];
int Qu[maxN],Dep[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);
int main(){
	ecnt=-1;memset(Hd,-1,sizeof(Hd));
	scanf("%d%d%d",&n,&m,&C);S=C+1;T=S+1;
	for (int i=1;i<=C;i++){
		int key;scanf("%d%d%d",&Y[i],&X[i],&key);
		Mp[X[i]][Y[i]]=i;Key[X[i]][Y[i]]=key;Mark[X[i]][Y[i]]=Col[(X[i]-1)%2][(Y[i]-1)%4];
	}
	for (int i=1;i<=C;i++){
		int x=X[i],y=Y[i];
		if (Mark[x][y]==3) Add_Edge(Mp[x][y],T,Key[x][y]);
		if (Mark[x][y]==4) Add_Edge(S,Mp[x][y],Key[x][y]);
		for (int f=0;f<4;f++){
			int xx=x+F1[f],yy=y+F2[f];
			if (!Mp[xx].count(yy)) continue;
			if (Mark[x][y]==1&&Mark[xx][yy]==2) Add_Edge(Mp[x][y],Mp[xx][yy],min(Key[x][y],Key[xx][yy]));
			if (Mark[x][y]==2&&Mark[xx][yy]==3) Add_Edge(Mp[x][y],Mp[xx][yy],inf);
			if (Mark[x][y]==4&&Mark[xx][yy]==1) Add_Edge(Mp[x][y],Mp[xx][yy],inf);
		}
	}

	int flow=0;
	while (bfs()){
		memcpy(cur,Hd,sizeof(cur));
		while (int di=dfs(S,inf)) flow+=di;
	}
	printf("%d\n",flow);return 0;
}
void Add_Edge(int u,int v,int flow){
	Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow});
	Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0});
	return;
}
bool bfs(){
	memset(Dep,-1,sizeof(Dep));int ql=1,qr=1;Dep[Qu[1]=S]=1;
	while (ql<=qr){
		int u=Qu[ql++];
		for (int i=Hd[u];i!=-1;i=Nt[i])
			if (E[i].flow&&Dep[E[i].v]==-1)
				Dep[Qu[++qr]=E[i].v]=Dep[u]+1;
	}
	return Dep[T]!=-1;
}
int dfs(int u,int flow){
	//cerr<<"dfs at:"<<u<<" "<<flow<<endl;
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Nt[i])
		if (E[i].flow&&Dep[E[i].v]==Dep[u]+1){
			int di=dfs(E[i].v,min(flow,E[i].flow));
			if (di){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
