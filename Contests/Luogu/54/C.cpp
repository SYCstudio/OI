#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1100000;
const int maxM=maxN*21;
const int inf=2147483647;

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],NW[maxN],Dist[maxN],Id[maxN];
int Q[maxN],Dg[maxN];
vector<int> Ans[200];

void Add_Edge(int u,int v);

int main(){
	//freopen("in.in","r",stdin);freopen("out","w",stdout);
	mem(Head,-1);
	scanf("%d%d",&n,&K);
	for (int i=0;i<(1<<K);i++)
		for (int j=0;j<K;j++)
			if (i&(1<<j)) Add_Edge(i^(1<<j),i);
	for (int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		NW[x]=1;Id[x]=i;
	}
	int h=1,t=0;Q[1]=0;Dist[0]=NW[0];
	do for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i]){
			Dist[V[i]]=max(Dist[V[i]],Dist[u]+NW[V[i]]);
			if ((--Dg[V[i]])==0) Q[++h]=V[i];
		}
	while (h!=t);
	printf("1\n");
	int mx=0;
	for (int i=0;i<(1<<K);i++)
		if (Id[i]){
			Ans[Dist[i]].push_back(i);
			mx=max(mx,Dist[i]);
		}
	printf("%d\n",mx);
	for (int i=1;i<=mx;i++){
		int sz=Ans[i].size();
		printf("%d ",sz);
		for (int j=0;j<sz;j++){
			printf("%d",Ans[i][j]);
			if (j!=sz-1) printf(" ");
		}
		printf("\n");
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;++Dg[v];
	return;
}
