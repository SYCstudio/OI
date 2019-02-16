#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int inf=2147483647;

int n,m;

class Splay_Data
{
public:
    int key,ch[2],size,fa,opt;
    Splay_Data()
	{
	    ch[0]=ch[1]=size=fa=opt=0;
	    return;
	}
};

class SplayTree
{
public:
    int cnt,root;
    Splay_Data S[maxN];
    SplayTree()
	{
	    cnt=0;root=0;
	    return;
	}
    void Update(int pos)
	{
	    S[pos].size=S[S[pos].ch[0]].size+S[S[pos].ch[1]].size+1;
	    return;
	}
    void PushDown(int pos)
	{
	    if ((pos)&&(S[pos].opt))
	    {
		S[S[pos].ch[0]].opt^=1;
		S[S[pos].ch[1]].opt^=1;
		swap(S[pos].ch[0],S[pos].ch[1]);
		S[pos].opt=0;
	    }
	    return;
	}
    void Rotate(int x)
	{
	    //cout<<"Before Rotate:"<<endl;
	    //OutpTree();
	    int y=S[x].fa;int z=S[y].fa;
	    bool sx=(x==S[y].ch[1]);
	    bool sy=(y==S[z].ch[1]);
	    S[z].ch[sy]=x;S[x].fa=z;
	    S[y].ch[sx]=S[x].ch[sx^1];S[S[x].ch[sx^1]].fa=y;
	    S[x].ch[sx^1]=y;S[y].fa=x;
	    Update(y);Update(x);
	    //cout<<"After Rotate:"<<endl;
	    //OutpTree();
	    return;
	}
    //*/
    void Splay(int x,int goal)
	{
	    while (S[x].fa!=goal)
	    {
		int y=S[x].fa;int z=S[y].fa;
		if (z!=goal)
		    ((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	    }
	    if (goal==0) root=x;
	    return;
	}
    void Insert(int key)
	{
	    int now=root,nowf=0;
	    while (now!=0)
	    {
		nowf=now;
		now=S[now].ch[key>S[now].key];
	    }
	    cnt++;now=cnt;
	    S[now].key=key;
	    S[now].fa=nowf;
	    S[now].size=1;
	    if (nowf==0) root=now;
	    else S[nowf].ch[key>S[nowf].key]=now;
	    //OutpTree();
	    Splay(now,0);
	    return;
	}
    int Rank(int kth)
	{
	    int now=root;
	    while (now!=0)
	    {
		PushDown(now);
		if (S[S[now].ch[0]].size+1<kth)
		{
		    kth=kth-S[S[now].ch[0]].size-1;
		    now=S[now].ch[1];
		}
		else if (S[S[now].ch[0]].size>=kth) now=S[now].ch[0];
		else return now;
	    }
	}
    void Outp(int now)
	{
	    PushDown(now);
	    if (S[now].ch[0]!=0) Outp(S[now].ch[0]);
	    if ((S[now].key!=0)&&(S[now].key!=n+1)) printf("%d ",S[now].key);
	    if (S[now].ch[1]!=0) Outp(S[now].ch[1]);
	    return;
	}
    void OutpTree()
	{
	    cout<<"Root:"<<root<<endl;
	    cout<<"id key fa lc rc siz opt"<<endl;
	    for (int i=1;i<=cnt;i++)
		cout<<" "<<i<<":  "<<S[i].key<<"  "<<S[i].fa<<"  "<<S[i].ch[0]<<"  "<<S[i].ch[1]<<"   "<<S[i].size<<"   "<<S[i].opt<<endl;
	}
};

SplayTree S;

int main()
{
    //freopen("sph.in","r",stdin);
    //freopen("sph.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=0;i<=n+1;i++) S.Insert(i);
    //S.OutpTree();
    for (int i=1;i<=m;i++)
    {
	int l,r;
	scanf("%d%d",&l,&r);
	
	int Rkl=S.Rank(l),Rkr=S.Rank(r+2);
	//cout<<"Rkl:"<<Rkl<<" Rkr:"<<Rkr<<endl;
	
	S.Splay(Rkl,0);S.Splay(Rkr,Rkl);
	S.S[S.S[S.S[Rkl].ch[1]].ch[0]].opt^=1;

	//S.OutpTree();
	//S.Outp(S.root);cout<<endl;
	//S.OutpTree();cout<<endl;
    }
    S.Outp(S.root);
    printf("\n");
    return 0;
}
