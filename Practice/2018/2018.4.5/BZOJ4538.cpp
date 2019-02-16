#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxM=maxN*2;
const int inf=2147483647;

class Heap
{
public:
	priority_queue<int> Q,Del;
	void MainTain(){
		while ((!Q.empty())&&(!Del.empty())&&(Q.top()==Del.top())) Q.pop(),Del.pop();
	}
	bool Empty(){
		MainTain();
		return (Q.size()-Del.size())==0;
	}
	void Push(int x){
		MainTain();
		Q.push(x);return;
	}
	int Top(){
		MainTain();
		return Q.top();
	}
	void Pop(){
		MainTain();Q.pop();
	}
	void Delete(int x){
		MainTain();Del.push(x);MainTain();return;
	}
};

class SegmentData
{
public:
	Heap H;
	int ls,rs;
};

class Range
{
public:
	int l,r;
};

int n,m,root,nodecnt;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
SegmentData S[maxN<<2];
int Hson[maxN],Top[maxN],Fa[maxN],Size[maxN],Depth[maxN];
int idcnt,Id[maxN];
int PU[maxN*2],PV[maxN*2],PW[maxN*2];

bool operator < (Range A,Range B);
void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
vector<Range> GetPath(int u,int v);
void Modify(int &now,int l,int r,int ql,int qr,int key,int opt);
int Query(int now,int l,int r,int pos);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Depth[n]=1;
	dfs1(n,n);dfs2(n,n);
	//for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
	int pcnt=0;
	while (m--)
	{
		pcnt++;
		int opt;scanf("%d",&opt);
		if (opt==0)
		{
			scanf("%d%d%d",&PU[pcnt],&PV[pcnt],&PW[pcnt]);
			vector<Range> R=GetPath(PU[pcnt],PV[pcnt]);
			for (int i=0;i<R.size();i++) Modify(root,1,n,R[i].l,R[i].r,PW[pcnt],1);
		}
		if (opt==1)
		{
			int t;scanf("%d",&t);
			vector<Range> R=GetPath(PU[t],PV[t]);
			for (int i=0;i<R.size();i++) Modify(root,1,n,R[i].l,R[i].r,PW[t],-1);
		}
		if (opt==2)
		{
			int x;scanf("%d",&x);
			//cout<<"Query:"<<Id[x]<<endl;
			printf("%d\n",Query(root,1,n,Id[x]));
		}
	}
	return 0;
}

bool operator < (Range A,Range B)
{
	if (A.l!=B.l) return A.l<B.l;
	return A.r<B.r;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa)
{
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[V[i]]=u;Depth[V[i]]=Depth[u]+1;
			dfs1(V[i],u);
			Size[u]+=Size[V[i]];
			if (Size[V[i]]>=Size[Hson[u]]) Hson[u]=V[i];
		}
	return;
}

void dfs2(int u,int top)
{
	Top[u]=top;
	Id[u]=++idcnt;
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i],V[i]);
	return;
}

vector<Range> GetPath(int u,int v)
{
	vector<Range> Ran;Ran.clear();
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		Ran.push_back((Range){Id[Top[u]],Id[u]});
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	Ran.push_back((Range){Id[u],Id[v]});
	sort(Ran.begin(),Ran.end());
	//for (int i=0;i<Ran.size();i++) cout<<"("<<Ran[i].l<<","<<Ran[i].r<<") ";cout<<endl;
	vector<Range> Ret;Ret.clear();
	if (Ran[0].l!=1) Ret.push_back((Range){1,Ran[0].l-1});
	for (int i=1;i<Ran.size();i++) if (Ran[i-1].r+1<=Ran[i].l-1) Ret.push_back((Range){Ran[i-1].r+1,Ran[i].l-1});
	if (Ran[Ran.size()-1].r!=n) Ret.push_back((Range){Ran[Ran.size()-1].r+1,n});
	//for (int i=0;i<Ret.size();i++) cout<<"("<<Ret[i].l<<","<<Ret[i].r<<") ";cout<<endl;
	return Ret;
}

void Modify(int &now,int l,int r,int ql,int qr,int key,int opt)
{
	if (now==0) now=++nodecnt;
	if ((l==ql)&&(r==qr))
	{
		if (opt==1) S[now].H.Push(key);
		else S[now].H.Delete(key);
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr,key,opt);
	else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr,key,opt);
	else
	{
		Modify(S[now].ls,l,mid,ql,mid,key,opt);
		Modify(S[now].rs,mid+1,r,mid+1,qr,key,opt);
	}
	return;
}

int Query(int now,int l,int r,int pos)
{
	if (now==0) return -1;
	int Ret=-1;
	if (S[now].H.Empty()==0) Ret=S[now].H.Top();
	//cout<<"Max:("<<l<<","<<r<<") "<<Ret<<endl;
	if (l==r) return Ret;
	int mid=(l+r)>>1;
	if (pos<=mid) return max(Ret,Query(S[now].ls,l,mid,pos));
	else return max(Ret,Query(S[now].rs,mid+1,r,pos));
}
