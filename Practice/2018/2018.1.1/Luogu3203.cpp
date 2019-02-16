#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200010;
const int inf=2147483647;

class Splay_Data
{
public:
    int key;
    int fa,ch[2];
    int size,rev;
    Splay_Data()
	{
	    size=fa=ch[0]=ch[1]=rev=0;
	    return;
	}
    void clear()
	{
	    size=fa=ch[0]=ch[1]=rev=0;
	    return;
	}
};

int n,m;

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
    bool Is_root(int x)
	{
	    if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
	    return 1;
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
	    int y=S[x].fa;int z=S[y].fa;
	    int sx=(x==S[y].ch[1]);
	    int sy=(y==S[z].ch[1]);
	    S[x].fa=z;if (Is_root(y)==0) S[z].ch[sy]=x;
	    if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	    S[y].ch[sx]=S[x].ch[sx^1];
	    S[x].ch[sx^1]=y;S[y].fa=x;
	    Update(y);Update(x);
	    return;
	}
    void Splay(int x)
	{
	    int stacktop=1;
	    int now=x;
	    Stack[stacktop]=now;
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
		    ((S[y].ch[0]==x)^(S[z].ch[0]==y))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	    }
	    return;
	}
    void Access(int x)
	{
	    int lastx=0;
	    while (x)
	    {
		//cout<<"Access:"<<x<<endl;Outp(n+1);
		Splay(x);
		S[x].ch[1]=lastx;
		Update(x);lastx=x;
	        //cout<<S[x].fa<<endl;
		x=S[x].fa;
	    }
	    return;
	}
    void Makeroot(int x)
	{
	    Access(x);Splay(x);
	    S[x].rev^=1;
	    swap(S[x].ch[0],S[x].ch[1]);
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
	    //cout<<"Split:"<<x<<" "<<y<<endl;
	    Makeroot(x);
	    //cout<<"Make root Finish:"<<endl;Outp();
	    Access(y);
	    //cout<<"Access Finish:"<<endl;Outp();
	    Splay(y);
	    //cout<<"Splay Finish:"<<endl;Outp();
	    return;
	}
    void Cut(int x,int y)
	{
	    //cout<<"Cut:"<<x<<" "<<y<<endl;
	    Split(x,y);S[x].fa=S[y].ch[0]=0;Update(x);
	    return;
	}
    void Link(int x,int y)
	{
	    //cout<<"Link:"<<x<<" "<<y<<endl;
	    Makeroot(x);S[x].fa=y;
	    return;
	}
    void Outp()
	{
	    printf("id fa ls rs size rev\n");
	    for (int i=1;i<=n+1;i++)
		if (Is_root(i))
		{
		    cout<<"root:"<<i<<endl;
		    _outp(i);
		}
	    /*
	    for (int i=1;i<=n;i++)
		printf("%2d%3d%3d%3d%5d%4d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].size,S[i].rev);
	    cout<<endl;
	    //*/
	}
    void _outp(int x)
	{
	    PushDown(x);
	    if (S[x].ch[0]) _outp(S[x].ch[0]);
	    printf("%2d%3d%3d%3d%5d%4d\n",x,S[x].fa,S[x].ch[0],S[x].ch[1],S[x].size,S[x].rev);
	    if (S[x].ch[1]) _outp(S[x].ch[1]);
	    return;
	}
};

int Put[maxN];
Link_Cut_Tree LCT;

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&Put[i]);
    for (int i=1;i<=n;i++) LCT.Link(i,min(n+1,i+Put[i]));
    //cout<<"init Link finish!"<<endl;
    //LCT.Outp(n+1);
    scanf("%d",&m);
    while (m--)
    {
	int opt;scanf("%d",&opt);
	if (opt==1)
	{
	    int x;scanf("%d",&x);x++;
	    //cout<<"Before Access:"<<endl;
	    //LCT.Outp(n+1);
	    LCT.Makeroot(n+1);
	    LCT.Access(x);
	    //cout<<"After Access,Before Splay:"<<endl;LCT.Outp(n+1);
	    LCT.Splay(x);
	    //cout<<"After Splay:"<<endl;LCT.Outp(n+1);
	    printf("%d\n",LCT.S[x].size-1);//-1因为最后n+1这个点不算
	}
	if (opt==2)
	{
	    int pos,key;scanf("%d%d",&pos,&key);pos++;
	    //cout<<"Before Cut:"<<endl;LCT.Outp();
	    LCT.Cut(pos,min(n+1,pos+Put[pos]));
	    //cout<<"After Cut:"<<endl;LCT.Outp();
	    Put[pos]=key;
	    LCT.Link(pos,min(n+1,pos+Put[pos]));
	}
	//LCT.Outp();cout<<endl;
    }
    return 0;
}
