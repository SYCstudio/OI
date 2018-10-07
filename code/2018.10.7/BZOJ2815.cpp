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

const int maxN=70000;
const int maxM=1010000;
const int maxBit=18;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN];
int Fa[maxBit][maxN],Dph[maxN],Size[maxN];
vector<int> To[maxN],Fd[maxN];
queue<int> Q;

void Add_Edge(int u,int v);
int LCA(int u,int v);
void dfs(int u);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		while (x){
			Add_Edge(x,i);Fd[i].push_back(x);scanf("%d",&x);
		}
	}

	for (int i=1;i<=n;i++) if (Dg[i]==0) Q.push(i),To[n+1].push_back(i)/*,cout<<i<<" ";cout<<endl*/;
	while (!Q.empty()){
		int u=Q.front();Q.pop();

		for (int i=Head[u];i!=-1;i=Next[i])
			if ((--Dg[V[i]])==0) Q.push(V[i]);
		
		int lca=0;
		for (int i=0,sz=Fd[u].size();i<sz;i++)
			if (lca==0) lca=Fd[u][i];
			else lca=LCA(lca,Fd[u][i]);
		//cout<<"u:"<<u<<" "<<lca<<endl;
		//cout<<"FD:";for (int i=0,sz=Fd[u].size();i<sz;i++) cout<<Fd[u][i]<<" ";cout<<endl;
		if (lca==0){
			Fa[0][u]=n+1;Dph[u]=1;continue;
		}
		To[lca].push_back(u);
		Fa[0][u]=lca;Dph[u]=Dph[lca]+1;
		for (int i=1;i<maxBit;i++)
			if (Fa[i-1][u]) Fa[i][u]=Fa[i-1][Fa[i-1][u]];
	}
	dfs(n+1);
	for (int i=1;i<=n;i++) printf("%d\n",Size[i]-1);return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Dg[v]++;
	return;
}

int LCA(int u,int v){
	//cout<<"LCA:"<<u<<" "<<v<<":";
	if (Dph[u]<Dph[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Dph[Fa[i][u]]>=Dph[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

void dfs(int u){
	Size[u]=1;
	for (int i=0,sz=To[u].size();i<sz;i++){
		dfs(To[u][i]);Size[u]+=Size[To[u][i]];
	}
	return;
}
