#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxN=101000;
const int maxM=maxN<<1;
const int inf=2147483647;

class Question
{
public:
	int k,id;
};

int n,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Col[maxN];
int Depth[maxN],Size[maxN],Hson[maxN],dfncnt,fst[maxN],lst[maxN],Id[maxN];
int BIT[maxN],Cnt[maxN],Ans[maxN];
vector<Question> T[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa,int hson);
void Modify(int col,int opt);
int Query(int pos);
void Add(int pos,int opt);
int Sum(int pos);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&Col[i]);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	for (int i=1;i<=Q;i++)
	{
		int v,k;scanf("%d%d",&v,&k);
		T[v].push_back((Question){k,i});
	}

	Depth[1]=1;
	dfs1(1,1);
	dfs2(1,1,1);

	for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa)
{
	//cout<<"dfs1:"<<u<<endl;
	Size[u]=1;Id[fst[u]=++dfncnt]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Depth[V[i]]=Depth[u]+1;
			dfs1(V[i],u);Size[u]+=Size[V[i]];
			if (Size[Hson[u]]<Size[V[i]]) Hson[u]=V[i];
		}
	lst[u]=dfncnt;
	return;
}

void dfs2(int u,int fa,int hson)
{
	//cout<<"dfs2:"<<u<<" "<<hson<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(V[i]!=Hson[u])) dfs2(V[i],u,0);
	if (Hson[u]) dfs2(Hson[u],u,1);

	Modify(Col[u],1);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(V[i]!=Hson[u]))
			for (int j=fst[V[i]];j<=lst[V[i]];j++)
				Modify(Col[Id[j]],1);

	//cout<<u<<endl;
	//for (int i=1;i<=100;i++) if (Cnt[i]) cout<<i<<":"<<Cnt[i]<<endl;

	int sz=T[u].size();
	for (int i=0;i<sz;i++) Ans[T[u][i].id]=Query(T[u][i].k);
	if (hson==0) for (int i=fst[u];i<=lst[u];i++) Modify(Col[Id[i]],-1);
	return;
}

void Modify(int col,int opt)
{
	if (Cnt[col]) Add(Cnt[col],-1);
	Cnt[col]+=opt;
	if (Cnt[col]) Add(Cnt[col],1);
	return;
}

int Query(int k){
	if (k>n) return 0;
	return Sum(n)-Sum(k-1);
}

void Add(int pos,int key){
	while (pos<=n){
		BIT[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=BIT[pos];pos-=lowbit(pos);
	}
	return ret;
}
/*
10 4
75 72 81 90 62 39 32 88 61 58
2 1
3 2
4 3
5 1
6 4
7 1
8 4
9 6
10 8
2 99
2 68
7 5
2 97
//*/
