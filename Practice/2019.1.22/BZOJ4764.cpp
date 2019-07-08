#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=202000;

class SplayData
{
public:
	int ch[2],fa,anc,sz;
};

int n,m,A[maxN];
SplayData S[maxN];

bool Isroot(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
int Findroot(int x);
void Link(int x,int y);
void Cut(int x,int y);
void outp();

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&A[i]),S[i].sz=1;
	for (int i=1; i<=n; i++) if (i+A[i]<=n&&i+A[i]>=1) Link(i,i+A[i]);
	while (m--) {
		int opt;
		scanf("%d",&opt);
		if (opt==1) {
			int x;
			scanf("%d",&x);
			Access(x);
			int rt=Findroot(x);
			Splay(rt);
			if (S[rt].anc==0) printf("%d\n",S[rt].sz);
			else printf("-1\n");
		} else {
			int x,y;
			scanf("%d%d",&x,&y);
			if (x+A[x]<=n&&x+A[x]>=1) Cut(x,x+A[x]);
			A[x]=y;
			if (x+A[x]<=n&&x+A[x]>=1) Link(x,x+A[x]);
		}
		//cout<<m<<endl;outp();
	}
	return 0;
}
bool Isroot(int x)
{
	if (S[S[x].fa].ch[0]==x||S[S[x].fa].ch[1]==x) return 0;
	return 1;
}
void Update(int x)
{
	S[x].sz=S[S[x].ch[0]].sz+S[S[x].ch[1]].sz+1;
	return;
}
void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;
	if (!Isroot(y)) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;
	S[x].ch[sx^1]=y;
	Update(y);
	return;
}
void Splay(int x)
{
	while (!Isroot(x)) {
		int y=S[x].fa,z=S[y].fa;
		if (!Isroot(y))
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
		S[x].ch[1]=lstx;
		Update(x);
		lstx=x;
		x=S[x].fa;
	}
	return;
}
int Findroot(int x)
{
	Access(x);
	Splay(x);
	while (S[x].ch[0]) x=S[x].ch[0];
	Splay(x);
	return x;
}
void Link(int x,int y)
{
	if (Findroot(x)==Findroot(y)) {
		S[x].anc=y;
		return;
	}
	Access(x);
	Splay(x);
	S[x].fa=y;
	return;
}
void Cut(int x,int y)
{
	//cout<<"Cut:"<<x<<" "<<y<<endl;
	if (S[x].anc==y) {
		S[x].anc=0;
		return;
	}
	int t=Findroot(x);
	Access(x);
	Splay(x);
	S[S[x].ch[0]].fa=0;
	S[x].ch[0]=0;
	Update(x);
	if (S[t].anc&&Findroot(t)!=Findroot(S[t].anc)) Link(t,S[t].anc),S[t].anc=0;
	return;
}
void outp()
{
	printf("id fa ls rs sz anc\n");
	for (int i=1; i<=n; i++) printf("%2d%3d%3d%3d%3d%4d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].sz,S[i].anc);
}
/*
3 19
1 1 1
1 1
1 2
1 3
2 1 2
1 1
1 2
1 3
2 3 -1
1 1
1 2
1 3
2 2 233
1 1
1 2
1 3
2 2 -233
1 1
1 2
1 3
//*/
