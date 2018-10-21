#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define lowbit(x) ((x)&(-x))

const int maxN=300101;
const int maxM=300101;
const int inf=2147483647;

int n;

class Edge
{
public:
	int u,v,w;
};

class TreeArr
{
public:
	int A[maxN];
	TreeArr()
		{
			memset(A,0,sizeof(A));
			return;
		}
	void Add(int pos,int x)
		{
			while (pos<=n)
			{
				A[pos]=A[pos]+x;
				pos=pos+lowbit(pos);
			}
			return;
		}
	int Sum(int x)
		{
			int ret=0;
			while (x>0)
			{
				ret=ret+A[x];
				x=x-lowbit(x);
			}
			return ret;
		}
	int query(int l,int r)
		{
			return Sum(r)-Sum(l-1);
		}
};

class Question
{
public:
	int u,v,w;
};

bool operator < (Question A,Question B)
{
	return A.w>B.w;
}

int qus;
int root,rootsize;
int longestpath=0;
//Graph
int cnt=0;
int Head[maxN];
int Next[maxN*2];
Edge E[maxN*2];
int Node_W[maxN];
//Tree_Chain
int Depth[maxN];
int Father[maxN];
int Top[maxN];
int Size[maxN];
int HeavySon[maxN];
int Id[maxN];
int dfn[maxN];
//TreeArr
TreeArr TA;
//Q
Question Q[maxM];
//Insert
int Num[maxN];

int read();
void Add_Edge(int u,int v,int w);
void dfs(int u,int father);//求重心
void dfs1(int u,int father);
void dfs2(int u,int nowTop);
int Calc_Path(int u,int v);
bool check(int nowmid);
void Insert(int u,int r);//差分

int main()
{
	memset(Head,-1,sizeof(Head));
	rootsize=inf;
	n=read();
	qus=read();
	for (int i=1;i<n;i++)
	{
		int u,v,w;
		u=read();
		v=read();
		w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	//处理出重心
	dfs(1,1);

	//树链剖分
	Depth[1]=1;
	dfs1(root,root);
	cnt=0;
	dfs2(root,root);
	for (int i=1;i<=n;i++)
		TA.Add(dfn[i],Node_W[i]);

	//构造路径
	for (int i=1;i<=qus;i++)
	{
		Q[i].u=read();
		Q[i].v=read();
		Q[i].w=Calc_Path(Q[i].u,Q[i].v);
		longestpath=max(Q[i].w,longestpath);
		//cout<<Q[i].w<<endl;
	}

	sort(&Q[1],&Q[qus+1]);

	int l=1,r=longestpath;
	int Ans;
	do
	{
		int mid=(l+r)/2;
		//cout<<mid<<" ";
		if (check(mid))
		{
			Ans=mid;
			r=mid-1;
			//cout<<"Yes!"<<endl;
		}
		else
		{
			l=mid+1;
			//cout<<"No!"<<endl;
		}
	}
	while (l<=r);
	printf("%d\n",Ans);
	return 0;
}

int read()
{
	int x=0;
	char ch=getchar();
	while ((ch>'9')||(ch<'0'))
		ch=getchar();
	while ((ch<='9')&&(ch>='0'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x;
}

void Add_Edge(int u,int v,int w)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].w=w;
	return;
}

void dfs(int u,int father)
{
	Size[u]=1;
	int mx=0,mn=inf;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if (v==father)
			continue;
		dfs(v,u);
		Size[u]+=Size[v];
		if (Size[v]>mx)
			mx=Size[v];
		else
			if (Size[v]<mn)
				mn=Size[v];
	}
	if (n-Size[u]>mx)
		mx=n-Size[u];
	else
		if (n-Size[u]<mn)
			mn=n-Size[u];
	if ((mx!=0)&&(mn!=inf)&&(mx-mn<rootsize))
	{
		root=u;
		rootsize=mx-mn;
	}
	return;
}

void dfs1(int u,int father)
{
	Size[u]=1;
	HeavySon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if (v==father)
			continue;
		Father[v]=u;
		Depth[v]=Depth[u]+1;
		Node_W[v]=E[i].w;//将边权转换成点权
		dfs1(v,u);
		Size[u]=Size[u]+Size[v];
		if ((HeavySon[u]==0)||(Size[HeavySon[u]]<Size[v]))
			HeavySon[u]=v;
	}
	return;
}

void dfs2(int u,int nowTop)
{
	cnt++;
	dfn[u]=cnt;
	Id[cnt]=u;
	Top[u]=nowTop;
	if (HeavySon[u]==0)
		return;
	dfs2(HeavySon[u],nowTop);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].v!=Father[u])&&(E[i].v!=HeavySon[u]))
			dfs2(E[i].v,E[i].v);
	return;
}

int Calc_Path(int u,int v)
{
	int path=0;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]])
			swap(u,v);
		path+=TA.query(dfn[Top[u]],dfn[u]);
		u=Father[Top[u]];
	}
	if (Depth[u]>Depth[v])
		swap(u,v);
	return path+TA.query(dfn[u]+1,dfn[v]);
}

bool check(int nowmid)
{
	int pos=0;
	while (Q[pos+1].w>nowmid)
	{
		pos++;
		Insert(Q[pos].u,Q[pos].v);
	}
	int now=0;
	for (int i=1;i<=n;i++)
	{
		now=now+Num[i];
		Num[i]=0;
		if ((now==pos)&&(longestpath-Node_W[Id[i]]<=nowmid))
		{
			for (int j=i+1;j<=n;j++)
				Num[j]=0;
			return 1;
		}
	}
	return 0;
}

void Insert(int u,int v)
{
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]])
			swap(u,v);
		Num[dfn[Top[u]]]++;
		Num[dfn[u]+1]--;
		u=Father[Top[u]];
	}
	if (Depth[u]>Depth[v])
		swap(u,v);
	Num[dfn[u]+1]++;
	Num[dfn[v]+1]--;
	return;
}
