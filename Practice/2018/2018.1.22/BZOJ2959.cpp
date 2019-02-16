#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=150010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int key,size;
	int rev;
};

int n;
Splay_Data S[maxN];
int UFS[maxN],Id[maxN];
int Stack[maxN];
int Mach[maxN];

int Find(int *f,int x);
bool Isroot(int x);
void PushDown(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
int Findroot(int x);
void Makeroot(int x);
void Link(int x,int y);
void Cut(int x,int y);
void Add_Edge(int u,int v);
void dfs(int now,int fa);

int main()
{
	int Q;
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&Mach[i]);
		S[i].key=S[i].size=Mach[i],UFS[i]=i,Id[i]=i;
	}
	while (Q--)
	{
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if (opt==1) Add_Edge(Find(Id,x),Find(Id,y));
		if (opt==2)
		{
			int xx=Find(Id,x);
			Makeroot(xx);S[xx].key+=y-Mach[x];Update(xx);Mach[x]=y;
		}
		if (opt==3)
		{
			x=Find(Id,x);y=Find(Id,y);
			if (Find(UFS,x)!=Find(UFS,y)) printf("-1\n");
			else
			{
				Makeroot(x);Access(y);Splay(y);
				printf("%d\n",S[y].size);
			}
		}
	}
	return 0;
}

int Find(int *f,int x)
{
	if (f[x]!=x) f[x]=Find(f,f[x]);
	return f[x];
}

bool Isroot(int x)
{
	int fa=Find(Id,S[x].fa);
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void PushDown(int x)
{
	if (S[x].rev)
	{
		S[x].rev=0;
		int lson=S[x].ch[0],rson=S[x].ch[1];
		swap(S[lson].ch[0],S[lson].ch[1]);
		swap(S[rson].ch[0],S[rson].ch[1]);
		if (lson) S[lson].rev^=1;
		if (rson) S[rson].rev^=1;
	}
	return;
}

void Update(int x)
{
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+S[x].key;
	return;
}

void Rotate(int x)
{
	int y=Find(Id,S[x].fa),z=Find(Id,S[y].fa);
	int sx=(x==S[y].ch[1]);
	int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);
	return;
}

void Splay(int x)
{
	int now=x;int stacktop=1;Stack[1]=x;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=Find(Id,S[now].fa);
		now=Find(Id,S[now].fa);
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		int y=Find(Id,S[x].fa);int z=Find(Id,S[y].fa);
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	return;
}

void Access(int x)
{
	int lastx=0;
	while(x)
	{
		Splay(x);S[x].ch[1]=lastx;
		Update(x);lastx=x;x=Find(Id,S[x].fa);
	}
	return;
}

int Findroot(int x)
{
	Access(x);Splay(x);
	int now=x;
	while (S[now].ch[0]) now=S[now].ch[0];
	return now;
}

void Makeroot(int x)
{
	Access(x);Splay(x);
	S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	return;
}

void Link(int x,int y)
{
	Makeroot(x);S[x].fa=y;
	return;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[x].fa=S[y].ch[0]=0;Update(y);
	return;
}

void Add_Edge(int u,int v)
{
	if (Find(UFS,u)!=Find(UFS,v))
	{
		UFS[Find(UFS,u)]=Find(UFS,v);
		Link(u,v);
		return;
	}
	else
	{
		Makeroot(u);Access(v);Splay(v);
		dfs(v,v);
		S[v].ch[0]=S[v].ch[1]=0;
	}
	return;
}

void dfs(int now,int fa)
{
	if (now!=fa) S[fa].key+=S[now].key,Id[now]=fa;
	if (S[now].ch[0]) dfs(S[now].ch[0],fa);
	if (S[now].ch[1]) dfs(S[now].ch[1],fa);
	return;
}
