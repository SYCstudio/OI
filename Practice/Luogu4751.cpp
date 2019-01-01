#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxM=maxN<<1;

class Mat{
public:
	int a00,a01,a10,a11;
	Mat(){
		a00=a01=a10=a11=0;return;
	}
	Mat(int a,int b,int c,int d){
		a00=a;a01=b;a10=c;a11=d;return;
	}
};

class SegmentData{
public:
	int ls,rs,mid;Mat M;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Key[maxN];
int Sz[maxN],Hs[maxN],Fa[maxN],Top[maxN],dfncnt,dfn[maxN],lst[maxN],Id[maxN],Sum[maxN];
int nodecnt,root[maxN];
SegmentData S[maxN*20];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Update(int x);
Mat operator * (Mat A,Mat B);
void Build(int &x,int l,int r);
void Modify(int x,int l,int r,int pos);
Mat Query(int x,int l,int r,int ql,int qr);

int main(){
	mem(Head,-1);scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Key[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs1(1,1);dfs2(1,1);
	for (int i=1;i<=n;i++) Sum[i]+=Sum[i-1];
	for (int i=1;i<=n;i++) if (Top[i]==i) Build(rt[i],dfn[i],lst[i]);
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;return;
}
void dfs1(int u,int fa){
	Sz[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i]){
		dfs1(V[i],u);Sz[u]+=Sz[V[i]];Fa[V[i]]=u;
		if (Sz[Hs[u]]<Sz[V[i]]) Hs[u]=V[i];
	}
	return;
}
void dfs2(int u,int top){
	Top[u]=top;Id[dfn[u]=++dfncnt]=u;Sum[dfn[u]]=Sz[u]-Sz[Hs[u]];
	if (Hs[u]) dfs2(Hs[u],top),lst[u]=lst[Hs[u]];
	else lst[u]=u;
	G[u][1]=Key[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Top[u])&&(V[i]!=Fa[u])){
			dfs2(V[i],V[i]);G[u][1]+=F[V[i]][0];
			G[u][0]+=max(F[V[i]][0],F[V[i]][1]);
		}
	F[u][0]=G[u][0]+max(F[Hs[u]][0],F[Hs[u]][1]);
	F[u][1]=G[u][1]+F[Hs[u]][0];
	return;
}
void Build(int &x,int l,int r){
	if (x==0) x=++nodecnt;
	if (l==r){
		S[x].M=((Mat){G[Id[l]][0],G[Id[l]][0],G[Id[l]][1],-inf});return;
	}
	int mid=(Sum[r]-Sum[l-1])/2;
	int p=l;while ((p+1<r)&&(Sum[p+1]-Sum[l-1]<=mi)) ++p;
	S[x].mid=p;
	Build(S[x].ls,l,p);Build(S[x].rs,p+1,r);
	Update(x);return;
}
Mat operator * (Mat A,Mat B){
	Mat R;
	R.a00=max(A.a00+B.a00,A.a01+B.a10);
	R.a01=max(A.a00+B.a01,A.a01+B.a11);
	R.a10=max(A.a10+B.a00,A.a11+B.a10);
	R.a11=max(A.a10+B.a01,A.a11+B.a11);
	return R;
}
void Update(int x){
	if ((!S[x].ls)||(!S[x].rs)) S[x].M=S[S[x].ls+S[x].rs].M;
	else S[x].M=S[S[x].ls].M*S[S[x].rs].M;
}
void Modify(int x,int l,int r,int pos){
	if (l==r){
		S[x].M=((Mat){G[Id[l]][0],G[Id[l]][0],G[Id[l]][1],-inf});return;
	}
	if (pos<=S[x].mid) Modify(S[x].ls,l,S[x].mid,pos);
	else Modify(S[x].rs,S[x].mid+1,r,pos);
	Update(x);return;
}
Mat Query(int x,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[x].M;
	
}
