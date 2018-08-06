#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Match[maxN];
int tim,Tim[maxN];

void Add_Edge(int u,int v);
bool dfs(int u);

int main(){
	mem(Head,-1);mem(Match,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int a,b;scanf("%d%d",&a,&b);
		Add_Edge(a,i);Add_Edge(b,i);
	}

	int ans=0;tim++;
	while (dfs(ans+1)) ans++,tim++;

	printf("%d\n",ans);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

bool dfs(int u){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Tim[V[i]]!=tim){
			Tim[V[i]]=tim;
			if ((Match[V[i]]==-1)||(dfs(Match[V[i]]))){
				Match[V[i]]=u;return 1;
			}
		}
	return 0;
}
