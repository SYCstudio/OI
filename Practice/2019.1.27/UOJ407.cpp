#include "werewolf.h"
#include<vector>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=201000<<1;
const int maxM=404000;
const int maxB=20;
class Edge
{
public:
	int u,v;
};
class Graph
{
public:
	int n,dfncnt,dfn[maxN],lst[maxN],Fa[maxB][maxN],root,Key[maxN];
	vector<int> T[maxN];
	void Add_Edge(int u,int v)
	{
		T[u].push_back(v);
		T[v].push_back(u);
		return;
	}
	void dfs(int u,int fa)
	{
		dfn[u]=++dfncnt;
		Fa[0][u]=fa;
		for (int i=0,sz=T[u].size(); i<sz; i++)
			if (T[u][i]!=fa) dfs(T[u][i],u);
		lst[u]=dfncnt;
		return;
	}
	void Init()
	{
		//cout<<"Rt:"<<root<<endl;
		dfs(root,0);
		for (int i=1; i<maxB; i++)
			for (int j=1; j<=n; j++)
				if (Fa[i-1][j]) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
		//for (int i=1;i<=n;i++) cout<<Fa[0][i]<<" ";cout<<endl;
		return;
	}
};
class Question
{
public:
	int p,ql,qr,id,opt;
};

int qcnt;
Edge EI[maxM];
int ufs[maxN],Ans[maxN],B[maxN];
Graph T1,T2;
Question Q[maxN];
pair<int,int> P[maxN];

bool cmpmin(Edge A,Edge B);
bool cmpmax(Edge A,Edge B);
int find(int x);
bool cmpq(Question A,Question B);
void Plus(int x,int k,int n);
int Sum(int x);
int Query(int l,int r);

vector<int> check_validity(int N,vector<int> X,vector<int> Y,
                           vector<int> S,vector<int> E,
                           vector<int> L,vector<int> R)
{
	for (int i=0,sz=X.size(); i<sz; i++) EI[i]=((Edge) {
		X[i]+1,Y[i]+1
	});

	T1.n=T2.n=N;
	for (int i=1; i<=N; i++) T1.Key[i]=T2.Key[i]=i;
	sort(&EI[0],&EI[X.size()],cmpmin);
	for (int i=1; i<=N+N; i++) ufs[i]=i;

	//for (int i=0;i<X.size();i++) cout<<EI[i].u<<" "<<EI[i].v<<endl;

	for (int i=0,sz=X.size(); i<sz; i++)
		if (find(EI[i].u)!=find(EI[i].v)) {
			int fu=find(EI[i].u),fv=find(EI[i].v);
			++T1.n;
			T1.Add_Edge(fu,T1.n);
			T1.Add_Edge(fv,T1.n);
			T1.Key[T1.n]=max(T1.Key[fu],T1.Key[fv]);
			ufs[fu]=ufs[fv]=T1.n;
		}
	for (int i=1; i<=T1.n; i++) if (ufs[i]==i) T1.root=i;
	sort(&EI[0],&EI[X.size()],cmpmax);
	for (int i=1; i<=N+N; i++) ufs[i]=i;

	//for (int i=0;i<X.size();i++) cout<<EI[i].u<<" "<<EI[i].v<<endl;

	for (int i=0,sz=X.size(); i<sz; i++)
		if (find(EI[i].u)!=find(EI[i].v)) {
			int fu=find(EI[i].u),fv=find(EI[i].v);
			++T2.n;
			T2.Add_Edge(fu,T2.n);
			T2.Add_Edge(fv,T2.n);
			T2.Key[T2.n]=min(T2.Key[fu],T2.Key[fv]);
			ufs[fu]=ufs[fv]=T2.n;
		}
	for (int i=1; i<=T2.n; i++) if (ufs[i]==i) T2.root=i;

	T1.Init();
	T2.Init();

	//for (int i=1;i<=T1.n;i++) cout<<T1.dfn[i]<<" "<<T1.lst[i]<<" "<<T1.Key[i]<<endl;cout<<endl;
	//for (int i=1;i<=T2.n;i++) cout<<T2.dfn[i]<<" "<<T2.lst[i]<<" "<<T2.Key[i]<<endl;cout<<endl;
	for (int i=0,sz=S.size(); i<sz; i++) {
		int u=S[i],v=E[i],l1=L[i],l2=R[i];
		++u;
		++v;
		++l1;
		++l2;
		//cout<<u<<" "<<l1<<endl;
		for (int j=maxB-1; j>=0; j--) if (T2.Fa[j][u]&&T2.Key[T2.Fa[j][u]]>=l1) u=T2.Fa[j][u];
		for (int j=maxB-1; j>=0; j--) if (T1.Fa[j][v]&&T1.Key[T1.Fa[j][v]]<=l2) v=T1.Fa[j][v];

		//cout<<u<<" "<<v<<"("<<T1.dfn[v]<<","<<T1.lst[v]<<") ("<<T2.dfn[u]<<","<<T2.lst[u]<<")"<<endl;
		Q[++qcnt]=((Question) {
			T1.dfn[v]-1,T2.dfn[u],T2.lst[u],i,-1
		});
		Q[++qcnt]=((Question) {
			T1.lst[v],T2.dfn[u],T2.lst[u],i,1
		});
	}
	sort(&Q[1],&Q[qcnt+1],cmpq);

	for (int i=1; i<=N; i++) P[i]=make_pair(T1.dfn[i],T2.dfn[i]);
	sort(&P[1],&P[N+1]);
	//for (int i=1;i<=N;i++) cout<<P[i].first<<" "<<P[i].second<<endl;

	for (int i=1,p=1; i<=qcnt; i++) {
		while (p<=N&&P[p].first<=Q[i].p) Plus(P[p++].second,1,N+N);
		//cout<<Q[i].p<<":";for (int j=1;j<=N+N;j++) cout<<Query(j,j)<<" ";cout<<endl;
		int r=Query(Q[i].ql,Q[i].qr);
		Ans[Q[i].id]+=Q[i].opt*r;
	}

	vector<int> Rt;
	for (int i=0,sz=S.size(); i<sz; i++) Rt.push_back(Ans[i]>=1);
	return Rt;
}
bool cmpmin(Edge A,Edge B)
{
	return max(A.u,A.v)<max(B.u,B.v);
}
bool cmpmax(Edge A,Edge B)
{
	return min(A.u,A.v)>min(B.u,B.v);
}
int find(int x)
{
	if (ufs[x]!=x) ufs[x]=find(ufs[x]);
	return ufs[x];
}
bool cmpq(Question A,Question B)
{
	return A.p<B.p;
}
void Plus(int x,int k,int n)
{
	while (x<=n) {
		B[x]+=k;
		x+=(x)&(-x);
	}
	return;
}
int Sum(int x)
{
	int ret=0;
	while (x) {
		ret+=B[x];
		x-=(x)&(-x);
	}
	return ret;
}
int Query(int l,int r)
{
	return Sum(r)-Sum(l-1);
}
