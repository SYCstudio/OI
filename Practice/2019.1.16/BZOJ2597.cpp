#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMp=110;
const int maxN=maxMp*maxMp;
const int maxM=maxN*20;
const int inf=2000000000;

class Edge{
public:
    int v,flow,w;
};

int n,S,T;
int In[maxMp][maxMp],Id[maxMp][maxMp],idcnt=0,W[maxMp];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
queue<int> Q;
int Dst[maxN],inq[maxN],Flow[maxN],From[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main(){
    scanf("%d",&n);idcnt=n;mem(Head,-1);
    for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++){
	    scanf("%d",&In[i][j]);
	    if (In[i][j]==1) ++W[i];
	    if (j>=i) continue;
	    if (In[i][j]==2) Id[i][j]=++idcnt;
	}
    S=idcnt+1;T=S+1;
    for (int i=n+1;i<=idcnt;i++) Add_Edge(S,i,1,0);
    for (int i=1;i<=n;i++) for (int j=1;j<i;j++) if (In[i][j]==2) Add_Edge(Id[i][j],i,1,0),Add_Edge(Id[i][j],j,1,0);
    for (int i=1;i<=n;i++) for (int j=0;j<=n;j++) Add_Edge(i,T,1,j+W[i]);

    int Ans=n*(n-1)*(n-2)/6;
    for (int i=1;i<=n;i++) Ans=Ans-W[i]*(W[i]-1)/2;
    //cout<<"W:";for (int i=1;i<=n;i++) cout<<W[i]<<" ";cout<<endl;

    int flow=0,cost=0;Flow[S]=inf;
    while (Spfa()){
	flow+=Flow[T];cost+=Flow[T]*Dst[T];
	int now=T;
	while (now!=S){
	    E[From[now]].flow-=Flow[T];
	    E[From[now]^1].flow+=Flow[T];
	    now=E[From[now]^1].v;
	}
    }

    for (int i=1;i<=n;i++)
	for (int j=1;j<i;j++)
	    if (In[i][j]==2){
		for (int k=Head[Id[i][j]];k!=-1;k=Next[k])
		    if ((E[k].v<=n)&&(E[k].flow==0)){
			//cout<<"("<<i<<" "<<j<<") "<<E[k].v<<endl;
			In[i][j]=(E[k].v==i);break;
		    }
		In[j][i]=In[i][j]^1;
	    }

    printf("%d\n",Ans-cost);
    for (int i=1;i<=n;i++){
	for (int j=1;j<=n;j++) printf("%d ",In[i][j]);
	printf("\n");
    }

    return 0;
}
void Add_Edge(int u,int v,int flow,int w){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,w});
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,-w});
    return;
}
bool Spfa(){
    mem(Dst,127);
    Dst[S]=0;Q.push(S);inq[S]=1;
    while (!Q.empty()){
	int u=Q.front();Q.pop();
	for (int i=Head[u];i!=-1;i=Next[i])
	    if ((E[i].flow)&&(Dst[u]+E[i].w<Dst[E[i].v])){
		Dst[E[i].v]=Dst[u]+E[i].w;From[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
		if (inq[E[i].v]==0){
		    Q.push(E[i].v);inq[E[i].v]=1;
		}
	    }
	inq[u]=0;
    }
    return Dst[T]!=Dst[0];
}
