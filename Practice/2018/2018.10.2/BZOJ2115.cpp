#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50500;
const int maxM=101000<<1;
const int maxBit=64;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Base[maxBit],W[maxM],NW[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,ll w);
void dfs(int u);
void Insert(ll key);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;ll w;scanf("%d%d%lld",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	dfs(1);
	ll Ans=NW[n];
	for (int i=maxBit-1;i>=0;i--)
		Ans=max(Ans,Ans^Base[i]);
	printf("%lld\n",Ans);return 0;
}

void Add_Edge(int u,int v,ll w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs(int u){
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			NW[V[i]]=NW[u]^W[i];dfs(V[i]);
		}
		else Insert(NW[u]^NW[V[i]]^W[i]);
	return;
}

void Insert(ll key){
	for (int i=maxBit-1;i>=0;i--)
		if (key&(1ll<<i)){
			if (Base[i]==0){
				Base[i]=key;return;
			}
			key^=Base[i];
		}
	return;
}
