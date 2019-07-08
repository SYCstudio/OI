#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)
#define ft first
#define sd second
#define mp make_pair
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=maxN<<1;
const int inf=1000000000;

class SegmentData
{
public:
	int mnflow,mnleaf,dflow,dcost,fob;
};

int n,M;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
pair<int,int> W[maxM],FaW[maxM];
int Sz[maxN],Hs[maxN],Top[maxN],Fa[maxN];
int dfncnt,dfn[maxN],lst[maxN],idfn[maxN];
SegmentData S[maxN<<2];
int top=0,St[maxN],use[maxN];

void Add_Edge(int u,int v,pair<int,int> w);
void dfs1(int u);
void dfs2(int u,int top);
void Update(int x);
void PushDown(int x);
void Build(int x,int l,int r);
int Querylf(int x,int l,int r);
int Queryc(int x,int l,int r,int p);
int Querymn(int x,int l,int r,int ql,int qr);
void Incflow(int x,int l,int r,int ql,int qr,int f);
void Inccost(int x,int l,int r,int ql,int qr,int c);
void Setfob(int x,int l,int r,int ql,int qr);

int main()
{
	scanf("%d%d",&n,&M);
	mem(Head,-1);
	for (int i=1; i<=n; i++) {
		int u,v,a,b;
		scanf("%d%d%d%d",&u,&v,&a,&b);
		Add_Edge(u,v,mp(a,b));
		Add_Edge(v,u,mp(a,b));
	}

	for (int i=Head[0]; i!=-1; i=Next[i]) FaW[V[i]]=W[i],dfs1(V[i]),dfs2(V[i],V[i]);

	//for (int i=1;i<=n;i++) cout<<FaW[i].ft<<" "<<FaW[i].sd<<endl;

	Build(1,1,n);

	int Ans=0;
	while (1) {
		if (S[1].mnleaf>=inf) break;
		int leaf=idfn[Querylf(1,1,n)];
		int now=leaf,cost=Queryc(1,1,n,dfn[leaf]),flow=inf;


		//cout<<"leaf:"<<leaf<<" "<<cost<<endl;

		while (now) {
			flow=min(flow,Querymn(1,1,n,dfn[Top[now]],dfn[now]));
			//cout<<dfn[Top[now]]<<" "<<dfn[now]<<endl;
			now=Fa[Top[now]];
		}

		if (flow==0) break;

		//cout<<cost<<" "<<flow<<endl;

		if (flow*cost>M) {
			Ans+=M/cost;
			break;
		}
		Ans+=flow;
		M-=flow*cost;

		now=leaf;
		top=0;
		while (now) {
			Incflow(1,1,n,dfn[Top[now]],dfn[now],-flow);
			now=Fa[Top[now]];
		}

		for (int i=1; i<=top; i++) {
			int u=St[i];
			if (use[u]) Setfob(1,1,n,dfn[u],lst[u]);
			else {
				use[u]=1;
				Incflow(1,1,n,dfn[u],dfn[u],FaW[u].sd-FaW[u].ft);
				Inccost(1,1,n,dfn[u],lst[u],1);
			}
		}
	}
	printf("%d\n",Ans);
	return 0;
}
void Add_Edge(int u,int v,pair<int,int> w)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	W[edgecnt]=w;
	return;
}
void dfs1(int u)
{
	Sz[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=Fa[u]) {
			Fa[V[i]]=u;
			FaW[V[i]]=W[i];
			dfs1(V[i]);
			Sz[u]+=Sz[V[i]];
			if (Sz[V[i]]>Sz[Hs[u]]) Hs[u]=V[i];
		}
	return;
}
void dfs2(int u,int top)
{
	Top[u]=top;
	idfn[dfn[u]=++dfncnt]=u;
	if (Hs[u]) {
		dfs2(Hs[u],top);
		for (int i=Head[u]; i!=-1; i=Next[i])
			if (V[i]!=Fa[u]&&V[i]!=Hs[u])
				dfs2(V[i],V[i]);
	}
	lst[u]=dfncnt;
	return;
}
void Update(int x)
{
	S[x].mnflow=min(S[ls].mnflow,S[rs].mnflow);
	S[x].mnleaf=min(S[ls].mnleaf,S[rs].mnleaf);
	return;
}
void PushDown(int x)
{
	if (S[x].fob) {
		S[ls].fob=S[rs].fob=1;
		S[ls].dflow=S[ls].dcost=S[rs].dflow=S[rs].dcost=0;
		S[ls].mnleaf=S[rs].mnleaf=S[ls].mnflow=S[rs].mnflow=inf;
		S[x].fob=0;
	}
	if (S[x].dflow) {
		S[ls].mnflow+=S[x].dflow;
		S[ls].dflow+=S[x].dflow;
		S[rs].mnflow+=S[x].dflow;
		S[rs].dflow+=S[x].dflow;
		S[x].dflow=0;
	}
	if (S[x].dcost) {
		S[ls].mnleaf+=S[x].dcost;
		S[ls].dcost+=S[x].dcost;
		S[rs].mnleaf+=S[x].dcost;
		S[rs].dcost+=S[x].dcost;
		S[x].dcost=0;
	}
	return;
}
void Build(int x,int l,int r)
{
	if (l==r) {
		S[x].mnflow=FaW[idfn[l]].ft;
		if (Hs[idfn[l]]==0) S[x].mnleaf=0;
		else S[x].mnleaf=inf;
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	Update(x);
	return;
}
int Querylf(int x,int l,int r)
{
	if (l==r) return l;
	int mid=(l+r)>>1;
	PushDown(x);
	if (S[x].mnleaf==S[ls].mnleaf) return Querylf(ls,l,mid);
	else return Querylf(rs,mid+1,r);
}
int Queryc(int x,int l,int r,int p)
{
	if (l==r) return S[x].mnleaf;
	int mid=(l+r)>>1;
	PushDown(x);
	if (p<=mid) return Queryc(ls,l,mid,p);
	else return Queryc(rs,mid+1,r,p);
}
int Querymn(int x,int l,int r,int ql,int qr)
{
	//cout<<"Qmn:"<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<S[x].mnflow<<endl;
	if (l==ql&&r==qr) return S[x].mnflow;
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) return Querymn(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Querymn(rs,mid+1,r,ql,qr);
	else return min(Querymn(ls,l,mid,ql,mid),Querymn(rs,mid+1,r,mid+1,qr));
}
void Incflow(int x,int l,int r,int ql,int qr,int f)
{
	if (l==ql&&r==qr) {
		if (S[x].mnflow+f==0) {
			if (l==r) {
				St[++top]=idfn[l];
				S[x].mnflow+=f;
				return;
			}
		} else {
			S[x].mnflow+=f;
			S[x].dflow+=f;
			return;
		}
	}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Incflow(ls,l,mid,ql,qr,f);
	else if (ql>=mid+1) Incflow(rs,mid+1,r,ql,qr,f);
	else Incflow(ls,l,mid,ql,mid,f),Incflow(rs,mid+1,r,mid+1,qr,f);
	Update(x);
	return;
}
void Inccost(int x,int l,int r,int ql,int qr,int c)
{
	if (l==ql&&r==qr) {
		S[x].mnleaf+=c;
		S[x].dcost+=c;
		return;
	}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Inccost(ls,l,mid,ql,qr,c);
	else if (ql>=mid+1) Inccost(rs,mid+1,r,ql,qr,c);
	else Inccost(ls,l,mid,ql,mid,c),Inccost(rs,mid+1,r,mid+1,qr,c);
	Update(x);
	return;
}
void Setfob(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) {
		S[x].fob=1;
		S[x].mnleaf=S[x].mnflow=inf;
		S[x].dcost=S[x].dflow=0;
		return;
	}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Setfob(ls,l,mid,ql,qr);
	else if (ql>=mid+1) Setfob(rs,mid+1,r,ql,qr);
	else Setfob(ls,l,mid,ql,mid),Setfob(rs,mid+1,r,mid+1,qr);
	Update(x);
	return;
}
