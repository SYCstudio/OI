#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int maxNode=maxN*maxN;
const int maxM=maxNode*40;
const ld eps=1e-8;
const int inf=2147483647;

class Edge
{
public:
	int v;ld flow;
};

int n,m;
ld sum=0;
int P[maxN],L[maxN],R[maxN],Spd[maxN];
int edgecnt=-1,Head[maxNode],Next[maxM],Id[maxN][maxN],S,T;
Edge E[maxM];
ld Tim[maxN];
int Q[maxNode],

bool check(ld t);
bool Bfs();
ld dfs(int u,ld flow);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d",&n,&m);sum=0;
		for (int i=1;i<=n;i++) scanf("%d%d%d",&P[i],&L[i],&R[i]),sum+=P[i];
		for (int i=1;i<=m;i++) scanf("%d",&Spd[i]);
		sort(&Spd[1],&Spd[m+1]);reverse(&Spd[1],&Spd[m+1]);
		for (int i=1;i<m;i++) Spd[i]=Spd[i]-Spd[i+1];
		ld L=0,R=1e9,Ans;
		do{
			ld mid=(L+R)/2.0;
			if (check(mid)) Ans=mid,R=mid-eps;
			else L=mid+eps;
		}
		while (L+eps<=R);
	}
}

bool check(ld t){
	int c1=0,cnt=1;
	for (int i=1;i<=n;i++) Tim[++c1]=L[i],Tim[++c1]=R[i]+t;
	sort(&Tim[1],&Tim[c1+1]);
	for (int i=2;i<=n;i++)
		if (fabs(Tim[i]-Tim[cnt])>eps) Tim[++cnt]=Tim[i];
	S=1;T=2;
	int idcnt=n+2;

	edgecnt=-1;mem(Head,-1);
	for (int i=1;i<=n;i++) Add_Edge(S,i+2,P[i]);
	for (int i=1;i<=m;i++)
		for (int j=1;j<cnt;j++){
			idcnt++;Add_Edge(idcnt,T,1.0*i*Spd[i]*(T[j+1]-T[j]));
			for (int k=1;k<=n;k++)
				if ((L[k]<Tim[j])&&(R[k]>Tim[j])) Add_Edge(i+2,idcnt,inf);
		}

	ld flow=0;
	while (Bfs()){
		for (int i=1;i<=idcnt;i++) cur[i]=Head[i];
		ld di;
		do{
			di=dfs(S,inf);
			flow+=di;
		}
		while (flow>eps);
	}

	return fabs(flow-sum)<eps;
}
