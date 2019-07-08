#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40400*8;
const int maxM=maxN<<1;
const int maxB=20;

class Mayuri
{
public:
	int x,y,c,k;
};
class Iriya
{
public:
	int x,yl,yr,opt;
};
class SegmentData
{
public:
	int lz,clr;
};

int n,P,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],lst[maxN],Fa[maxB][maxN],dep[maxN];
int Ans[maxN];
Mayuri Myr[maxN],Mdf[maxN],Bp1[maxN],Bp2[maxN];
Iriya Sorter[maxN];
SegmentData S[maxN<<2];

void Add_Edge(int u,int v);
void dfs(int u,int fa);
bool cmpx(Mayuri A,Mayuri B);
bool cmpc(Mayuri A,Mayuri B);
bool cmpi(Iriya A,Iriya B);
void Divide(int ml,int mr,int ql,int qr);
void Clear(int x);
void PushDown(int x);
void Modify(int x,int l,int r,int ql,int qr,int k);
int Query(int x,int l,int r,int p);

int main()
{
	//freopen("7.in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d%d",&n,&P,&Q);
	mem(Head,-1);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,0);
	for (int i=1; i<maxB; i++) for (int j=1; j<=n; j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	for (int i=1; i<=P; i++) scanf("%d%d%d",&Mdf[i].x,&Mdf[i].y,&Mdf[i].c);
	for (int i=1; i<=Q; i++) scanf("%d%d%d",&Myr[i].x,&Myr[i].y,&Myr[i].k),Myr[i].c=i,Myr[i].x=dfn[Myr[i].x],Myr[i].y=dfn[Myr[i].y];
	sort(&Myr[1],&Myr[Q+1],cmpx);
	sort(&Mdf[1],&Mdf[P+1],cmpc);
	Divide(1,P,1,Q);
	for (int i=1; i<=n; i++) printf("%d\n",Ans[i]);
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs(int u,int fa)
{
	dfn[u]=++dfncnt;
	Fa[0][u]=fa;
	dep[u]=dep[fa]+1;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) dfs(V[i],u);
	lst[u]=dfncnt;
	return;
}
bool cmpx(Mayuri A,Mayuri B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
bool cmpc(Mayuri A,Mayuri B)
{
	if (A.c!=B.c) return A.c<B.c;
	return A.x<B.x;
}
bool cmpi(Iriya A,Iriya B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.yl<B.yl;
}
void Divide(int ml,int mr,int ql,int qr)
{
	if (ml>mr) return;
	//cout<<"Divide:"<<ml<<" "<<mr<<" "<<ql<<" "<<qr<<endl;
	int mid=(ml+mr)>>1,scnt=0;
	//for (int i=ml;i<=mid;i++) cout<<"("<<Mdf[i].x<<","<<Mdf[i].y<<") ";cout<<endl;
	//for (int i=ql;i<=qr;i++) cout<<"("<<Myr[i].x<<" "<<Myr[i].y<<") ";cout<<endl;
	for (int i=ml; i<=mid; i++) {
		int u=Mdf[i].x,v=Mdf[i].y;
		if (dep[u]>dep[v]) swap(u,v);

		//int lstscnt=scnt;

		if (dfn[v]>=dfn[u]&&lst[v]<=lst[u]) {
			int vv=v;
			for (int j=maxB-1; j>=0; j--) if (Fa[j][vv]&&dep[Fa[j][vv]]>dep[u]) vv=Fa[j][vv];
			Sorter[++scnt]=((Iriya) {
				dfn[v],1,dfn[vv]-1,1
			});
			Sorter[++scnt]=((Iriya) {
				lst[v]+1,1,dfn[vv]-1,-1
			});
			Sorter[++scnt]=((Iriya) {
				1,dfn[v],lst[v],1
			});
			Sorter[++scnt]=((Iriya) {
				dfn[vv],dfn[v],lst[v],-1
			});
			if (lst[vv]!=n) {
				Sorter[++scnt]=((Iriya) {
					dfn[v],lst[vv]+1,n,1
				});
				Sorter[++scnt]=((Iriya) {
					lst[v]+1,lst[vv]+1,n,-1
				});
				Sorter[++scnt]=((Iriya) {
					lst[vv]+1,dfn[v],lst[v],1
				});
			}
		} else {
			Sorter[++scnt]=((Iriya) {
				dfn[u],dfn[v],lst[v],1
			});
			Sorter[++scnt]=((Iriya) {
				lst[u]+1,dfn[v],lst[v],-1
			});
			Sorter[++scnt]=((Iriya) {
				dfn[v],dfn[u],lst[u],1
			});
			Sorter[++scnt]=((Iriya) {
				lst[v]+1,dfn[u],lst[u],-1
			});
		}

		//cout<<"("<<u<<" "<<v<<")"<<endl;
		//for (int j=lstscnt+1;j<=scnt;j++) cout<<"("<<Sorter[j].x<<" ["<<Sorter[j].yl<<" "<<Sorter[j].yr<<" "<<Sorter[j].opt<<"])"<<endl;//cout<<endl;
	}

	sort(&Sorter[1],&Sorter[scnt+1],cmpi);

	int top1=0,top2=0,lstx=0;
	Clear(1);
	for (int i=1,j=ql;;) {
		while (j<=qr&&(i>scnt||Myr[j].x<Sorter[i].x)) {
			int r=Query(1,1,n,Myr[j].y);
			//cout<<"Calc:"<<j<<" "<<r<<"|"<<Myr[j].x<<" "<<Myr[j].y<<" "<<Myr[j].c<<" "<<Myr[j].k<<"|"<<lstx<<endl;
			if (r>=Myr[j].k) Ans[Myr[j].c]=Mdf[mid].c,Bp1[++top1]=Myr[j];
			else Myr[j].k-=r,Bp2[++top2]=Myr[j];
			++j;
		}
		if (i>scnt) break;
		lstx=Sorter[i].x;
		while (Sorter[i].x==lstx&&i<=scnt) {
			Modify(1,1,n,Sorter[i].yl,Sorter[i].yr,Sorter[i].opt);
			++i;
		}
	}
	int p=ql-1,dvt;
	for (int i=1; i<=top1; i++) Myr[++p]=Bp1[i];
	dvt=p;
	for (int i=1; i<=top2; i++) Myr[++p]=Bp2[i];
	if (dvt>=ql) Divide(ml,mid-1,ql,dvt);
	if (dvt<qr) Divide(mid+1,mr,dvt+1,qr);
	return;
}
#define ls (x<<1)
#define rs (ls|1)
void Clear(int x)
{
	S[x].lz=0;
	S[x].clr=1;
	return;
}
void PushDown(int x)
{
	if (S[x].clr) {
		Clear(ls);
		Clear(rs);
		S[x].clr=0;
	}
	return;
}
void Modify(int x,int l,int r,int ql,int qr,int k)
{
	if ((l==ql)&&(r==qr)) {
		S[x].lz+=k;
		return;
	}
	PushDown(x);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,k);
	else Modify(ls,l,mid,ql,mid,k),Modify(rs,mid+1,r,mid+1,qr,k);
	return;
}
int Query(int x,int l,int r,int p)
{
	if (l==r) return S[x].lz;
	PushDown(x);
	int mid=(l+r)>>1;
	if (p<=mid) return S[x].lz+Query(ls,l,mid,p);
	else return S[x].lz+Query(rs,mid+1,r,p);
}
