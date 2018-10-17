#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,S;
int NW[maxN];
map<int,int> M;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Ans=0;

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&S);
	for (int i=1;i<=n;i++) scanf("%d",&NW[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	M[0]=1;
	dfs(1,0);
	printf("%lld\n",Ans);return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int fa){
	NW[u]=NW[u]+NW[fa];
	M[NW[u]]++;
	Ans=Ans+M[NW[u]-S];
	for (int i=Head[u];i!=-1;i=Next[i])
		dfs(V[i],u);
	M[NW[u]]--;
	return;
}
