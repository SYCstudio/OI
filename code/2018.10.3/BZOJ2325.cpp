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

const int maxN=50100;
const int maxM=maxN<<1;
const int inf=100000000;

class SegmentData
{
public:
	int d11,d12,d21,d22;
	int f11,f12,f21,f22;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Hs[maxN],Top[maxN],Fa[maxN],Dpt[maxN];
int dfncnt,dfn[maxN];
char Ar[maxN][5];
SegmentData S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Modify(int now,int l,int r,int pos,int key);
SegmentData Query(int now,int l,int r,int ql,int qr);
int LCA(int u,int v);
SegmentData operator + (SegmentData A,SegmentData B);
void Outp(int now,int l,int r);
ostream & operator << (ostream &os,SegmentData A);

int main(){
	//freopen("in","r",stdin);freopen("out","w",stdout);
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	Dpt[1]=1;dfs1(1,1);dfs2(1,1);
	for (int i=1;i<=n;i++){
		scanf("%s",Ar[i]);
		int key=0;
		if (Ar[i][0]=='.') key|=1;
		if (Ar[i][1]=='.') key|=2;
		Modify(1,1,n,dfn[i],key);
	}

	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	//Outp(1,1,n);cout<<endl;
	while (m--){
		char opt;
		scanf(" %c",&opt);
		if (opt=='C'){
			int u;scanf("%d",&u);scanf(" %s",Ar[u]);
			int key=0;
			if (Ar[u][0]=='.') key|=1;
			if (Ar[u][1]=='.') key|=2;
			Modify(1,1,n,dfn[u],key);
		}
		if (opt=='Q'){
			int u,v;scanf("%d%d",&u,&v);
			printf("%d\n",LCA(u,v));
		}
		//Outp(1,1,n);cout<<endl;
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	Size[u]=1;Hs[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Dpt[V[i]]=Dpt[u]+1;Fa[V[i]]=u;dfs1(V[i],u);
			Size[u]+=Size[V[i]];
			if (Size[V[i]]>Size[Hs[u]]) Hs[u]=V[i];
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

void Modify(int now,int l,int r,int pos,int key){
	if (l==r){
		S[now].d11=S[now].d12=S[now].d21=S[now].d22=-inf;
		S[now].f11=S[now].f12=S[now].f21=S[now].f22=-inf;
		if (key&1) S[now].d11=S[now].f11=S[now].f21=1;
		if (key&2) S[now].d22=S[now].f12=S[now].f22=1;
		if ((key&1)&&(key&2)) S[now].d12=S[now].d21=S[now].f11=S[now].f12=S[now].f21=S[now].f22=2;
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	S[now]=S[lson]+S[rson];return;
}

SegmentData Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}

int LCA(int u,int v){
	if ((Ar[u][0]=='#')&&(Ar[u][1]=='#')) return 0;
	SegmentData A1,A2;
	A1=A2=((SegmentData){0,0,0,0,0,0,0,0});
	while (Top[u]!=Top[v]){
		if (Dpt[Top[u]]>Dpt[Top[v]]) A1=Query(1,1,n,dfn[Top[u]],dfn[u])+A1,u=Fa[Top[u]];
		else A2=Query(1,1,n,dfn[Top[v]],dfn[v])+A2,v=Fa[Top[v]];
	}
	if (Dpt[u]<Dpt[v]) A2=Query(1,1,n,dfn[u],dfn[v])+A2;
	else A1=Query(1,1,n,dfn[v],dfn[u])+A1;
	//cout<<"A1:"<<A1<<endl<<"A2:"<<A2<<endl;
	swap(A1.d12,A1.d21);swap(A1.f11,A1.f21);swap(A1.f12,A1.f22);
	A1=A1+A2;
	return max(A1.f11,A1.f12);
}

SegmentData operator + (SegmentData A,SegmentData B){
	SegmentData rt;
	rt.d11=max(A.d11+B.d11,A.d12+B.d21);if (rt.d11<0) rt.d11=-inf;
	rt.d12=max(A.d12+B.d22,A.d11+B.d12);if (rt.d12<0) rt.d12=-inf;
	rt.d21=max(A.d21+B.d11,A.d22+B.d21);if (rt.d21<0) rt.d21=-inf;
	rt.d22=max(A.d22+B.d22,A.d21+B.d12);if (rt.d22<0) rt.d22=-inf;
	rt.f11=max(A.f11,max(A.d11+B.f11,A.d12+B.f12));if (rt.f11<0) rt.f11=-inf;
	rt.f12=max(A.f12,max(A.d21+B.f11,A.d22+B.f12));if (rt.f12<0) rt.f12=-inf;
	rt.f21=max(B.f21,max(B.d11+A.f21,B.d21+A.f22));if (rt.f21<0) rt.f21=-inf;
	rt.f22=max(B.f22,max(B.d12+A.f21,B.d22+A.f22));if (rt.f22<0) rt.f22=-inf;
	//cout<<"Merge:("<<A<<") ("<<B<<") -> "<<rt<<endl;
	return rt;
}

void Outp(int now,int l,int r){
	cout<<"["<<l<<","<<r<<"] "<<S[now].d11<<" "<<S[now].d12<<" "<<S[now].d21<<" "<<S[now].d22<<" "<<S[now].f11<<" "<<S[now].f12<<" "<<S[now].f21<<" "<<S[now].f22<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	Outp(lson,l,mid);Outp(rson,mid+1,r);
	return;
}

ostream & operator << (ostream &os,SegmentData A){
	os<<A.d11<<" "<<A.d12<<" "<<A.d21<<" "<<A.d22<<" "<<A.f11<<" "<<A.f12<<" "<<A.f21<<" "<<A.f22;return os;
}
