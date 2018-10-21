#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int size,vsize;
	int rev;
};

int n;
Splay_Data S[maxN];
int Stack[maxN];
set<int> Exi[maxN];

bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
int Findroot(int x);
void Makeroot(int x);
void Link(int x,int y);
void Cut(int x,int y);

int main()
{
	int Q;
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) S[i].size=1,S[i].vsize=0;
	while (Q--)
	{
		int type,x,y;scanf("%d%d%d",&type,&x,&y);
		if (type==0)
		{
			if (Findroot(x)==Findroot(y)) printf("ILLEGAL\n");
			else
			{
				Link(x,y);Exi[x].insert(y);Exi[y].insert(x);
				printf("OK\n");
			}
		}
		if (type==1)
		{
			if (Exi[x].find(y)==Exi[x].end()) printf("ILLEGAL\n");
			else
			{
				Cut(x,y);
				Exi[x].erase(y);Exi[y].erase(x);
				printf("OK\n");
			}
		}
		if (type==2)
		{
			if (Findroot(x)!=Findroot(y))
			{
				printf("ILLEGAL\n");
				continue;
			}
			Makeroot(x);Access(y);Splay(y);
			printf("%d.0000\n",S[y].size-S[y].vsize-1);
		}
	}
	return 0;
}

bool Isroot(int x)
{
	if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
	return 1;
}

void Update(int x)
{
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1+S[x].vsize;
	return;
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

void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
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
	int now=x;
	int stacktop=1;Stack[1]=x;
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
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);
		S[x].vsize=S[x].vsize-S[lastx].size+S[S[x].ch[1]].size;
		S[x].ch[1]=lastx;S[lastx].fa=x;Update(x);
		lastx=x;x=S[x].fa;
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
	Makeroot(x);Makeroot(y);
	S[y].vsize+=S[x].size;
	S[x].fa=y;Update(y);
	return;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[y].size-=S[x].size;
	S[y].ch[0]=S[x].fa=0;Update(y);
	return;
}
