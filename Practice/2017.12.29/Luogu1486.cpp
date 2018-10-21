#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200100;
const int inf=2147483647;

class Splay_Data
{
public:
    int key;
    int fa,ch[2];
    int size,cnt;
    Splay_Data()
	{
	    fa=ch[0]=ch[1]=0;
	    size=cnt=0;
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
	    cnt=0;
	    root=0;
	    Insert(inf);Insert(-inf);
	    return;
	}
    void Update(int x)
	{
	    int lson=S[x].ch[0],rson=S[x].ch[1];
	    S[x].size=S[lson].size+S[rson].size+S[x].cnt;
	    return;
	}
    void Rotate(int x)
	{
	    int y=S[x].fa,z=S[y].fa;
	    int sx=(x==S[y].ch[1]);
	    int sy=(y==S[z].ch[1]);
	    S[x].fa=z;S[z].ch[sy]=x;
	    S[S[x].ch[sx^1]].fa=y;S[y].ch[sx]=S[x].ch[sx^1];
	    S[y].fa=x;S[x].ch[sx^1]=y;
	    Update(y);Update(x);
	}
    void Splay(int x,int goal)
	{
	    while (S[x].fa!=goal)
	    {
		int y=S[x].fa,z=S[y].fa;
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
	    while ((now)&&(S[now].key!=key))
	    {
		nowf=now;
		now=S[now].ch[S[now].key<key];
	    }
	    if (now==0)
	    {
		now=++cnt;
		S[now].key=key;S[now].fa=nowf;S[now].cnt=S[now].size=1;
		if (nowf==0) root=now;
		else S[nowf].ch[S[nowf].key<key]=now;
	    }
	    else S[now].cnt++;
	    Splay(now,0);
	    return;
	}
    void Find(int key)
	{
	    int now=root;
	    while ((S[now].key!=key)&&(S[now].ch[S[now].key<key]!=0))
	    {
		now=S[now].ch[S[now].key<key];
	    }
	    Splay(now,0);
	    return;
	}
    int PN(int key,int opt)//查找前驱后继，opt=0前驱，opt=1后继
	{
	    Find(key);
	    if ((S[root].key<key)&&(opt==0)) return root;
	    if ((S[root].key>key)&&(opt==1)) return root;
	    int now=S[root].ch[opt];
	    while (S[now].ch[opt^1]!=0) now=S[now].ch[opt^1];
	    return now;
	}
    int Rank(int kth)
	{
	    if (S[root].size-2<kth) return -1;//注意这里因为提前插入了inf和-inf，所以是-2
	    int now=root;
	    kth++;
	    while (now)
	    {
		int lson=S[now].ch[0];
		if (S[lson].size>=kth) now=lson;
		else if ((S[lson].size<kth)&&(S[lson].size+S[now].cnt>=kth)) return now;
		else kth=kth-S[lson].size-S[now].cnt,now=S[now].ch[1];
	    }
	    return 0;
	}
    int Rank2(int kth)//查询倒数第kth个
	{
	    if (S[root].size-2<kth) return -1;
	    int now=root;
	    kth++;
	    while (now)
	    {
		int rson=S[now].ch[1];
		if (S[rson].size>=kth) now=rson;
		else if ((S[rson].size<kth)&&(S[rson].size+S[now].cnt>=kth)) return now;
		else kth=kth-S[rson].size-S[now].cnt,now=S[now].ch[0];
	    }
	    return 0;
	}
    void Outp(int x)
	{
	    if (S[x].ch[0]) Outp(S[x].ch[0]);
	    if ((S[x].key!=inf)&&(S[x].key!=-inf))
	        cout<<S[x].key<<" ";
	    if (S[x].ch[1]) Outp(S[x].ch[1]);
	    return;
	}
    void _Outp(int x)
	{
	    //cout<<"Id key ls rs fa siz ct"<<endl;
	    if (S[x].ch[0]) _Outp(S[x].ch[0]);
	    //if (S[x].key==-inf) cout<<"-inf";
	    //else if (S[x].key==inf) cout<<" inf";
	    if ((S[x].key!=inf)&&(S[x].key!=-inf))
	    {
		printf("%2d",x);
		printf("%4d",S[x].key);
		printf("%3d%3d%3d%4d%3d\n",S[x].ch[0],S[x].ch[1],S[x].fa,S[x].size,S[x].cnt);
	    }
	    if (S[x].ch[1]) _Outp(S[x].ch[1]);
	    return;
	}
};

int n,MIN;
int nowsum=0;
int leftcnt=0;
SplayTree S;

int main()
{
    scanf("%d%d",&n,&MIN);
    while (n--)
    {
	char opt;cin>>opt;
	if (opt=='I')
	{
	    int k;scanf("%d",&k);
	    if (k<MIN) continue;
	    S.Insert(k-nowsum);
	}
	if (opt=='A')
	{
	    int k;scanf("%d",&k);
	    nowsum+=k;
	}
	if (opt=='S')
	{
	    int k;scanf("%d",&k);
	    nowsum=nowsum-k;
	    int l=S.Rank(0),r;
	    S.Find(MIN-nowsum);
	    if (S.S[S.root].key!=MIN-nowsum) r=S.PN(MIN-nowsum,1);
	    else r=S.root;
	    //cout<<MIN-nowsum<<endl;
	    //cout<<"l:"<<l<<" r:"<<r<<endl;
	    if (l==r) continue;
	    S.Splay(l,0);S.Splay(r,l);
	    leftcnt+=S.S[S.S[r].ch[0]].size;
	    S.S[r].ch[0]=0;
	    S.Update(r);S.Update(l);
	}
	if (opt=='F')
	{
	    int k;scanf("%d",&k);
	    int rk=S.Rank2(k);
	    //cout<<"id:"<<rk<<" tree-size:"<<S.S[S.root].size<<endl;
	    if (rk==-1) printf("-1\n");
	    else printf("%d\n",S.S[rk].key+nowsum);
	}
	//cout<<"nowsum:"<<nowsum<<" ";
	//cout<<"Root:"<<S.root<<endl;
	//cout<<"Id key ls rs fa siz ct"<<endl;
	//S._Outp(S.root);
	//S.Outp(S.root);cout<<endl;
    }
    printf("%d\n",leftcnt);
    return 0;
}
