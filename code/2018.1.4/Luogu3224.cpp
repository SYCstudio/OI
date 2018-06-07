#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=100010;
const int maxNode=maxN*10;
const int inf=2147483647;

class Splay_Data
{
public:
    int key;
    int fa,ch[2];
    int size;
    Splay_Data()
    {
	fa=ch[0]=ch[1]=size=0;
	return;
    }
};

int n,m;
int splaycnt=0;
Splay_Data S[maxNode];
int Root[maxN];//n棵Splay的根
int Mayuri[maxN];
int Queue[maxN];

void Insert(int rootid,int key);
int Find(int x);
void Update(int x);
void Rotate(int x);
void Splay(int rootid,int x,int goal);
void Union(int id1,int id2);
void OutpSplay();
void _outpdfs(int x);
int Rank(int rootid,int kth);

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) Mayuri[i]=i;
    for (int i=1;i<=n;i++)
    {
	int key;scanf("%d",&key);
	//Insert(i,inf);Insert(i,-inf);
	Insert(i,key);
    }
    for (int i=1;i<=n;i++) Insert(i,inf),Insert(i,-inf);
    //OutpSplay();
    //cout<<endl;
    for (int i=1;i<=m;i++)
    {
	int u,v;scanf("%d%d",&u,&v);
	Union(u,v);
	//OutpSplay();
	//cout<<endl;
    }
    int Q;scanf("%d",&Q);
    while (Q--)
    {
	char opt;cin>>opt;
	if (opt=='Q')
	{
	    int qid,kth;scanf("%d%d",&qid,&kth);
	    qid=Find(qid);
	    printf("%d\n",Rank(qid,kth));
	}
	if (opt=='B')
	{
	    int u,v;scanf("%d%d",&u,&v);
	    Union(u,v);
	}
    }
    return 0;
}

int Find(int x)
{
    if (Mayuri[x]!=x)
	Mayuri[x]=Find(Mayuri[x]);
    return Mayuri[x];
}

void Update(int x)
{
    int lson=S[x].ch[0],rson=S[x].ch[1];
    S[x].size=S[lson].size+S[rson].size+1;
    return;
}

void Rotate(int x)
{
    int y=S[x].fa;int z=S[y].fa;
    int sx=(x==S[y].ch[1]);
    int sy=(y==S[z].ch[1]);
    S[x].fa=z;S[z].ch[sy]=x;
    S[S[x].ch[sx^1]].fa=y;S[y].ch[sx]=S[x].ch[sx^1];
    S[y].fa=x;S[x].ch[sx^1]=y;
    Update(y);Update(x);
    return;
}

void Splay(int rootid,int x,int goal)
{
    while (S[x].fa!=goal)
    {
	int y=S[x].fa;int z=S[y].fa;
	if (S[y].fa!=goal)
	    ((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
	Rotate(x);
    }
    if (goal==0) Root[rootid]=x;
    return;
}

void Insert(int rootid,int key)
{
    int now=Root[rootid],nowf=0;
    while (now)
    {
	nowf=now;now=S[now].ch[key>S[now].key];
    }
    now=++splaycnt;
    S[now].key=key;
    S[now].size=1;
    S[now].fa=nowf;
    if (nowf==0) Root[rootid]=now;
    else S[nowf].ch[key>S[nowf].key]=now;
    Splay(rootid,now,0);
    return;
}

void Union(int id1,int id2)
{
    id1=Find(id1);id2=Find(id2);
    if (id1==id2) return;
    if (S[Root[id1]].size<S[Root[id2]].size) swap(id1,id2);//保证id1所在的Splay大小大于id2所在的Splay大小，那么就是把id2合并到id1中
    Mayuri[id2]=id1;
    int h=1,t=0;Queue[1]=Root[id2];
    do
    {
	int u=Queue[++t];
	if (S[u].ch[0]) Queue[++h]=S[u].ch[0];
	if (S[u].ch[1]) Queue[++h]=S[u].ch[1];
	S[u].fa=S[u].ch[0]=S[u].ch[1]=S[u].size=0;
    }
    while (t!=h);
    for (int i=h;i>=1;i--)
    {
	int x=Queue[i];
	if ((S[x].key==inf)||(S[x].key==-inf)) continue;
	int now=Root[id1],nowf=0;
	while (now)
	{
	    nowf=now;now=S[now].ch[S[x].key>S[now].key];
	}
	now=x;
	S[now].fa=nowf;
	S[nowf].ch[S[x].key>S[nowf].key]=now;
	S[now].size=1;
	Splay(id1,now,0);
    }
    return;
}

int Rank(int rootid,int kth)
{
    int now=Root[rootid];
    if (S[now].size-2<kth) return -1;
    kth++;
    while (now)
    {
	int lson=S[now].ch[0];
	if (S[lson].size>=kth) now=lson;
	else if (S[lson].size+1==kth) return now;
	else kth=kth-S[lson].size-1,now=S[now].ch[1];
    }
}

void OutpSplay()
{
    printf("id key fa ls rs siz\n");
    for (int i=1;i<=n;i++)
	if (Find(i)==i)
	{
	    cout<<"root:"<<Root[i]<<endl;
	    _outpdfs(Root[i]);
	}
    return;
}

void _outpdfs(int x)
{
    printf("%2d%4d%3d%3d%3d%4d\n",x,S[x].key,S[x].fa,S[x].ch[0],S[x].ch[1],S[x].size);
    if (S[x].ch[0]) _outpdfs(S[x].ch[0]);
    if (S[x].ch[1]) _outpdfs(S[x].ch[1]);
    return;
}
