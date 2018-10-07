#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=24;
const int maxNode=maxN*maxN*3;
const int maxM=maxNode*20;
const int F1[]={-1,-1,-1,0,0,1,1,1};
const int F2[]={-1,0,1,-1,1,-1,0,1};
const int inf=10000000;

class Edge
{
public:
	int v,flow,w;
};

int n,m,S,T;
char ST[maxN][maxN],ED[maxN][maxN],Input[maxN];
int Id[maxN][maxN];
int edgecnt=-1,Head[maxNode],Next[maxM];
Edge E[maxM];
int Dist[maxNode],Path[maxNode],Flow[maxNode];
bool inq[maxNode];
queue<int> Q;

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	S=n*m*3+1;T=n*m*3+2;
	for (int i=1,idcnt=0;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt,idcnt+=2;

	int bcnt1=0,bcnt2=0;
	for (int i=1;i<=n;i++){
		scanf("%s",ST[i]+1);
		for (int j=1;j<=m;j++) if (ST[i][j]=='1') Add_Edge(S,Id[i][j],1,0),Add_Edge(Id[i][j],Id[i][j]+1,1,0),bcnt1++;
	}
	for (int i=1;i<=n;i++){
		scanf("%s",ED[i]+1);
		for (int j=1;j<=m;j++){
			if (ED[i][j]=='1') Add_Edge(Id[i][j]+2,T,1,0),bcnt2++;
			if ((ST[i][j]=='1')&&(ED[i][j]=='1')) Add_Edge(Id[i][j],Id[i][j]+2,1,0);
		}
	}
	for (int i=1;i<=n;i++){
		scanf("%s",Input+1);
		for (int j=1;j<=m;j++) Add_Edge(Id[i][j]+1,Id[i][j]+2,Input[j]-'0',0);
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int f=0;f<8;f++){
				int xx=i+F1[f],yy=j+F2[f];
				if ((xx<=0)||(yy<=0)||(xx>n)||(yy>m)) continue;
				Add_Edge(Id[i][j]+2,Id[xx][yy]+1,inf,1);
			}
	
	if (bcnt1!=bcnt2){
		printf("-1\n");return 0;
	}

	int flow=0,w=0;
	while (Spfa()){
		int now=T;flow+=Flow[T];w+=Dist[T]*Flow[T];
		cout<<Dist[T]<<" "<<Flow[T]<<endl;
		while (now!=S){
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]^1].v;
		}
	}

	if (flow!=bcnt1) printf("-1\n");
	else printf("%d\n",w);return 0;
}

void Add_Edge(int u,int v,int flow,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,-w});
	return;
}

bool Spfa(){
	mem(inq,0);for (int i=1;i<=T;i++) Dist[i]=inf;while (!Q.empty()) Q.pop();
	Dist[S]=0;Flow[S]=inf;Q.push(S);inq[S]=1;
	do{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow)&&(Dist[E[i].v]>Dist[u]+E[i].w)){
				Dist[E[i].v]=Dist[u]+E[i].w;Path[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
				if (inq[E[i].v]==0){
					inq[E[i].v]=1;Q.push(E[i].v);
				}
			}
		inq[u]=0;
	}
	while (!Q.empty());
	return Dist[T]!=inf;
}
