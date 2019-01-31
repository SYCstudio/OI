#include<bits/stdc++.h>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2020*2;
const int maxM=101000*10;

class Edge{
public:
	int v,flow,w;
};

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN],inq[maxN],Flow[maxN],Path[maxN];
queue<int> Q;
int In[maxN],Out[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main(){
	freopen("oldcomputer4.in","r",stdin);
	freopen("oldcomputer4.out","w",stdout);
	mem(Head,-1);
	scanf("%d%d%d",&n,&n,&m);S=n+n+1;T=S+1;
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u+n,v,1,1);Add_Edge(v+n,u,1,1);
	}
	for (int i=1;i<=n;i++) Add_Edge(i,i+n,1,0);
	for (int i=1;i<=50;i++) Add_Edge(S,i,1,0);
	for (int i=51;i<=100;i++) Add_Edge(i+n,T,1,0);

	cerr<<S<<" "<<T<<endl;

	while (Spfa()){
		int now=T;
		while (now!=S){
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]^1].v;
		}
	}
	for (int i=1;i<=n;i++)
		for (int j=Head[i+n];j!=-1;j=Next[j])
			if (E[j].flow==0&&E[j].v<=n&&E[j].v!=i){
				//cerr<<i<<" "<<E[j].v<<endl;
				In[E[j].v]=i;Out[i]=E[j].v;
				break;
			}

	for (int i=1;i<=n;i++) cerr<<In[i]<<" "<<Out[i]<<endl;
	
	for (int i=1;i<=50;i++) cout<<"node "<<i<<endl<<"read 0 a"<<endl<<"write a "<<Out[i]<<endl;
	for (int i=51;i<=100;i++) cout<<"node "<<i<<endl<<"read "<<In[i]<<" a"<<endl<<"write a 0"<<endl;
	for (int i=101;i<=n;i++)
		if (In[i])
			cout<<"node "<<i<<endl<<"read "<<In[i]<<" a"<<endl<<"write a "<<Out[i]<<endl;
	return 0;
}

void Add_Edge(int u,int v,int flow,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,-w});
	return;
}
bool Spfa(){
	mem(Dist,63);Dist[S]=0;inq[S]=1;Q.push(S);Flow[S]=Dist[0];
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if (E[i].flow&&Dist[E[i].v]>Dist[u]+E[i].w){
				Dist[E[i].v]=Dist[u]+E[i].w;Path[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
				if (inq[E[i].v]==0){
					Q.push(E[i].v);inq[E[i].v]=1;
				}
			}
		inq[u]=0;
	}
	return Dist[T]!=Dist[0];
}
