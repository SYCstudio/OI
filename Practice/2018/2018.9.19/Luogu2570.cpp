#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int maxNode=maxN*maxN;
const int maxM=maxNode*80;
const ld eps=1e-8;
const int inf=2147483647;

class Edge
{
public:
	int v;ld flow;
};

int n,m;
ld sum=0;
ld P[maxN],L[maxN],R[maxN],Spd[maxN];
int edgecnt=-1,Head[maxNode],Next[maxM],Id[maxN][maxN],S,T;
Edge E[maxM];
ld Tim[maxNode];
int Q[maxNode],Depth[maxNode],cur[maxNode];

bool check(ld t);
void Add_Edge(int u,int v,ld flow);
bool Bfs();
ld dfs(int u,ld flow);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d",&n,&m);sum=0;
		for (int i=1;i<=n;i++) scanf("%LF%LF%LF",&P[i],&L[i],&R[i]),sum+=P[i];
		for (int i=1;i<=m;i++) scanf("%LF",&Spd[i]);
		sort(&Spd[1],&Spd[m+1]);reverse(&Spd[1],&Spd[m+1]);
		for (int i=1;i<m;i++) Spd[i]=Spd[i]-Spd[i+1];
		ld L=0,R=1e9,Ans;
		do{
			ld mid=(L+R)/2.0;
			if (check(mid)) Ans=mid,R=mid-eps;
			else L=mid+eps;
		}
		while (L+eps<=R);

		printf("%.6LF\n",Ans);
	}

	return 0;
}

bool check(ld t){
	int c1=0,cnt=1;
	for (int i=1;i<=n;i++) Tim[++c1]=L[i],Tim[++c1]=(ld)R[i]+t;
	sort(&Tim[1],&Tim[c1+1]);
	for (int i=2;i<=c1;i++)
		if (fabs(Tim[i]-Tim[cnt])>eps) Tim[++cnt]=Tim[i];
	//cout<<"check:"<<t<<endl;
	//for (int i=1;i<=cnt;i++) cout<<Tim[i]<<" ";cout<<endl;
	S=1;T=2;
	int idcnt=n+2;

	edgecnt=-1;mem(Head,-1);
	for (int i=1;i<=n;i++) Add_Edge(S,i+2,P[i]);
	for (int i=1;i<=m;i++)
		for (int j=1;j<cnt;j++){
			idcnt++;Add_Edge(idcnt,T,1.0*i*Spd[i]*(Tim[j+1]-Tim[j]));
			//cout<<idcnt<<": ["<<Tim[j]<<","<<Tim[j+1]<<"] "<<i<<" "<<j<<endl;
			for (int k=1;k<=n;k++)
				if ((L[k]<=Tim[j])&&(R[k]+t>=Tim[j+1])) Add_Edge(k+2,idcnt,Spd[i]*(Tim[j+1]-Tim[j]));
		}

	/*
	for (int i=1;i<=idcnt;i++)
		for (int j=Head[i];j!=-1;j=Next[j])
			if (E[j].flow>eps) cout<<i<<" -> "<<E[j].v<<" "<<E[j].flow<<endl;
	//*/

	ld flow=0;
	while (Bfs()){
		for (int i=1;i<=idcnt;i++) cur[i]=Head[i];
		ld di;
		do{
			di=dfs(S,inf);
			flow+=di;
		}
		while (di>eps);
	}

	//cout<<flow<<" "<<sum<<endl;
	return fabs(flow-sum)<eps;
}

void Add_Edge(int u,int v,ld flow){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

bool Bfs(){
	mem(Depth,-1);int h=1,t=0;Q[1]=S;
	do for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
		   if ((E[i].flow>eps)&&(Depth[E[i].v]==-1))
			   Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

ld dfs(int u,ld flow){
	if (u==T) return flow;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].flow>eps)&&(Depth[E[i].v]==Depth[u]+1)){
			ld di=dfs(E[i].v,min(flow,E[i].flow));
			if (di>eps){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
/*
1
2 2
13 0 4
10 1 3
4
2

2
2 2
13 0 4
10 1 3
4
2
1 1
1 0 2
1
//*/
