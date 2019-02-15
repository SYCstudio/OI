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
const int inf=2147483647;

class SegmentData
{
public:
	ll sum,lz;
};

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Hs[maxN],dfncnt,dfn[maxN],lst[maxN],Dph[maxN],Top[maxN],Fa[maxN];
SegmentData S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u);
void dfs2(int u,int top);
void Modify(int now,int l,int r,int ql,int qr,ll key);
ll Query(int now,int l,int r,int ql,int qr);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);++u;++v;Add_Edge(u,v);
	}
	Dph[1]=1;dfs1(1);dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<Dph[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	int Q;scanf("%d",&Q);
	while (Q--){
		char opt[10];scanf("%s",opt);
		if (opt[0]=='A'){
			int u,v;ll w;scanf("%d%d%lld",&u,&v,&w);u++;v++;
			//cout<<u<<" "<<v<<endl;
			while (Top[u]!=Top[v]){
				if (Dph[Top[u]]<Dph[Top[v]]) swap(u,v);
				Modify(1,1,n,dfn[Top[u]],dfn[u],w);
				u=Fa[Top[u]];
			}
			if (Dph[u]>Dph[v]) swap(u,v);
			Modify(1,1,n,dfn[u],dfn[v],w);
		}
		if (opt[0]=='Q'){
			int u;scanf("%d",&u);u++;
			printf("%lld\n",Query(1,1,n,dfn[u],lst[u]));
		}
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u){
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i]){
		Fa[V[i]]=u;Dph[V[i]]=Dph[u]+1;
		dfs1(V[i]);Size[u]+=Size[V[i]];
		if (Size[V[i]]>Size[Hs[u]]) Hs[u]=V[i];
	}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;dfn[u]=++dfncnt;
	if (Hs[u]!=0){
		dfs2(Hs[u],top);
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=Hs[u]) dfs2(V[i],V[i]);
	}
	lst[u]=dfncnt;return;
}

void Modify(int now,int l,int r,int ql,int qr,ll key){
	S[now].sum+=key*(qr-ql+1);
	if ((l==ql)&&(r==qr)){
		S[now].lz+=key;return;
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

ll Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;ll rt=S[now].lz*(qr-ql+1);
	if (qr<=mid) return Query(lson,l,mid,ql,qr)+rt;
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr)+rt;
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr)+rt;
}

