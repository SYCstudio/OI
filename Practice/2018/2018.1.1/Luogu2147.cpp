#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=21000;
const int inf=2147483647;

class Splay_Data
{
public:
    int fa,ch[2],rev;
    Splay_Data()
	{
	    fa=ch[0]=ch[1]=rev=0;
	    return;
	}
};

class Link_Cut_Tree
{
public:
    int cnt,root;
    Splay_Data S[maxN];
    int Stack[maxN];
    Link_Cut_Tree()
	{
	    cnt=root=0;
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
    int Is_root(int x)
	{
	    if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
	    return 1;
	}
    void Rotate(int x)
	{
	    int y=S[x].fa;int z=S[y].fa;
	    int sx=(x==S[y].ch[1]);
	    int sy=(y==S[z].ch[1]);
	    S[x].fa=z;if (Is_root(y)==0) S[z].ch[sy]=x;
	    if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	    S[y].ch[sx]=S[x].ch[sx^1];
	    S[y].fa=x;S[x].ch[sx^1]=y;
	    return;
	}
    void Splay(int x)
	{
	    int now=x;
	    int stacktop=1;Stack[1]=now;
	    while (Is_root(now)==0)
	    {
		stacktop++;Stack[stacktop]=S[now].fa;
		now=S[now].fa;
	    }
	    for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	    while (Is_root(x)==0)
	    {
		int y=S[x].fa;int z=S[y].fa;
		if (Is_root(y)==0)
		    ((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):Rotate(y);
		Rotate(x);
	    }
	    return;
	}
    void Access(int x)
	{
	    int lastx=0;
	    while (x)
	    {
		Splay(x);
		S[x].ch[1]=lastx;
		lastx=x;x=S[x].fa;
	    }
	    return;
	}
    void Makeroot(int x)
	{
	    Access(x);Splay(x);S[x].rev^=1;swap(S[x].ch[0],S[x].ch[1]);
	    return;
	}
    int Findroot(int x)
	{
	    Access(x);Splay(x);
	    int now=x;
	    while (S[now].ch[0]) now=S[now].ch[0];
	    return now;
	}
    void Split(int x,int y)
	{
	    Makeroot(x);Access(y);Splay(y);
	    return;
	}
    void Link(int x,int y)
	{
	    Makeroot(x);S[x].fa=y;
	    return;
	}
    void Cut(int x,int y)
	{
	    Split(x,y);
	    S[y].ch[0]=S[x].fa=0;
	    return;
	}
};

int n,m;
char opt[20];
Link_Cut_Tree LCT;

int main()
{
    scanf("%d%d",&n,&m);
    while (m--)
    {
	int u,v;
	scanf("%s%d%d",opt,&u,&v);
	if (opt[0]=='C') LCT.Link(u,v);
	if (opt[0]=='D') LCT.Cut(u,v);
	if (opt[0]=='Q')
	    if (LCT.Findroot(u)==LCT.Findroot(v))
		printf("Yes\n");
	    else printf("No\n");
	//cout<<m<<endl;
    }
    return 0;
}
