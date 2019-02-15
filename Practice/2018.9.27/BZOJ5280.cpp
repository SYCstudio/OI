#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN];
vector<int> M[maxN];
priority_queue<int,vector<int>,greater<int> > H;
queue<int> Q;

void Add_Edge(int u,int v);
bool check(int mid);
void PushEdge(int limit);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int mi;scanf("%d",&mi);
		for (int j=1;j<=mi;j++){
			int u;scanf("%d",&u);
			M[i].push_back(u);
		}
	}
	int L=0,R=m,X=0;
	do{
		int mid=(L+R)>>1;
		if (check(mid)) X=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);

	PushEdge(X);
	for (int i=1;i<=n;i++) if (Dg[i]==0) H.push(i);
	do{
		int u=H.top();H.pop();printf("%d ",u);
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((--Dg[V[i]])==0) H.push(V[i]);
	}
	while (!H.empty());
	printf("\n");return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Dg[v]++;
	return;
}

bool check(int mid){
	PushEdge(mid);
	for (int i=1;i<=n;i++) if (Dg[i]==0) Q.push(i);
	int cnt=0;
	while (!Q.empty()){
		int u=Q.front();Q.pop();cnt++;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((--Dg[V[i]])==0) Q.push(V[i]);
	}
	return cnt==n;
}

void PushEdge(int limit){
	edgecnt=0;mem(Head,-1);mem(Dg,0);
	for (int i=1;i<=limit;i++)
		for (int j=1;j<M[i].size();j++)
			Add_Edge(M[i][j-1],M[i][j]);
	return;
}
