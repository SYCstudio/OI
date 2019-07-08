#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define NAME "A"
const int maxT=55;
const int maxN=maxT*maxT*5;
const int maxM=maxN*10;
const int F1[]= {1,0,-1,0};
const int F2[]= {0,1,0,-1};
const int inf=1000000000;

class Edge
{
public:
	int v,flow;
};

int n,m,sx,sy,tx,ty,S,T;
int Id[maxT][maxT],Mt[maxT][maxT];
int ecnt=-1,Hd[maxN],Nt[maxM];
Edge E[maxM];
int cur[maxN],Qu[maxN],label[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		ecnt=-1;
		memset(Hd,-1,sizeof(Hd));
		scanf("%d%d",&n,&m);
		int idcnt=0;
		for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) Id[i][j]=++idcnt;
		S=++idcnt;
		T=++idcnt;
		scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
		for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) scanf("%d",&Mt[i][j]);
		for (int i=1; i<=n; i++)
			for (int j=1; j<=m; j++) {
				pair<int,int> Vr[8];
				int vcnt=0;
				for (int f=0; f<4; f++) {
					int x=i+F1[f],y=j+F2[f];
					if (x<=0||y<=0||x>n||y>m) continue;
					if (Mt[x][y]<Mt[i][j]) continue;
					Vr[++vcnt]=make_pair(Mt[x][y],Id[x][y]);
				}
				if ((i==tx&&j==ty)||(i==sx&&j==sy)) {
					for (int k=1; k<=vcnt; k++) Add_Edge(Vr[k].second,Id[i][j],inf);
					continue;
				}
				sort(&Vr[1],&Vr[vcnt+1]);
				Vr[0]=make_pair(Mt[i][j]-1,Id[i][j]);
				//cout<<"p:"<<p<<endl;
				for (int k=1; k<=vcnt; k++) {
					Add_Edge(idcnt+k,Id[i][j],Vr[k].first-Vr[k-1].first);
					for (int l=1; l<=k; l++) Add_Edge(Vr[k].second,idcnt+l,inf);
				}
				idcnt+=vcnt;
			}
		Add_Edge(S,Id[sx][sy],inf);
		Add_Edge(Id[tx][ty],T,inf);
		int flow=0;
		while (bfs()) {
			memcpy(cur,Hd,sizeof(cur));
			while (int di=dfs(S,inf)) flow+=di;//,cout<<di<<endl;
		}
		flow>=inf?puts("-1"):printf("%d\n",flow);
	}
	return 0;
}
void Add_Edge(int u,int v,int flow)
{
	//cout<<"ADD:"<<u<<" "<<v<<" "<<flow<<endl;
	Nt[++ecnt]=Hd[u];
	Hd[u]=ecnt;
	E[ecnt]=((Edge) {
		v,flow
	});
	Nt[++ecnt]=Hd[v];
	Hd[v]=ecnt;
	E[ecnt]=((Edge) {
		u,0
	});
	return;
}
bool bfs()
{
	memset(label,-1,sizeof(label));
	int ql=1,qr=1;
	Qu[1]=S;
	label[S]=1;
	while (ql<=qr) for (int u=Qu[ql++],i=Hd[u]; i!=-1; i=Nt[i]) if (E[i].flow&&label[E[i].v]==-1) label[Qu[++qr]=E[i].v]=label[u]+1;
	return label[T]!=-1;
}
int dfs(int u,int flow)
{
	//cout<<"dfs:"<<u<<" "<<flow<<endl;
	if (u==T) return flow;
	for (int &i=cur[u]; i!=-1; i=Nt[i]) if (E[i].flow&&label[E[i].v]==label[u]+1) if (int di=dfs(E[i].v,min(flow,E[i].flow))) return E[i].flow-=di,E[i^1].flow+=di,di;
	return 0;
}