#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100;
const int inf=2147483647;

int n,id;
int Size[maxN],Depth[maxN];
int Ls[maxN],Rs[maxN],Fa[maxN];
int Seq[maxN];

void dfs_init(int u);
void dfs_min(int u);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int d;scanf("%d",&d);
		if (d<100) Ls[d]=i,Fa[i]=d;
		else Rs[d-100]=i,Fa[i]=d-100;
	}
	Depth[0]=1;
	dfs_init(0);

	//for (int i=0;i<=n;i++) cout<<Ls[i]<<" "<<Rs[i]<<endl;
	//for (int i=0;i<=n;i++) cout<<Size[i]<<" ";cout<<endl<<endl;

	int root=0;Depth[n+1]=inf;
	for (int i=1;i<=n+1;i++){
		id=n+1;
		dfs_min(root);

		if ((Ls[id])&&(Size[Ls[id]]==1)) id=Ls[id];
		
		Seq[i]=id;
		if (id==root){
			root=Ls[root];Depth[root]=1;Fa[root]=-1;
		}
		else{
			if (Ls[id]) Fa[Ls[id]]=Fa[id],Ls[Fa[id]]=Ls[id];
			else Ls[Fa[id]]=0;
			for (int now=Fa[id];now!=root;now=Fa[now]) swap(Ls[now],Rs[now]);
			swap(Ls[root],Rs[root]);
		}
		dfs_init(root);

		//cout<<root<<" "<<id<<endl;
		//for (int j=0;j<=n;j++) cout<<Ls[j]<<" "<<Rs[j]<<endl;
		//for (int j=0;j<=n;j++) cout<<Fa[j]<<" ";cout<<endl;
		//for (int j=0;j<=n;j++) cout<<Size[j]<<" ";cout<<endl<<endl;
	}

	for (int i=n+1;i>=1;i--) printf("%d ",Seq[i]);
	return 0;
}

void dfs_init(int u){
	Size[u]=1;
	if (Ls[u]){
		Depth[Ls[u]]=Depth[u]+1;
		dfs_init(Ls[u]);Size[u]+=Size[Ls[u]];
	}
	if (Rs[u]){
		Depth[Rs[u]]=Depth[u]+1;
		dfs_init(Rs[u]);Size[u]+=Size[Rs[u]];
	}
	return;
}

void dfs_min(int u){
	if ((Rs[u]==0)&&(Depth[u]<Depth[id])) id=u;
	if (Ls[u]) dfs_min(Ls[u]);
	return;
}
