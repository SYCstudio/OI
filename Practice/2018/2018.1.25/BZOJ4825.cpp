#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int size,rev;
	int sls,srs,sfa;
};

int root,nodecnt=0;
Splay_Data S[maxN];
int Stack[maxN];
set<int> Set;
map<int,int> Map;

bool Isroot(int x);
void PushDown(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
int Findroot(int x);
void Cut(int x,int y);
void Link(int x,int y);
void Insert(int key);
void Splay_min();
void Splay_max();
void Delete_min();
void Delete_max();

int main()
{
	int Q;scanf("%d",&Q);
	while (Q--)
	{
		int c,key;scanf("%d",&c);
		if (c==1) {scanf("%d",&key);Insert(key);}
		if (c==2) Splay_min();
		if (c==3) Splay_max();
		if (c==4) Delete_min();
		if (c==5) Delete_max();
		//cout<<"finish!"<<endl;
	}
	return 0;
}

bool Isroot(int x)
{
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void PushDown(int x)
{
	if (S[x].rev)
	{
		S[x].rev=0;
		int ls=S[x].ch[0],rs=S[x].ch[1];
		swap(S[ls].ch[0],S[ls].ch[1]);swap(S[rs].ch[0],S[rs].ch[1]);
		if (ls) S[ls].rev^=1;
		if (rs) S[rs].rev^=1;
	}
	return;
}

void Update(int x)
{
	S[x].size=S[S[x].ch[0]].size+S[S[x].ch[1]].size+1;
	return;
}

void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]);
	int sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}

void Splay(int x)
{
	int now=x,stacktop=1;Stack[1]=x;
	while (Isroot(now)==0)
	{
		Stack[++stacktop]=S[now].fa;now=S[now].fa;
	}
	for (int i=stacktop;i>=1;i--) PushDown(Stack[i]);
	while (Isroot(x)==0)
	{
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);S[x].ch[1]=lastx;Update(x);
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
	while (S[x].ch[0]) x=S[x].ch[0];
	return x;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	if (S[y].ch[0]!=x) return;
	S[x].fa=S[y].ch[0]=0;
	return;
}

void Link(int x,int y)
{
	Makeroot(x);S[x].fa=y;
	return;
}

void Insert(int key)
{
	nodecnt++;S[nodecnt].size=1;Map[key]=nodecnt;
	if (Set.empty())
	{
		Set.insert(key);root=nodecnt;printf("1\n");
		return;
	}
	set<int>::iterator pos=Set.lower_bound(key);
	if ((pos==Set.end())||(S[Map[*pos]].sls!=0))//到了最后一个，或者是后继的左儿子非空，那么放到前驱的右儿子
	{
		pos--;
		S[Map[*pos]].srs=nodecnt;S[nodecnt].sfa=Map[*pos];
		Link(nodecnt,Map[*pos]);
	}
	else//否则放到后继的左儿子
	{
		S[Map[*pos]].sls=nodecnt;S[nodecnt].sfa=Map[*pos];
		Link(nodecnt,Map[*pos]);
	}
	Set.insert(key);
	Makeroot(nodecnt);Access(root);Splay(root);
	printf("%d\n",S[root].size);
	return;
}

void Splay_min()
{
	int key=*Set.begin();
	int pos=Map[key];
	if (root==pos) {printf("1\n");return;}
	Makeroot(pos);Access(root);Splay(root);
	printf("%d\n",S[root].size);
	Cut(pos,S[pos].sfa);if (S[pos].srs) Cut(pos,S[pos].srs);
	Link(pos,root);if (S[pos].srs) Link(S[pos].sfa,S[pos].srs);
	S[root].sfa=pos;
	S[S[pos].sfa].sls=S[pos].srs;if (S[pos].srs) S[S[pos].srs].sfa=S[pos].sfa;
	S[pos].sfa=0;S[pos].srs=root;
	root=pos;return;
}

void Splay_max()
{
	int key=*(--Set.end());
	int pos=Map[key];
	if (root==pos) {printf("1\n");return;}
	Makeroot(pos);Access(root);Splay(root);
	printf("%d\n",S[root].size);
	Cut(S[pos].sfa,pos);if (S[pos].sls) Cut(S[pos].sls,pos);
	Link(pos,root);if (S[pos].sls) Link(S[pos].sfa,S[pos].sls);
	S[root].sfa=pos;
	S[S[pos].sfa].srs=S[pos].sls;if (S[pos].sls) S[S[pos].sls].sfa=S[pos].sfa;
	S[pos].sfa=0;S[pos].sls=root;
	root=pos;return;
}

void Delete_min()
{
	int key=*Set.begin();
	int pos=Map[key];
	Set.erase(Set.begin());
	if (pos==root)
	{
		printf("1\n");
		S[S[pos].srs].sfa=0;
		if (S[pos].srs) Cut(pos,S[pos].srs);
		root=S[pos].srs;
		return;
	}
	Makeroot(pos);Access(root);Splay(root);
	printf("%d\n",S[root].size);
	Cut(pos,S[pos].sfa);if (S[pos].srs) Cut(pos,S[pos].srs);
	if (S[pos].srs) Link(S[pos].sfa,S[pos].srs);
	S[S[pos].sfa].sls=S[pos].srs;if (S[pos].srs) S[S[pos].srs].sfa=S[pos].sfa;
	return;
}

void Delete_max()
{
	int key=*(--Set.end());
	int pos=Map[key];
	Set.erase(--Set.end());
	if (pos==root)
	{
		printf("1\n");
		S[S[pos].sls].sfa=0;
		if (S[pos].sls) Cut(pos,S[pos].sls);
		root=S[pos].sls;
		return;
	}
	Makeroot(pos);Access(root);Splay(root);
	printf("%d\n",S[root].size);
	Cut(pos,S[pos].sfa);if (S[pos].sls) Cut(pos,S[pos].sls);
	if (S[pos].sls) Link(S[pos].sls,S[pos].sfa);
	S[S[pos].sfa].srs=S[pos].sls;if (S[pos].sls) S[S[pos].sls].sfa=S[pos].sfa;
	return;
}
