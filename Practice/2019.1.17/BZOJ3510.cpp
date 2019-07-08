#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;

class SplayData
{
public:
	int ch[2],fa,vsz,sum,rev;
};

int n,Q,ufs[maxN],Ans,St[maxN];
SplayData S[maxN];

int find(int x);
bool Isroot(int x);
void Reverse(int x);
void PushDown(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
void Link(int x,int y);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&Q);
	for (int i=1; i<=n; i++) ufs[i]=i,Ans^=i,S[i].sum=1;
	while (Q--) {
		char ipt[5];
		scanf("%s",ipt);
		if (ipt[0]=='X') printf("%d\n",Ans);
		else if (ipt[0]=='Q') {
			int u;
			scanf("%d",&u);
			printf("%d\n",find(u));
		} else {
			int a,b;
			scanf("%d%d",&a,&b);
			Link(a,b);
		}
	}
	return 0;
}
int find(int x)
{
	if (ufs[x]!=x) ufs[x]=find(ufs[x]);
	return ufs[x];
}
bool Isroot(int x)
{
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}
void Reverse(int x)
{
	S[x].rev^=1;
	swap(S[x].ch[0],S[x].ch[1]);
	return;
}
void PushDown(int x)
{
	if (S[x].rev) {
		if (S[x].ch[0]) Reverse(S[x].ch[0]);
		if (S[x].ch[1]) Reverse(S[x].ch[1]);
		S[x].rev=0;
	}
	return;
}
void Update(int x)
{
	S[x].sum=S[x].vsz+S[S[x].ch[0]].sum+S[S[x].ch[1]].sum+1;
	return;
}
void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;
	if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;
	S[y].fa=x;
	Update(y);
	return;
}
void Splay(int x)
{
	int now=x,top=0;
	while (Isroot(now)==0) {
		St[++top]=now;
		now=S[now].fa;
	}
	St[++top]=now;
	while (top) PushDown(St[top--]);
	while (Isroot(x)==0) {
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
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
		S[x].vsz+=S[S[x].ch[1]].sum;
		S[x].vsz-=S[lstx].sum;
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
void Link(int x,int y)
{
	Makeroot(x);
	Makeroot(y);
	S[x].fa=y;
	S[y].vsz+=S[x].sum;
	Update(y);
	x=find(x);
	y=find(y);
	Makeroot(x);
	Access(y);
	Splay(x);
	int newrt=n+1,lsum=0,rsum=0,limit=S[x].sum/2,now=x;
	while (now) {
		PushDown(now);
		if ((S[S[now].ch[0]].sum+lsum<=limit)&&(S[S[now].ch[1]].sum+rsum<=limit)) newrt=min(newrt,now);
		if (S[S[now].ch[0]].sum+lsum>S[S[now].ch[1]].sum+rsum)
			rsum+=S[now].vsz+S[S[now].ch[1]].sum+1,now=S[now].ch[0];
		else lsum+=S[now].vsz+S[S[now].ch[0]].sum+1,now=S[now].ch[1];
	}
	ufs[x]=ufs[y]=ufs[newrt]=newrt;
	Ans^=x^y^newrt;
	Splay(newrt);
	return;
}
