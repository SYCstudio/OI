#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010+100010;
const int maxM=100010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int rev;
	int key,mxid;
	int d1,d2;
};

class Edge
{
public:
	int u,v,a,b;
};

bool operator < (Edge A,Edge B)
{
	return A.a<B.a;
}

int n,m;
int nodecnt;
Splay_Data S[maxN];
int Stack[maxN];
int UFS[maxN];
Edge E[maxM];

bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
int Findroot(int x);
void Link(int x,int y);
void Cut(int x,int y);
int GetMax(int a,int b);
int Find(int x);
void Add_Edge(int u,int v,int w);
bool Delete(int u,int v,int w);

int main()
{
	scanf("%d%d",&n,&m);
	nodecnt=n+1;
	for (int i=1;i<=n;i++) S[i].key=0,UFS[i]=i;
	for (int i=1;i<=m;i++) scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
	sort(&E[1],&E[m+1]);
	//for (int i=1;i<=m;i++) cout<<E[i].u<<" "<<E[i].v<<" "<<E[i].a<<" "<<E[i].b<<endl;
	int Ans=inf;
	for (int i=1;i<=m;i++)
	{
		if (E[i].u==E[i].v) continue;
		Add_Edge(E[i].u,E[i].v,E[i].b);
		if (Find(1)==Find(n))
		{
			Makeroot(1);Access(n);Splay(n);
			Ans=min(Ans,E[i].a+S[S[n].mxid].key);
		}
	}
	if (Ans!=inf) printf("%d\n",Ans);
	else printf("-1\n");
	return 0;
}

bool Isroot(int x)
{
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void Update(int x)
{
	S[x].mxid=GetMax(x,GetMax(S[S[x].ch[0]].mxid,S[S[x].ch[1]].mxid));
	return;
}

void PushDown(int x)
{
	if (S[x].rev)
	{
		S[x].rev=0;
		int lson=S[x].ch[0],rson=S[x].ch[1];
		swap(S[lson].ch[0],S[lson].ch[1]);swap(S[rson].ch[0],S[rson].ch[1]);
		if (lson) S[lson].rev^=1;
		if (rson) S[rson].rev^=1;
	}
	return;
}

void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]);
	int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;S[y].fa=x;
	Update(y);
	return;
}

void Splay(int x)
{
	int now=x,stacktop=1;Stack[1]=x;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=S[now].fa;
		now=S[now].fa;
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[1])^(y==S[z].ch[1]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);S[x].ch[1]=lastx;Update(x);
		lastx=x;x=S[x].fa;
	}
	return;
}

void Makeroot(int x)
{
	Access(x);Splay(x);S[x].rev^=1;
	swap(S[x].ch[0],S[x].ch[1]);
	return;
}

int Findroot(int x)
{
	Access(x);Splay(x);
	while (S[x].ch[0]) x=S[x].ch[0];
	return x;
}

void Link(int x,int y)
{
	Makeroot(x);Makeroot(y);S[x].fa=y;
	return;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[y].ch[0]=S[x].fa=0;
	return;
}

int GetMax(int a,int b)
{
	return (S[a].key<S[b].key)?(b):(a);
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

bool Delete(int u,int v,int w)
{
	Makeroot(u);Access(v);Splay(v);
	int eid=S[v].mxid;
	if (S[eid].key<=w) return 0;
	Cut(eid,S[eid].d1);Cut(eid,S[eid].d2);
	return 1;
}

void Add_Edge(int u,int v,int w)
{
	//cout<<"Add:"<<u<<" "<<v<<" "<<w<<endl;
	//cout<<Find(u)<<" "<<Find(v)<<endl;
	if (Find(u)==Find(v))
		if (Delete(u,v,w)==0) return;
	UFS[Find(u)]=Find(v);
	int eid=++nodecnt;
	Makeroot(u);Makeroot(v);
	S[u].fa=S[v].fa=eid;
	S[eid].d1=u;S[eid].d2=v;
	S[eid].key=w;
	return;
}
