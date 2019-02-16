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

const int maxN=50500;
const int maxM=maxN;
const int Mod=2019;
const int inf=2147483647;

class SegmentData
{
public:
	int sc,ssc,s,ss,lz;
};

int n,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],NW[maxN];
int Size[maxN],Top[maxN],Hs[maxN],Fa[maxN],Dph[maxN],dfncnt,dfn[maxN],lst[maxN],ifd[maxN];
SegmentData S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u);
void dfs2(int u,int top);
void Update(int now);
void PushDown(int now);
void Plus(int now,int key);
void Build(int now,int l,int r);
void Modify(int now,int l,int r,int ql,int qr,int key);
int Query(int now,int l,int r,int ql,int qr,int size);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&Q);
	for (int i=2;i<=n;i++){
		scanf("%d%d",&Fa[i],&NW[i]);
		Add_Edge(Fa[i],i);
	}

	dfs1(1);dfs2(1,1);
	Build(1,1,n);

	//for (int i=1;i<=n;i++) cout<<ifd[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" "<<lst[i]<<endl;

	char opt[10];
	while (Q--){
		scanf(" %s",opt);
		if (opt[0]=='I'){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);w%=Mod;
			while (Top[u]!=Top[v]){
				if (Dph[Top[u]]<Dph[Top[v]]) swap(u,v);
				Modify(1,1,n,dfn[Top[u]],dfn[u],w);
				u=Fa[Top[u]];
			}
			if (Dph[u]>Dph[v]) swap(u,v);
			if (u!=v) Modify(1,1,n,dfn[u]+1,dfn[v],w);
		}
		if (opt[0]=='A'){
			int u;scanf("%d",&u);
			if (dfn[u]==lst[u]) printf("0\n");
			else printf("%d\n",(Query(1,1,n,dfn[u]+1,lst[u],Size[u])+Mod)%Mod);
		}
	}

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u){
	Size[u]=1;Hs[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i]){
		Dph[V[i]]=Dph[u]+1;
		dfs1(V[i]);Size[u]+=Size[V[i]];
		if (Size[V[i]]>Size[Hs[u]]) Hs[u]=V[i];
	}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;ifd[dfn[u]=++dfncnt]=u;
	if (Hs[u]==0){
		lst[u]=dfncnt;return;
	}
	dfs2(Hs[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Hs[u]) dfs2(V[i],V[i]);
	lst[u]=dfncnt;return;
}

void Update(int now){
	S[now].sc=(S[lson].sc+S[rson].sc)%Mod;
	S[now].ssc=(S[lson].ssc+S[rson].ssc)%Mod;
	S[now].s=(S[lson].s+S[rson].s)%Mod;
	S[now].ss=(S[lson].ss+S[rson].ss)%Mod;
	return;
}

void PushDown(int now){
	if (S[now].lz){
		Plus(lson,S[now].lz);
		Plus(rson,S[now].lz);
		S[now].lz=0;
	}
	return;
}

void Plus(int now,int key){
	S[now].sc=(S[now].sc+S[now].s*key%Mod)%Mod;
	S[now].ssc=(S[now].ssc+S[now].ss*key%Mod)%Mod;
	S[now].lz=(S[now].lz+key)%Mod;return;
}

void Build(int now,int l,int r){
	if (l==r){
		int u=ifd[l];
		S[now].sc=Size[u]*NW[u]%Mod;
		S[now].ssc=Size[u]%Mod*Size[u]%Mod*NW[u]%Mod;
		S[now].s=Size[u]%Mod;
		S[now].ss=Size[u]%Mod*Size[u]%Mod;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Update(now);return;
}

void Modify(int now,int l,int r,int ql,int qr,int key){
	if ((l==ql)&&(r==qr)){
		Plus(now,key);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	Update(now);return;
}

int Query(int now,int l,int r,int ql,int qr,int size){
	//cout<<"Query:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<size<<":"<<S[now].sc<<" "<<S[now].ssc<<" "<<S[now].s<<" "<<S[now].ss<<endl;
	if ((l==ql)&&(r==qr)) return (size%Mod*S[now].sc%Mod-S[now].ssc)%Mod;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr,size);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr,size);
	else return (Query(lson,l,mid,ql,mid,size)+Query(rson,mid+1,r,mid+1,qr,size))%Mod;
}
