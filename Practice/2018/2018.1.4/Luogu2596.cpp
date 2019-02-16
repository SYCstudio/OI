#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=80010;
const int inf=2147483647;

class Splay_Data
{
public:
    int key;
    int fa,ch[2];
    int size;
};

int n,m;
int root=0,splaycnt=0;
int infid1,infid2;//记录左右哨兵的编号
Splay_Data S[maxN];
int Input[maxN];
int Id[maxN];

void Build(int l,int r,int father,int opt);
void Update(int x);
void Rotate(int x);
void Splay(int x,int goal);
int Rank(int kth);
int Next(int x,int opt);
void OutpSplay();
void _outpdfs(int x);
void OutpRange();
void _rangedfs(int x);

int main()
{
    scanf("%d%d",&n,&m);
    Input[0]=Input[n+1]=inf;
    for (int i=1;i<=n;i++)scanf("%d",&Input[i]);
    root=1;
    Build(0,n+1,0,0);
    char Opt[10];
    //OutpRange();
    //OutpSplay();
    //for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
    while (m--)
    {
	scanf("%s",Opt);
	if (Opt[0]=='T')//把编号为id的书放到最前面
	{
	    int id;scanf("%d",&id);
	    id=Id[id];
	    int nex=Next(id,1);//先提取其后继
	    Splay(infid1,0);//把左哨兵旋转到根
	    Splay(id,infid1);
	    Splay(nex,id);//把三个连在一起
	    if (S[id].ch[0])//此时要转移的区间就在id的左儿子，把它转移给next的左儿子
	    {
		int lson=S[id].ch[0];
		S[nex].ch[0]=lson;S[lson].fa=nex;S[id].ch[0]=0;
		Update(nex);Update(id);Update(infid1);
	    }
	}
	if (Opt[0]=='B')
	{
	    int id;scanf("%d",&id);
	    id=Id[id];
	    int pre=Next(id,0);
	    Splay(infid2,0);Splay(id,infid2);Splay(pre,id);
	    if (S[id].ch[1])
	    {
		int rson=S[id].ch[1];
		S[rson].fa=pre;S[pre].ch[1]=rson;S[id].ch[1]=0;
		Update(pre);Update(id);Update(infid2);
	    }
	}
	if (Opt[0]=='I')
	{
	    int id,t;scanf("%d%d",&id,&t);
	    if (t==0) continue;
	    id=Id[id];
	    if (t==-1)
	    {
		int pre=Next(id,0);
		int key1=S[id].key,key2=S[pre].key;
		Id[key1]=pre;Id[key2]=id;
		swap(S[pre].key,S[id].key);
	    }
	    if (t==1)
	    {
		int nex=Next(id,1);
		int key1=S[id].key,key2=S[nex].key;
		Id[key1]=nex;Id[key2]=id;
		swap(S[nex].key,S[id].key);
	    }
	}
	if (Opt[0]=='A')
	{
	    int id;scanf("%d",&id);
	    id=Id[id];
	    Splay(id,0);
	    printf("%d\n",S[S[id].ch[0]].size-1);
	}
	if (Opt[0]=='Q')
	{
	    int rk;scanf("%d",&rk);
	    int id=Rank(rk+1);
	    printf("%d\n",S[id].key);
	}
    }
    return 0;
}

void Update(int x)
{
    S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1;
    return;
}

void Build(int l,int r,int father,int opt)
{
    //cout<<"Build:"<<l<<" "<<r<<endl;
    int mid=(l+r)/2;
    int now=++splaycnt;
    if (l==r)
	S[now].size=1;
    S[now].key=Input[mid];
    S[now].fa=father;
    if (Input[mid]!=inf) Id[Input[mid]]=now;
    if (Input[mid]==inf)
    {
	if (infid1==0) infid1=now;
	else infid2=now;
    }
    if (father) S[father].ch[opt]=now;
    if (l<mid) Build(l,mid-1,now,0);
    if (r>mid) Build(mid+1,r,now,1);
    Update(now);
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

int Rank(int kth)
{
    int now=root;
    while (now)
    {
	int lson=S[now].ch[0];
	if (S[lson].size>=kth) now=lson;
	else if (S[lson].size+1==kth) return now;
	else kth=kth-S[lson].size-1,now=S[now].ch[1];
    }
    return 0;
}

int Next(int x,int opt)
{
    Splay(x,0);
    int now=S[x].ch[opt];
    while (S[now].ch[opt^1]) now=S[now].ch[opt^1];
    return now;
}

void OutpSplay()
{
    printf("id key fa ls rs siz\n");
    _outpdfs(root);
    cout<<endl;
}

void _outpdfs(int x)
{
    printf("%2d%4d%3d%3d%3d%4d\n",x,S[x].key,S[x].fa,S[x].ch[0],S[x].ch[1],S[x].size);
    if (S[x].ch[0]) _outpdfs(S[x].ch[0]);
    if (S[x].ch[1]) _outpdfs(S[x].ch[1]);
    return;
}

void OutpRange()
{
    _rangedfs(root);
    cout<<endl<<endl;
    return;
}

void _rangedfs(int x)
{
    if (S[x].ch[0]) _rangedfs(S[x].ch[0]);
    cout<<S[x].key<<" ";
    if (S[x].ch[1]) _rangedfs(S[x].ch[1]);
    return;
}
