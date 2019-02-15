#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxM=maxN<<1;
const int inf=1000000000;

namespace IO{
    const int maxn((1 << 21) + 1);
    char ibuf[maxn], *iS, *iT, obuf[maxn], *oS = obuf, *oT = obuf + maxn - 1, c, st[55];
    int f, tp;
    char Getc() {
        return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
    }
    void Flush() {
        fwrite(obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }
    void Putc(char x) {
        *oS++ = x;
        if (oS == oT) Flush();
    }
    template <class Int> void Input(Int &x) {
        for (f = 1, c = Getc(); c < '0' || c > '9'; c = Getc()) f = c == '-' ? -1 : 1;
        for (x = 0; c <= '9' && c >= '0'; c = Getc()) x = (x << 3) + (x << 1) + (c ^ 48);
        x *= f;
    }
    template <class Int> void Print(Int x) {
        if (!x) Putc('0');
        if (x < 0) Putc('-'), x = -x;
        while (x) st[++tp] = x % 10 + '0', x /= 10;
        while (tp) Putc(st[tp--]);
    }
    void Getstr(char *s, int &l) {
        for (c = Getc(); c < 'a' || c > 'z'; c = Getc());
        for (l = 0; c <= 'z' && c >= 'a'; c = Getc()) s[l++] = c;
        s[l] = 0;
    }
    void Putstr(const char *s) {
        for (int i = 0, n = strlen(s); i < n; ++i) Putc(s[i]);
    }
}

using namespace IO;

struct Mat{
public:
	int a00,a01,a10,a11;
	Mat(){
		a00=a01=a10=a11=0;return;
	}
	Mat(int a,int b,int c,int d){
		a00=a;a01=b;a10=c;a11=d;return;
	}
};

struct SegmentData{
public:
	int ls,rs,mid;Mat M;
};

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Sz[maxN],Hs[maxN],Fa[maxN],Top[maxN],dfncnt,dfn[maxN],lst[maxN],Id[maxN],Val[maxN];
int Key[maxN],F[maxN][2],G[maxN][2];
int nodecnt,rt[maxN];
SegmentData S[maxN*4];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Build(int &x,int l,int r);
void Modify(int x,int l,int r,int pos);
Mat Query(int x,int l,int r,int ql,int qr);
Mat operator * (Mat A,Mat B);

int main(){
	//freopen("in","r",stdin);
	int Q,i,u,v,lstans;Mat R;//scanf("%d%d",&n,&Q);
	Input(n);Input(Q);mem(Head,-1);
	for (i=1;i<=n;++i) Input(Key[i]);//scanf("%d",&Key[i]);
	for (i=1;i<n;++i){
		Input(u);Input(v);//scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	dfs1(1,1);dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<lst[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Hs[i]<<" ";cout<<endl;
	for (i=1;i<=n;++i) Val[i]=Sz[Id[i]]-Sz[Hs[Id[i]]];
	for (i=1;i<=n;++i) Val[i]+=Val[i-1];
	for (i=1;i<=n;++i) if (Top[i]==i) Build(rt[i],dfn[i],lst[i]);
	while (Q--){
		Input(u);Input(v);//scanf("%d%d",&x,&y);
		u^=lstans;
		G[u][1]+=v-Key[u];Key[u]=v;
		while (u){
			Modify(rt[Top[u]],dfn[Top[u]],lst[Top[u]],dfn[u]);
			u=Top[u];
			R=Query(rt[u],dfn[u],lst[u],dfn[u],lst[u]);
			if (Fa[u]==0){
				F[u][0]=R.a00;F[u][1]=R.a10;break;
			}
			G[Fa[u]][0]-=max(F[u][0],F[u][1]);
			G[Fa[u]][1]-=F[u][0];
			F[u][0]=R.a00;F[u][1]=R.a10;
			G[Fa[u]][0]+=max(F[u][0],F[u][1]);
			G[Fa[u]][1]+=F[u][0];
			u=Fa[u];
		}
		Print(lstans=max(F[1][0],F[1][1]));Putc('\n');
	}
	Flush();
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
void dfs1(int u,int fa){
	Sz[u]=1;Hs[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Fa[V[i]]=u;dfs1(V[i],u);Sz[u]+=Sz[V[i]];
			if (Sz[V[i]]>Sz[Hs[u]]) Hs[u]=V[i];
		}
	return;
}
void dfs2(int u,int top){
	Top[u]=top;Id[dfn[u]=++dfncnt]=u;
	if (Hs[u]) dfs2(Hs[u],top),lst[u]=lst[Hs[u]];
	else lst[u]=dfncnt;
	G[u][0]=0;G[u][1]=Key[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u])){
			dfs2(V[i],V[i]);G[u][1]+=F[V[i]][0];
			G[u][0]+=max(F[V[i]][0],F[V[i]][1]);
		}
	F[u][0]=G[u][0]+max(F[Hs[u]][0],F[Hs[u]][1]);
	F[u][1]=G[u][1]+F[Hs[u]][0];
	return;
}
void Build(int &x,int l,int r){
	if (!x) x=++nodecnt;
	//cout<<"Build:"<<x<<" "<<l<<" "<<r<<endl;
	if (l==r){
		S[x].M=((Mat){G[Id[l]][0],G[Id[l]][0],G[Id[l]][1],-inf});
		return;
	}
	int sz=(Val[r]-Val[l-1])/2,L=l,R=r-1,pos=l;
	do{
		int mid=(L+R)>>1;
		if (Val[mid]-Val[l-1]<=sz) pos=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);S[x].mid=pos;
	Build(S[x].ls,l,S[x].mid);Build(S[x].rs,S[x].mid+1,r);
	S[x].M=S[S[x].ls].M*S[S[x].rs].M;return;
}
void Modify(int x,int l,int r,int pos){
	if (l==r){
		S[x].M=((Mat){G[Id[l]][0],G[Id[l]][0],G[Id[l]][1],-inf});
		return;
	}
	if (pos<=S[x].mid) Modify(S[x].ls,l,S[x].mid,pos);
	else Modify(S[x].rs,S[x].mid+1,r,pos);
	S[x].M=S[S[x].ls].M*S[S[x].rs].M;return;
}
Mat Query(int x,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[x].M;
	if (qr<=S[x].mid) return Query(S[x].ls,l,S[x].mid,ql,qr);
	else if (ql>=S[x].mid+1) return Query(S[x].rs,S[x].mid+1,r,ql,qr);
	else return Query(S[x].ls,l,S[x].mid,ql,S[x].mid)*Query(S[x].rs,S[x].mid+1,r,S[x].mid+1,qr);
}
Mat operator * (Mat A,Mat B){
	Mat R;
	R.a00=max(A.a00+B.a00,A.a01+B.a10);
	R.a01=max(A.a00+B.a01,A.a01+B.a11);
	R.a10=max(A.a10+B.a00,A.a11+B.a10);
	R.a11=max(A.a10+B.a01,A.a11+B.a11);
	return R;
}
