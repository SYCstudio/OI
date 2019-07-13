#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second

const int maxN=50500*3;
const int maxM=maxN*10;
const double eps=1e-8;
const double inf=1e18;

class Edge{
public:
	int v;double flow;
};

int n,S,T;
map<pair<int,int>,int> Mp;
int Mk[maxN];
int ecnt=-1,Hd[maxN],Nt[maxM];
Edge E[maxM];
int Qu[maxN],cur[maxN],Dep[maxN];

void Push(int x,int y,int z,int id);
void Add_Edge(int u,int v,double flow);
bool bfs();
double dfs(int u,double flow);
int main(){
	memset(Hd,-1,sizeof(Hd));
	scanf("%d",&n);S=1;T=2;int nodecnt=2;
	double sum=0;
	for (int i=1;i<=n;i++){
		int x,y,z;double key;scanf("%d%d%d%lf",&x,&y,&z,&key);
		pair<int,int> q=mp(x-y,y-z);
		if (!Mp.count(q)){
			Mp[q]=++nodecnt;Mk[nodecnt]=((x+y+z)%3+3)%3;
			if (Mk[nodecnt]==0) ++nodecnt;
		}
		int id=Mp[q],sp=++nodecnt;
		if (Mk[id]==0) Add_Edge(id,sp,key*1.1),Add_Edge(sp,id+1,key*1.1),sum+=key*1.1;
		else if (Mk[id]==1) Add_Edge(S,sp,key),Add_Edge(sp,id,inf),sum+=key;
		else Add_Edge(id,sp,inf),Add_Edge(sp,T,key),sum+=key;
	}

	for (map<pair<int,int>,int>::iterator it=Mp.begin();it!=Mp.end();it++){
		int x=(*it).ft.ft,y=(*it).ft.sd,z=0,id=(*it).sd;x+=y;
		if (Mk[id]==0){
			Push(x+1,y,z,id);Push(x-1,y,z,id);
			Push(x,y+1,z,id);Push(x,y-1,z,id);
			Push(x,y,z+1,id);Push(x,y,z-1,id);
		}
	}

	double flow=0;
	while (bfs()){
		memcpy(cur,Hd,sizeof(cur));
		while(1){
			double di=dfs(S,inf);
			if (di<eps) break;
			flow+=di;
		}
	}
	printf("%.1lf\n",sum-flow);return 0;
}
void Add_Edge(int u,int v,double flow){
	Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow});
	Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0});
	return;
}
void Push(int x,int y,int z,int id){
	if (!Mp.count(mp(x-y,y-z))) return;
	int to=Mp[mp(x-y,y-z)];
	if (Mk[to]==1) Add_Edge(to,id,inf);
	else Add_Edge(id+1,to,inf);
	return;
}
bool bfs(){
	memset(Dep,-1,sizeof(Dep));int ql=1,qr=1;Dep[Qu[1]=S]=1;
	while (ql<=qr)
		for (int u=Qu[ql++],i=Hd[u];i!=-1;i=Nt[i])
			if (E[i].flow>eps&&Dep[E[i].v]==-1)
				Dep[Qu[++qr]=E[i].v]=Dep[u]+1;
	return Dep[T]!=-1;
}
double dfs(int u,double flow){
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Nt[i])
		if (E[i].flow>eps&&Dep[E[i].v]==Dep[u]+1){
			double di=dfs(E[i].v,min(flow,E[i].flow));
			if (di>eps){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
