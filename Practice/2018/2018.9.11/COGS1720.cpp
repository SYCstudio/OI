#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "graphgame"

const int maxN=1010;
const int maxM=50100*2;
const int inf=2147483647;

int n1,n2,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Match[maxN];
int tim,Tim[maxN];

void Add_Edge(int u,int v);
bool Hungary(int u);
bool dfs(int u);

int main(){
	freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	mem(Head,-1);
	scanf("%d%d%d",&n1,&n2,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);v+=n1;
		Add_Edge(u,v);Add_Edge(v,u);
	}

	mem(Match,-1);
	for (int i=1;i<=n1+n2;i++)
		if (Match[i]==-1){
			tim++;Hungary(i);
		}

	for (int i=1;i<=n1;i++)
		if (Match[i]==-1) printf("P");
		else{
			tim++;Tim[i]=tim;
			if (dfs(Match[i])) printf("P");
			else printf("N");
		}

	printf("\n");
	for (int i=1;i<=n2;i++)
		if (Match[n1+i]==-1) printf("P");
		else{
			tim++;Tim[n1+i]=tim;
			if (dfs(Match[n1+i])) printf("P");
			else printf("N");
		}
	printf("\n");return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

bool Hungary(int u){
	Tim[u]=tim;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Tim[V[i]]!=tim){
			Tim[V[i]]=tim;
			if ((Match[V[i]]==-1)||(Hungary(Match[V[i]]))){
				Match[V[i]]=u;Match[u]=V[i];return 1;
			}
		}
	return 0;
}

bool dfs(int u){
	Tim[u]=tim;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Tim[V[i]]!=tim){
			Tim[V[i]]=tim;
			if ((Match[V[i]]==-1)||(dfs(Match[V[i]]))) return 1;
		}
	return 0;
}
