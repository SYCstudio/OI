#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int inf=10000000;

class Mat{
public:
	int a00,a01,a10,a11;
	Mat(){}
	Mat(int a,int b,int c,int d){
		a00=a;a01=b;a10=c;a11=d;return;
	}
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Key[maxN];
int Sz[maxN],Hs[maxN],Top[maxN],Fa[maxN],dfncnt,dfn[maxN],lst[maxN],Id[maxN];
int F[maxN][2],G[maxN][2];
Mat S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
Mat operator * (Mat A,Mat B);
void Update(int x);
void Modify(int x,int l,int r,int pos);
Mat Query(int x,int l,int r,int ql,int qr);
void Skip(int u,int key);
void Outp(int x,int l,int r);

int main(){
	freopen("in","r",stdin);
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Key[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs1(1,1);dfs2(1,1);
	//Outp(1,1,n);
	//for (int i=1;i<=n;i++) cout<<"("<<F[i][0]<<","<<F[i][1]<<") ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<"("<<G[i][0]<<","<<G[i][1]<<") ";cout<<endl;
	//cout<<Query(1,1,n,1,lst[1]).a00<<" "<<Query(1,1,n,1,lst[1]).a10<<endl;
	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" "<<lst[i]<<endl;
	for (int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);Skip(x,y);
		printf("%d\n",max(F[1][0],F[1][1]));
		//for (int j=1;j<=n;j++) cout<<"("<<F[j][0]<<","<<F[j][1]<<") ";cout<<endl;
		//for (int j=1;j<=n;j++) cout<<"("<<G[j][0]<<","<<G[j][1]<<") ";cout<<endl;
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
	Top[u]=top;Id[dfn[u]=++dfncnt]=u;
	if (Hs[u]) dfs2(Hs[u],top),lst[u]=lst[Hs[u]];
	else lst[u]=dfncnt;
	G[u][1]=Key[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u])){
			dfs2(V[i],V[i]);G[u][1]+=F[V[i]][0];
			G[u][0]+=max(F[V[i]][0],F[V[i]][1]);
		}
	Modify(1,1,n,dfn[u]);
	F[u][0]=G[u][0]+max(F[Hs[u]][0],F[Hs[u]][1]);
	F[u][1]=G[u][1]+F[Hs[u]][0];
	return;
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
	S[x]=S[ls]*S[rs];return;
}
void Modify(int x,int l,int r,int pos){
	if (l==r){
		S[x]=((Mat){G[Id[pos]][0],G[Id[pos]][0],G[Id[pos]][1],-inf});return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(ls,l,mid,pos);else Modify(rs,mid+1,r,pos);
	Update(x);return;
}
Mat Query(int x,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return Query(ls,l,mid,ql,mid)*Query(rs,mid+1,r,mid+1,qr);
}
void Skip(int u,int key){
	G[u][1]=G[u][1]-Key[u]+key;Key[u]=key;
	while (u){
		Modify(1,1,n,dfn[u]);
		u=Top[u];
		Mat M=Query(1,1,n,dfn[u],lst[u]);
		if (Fa[u]==0){
			F[u][0]=M.a00;F[u][1]=M.a10;break;
		}
		G[Fa[u]][0]-=max(F[u][0],F[u][1]);
		G[Fa[u]][1]-=F[u][0];
		F[u][0]=M.a00;F[u][1]=M.a10;
		G[Fa[u]][0]+=max(F[u][0],F[u][1]);
		G[Fa[u]][1]+=F[u][0];
		u=Fa[u];
	}
	return;
}

void Outp(int x,int l,int r){
	cout<<x<<" ["<<l<<","<<r<<"] "<<" "<<S[x].a00<<" "<<S[x].a01<<" "<<S[x].a10<<" "<<S[x].a11<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	Outp(ls,l,mid);Outp(rs,mid+1,r);
	return;
}
