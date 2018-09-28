#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1020;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
vector<pair<int,int> > Vc[maxN];
bool vis[maxN];
int NodeW[maxN];

void Add_Edge(int u,int v,int w);
bool dfs(int u);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		edgecnt=0;mem(Head,-1);mem(vis,0);mem(NodeW,0);
		scanf("%d%d%d",&n,&m,&K);
		for (int i=1;i<=n;i++) Vc[i].clear();
		for (int i=1;i<=K;i++){
			int x,y,c;scanf("%d%d%d",&x,&y,&c);
			Vc[x].push_back(make_pair(y,c));
		}

		for (int i=1;i<=n;i++)
			if (Vc[i].size()){
				sort(Vc[i].begin(),Vc[i].end());
				for (int j=1,sz=Vc[i].size();j<sz;j++)
					Add_Edge(Vc[i][j-1].first,Vc[i][j].first,Vc[i][j].second-Vc[i][j-1].second);
			}

		bool flag=1;
		for (int i=1;i<=m;i++)
			if (vis[i]==0)
				if (dfs(i)==0){
					flag=0;break;
				}

		if (flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=-w;
	return;
}

bool dfs(int u){
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			NodeW[V[i]]=NodeW[u]+W[i];
			if (dfs(V[i])==0) return 0;
		}
		else if (NodeW[V[i]]!=NodeW[u]+W[i]) return 0;
	return 1;
}
/*
2
2 2 4
1 1 0
1 2 0
2 1 2
2 2 2
2 2 4
1 1 0
1 2 0
2 1 2
2 2 1
//*/
