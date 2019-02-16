#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500010*2;
const int inf=2147483647;

class Splay_Data
{
public:
    int key;
    int fa,ch[2];
    int size,cnt;
    Splay_Data()
	{
	    fa=ch[0]=ch[1]=size=cnt=0;
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
	    cnt=root=0;
	    Insert(inf);Insert(-inf);
	    return;
	}
    void Update(int x)
	{
	    int lson=S[x].ch[0],rson=S[x].ch[1];
	    S[x].size=S[lson].size+S[x].cnt+S[rson].size;
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
	    return;
	}
    void Splay(int x,int goal)
	{
	    while (S[x].fa!=goal)
	    {
		int y=S[x].fa,z=S[y].fa;
		if (z!=goal)
		    (x==S[y].ch[0])^(y==S[z].ch[0])?(Rotate(x)):(Rotate(y));
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
		S[now].key=key;
		S[now].fa=nowf;
		S[now].size=S[now].cnt=1;
		if (nowf==0) root=now;
		else S[nowf].ch[S[nowf].key<key]=now;
	    }
	    else
		S[now].cnt++;
	    Splay(now,0);
	    return;
	}
    void Find(int key)
	{
	    int now=root;
	    while ((S[now].key!=key)&&(S[now].ch[S[now].key<key]!=0))
		now=S[now].ch[S[now].key<key];
	    Splay(now,0);
	    return;
	}
    int PN(int key,int opt)
	{
	    Find(key);
	    if ((S[root].key<key)&&(opt==0)) return root;
	    if ((S[root].key>key)&&(opt==1)) return root;
	    if ((S[root].key==key)&&(S[root].cnt>=1)) return root;
	    int now=S[root].ch[opt];
	    while (S[now].ch[opt^1])
		now=S[now].ch[opt^1];
	    return now;
	}
    void Delete(int key)
	{
	    Find(key);
	    if (S[root].key!=key) return;
	    if (S[root].cnt>1) {S[root].cnt--;Update(root);return;}
	    int l=PN(key,0),r=PN(key,1);
	    Splay(l,0);Splay(r,l);
	    S[r].ch[0]=0;
	    Update(r);Update(l);
	    return;
	}
    void Outp(int x)
	{
	    if (S[x].ch[0]) Outp(S[x].ch[0]);
	    if ((S[x].key!=inf)&&(S[x].key!=-inf)) cout<<S[x].key<<" ";
	    if (S[x].ch[1]) Outp(S[x].ch[1]);
	}
};

int n,m;
int Head[maxN],Last[maxN];
priority_queue<int,vector<int>,greater<int> >H1,H2;
SplayTree S;

void OutpHeap();

int main()
{
    int Ans1=inf;
    mem(Head,-1);mem(Last,-1);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
	int x;scanf("%d",&x);
	int id=S.PN(x,0);
	if ((S.S[id].key!=inf)&&(S.S[id].key!=-inf)) Ans1=min(x-S.S[id].key,Ans1)/*,cout<<"D1:"<<x-S.S[id].key<<endl*/;
	id=S.PN(x,1);
	if ((S.S[id].key!=inf)&&(S.S[id].key!=-inf)) Ans1=min(S.S[id].key-x,Ans1)/*,cout<<"D2:"<<S.S[id].key-x<<endl*/;
	S.Insert(x);
	Head[i]=x;
	if (Head[i-1]!=-1) H1.push(abs(x-Head[i-1]));
    }
    //cout<<"Ans1:"<<Ans1<<endl;
    //S.Outp(S.root);cout<<endl;
    //OutpHeap();
    char Opt[20];
    int mi=1;
    while (m--)
    {
	scanf("%s",Opt);
	if (Opt[0]=='I')
	{
	    int pos,num;scanf("%d%d",&pos,&num);
	    if (Last[pos]==-1)
	    {
		if (Head[pos+1]!=-1)
		    H2.push(abs(Head[pos+1]-Head[pos]));
		H1.push(abs(Head[pos]-num));
		if (Head[pos+1]!=-1)
		    H1.push(abs(Head[pos+1]-num));
		Last[pos]=num;
	    }
	    else
	    {
		if (Head[pos+1]!=-1)
		    H2.push(abs(Last[pos]-Head[pos+1]));
		H1.push(abs(Last[pos]-num));
		if (Head[pos+1]!=-1)
		    H1.push(abs(Head[pos+1]-num));
		Last[pos]=num;
	    }
	    int id=S.PN(num,0);
	    //cout<<"id1:"<<id<<" "<<S.S[id].key<<endl;
	    if ((S.S[id].key!=inf)&&(S.S[id].key!=-inf)) Ans1=min(Ans1,num-S.S[id].key)/*,cout<<mi<<" D1:"<<num-S.S[id].key<<endl*/;
	    id=S.PN(num,1);
	    //cout<<"id2:"<<id<<" "<<S.S[id].key<<endl;
	    if ((S.S[id].key!=inf)&&(S.S[id].key!=-inf)) Ans1=min(Ans1,S.S[id].key-num)/*,cout<<mi<<" D2:"<<S.S[id].key-num<<endl*/;
	    S.Insert(num);
	}
	while ((!H1.empty())&&(!H2.empty())&&(H1.top()==H2.top()))
	    H1.pop(),H2.pop();
	if (Opt[4]=='G')
	    printf("%d\n",H1.top());
	if (Opt[4]=='S')
	    printf("%d\n",Ans1);
	//cout<<"Ans1:"<<Ans1<<endl;
	//cout<<"Splay:";
	//S.Outp(S.root);cout<<endl;
	//OutpHeap();
	mi++;
    }
    return 0;
}

priority_queue<int,vector<int>,greater<int> > HH;

void OutpHeap()
{
    while (!HH.empty()) HH.pop();
    cout<<"H1:";
    while (!H1.empty())
    {
	cout<<H1.top()<<" ";
	H2.push(H1.top());H1.pop();
    }
    cout<<endl;
    while (!H2.empty())
    {
	H1.push(H2.top());H2.pop();
    }
    return;
}
