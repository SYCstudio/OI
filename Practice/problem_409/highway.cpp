#include "highway.h"
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back
#define ft first
#define sd second
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=90100;

int n,m;
vector<int> Rw;
vector<pair<int,int> > T[maxN];
int Dist[2][maxN],dfncnt,dfn[2][maxN],idfn[2][maxN],Fa[2][maxN],Qu[maxN];
bool vis[maxN];

void Bfs(int u,int opt);
bool dfs_getdfn(int u,int opt);

void find_pair(int N,vector<int> U,vector<int> V,int A,int B){
	m=U.size();n=N;
	for (int i=0;i<m;i++) T[U[i]+1].pb(mp(V[i]+1,i+1)),T[V[i]+1].pb(mp(U[i]+1,i+1));
	for (int i=0;i<m;i++) Rw.push_back(0);
	ll DIST=ask(Rw);
	//cout<<"DIST:"<<DIST<<endl;
	
	int l=0,r=m-1,p=0;
	while (l<=r){
		int mid=(l+r)>>1;
		for (int i=0;i<=mid;i++) Rw[i]=0;for (int i=mid+1;i<m;i++) Rw[i]=1;
		if (ask(Rw)==DIST) p=mid,r=mid-1;
		else l=mid+1;
	}
	int su=U[p]+1,sv=V[p]+1,dfn1,dfn2,S,T;
	//cout<<su<<" "<<sv<<endl;
	mem(vis,0);Bfs(su,0);
	mem(vis,0);Bfs(sv,1);
	mem(vis,0);dfncnt=0;dfs_getdfn(su,0);dfn1=dfncnt;
	mem(vis,0);dfncnt=0;dfs_getdfn(sv,1);dfn2=dfncnt;

	DIST=DIST/A*B;
	/*
	cout<<"DIST:"<<DIST<<endl;
	cout<<n<<endl;
	for (int i=1;i<=n;i++) cout<<Dist[0][i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Dist[1][i]<<" ";cout<<endl;
	for (int i=1;i<=dfn1;i++) cout<<idfn[0][i]<<" ";cout<<endl;
	for (int i=1;i<=dfn2;i++) cout<<idfn[1][i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Fa[0][i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Fa[1][i]<<" ";cout<<endl;
	//*/

	for (int i=0;i<m;i++) Rw[i]=1;
	l=1;r=dfn1;p=1;
	while (l<=r){
		int mid=(l+r)>>1;
		for (int i=1;i<mid;i++) if (Fa[0][idfn[0][i]]) Rw[Fa[0][idfn[0][i]]-1]=1;
		for (int i=mid;i<=dfn1;i++) if (Fa[0][idfn[0][i]]) Rw[Fa[0][idfn[0][i]]-1]=0;
		if (ask(Rw)!=DIST) p=mid,l=mid+1;
		else r=mid-1;
	}
	S=idfn[0][p]-1;

	for (int i=0;i<m;i++) Rw[i]=1;
	l=1;r=dfn2;p=1;
	while (l<=r){
		int mid=(l+r)>>1;
		for (int i=1;i<mid;i++) if (Fa[1][idfn[1][i]]) Rw[Fa[1][idfn[1][i]]-1]=1;
		for (int i=mid;i<=dfn2;i++) if (Fa[1][idfn[1][i]]) Rw[Fa[1][idfn[1][i]]-1]=0;
		if (ask(Rw)!=DIST) p=mid,l=mid+1;
		else r=mid-1;
	}
	T=idfn[1][p]-1;
	answer(S,T);return;
}
void Bfs(int S,int opt){
	int ql=1,qr=1;Dist[opt][S]=0;Qu[1]=S;vis[S]=1;
	while (ql<=qr)
		for (int u=Qu[ql++],i=0,sz=T[u].size();i<sz;i++)
			if (vis[T[u][i].first]==0){
				Dist[opt][T[u][i].first]=Dist[opt][u]+1;
				Qu[++qr]=T[u][i].first;vis[T[u][i].first]=1;
			}
	return;
}
bool dfs_getdfn(int u,int opt){
	if ( (Dist[opt][u]>Dist[opt^1][u]) || ((Dist[opt][u]==Dist[opt^1][u])&&(opt==1))) return 0 ;
	vis[u]=1;
	idfn[opt][dfn[opt][u]=++dfncnt]=u;
	for (int i=0,sz=T[u].size();i<sz;i++){
		int v=T[u][i].first;if (vis[v]) continue;
		if (dfs_getdfn(v,opt)) Fa[opt][v]=T[u][i].second;
	}
	return 1;
}
