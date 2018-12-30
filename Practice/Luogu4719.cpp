#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int maxM=maxN<<1;

class Mat{
public:
	int a00,a01,a10,a11;
	Mat(){}
	Mat(int a,int b,int c,int d){
		a00=a;a01=b;a10=c;a11=d;return;
	}
};

class SegmentData{
public:
	int ls,rs;Mat M;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Key[maxN];
int Sz[maxN],Hs[maxN],Top[maxN],Fa[maxN],dfncnt,dfn[maxN];
int F[maxN][2],G[maxN][2];
SegmentData S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
Mat operator * (Mat A,Mat B);
void Update(int x);
void Modify(int x,int l,int r,int pos,Mat M);
Mat Query(int x,int l,int r,int ql,int qr);
void Skip(int u);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Key[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs1(1,1);dfs2(1,1);
	for (int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		Key[x]=y;Skip(x);
		printf("%d\n",max(S[1].M.a00,S[1].M.a10));
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
void dfs1(int u,int fa){
	Sz[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dfs1(V[i],u);Sz[u]+=Sz[V[i]];Fa[V[i]]=u;
			if (Sz[V[i]]>Sz[Hs[u]]) Hs[u]=V[i];
		}
	return;
}
void dfs2(int u,int top){
	Top[u]=top;dfn[u]=++dfncnt;
	if (Hs[u]==0){
		Modify(1,1,n,dfn[u],((Mat){0,0,Key[u],-inf}));
		return;
	}
	dfs2(Hs[u],top);int g0=0,g1=Key[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u])){
			dfs2(V[i],V[i]);
}
Mat operator * (Mat A,Mat B);
void Update(int x);
void Modify(int x,int l,int r,int pos,Mat M);
Mat Query(int x,int l,int r,int ql,int qr);
void Skip(int u);
