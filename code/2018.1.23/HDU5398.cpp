#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxNum=100000;
const int maxN=500010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int key;
	int mnid;
	int rev;
	int d1,d2;
};

int n;
Splay_Data S[maxN];
int Stack[maxN];
int nodecnt=maxNum,Rubtop=0,Rub[maxN];//回收
int Ansmst=0;
int Ans[maxNum+10],Fact[maxN];
int UFS[maxN];

IL int GetMin(RG int a,RG int b);
IL bool Isroot(RG int x);
IL void Update(RG int x);
IL void PushDown(RG int x);
IL void Rotate(RG int x);
IL void Splay(RG int x);
IL void Access(RG int x);
IL void Makeroot(RG int x);
IL int Findroot(RG int x);
IL void Link(RG int x,RG int y);
IL void Cut(RG int x,RG int y);
IL int NewNode();
IL bool Delete(RG int u,RG int v,RG int w);
IL void Add_Edge(RG int u,RG int v);
IL int gcd(RG int u,RG int v);
IL void Outp();
int Find(int x);

int main()
{
	//freopen("out.out","w",stdout);
	for (RG int i=0;i<=maxNum;i++) S[i].key=maxNum+10,UFS[i]=i;
	//Outp();
	for (RG int i=2;i<=maxNum;i++)
	{
		RG int fcnt=0;
		for (RG int j=1;(ll)j*(ll)j<=i;j++)
			if (i%j==0)
			{
				Fact[++fcnt]=j;
				if ((ll)j*(ll)j!=i) Fact[++fcnt]=i/j;
			}
		sort(&Fact[1],&Fact[fcnt+1]);
		for (RG int j=1;j<=fcnt;j++) Add_Edge(i,Fact[j]);
		Ans[i]=Ansmst;
	}
	RG int n;
	while (scanf("%d",&n)!=EOF)
		printf("%d\n",Ans[n]);
	return 0;
}

IL int GetMin(RG int a,RG int b)
{
	return ((S[a].key<S[b].key)?(a):(b));
}

IL bool Isroot(RG int x)
{
	RG int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

IL void Update(RG int x)
{
	S[x].mnid=GetMin(x,GetMin(S[S[x].ch[0]].mnid,S[S[x].ch[1]].mnid));
	return;
}

IL void PushDown(RG int x)
{
	if (S[x].rev)
	{
		S[x].rev=0;
		RG int lson=S[x].ch[0],rson=S[x].ch[1];
		swap(S[lson].ch[0],S[lson].ch[1]);
		swap(S[rson].ch[0],S[rson].ch[1]);
		if (lson) S[lson].rev^=1;
		if (rson) S[rson].rev^=1;
	}
	return;
}

IL void Rotate(RG int x)
{
	RG int y=S[x].fa,z=S[y].fa;
	RG int sx=(x==S[y].ch[1]);
	RG int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);
	return;
}

IL void Splay(RG int x)
{
	RG int stacktop=1,now=x;
	Stack[1]=x;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=S[now].fa;
		now=S[now].fa;
	}
	for (RG int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		RG int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	return;
}

IL void Access(RG int x)
{
	RG int lastx=0;
	while (x)
	{
		Splay(x);S[x].ch[1]=lastx;
		Update(x);lastx=x;x=S[x].fa;
	}
	return;
}

IL void Makeroot(RG int x)
{
	Access(x);Splay(x);S[x].rev^=1;
	swap(S[x].ch[0],S[x].ch[1]);
	return;
}

IL int Findroot(RG int x)
{
	Access(x);Splay(x);
	RG int now=x;
	while (S[now].ch[0]) now=S[now].ch[0];
	return now;
}

IL void Link(RG int x,RG int y)
{
	Makeroot(x);S[x].fa=y;
	return;
}

IL void Cut(RG int x,RG int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[x].fa=S[y].ch[0]=0;//Update(y);
	return;
}

IL int NewNode()
{
	RG int pos;
	if (Rubtop!=0) pos=Rub[Rubtop--];
	else pos=++nodecnt;
	S[pos].fa=S[pos].ch[0]=S[pos].ch[1]=0;
	return pos;
}

IL bool Delete(RG int u,RG int v,RG int w)
{
	Makeroot(u);Access(v);Splay(v);
	RG int eid=S[v].mnid;
	if (S[eid].key>w) return 0;
	Ansmst-=S[eid].key;
	Cut(eid,S[eid].d1);Cut(eid,S[eid].d2);
	Rub[++Rubtop]=eid;
	return 1;
}

IL void Add_Edge(RG int u,RG int v)
{
	RG int w=gcd(u,v);
	if (Find(u)==Find(v))
		if (Delete(u,v,w)==0) return;
	UFS[Find(u)]=Find(v);
	RG int eid=NewNode();
	Makeroot(u);Makeroot(v);
	S[u].fa=S[v].fa=eid;
	S[eid].key=w;
	Ansmst+=w;
	S[eid].d1=u;S[eid].d2=v;
	return;
}

IL int gcd(RG int u,RG int v)
{
	RG int t;
	while (v) {t=u;u=v;v=t%v;}
	return u;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

void Outp()
{
	printf("id fa ls rs mnid    key\n");
	for (int i=1;i<=nodecnt;i++) printf("%2d%3d%3d%3d%5d [%6d]%12d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].mnid,S[S[i].mnid].key,S[i].key);
	return;
}
