#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class SplayData
{
public:
	int key;
	int fa,ch[2];
	int rev,size;
};

class Data
{
public:
	int key,pos;
};

int n,root;
SplayData S[maxN];
int Stack[maxN];
Data D[maxN];

void Update(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x,int goal);
void Outp(int now);
void Outp2(int now);
int Rank(int rth);
bool cmp(Data A,Data B);

int main()
{
	scanf("%d",&n);
	S[1].key=-1;
	for (int i=1;i<=n;i++) scanf("%d",&S[i+1].key),D[i]=(Data){S[i+1].key,i+1};
	S[n+2].key=-1;
	S[1].fa=0;S[1].ch[1]=2;
	root=1;
	for (int i=2;i<=n+1;i++) S[i].fa=i-1,S[i].ch[1]=i+1;
	S[n+2].fa=n+1;
	Splay(n+2,0);
	sort(&D[1],&D[n+1],cmp);
	for (int i=1;i<=n;i++)
	{
		int l=Rank(i),r=D[i].pos;
		Splay(r,0);
		printf("%d ",S[S[r].ch[0]].size);
		r=S[r].ch[1];PushDown(r);while (S[r].ch[0]) r=S[r].ch[0],PushDown(r);
		Splay(l,0);
		Splay(r,l);
		int node=S[r].ch[0];
		swap(S[node].ch[0],S[node].ch[1]);
		if (node) S[node].rev^=1;
	}
	return 0;
}

void Update(int x)
{
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1;
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
	S[x].fa=z;if (z) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}

void Splay(int x,int goal)
{
	int now=x,stacktop=1;Stack[1]=x;
	while (now!=root)
	{
		Stack[++stacktop]=S[now].fa;now=S[now].fa;
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (S[x].fa!=goal)
	{
		int y=S[x].fa,z=S[y].fa;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	if (goal==0) root=x;
	Update(x);return;
}

int Rank(int kth)
{
	int now=root;
	do
	{
		PushDown(now);
		int lson=S[now].ch[0];
		if (S[lson].size+1==kth) return now;
		if (S[lson].size>=kth) now=lson;
		else kth=kth-S[lson].size-1,now=S[now].ch[1];
	}
	while (1);
}

bool cmp(Data A,Data B)
{
	if (A.key!=B.key) return A.key<B.key;
	else return A.pos<B.pos;
}
