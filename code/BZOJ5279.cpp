#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int maxM=maxN<<1;
const int meminf=2139062143;
const int inf=2147483647;

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Hs[maxN],Fa[maxN],Top[maxN],Dph[maxN];
int nodecnt=0,rt[maxN],dfncnt,dfn[maxN];
int Mn[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Cover(int u,int v,int w);
void Modify(int now,int l,int r,int ql,int qr,int key);
int Query(int now,int l,int r,int pos);

int main(){
	mem(Head,-1);mem(Mn,127);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	Dph[1]=1;dfs1(1,1);dfs2(1,1);

	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Hs[i]<<" ";cout<<endl;

	while (m--){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Cover(u,v,w);
	}

	for (int i=0;i<=edgecnt;i+=2){
		//cout<<V[i]<<" "<<V[i^1]<<endl;
		int mn=meminf;
		if (Dph[V[i]]>Dph[V[i^1]]) mn=Query(1,1,n,dfn[V[i]]);
		else mn=Query(1,1,n,dfn[V[i^1]]);
		if (mn==meminf) printf("-1\n");
		else printf("%d\n",mn);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Dph[V[i]]=Dph[u]+1;Fa[V[i]]=u;
			dfs1(V[i],u);Size[u]+=Size[V[i]];
			if (Size[V[i]]>Hs[u]) Hs[u]=V[i];
		}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;dfn[u]=++dfncnt;
	if (Hs[u]==0) return;
	dfs2(Hs[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u]))
			dfs2(V[i],V[i]);
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key){
	if ((l==ql)&&(r==qr)){
		Mn[now]=min(Mn[now],key);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	return;
}

int Query(int now,int l,int r,int pos){
	if (l==r) return Mn[now];
	int mid=(l+r)>>1;
	if (pos<=mid) return min(Mn[now],Query(lson,l,mid,pos));
	else return min(Mn[now],Query(rson,mid+1,r,pos));
}

void Cover(int u,int v,int w){
	//cout<<"Cover:"<<u<<" "<<v<<" "<<w<<endl;
	while (Top[u]!=Top[v]){
		//cout<<u<<" "<<v<<" "<<Top[u]<<" "<<Top[v]<<endl;
		if (Dph[Top[u]]<Dph[Top[v]]) swap(u,v);
		Modify(1,1,n,dfn[Top[u]],dfn[u],w);
		u=Fa[Top[u]];
	}
	if (Dph[u]>Dph[v]) swap(u,v);
	if (u!=v) Modify(1,1,n,dfn[u]+1,dfn[v],w);
	return;
}
