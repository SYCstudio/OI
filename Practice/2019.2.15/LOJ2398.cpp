#include "park.h"
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;

#define RG register
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=1401;
const int maxM=1500<<1;

int n;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],Qu[maxN],qsize,Qs[maxN];
int vis[maxN],tim,Tim[maxN],check[maxN];

void Solve(int S,int T);
bool Bfs();
void Add_Edge(int u,int v);

void Detect(int T,int N){
	n=N;mem(vis,0);vis[0]=1;mem(Head,-1);edgecnt=-1;
	for (int i=1;i<n;i++) if (vis[i]==0) Solve(0,i);
}

void Solve(int S,int T){
	RG int i,l,r,pos,mid;
	if (S==T||vis[T]) return;
	mem(Qs,0);Qs[S]=Qs[T]=1;
	if (!Ask(min(S,T),max(S,T),Qs)){
		l=0;r=n-1;pos=-1;
		while (l<=r){
			mid=(l+r)>>1;
			memcpy(Qs,vis,sizeof(vis));
			for (i=0;i<=mid;++i) Qs[i]=1;
			Qs[S]=Qs[T]=1;
			if (Ask(min(S,T),max(S,T),Qs)) pos=mid,r=mid-1;
			else l=mid+1;
		}
		if (pos!=-1&&pos!=S){
			Solve(S,pos);Solve(pos,T);return;
		}
	}
	mem(check,0);
	while (Bfs()){
		//cout<<"Qu:";for (int i=1;i<=qsize;i++) cout<<Qu[i]<<" ";cout<<endl;
		mem(Qs,0);
		for (i=1;i<=qsize;++i) Qs[Qu[i]]=1;
		Qs[T]=1;
		if (!Ask(min(Qu[1],T),max(Qu[1],T),Qs)){
			for (i=1;i<=qsize;++i) check[Qu[i]]=1;
			continue;
		}
		l=1;r=qsize;pos=-1;
		while (l<=r){
			mid=(l+r)>>1;mem(Qs,0);Qs[T]=1;
			for (i=1;i<=mid;++i) Qs[Qu[i]]=1;
			if (Ask(min(Qu[1],T),max(Qu[1],T),Qs)) pos=mid,r=mid-1;
			else l=mid+1;
		}
		Add_Edge(Qu[pos],T);check[Qu[pos]]=1;
	}
	vis[T]=1;
	return;
}
bool Bfs(){
	qsize=0;++tim;
	for (int i=0;i<n&&!qsize;i++) if (vis[i]&&!check[i]) Tim[Qu[++qsize]=i]=tim;
	if (!qsize) return 0;
	int ql=1,qr=1;
	while (ql<=qr) for (int u=Qu[ql++],i=Head[u];i!=-1;i=Next[i]) if (!check[V[i]]&&Tim[V[i]]!=tim) Tim[Qu[++qr]=V[i]]=tim;
	qsize=qr;return 1;
}
void Add_Edge(int u,int v){
	//cout<<"Add:"<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	Answer(min(u,v),max(u,v));return;
}