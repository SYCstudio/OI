#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200110;
const int maxM=maxN*2;
const int maxBit=20;
const int inf=214748367;

class Heap
{
public:
	priority_queue<int> Q1,Q2;
	void Update(){
		while ((!Q2.empty())&&(Q1.top()==Q2.top())) Q1.pop(),Q2.pop();
	}
	int Size(){
		return Q1.size()-Q2.size();
	}
	void Insert(const int x){
		Q1.push(x);
	}
	void Delete(const int x){
		Q2.push(x);
	}
	bool Empty(){
		Update();return Q1.empty();
	}
	void Pop(){
		Update();Q1.pop();
	}
	int Top(){
		Update();return Q1.top();
	}
	int STop(){
		int x=Top();Pop();
		int ret=Top();Insert(x);
		return ret;
	}
};

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Depth[maxN],ST[maxN][maxBit+1];
int root,mxSon[maxN],nowsum;
bool vis[maxN];
int offcnt=0,Fa[maxN];
Heap H1[maxN],H2[maxN],Ans;
bool Status[maxN];

void Add_Edge(int u,int v);
void dfs_ST(int u,int fa);
int Dist(int u,int v);
void GetRoot(int u,int fa);
void Div(int u);
void Insert_Ans(int u);
void Delete_Ans(int u);
void Off(int u);
void On(int u);

int main()
{
	//ios::sync_with_stdio(false);
	mem(Head,-1);

	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);//cin>>u>>v;
		Add_Edge(u,v);Add_Edge(v,u);
	}

	Depth[1]=1;
	dfs_ST(1,1);
	for (int i=1;i<=maxBit;i++)
		for (int j=1;j<=n;j++)
			if (ST[j][i-1])
			ST[j][i]=ST[ST[j][i-1]][i-1];

	nowsum=n;mxSon[0]=inf;root=0;
	GetRoot(1,1);Fa[root]=0;
	Div(root);

	for (int i=1;i<=n;i++) Off(i);

	int m;scanf("%d",&m);
	while (m--)
	{
		char opt[5];scanf("%s",opt);
		if (opt[0]=='G')
			if (offcnt==1) printf("0\n");
			else if (offcnt==0) printf("-1\n");
			else printf("%d\n",Ans.Top());
		if (opt[0]=='C')
		{
			int u;scanf("%d",&u);
			if (Status[u]==0) On(u);
			else Off(u);
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs_ST(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Depth[V[i]]=Depth[u]+1;ST[V[i]][0]=u;
			dfs_ST(V[i],u);
		}
	return;
}

int Dist(int u,int v)
{
	int ret=Depth[u]+Depth[v];
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit;i>=0;i--)
		if ((ST[u][i]!=0)&&(Depth[ST[u][i]]>=Depth[v])) u=ST[u][i];
	if (u==v) return ret-2*Depth[u];
	for (int i=maxBit;i>=0;i--)
		if ((ST[u][i]!=0)&&(ST[v][i]!=0)&&(ST[u][i]!=ST[v][i])) u=ST[u][i],v=ST[v][i];
	u=ST[u][0];
	return ret-2*Depth[u];
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			GetRoot(V[i],u);Size[u]+=Size[V[i]];
			mxSon[u]=max(mxSon[u],Size[V[i]]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Div(int u)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			GetRoot(V[i],V[i]);Fa[root]=u;
			Div(root);
		}
	return;
}

void Insert_Ans(int u)
{
	if (H2[u].Size()>=2) Ans.Insert(H2[u].Top()+H2[u].STop());
	return;
}

void Delete_Ans(int u)
{
	if (H2[u].Size()>=2) Ans.Delete(H2[u].Top()+H2[u].STop());
	return;
}

void Off(int u)
{
	offcnt++;Status[u]=0;
	Delete_Ans(u);
	H2[u].Insert(0);
	Insert_Ans(u);

	int now=u;
	while (Fa[now])
	{
		Delete_Ans(Fa[now]);
		
		if (!H1[now].Empty()) H2[Fa[now]].Delete(H1[now].Top());
		H1[now].Insert(Dist(u,Fa[now]));
		H2[Fa[now]].Insert(H1[now].Top());
		
		Insert_Ans(Fa[now]);
		now=Fa[now];
	}
	return;
}

void On(int u)
{
	offcnt--;Status[u]=1;
	Delete_Ans(u);
	H2[u].Delete(0);
	Insert_Ans(u);

	int now=u;
	while (Fa[now])
	{
		Delete_Ans(Fa[now]);
		
		H2[Fa[now]].Delete(H1[now].Top());
		H1[now].Delete(Dist(u,Fa[now]));
		if (!H1[now].Empty()) H2[Fa[now]].Insert(H1[now].Top());
		Insert_Ans(Fa[now]);
		now=Fa[now];
	}
	return;
}
