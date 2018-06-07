#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500010;
const int inf=2147483647;

class Splay_Data
{
public:
	int fa,ch[2];
	int rev;
	int len,sum,tem;
	int mnid,d1,d2;
};

int n,nodecnt;
Splay_Data S[maxN];
int Stack[maxN],UFS[maxN];

bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
void Makeroot(int x);
int Findroot(int x);
void Link(int x,int y);
void Cut(int x,int y);
int GetMin(int id1,int id2);
int Find(int x);
void Add_Edge(int u,int v,int id,int ten,int len);
bool Delete(int u,int v,int tem);
void Outp();

int main()
{
	int Q;
	scanf("%d%d",&n,&Q);
	for (int i=0;i<=n;i++) S[i].len=0,S[i].tem=inf,UFS[i]=i;
	char opt[10];
	while (Q--)
	{
		scanf("%s",opt);
		if (opt[0]=='f')
		{
			int id,u,v,tem,len;scanf("%d%d%d%d%d",&id,&u,&v,&tem,&len);u++;v++;
			Add_Edge(u,v,id,tem,len);
		}
		if (opt[0]=='m')
		{
			int u,v;scanf("%d%d",&u,&v);u++;v++;
			if (Find(u)!=Find(v)) printf("-1\n");
			else
			{
				//cout<<"Before makeroot:"<<endl;
				//Outp();
				Makeroot(u);
				//cout<<"After makeroot:"<<endl;
				//Outp();
				Access(v);Splay(v);
				printf("%d\n",S[v].sum);
			}
		}
		if (opt[0]=='c')
		{
			int id,len;scanf("%d%d",&id,&len);id=id+n+1;
			Makeroot(id);S[id].len=len;Update(id);
		}
		//Outp();
	}
	return 0;
}

bool Isroot(int x)
{
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void Update(int x)
{
	S[x].sum=S[S[x].ch[0]].sum+S[S[x].ch[1]].sum+S[x].len;
	S[x].mnid=GetMin(x,GetMin(S[S[x].ch[0]].mnid,S[S[x].ch[1]].mnid));
	return;
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
	int now=x,stacktop=1;Stack[1]=now;
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
		//cout<<"X:"<<x<<endl;
		//Outp();
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

void Link(int x,int y)
{
	Makeroot(x);S[x].fa=y;
	return;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[x].fa=S[y].ch[0]=0;
	return;
}

int GetMin(int id1,int id2)
{
	return (S[id1].tem<S[id2].tem)?(id1):(id2);
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

void Add_Edge(int u,int v,int id,int tem,int len)
{
	id=id+n+1;
	//cout<<Find(u)<<" "<<Find(v)<<endl;
	if (Find(u)==Find(v))
		if (Delete(u,v,tem)==0) return;
	//cout<<"Link:"<<u-1<<" "<<v-1<<endl;
	UFS[Find(u)]=Find(v);
	Makeroot(u);Makeroot(v);
	S[id].len=len;S[id].tem=tem;S[id].d1=u;S[id].d2=v;
	S[u].fa=id;S[v].fa=id;Update(id);
	return;
}

bool Delete(int u,int v,int tem)
{
	Makeroot(u);Access(v);Splay(v);
	if (S[S[v].mnid].tem>tem) return 0;
	int mnid=S[v].mnid;
	Makeroot(mnid);
	Cut(mnid,S[mnid].d1);Cut(mnid,S[mnid].d2);
	//cout<<"Delete:"<<S[mnid].d1-1<<" "<<S[mnid].d2-1<<endl;
	S[mnid].fa=S[mnid].ch[0]=S[mnid].ch[1]=0;
	return 1;
}

void Outp()
{
	printf("id fa ls rs d1 d2 mnid len tem sum\n");
	for (int i=1;i<=n+5;i++) printf("%2d%3d%3d%3d%3d%3d%5d%4d%4d%4d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].d1,S[i].d2,S[i].mnid,S[i].len,S[i].tem,S[i].sum);
	return;
}
