#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pw(x) (1<<(x))
const int maxB=30;
const int maxN=101000;

class SplayData
{
public:
	int ch[2],fa,siz,key,lz,rev;
	int zero[maxB];
	int Xor()
	{
		int sum=0;
		for (int i=0; i<maxB; i++) if ((siz-zero[i])&1) sum|=pw(i);
		return sum;
	}
	int And()
	{
		int sum=0;
		for (int i=0; i<maxB; i++) if (siz&&zero[i]==0) sum|=pw(i);
		return sum;
	}
	int Or()
	{
		int sum=0;
		for (int i=0; i<maxB; i++) if (siz-zero[i]) sum|=pw(i);
		return sum;
	}
	ll Sum()
	{
		ll sum=0;
		for (int i=0; i<maxB; i++) sum=sum+1ll*pw(i)*(siz-zero[i]);
		return sum;
	}
};

int n;
SplayData S[maxN];

bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Xor(int x,int key);
void Reverse(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
void Split(int x,int y);
void Link(int x,int y);
void Cut(int x,int y);

int main()
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for (int i=1; i<=n; i++) {
		int key;
		scanf("%d",&key);
		Xor(i,key);
		S[i].siz=1;
	}
	while (Q--) {
		char opt;
		int x,y;
		scanf(" %c%d%d",&opt,&x,&y);
		if (opt=='L') Link(x,y);
		if (opt=='C') Cut(x,y);
		if (opt=='U') {
			int key;
			scanf("%d",&key);
			Split(x,y);
			Xor(y,key);
		}
		if (opt=='A') {
			Split(x,y);
			printf("%d\n",S[y].And());
		}
		if (opt=='O') {
			Split(x,y);
			printf("%d\n",S[y].Or());
		}
		if (opt=='X') {
			Split(x,y);
			printf("%d\n",S[y].Xor());
		}
		if (opt=='S') {
			Split(x,y);
			printf("%lld\n",S[y].Sum());
		}
	}
	return 0;
}
bool Isroot(int x)
{
	int fa=S[x].fa;
	if (S[fa].ch[0]==x||S[fa].ch[1]==x) return 0;
	return 1;
}
void Update(int x)
{
	for (int i=0; i<maxB; i++)
		S[x].zero[i]=S[S[x].ch[0]].zero[i]+S[S[x].ch[1]].zero[i]+((~S[x].key>>i)&1);
	S[x].siz=S[S[x].ch[0]].siz+S[S[x].ch[1]].siz+1;
	return;
}
void PushDown(int x)
{
	if (S[x].lz) {
		if (S[x].ch[0]) Xor(S[x].ch[0],S[x].lz);
		if (S[x].ch[1]) Xor(S[x].ch[1],S[x].lz);
		S[x].lz=0;
	}
	if (S[x].rev) {
		if (S[x].ch[0]) Reverse(S[x].ch[0]);
		if (S[x].ch[1]) Reverse(S[x].ch[1]);
		S[x].rev=0;
	}
	return;
}
void Xor(int x,int key)
{
	S[x].lz^=key;
	S[x].key^=key;
	for (int i=0; i<maxB; i++) if ((key>>i)&1) S[x].zero[i]=S[x].siz-S[x].zero[i];
	return;
}
void Reverse(int x)
{
	swap(S[x].ch[0],S[x].ch[1]);
	S[x].rev^=1;
}
void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;
	if (!Isroot(y)) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;
	S[y].fa=x;
	Update(y);
	return;
}
void Splay(int x)
{
	static int St[maxN];
	int now=x,top=1;
	St[1]=now;
	while (!Isroot(now)) St[++top]=now=S[now].fa;
	while (top) PushDown(St[top--]);
	while (!Isroot(x)) {
		int y=S[x].fa,z=S[y].fa;
		if (!Isroot(y)) ((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
		Rotate(x);
	}
	Update(x);
	return;
}
void Access(int x)
{
	int lstx=0;
	while (x) {
		Splay(x);
		S[x].ch[1]=lstx;
		Update(x);
		lstx=x;
		x=S[x].fa;
	}
	return;
}
void Makeroot(int x)
{
	Access(x);
	Splay(x);
	Reverse(x);
	return;
}
void Split(int x,int y)
{
	Makeroot(x);
	Access(y);
	Splay(y);
	return;
}
void Link(int x,int y)
{
	Makeroot(x);
	S[x].fa=y;
	return;
}
void Cut(int x,int y)
{
	Split(x,y);
	S[y].ch[0]=S[x].fa=0;
	Update(x);
	Update(y);
	return;
}
