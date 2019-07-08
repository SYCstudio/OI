#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=50500;
const int maxM=101000;
const int Block=300;

class Edge
{
public:
	int u,v,a,b;
};
class Question
{
public:
	int u,v,a,b,id;
};
class UFSO
{
public:
	int u,v,ma,mb,sz;
};

int n,m,T,utop;
int ufs[maxN],ma[maxN],mb[maxN],size[maxN];
Edge E[maxM],Bp[maxM];
Question Q[maxN],Sq[maxN];
UFSO U[maxN];
int Ans[maxN];

bool cmpa(Edge A,Edge B);
bool cmpb(Edge A,Edge B);
bool qcmp(Question A,Question B);
int find(int x);
void Merge(int u,int v,int a,int b);
int main()
{
	//freopen("7.in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
	sort(&E[1],&E[m+1],cmpa);
	scanf("%d",&T);
	for (int i=1; i<=T; i++) scanf("%d%d%d%d",&Q[i].u,&Q[i].v,&Q[i].a,&Q[i].b),Q[i].id=i;
	sort(&Q[1],&Q[T+1],qcmp);
	for (int lo=1,ro,lst; lo<=m; lo=ro+1) {
		ro=min(m,lo+Block);
		int top=0;
		for (int i=1; i<=n; i++) ufs[i]=i,ma[i]=mb[i]=-1,size[i]=1;
		for (int i=1; i<=T; i++) if (Q[i].a>=E[lo].a&&(ro==m||Q[i].a<E[ro+1].a)) Sq[++top]=Q[i];
		//cerr<<"running at:"<<lo<<" "<<ro<<" "<<top<<" "<<E[lo].a<<" "<<E[ro].a<<endl;
		if (lo!=1) {
			sort(&E[lst],&E[lo],cmpb);
			int p1=1,p2=lst;
			for (int i=1; i<lo; i++) if (p1==lst||(p2<lo&&E[p2].b<=E[p1].b)) Bp[i]=E[p2++];
				else Bp[i]=E[p1++];
			for (int i=1; i<lo; i++) E[i]=Bp[i];
		}
		for (int i=1,j=1; i<=top; i++) {
			while (j<lo&&E[j].b<=Sq[i].b) {
				Merge(E[j].u,E[j].v,E[j].a,E[j].b);
				++j;
			}
			utop=0;
			for (int k=lo; k<=ro; k++) if (E[k].a<=Sq[i].a&&E[k].b<=Sq[i].b) Merge(E[k].u,E[k].v,E[k].a,E[k].b);
			if (find(Sq[i].u)==find(Sq[i].v)) {
				int f=find(Sq[i].u);
				if (ma[f]>=Sq[i].a&&mb[f]>=Sq[i].b) Ans[Sq[i].id]=1;
			}
			while (utop) {
				ma[U[utop].u]=U[utop].ma;
				mb[U[utop].u]=U[utop].mb;
				size[U[utop].u]=U[utop].sz;
				ufs[U[utop].v]=U[utop].v;
				--utop;
			}
		}
		lst=lo;
	}
	for (int i=1; i<=T; i++) Ans[i]?puts("Yes"):puts("No");
	return 0;
}
bool cmpa(Edge A,Edge B)
{
	return A.a<B.a;
}
bool cmpb(Edge A,Edge B)
{
	return A.b<B.b;
}
bool qcmp(Question A,Question B)
{
	return A.b<B.b;
}
int find(int x)
{
	if (ufs[x]!=x) return find(ufs[x]);
	return ufs[x];
}
void Merge(int u,int v,int a,int b)
{
	u=find(u);
	v=find(v);
	if (u==v) {
		U[++utop]=((UFSO) {
			u,v,ma[u],mb[u],size[u]
		});
		ma[u]=max(ma[u],a);
		mb[u]=max(mb[u],b);
	} else {
		if (size[u]<size[v]) swap(u,v);
		U[++utop]=((UFSO) {
			u,v,ma[u],mb[u],size[u]
		});
		ma[u]=max(ma[u],max(ma[v],a));
		mb[u]=max(mb[u],max(mb[v],b));
		ufs[v]=u;
		size[u]+=size[v];
	}
	return;
}