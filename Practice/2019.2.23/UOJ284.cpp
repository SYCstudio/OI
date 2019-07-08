#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
class QData
{
public:
	ll dep,w,sum;
};
const int maxN=303000;
const int maxM=maxN<<1;
const int maxB=20;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Md[maxN],Mx[maxN],dfncnt,dfn[maxN],Dep[maxN];
ll Nw[maxN],Ans[maxN];
vector<pair<int,int> > Qn[maxN];
int Fa[maxB][maxN],FaW[maxB][maxN],ql[maxN],qr[maxN];
QData Qu[maxN],Bp[maxN];

void Add_Edge(int u,int v);
int LCA(int u,int v);
void dfs_init(int u,int fa);
void dfs_solve(int u);
void push_front(int u,QData d);
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%lld",&Nw[i]);
	mem(Head,-1);
	for (int i=2; i<=n; i++) {
		int fa;
		scanf("%d",&fa);
		Add_Edge(fa,i);
	}
	dfs_init(1,0);
	for (int i=1; i<maxB; i++) for (int j=1; j<=n; j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]],FaW[i][j]=max(FaW[i-1][j],FaW[i-1][Fa[i-1][j]]);
	int Q;
	scanf("%d",&Q);
	for (int i=1; i<=Q; i++) {
		int s,t;
		scanf("%d%d",&s,&t);
		Ans[i]=Dep[t]-Dep[s];
		if (s!=t) Qn[s].push_back(make_pair(t,i));
	}
	dfs_solve(1);
	for (int i=1; i<=Q; i++) printf("%lld\n",Ans[i]);
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs_init(int u,int fa)
{
	Fa[0][u]=fa;
	FaW[0][u]=Nw[fa];
	Dep[u]=Dep[fa]+1;
	Md[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			dfs_init(V[i],u);
			Md[u]=max(Md[u],Md[V[i]]+1);
			if (Md[V[i]]+1>Md[Mx[u]]) Mx[u]=V[i];
		}
	return;
}
int LCA(int u,int v)
{
	if (Dep[u]<Dep[v]) swap(u,v);
	for (int i=maxB-1; i>=0; i--) if (Fa[i][u]&&Dep[Fa[i][u]]>=Dep[v]) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxB-1; i>=0; i--) if (Fa[i][u]&&Fa[i][v]&&Fa[i][u]!=Fa[i][v]) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}
ll PathW(int u,int v)
{
	int l=LCA(u,v),ret=0;
	for (int i=maxB-1; i>=0; i--) if (Fa[i][u]&&Dep[Fa[i][u]]>Dep[l]) ret=max(ret,FaW[i][u]),u=Fa[i][u];
	for (int i=maxB-1; i>=0; i--) if (Fa[i][v]&&Dep[Fa[i][v]]>Dep[l]) ret=max(ret,FaW[i][v]),v=Fa[i][v];
	return ret;
}
void dfs_solve(int u)
{
	dfn[u]=++dfncnt;
	if (Mx[u]) dfs_solve(Mx[u]),ql[u]=ql[Mx[u]],qr[u]=qr[Mx[u]];
	else ql[u]=dfn[u]+1,qr[u]=dfn[u];
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=Mx[u]&&V[i]!=Fa[0][u]) {
			int top=0,v=V[i];
			dfs_solve(v);
			while (ql[u]<=qr[u]&&Qu[ql[u]].dep<=Qu[qr[v]].dep) Bp[++top]=Qu[ql[u]++];
			while (top||ql[v]<=qr[v])
				if (ql[v]>qr[v]||(top&&Bp[top].dep>=Qu[qr[v]].dep)) push_front(u,Bp[top--]);
				else push_front(u,Qu[qr[v]--]);
		}
	for (int i=0,sz=Qn[u].size(); i<sz; i++) {
		int t=Qn[u][i].first,mxw=PathW(u,t);
		if (mxw<Qu[ql[u]].w) {
			Ans[Qn[u][i].second]+=(Qu[ql[u]].dep-Dep[u])*mxw;
			continue;
		}
		int l=ql[u],r=qr[u],pos;
		while (l<=r) {
			int mid=(l+r)>>1;
			if (Qu[mid].w>=mxw) pos=mid,r=mid-1;
			else l=mid+1;
		}
		Ans[Qn[u][i].second]+=Qu[ql[u]].sum-Qu[pos].sum+(mxw-Qu[pos].w)*(Qu[pos].dep-Dep[u])+Qu[ql[u]].w*(Qu[ql[u]].dep-Dep[u])-(Qu[pos].w-Qu[ql[u]].w)*Dep[u];
	}
	push_front(u,((QData) {
		Dep[u],Nw[u],0
	}));
	return;
}
void push_front(int u,QData d)
{
	while (ql[u]<=qr[u]&&Qu[ql[u]].w<=d.w) ++ql[u];
	if (ql[u]>qr[u]||Qu[ql[u]].dep>d.dep) {
		Qu[--ql[u]]=d;
		if (ql[u]!=qr[u]) Qu[ql[u]].sum=Qu[ql[u]+1].sum+(Qu[ql[u]+1].w-Qu[ql[u]].w)*Qu[ql[u]+1].dep;
		else Qu[ql[u]].sum=0;
	}
}