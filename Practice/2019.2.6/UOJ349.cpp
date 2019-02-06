#include "rts.h"
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=303000;
const int maxM=maxN<<1;
const double alpha=0.8;
const int inf=1000000000;

int n,frt=1;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int Dsz[maxN],Sz[maxN],Mx[maxN],root,top,Bp[maxN];
bool vis[maxN],use[maxN];
map<int,int> Son[maxN];
vector<int> Dt[maxN];
int Seq[maxN],Sk[maxN+maxN];

void Add_Edge(int u,int v);
void Solve(int u,int q);
void dfs_mark(int u);
void dfs_root(int u,int fa,int size);
void Divide(int u,int size);

void play(int _n, int T, int dataType) {
	mem(Head,-1);n=_n;use[1]=1;Mx[0]=inf;vis[1]=use[1]=1;
	for (int i=1;i<=n;i++) Seq[i]=i;
	for (int i=1;i<=n;i++){
		int u=rand()%n+1,v=rand()%n+1;
		swap(Seq[u],Seq[v]);
	}
	if (dataType==3){
		int left=maxN,right=maxN;Sk[left]=1;
		for (int ti=1;ti<=n;ti++)
			if (vis[Seq[ti]]==0){
				int t=Seq[ti];
				int r=explore(Sk[left],t);
				if (r==Sk[left+1]){
					do{
						r=explore(Sk[right],t);
						Sk[++right]=r;vis[r]=1;
					}
					while (r!=t);
				}
				else{
					Sk[--left]=r;vis[r]=1;
					while (r!=t){
						r=explore(Sk[left],t);
						Sk[--left]=r;vis[r]=1;
					}
				}
			}
		return;
	}
	for (int ti=1;ti<=n;++ti)
		if (use[Seq[ti]]==0){
			int t=Seq[ti];
			top=0;Solve(frt,t);
			for (int i=1;i<top;i++)
				if (Dsz[Bp[i]]*alpha<Dsz[Bp[i+1]]){
					int u=Bp[i];
					dfs_mark(u);
					root=0;dfs_root(u,u,Dsz[u]);
					if (i!=1){
						for (map<int,int>::iterator it=Son[Bp[i-1]].begin();it!=Son[Bp[i-1]].end();++it)
							if ((*it).second==u){
								int ut=(*it).first;Son[Bp[i-1]][ut]=root;
								break;
							}
						for (int j=0,sz=Dt[Bp[i-1]].size();j<sz;j++)
							if (Dt[Bp[i-1]][j]==u){
								Dt[Bp[i-1]][j]=root;break;
							}
					}
					//cout<<"nrt:"<<root<<endl;
					if (u==frt) frt=root;
					Divide(root,Dsz[u]);
					break;
				}
		}
	return;
}
void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}
void Solve(int u,int q){
	//cout<<"Solve:"<<u<<" "<<q<<endl;
	int r=explore(u,q);Bp[++top]=u;
	if (r==q){
		Bp[++top]=q;
		Add_Edge(u,q);Dsz[q]=1;++Dsz[u];
		Son[u][q]=q;Dt[u].push_back(q);use[q]=vis[q]=1;
	}
	else if (Son[u].count(r)){
		Dsz[u]-=Dsz[Son[u][r]];Solve(Son[u][r],q);Dsz[u]+=Dsz[Son[u][r]];
	}
	else{
		Son[u][r]=r;use[r]=vis[r]=1;Add_Edge(u,r);Dsz[r]=1;Dt[u].push_back(r);
		Solve(r,q);Dsz[u]+=Dsz[r];
	}
}
void dfs_mark(int u){
	vis[u]=0;Son[u].clear();
	for (int i=0,sz=Dt[u].size();i<sz;i++) dfs_mark(Dt[u][i]);
	Dt[u].clear();return;
}
void dfs_root(int u,int fa,int size){
	Sz[u]=1;Mx[u]=0;
	//cout<<"dfsroot:"<<u<<" "<<fa<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa&&vis[V[i]]==0){
			dfs_root(V[i],u,size);Sz[u]+=Sz[V[i]];
			Mx[u]=max(Mx[u],Sz[V[i]]);
		}
	Mx[u]=max(Mx[u],size-Sz[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}
void Divide(int u,int size){
	//cout<<"Divide:"<<u<<" "<<size<<endl;
	Dsz[u]=size;vis[u]=1;Son[u].clear();
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			int s=(Sz[V[i]]>Sz[u])?size-Sz[u]:Sz[V[i]];
			root=0;dfs_root(V[i],V[i],s);
			//cout<<u<<"->"<<root<<endl;
			Son[u][V[i]]=root;Dt[u].push_back(root);Divide(root,s);
		}
	return;
}