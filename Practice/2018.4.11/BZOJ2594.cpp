#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000+1010000;
const int inf=2147483647;

class LCT
{
public:
	int fa,ch[2];
	int mxid,key;
	int rev;
	int u,v;
};

class Edge
{
public:
	int u,v,w;
	bool del;
	int id;
};

class Option
{
public:
	int k,a,b;
	int ans;
	int id;
};

int n,m,Q;
int edgecnt=0,Head[maxN],Next[maxN];
int UFS[maxN];
Edge E[maxN];
LCT S[maxN];
Option Opt[maxN];

int read();
bool cmp1(Edge A,Edge B);
bool cmp2(Edge A,Edge B);
void Add_Edge(int u,int v,int w);
void LINK(int eid);
bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
//int Findroot(int x);
void Makeroot(int x);
void Link(int x,int y);
void Cut(int x,int y);
int Find(int x);

int main()
{
	//freopen("tube10.in","r",stdin);freopen("tube.out","w",stdout);
	S[0].key=-inf;S[0].mxid=0;mem(Head,-1);
	
	n=read();m=read();Q=read();//scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();//scanf("%d%d%d",&u,&v,&w);
		if (u>v) swap(u,v);
		Add_Edge(u,v,w);
		E[i].id=i;
	}
	for (int i=1;i<=Q;i++)
	{
		Opt[i].k=read();Opt[i].a=read();Opt[i].b=read();//scanf("%d%d%d",&Opt[i].k,&Opt[i].a,&Opt[i].b);
		if (Opt[i].k==2)
		{
			if (Opt[i].a>Opt[i].b) swap(Opt[i].a,Opt[i].b);
			for (int j=Head[Opt[i].a];j!=-1;j=Next[j])
				if (E[j].v==Opt[i].b)
				{
					Opt[i].id=j;E[j].del=1;
					break;
				}
		}
	}
	//cerr<<"Input over!"<<endl;
	for (int i=1;i<=n;i++) UFS[i]=i;
	for (int i=1;i<=n;i++) S[i].mxid=i,S[i].key=-inf;
	for (int i=1;i<=m;i++) S[i+n].mxid=i+n,S[i+n].key=E[i].w,S[i+n].u=E[i].u,S[i+n].v=E[i].v;
	//for (int i=1;i<=m;i++) if (E[i].del==0) LINK(i);
	//cout<<"Link over!"<<endl;
	sort(&E[1],&E[m+1],cmp1);
	int linkcnt=0;
	for (int i=1;i<=m;i++)
	{
		if (E[i].del==1) continue;
		if (Find(E[i].u)!=Find(E[i].v))
		{
			Link(E[i].id+n,E[i].u);Link(E[i].id+n,E[i].v);
			UFS[Find(E[i].u)]=Find(E[i].v);
			linkcnt++;
			if (linkcnt==n-1) break;
		}
	}
	sort(&E[1],&E[m+1],cmp2);

	for (int i=Q;i>=1;i--)
	{
		//cout<<i<<endl;
		if (Opt[i].k==1)
		{
			int u=Opt[i].a,v=Opt[i].b;
			Makeroot(u);Access(v);Splay(v);
			Opt[i].ans=S[S[v].mxid].key;
		}
		if (Opt[i].k==2) LINK(Opt[i].id);
	}
	for (int i=1;i<=Q;i++) if (Opt[i].k==1) printf("%d\n",Opt[i].ans);
	return 0;
}

int read()
{
	char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	int x=0;
	while ((ch<='9')&&(ch>='0')) x=x*10+ch-48,ch=getchar();
	return x;
}

bool cmp1(Edge A,Edge B){
	return A.w<B.w;
}

bool cmp2(Edge A,Edge B){
	return A.id<B.id;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].w=w;
	return;
}

void LINK(int eid)
{
	int u=E[eid].u,v=E[eid].v;
	//cout<<"link:"<<E[eid].u<<" "<<E[eid].v<<endl;
	//cout<<Findroot(u)<<" "<<Findroot(v)<<endl;
	if (Find(u)==Find(v))
	{
		//cout<<"case 1"<<endl;
		Makeroot(u);Access(v);Splay(v);
		//cout<<"hist mx key:"<<S[S[v].mxid].key<<endl;
		if (S[S[v].mxid].key<=E[eid].w) return;
		int e=S[v].mxid,eu=S[e].u,ev=S[e].v;
		Cut(e,eu);Cut(e,ev);
	}
	//cout<<"Link succeed!"<<endl;
	Link(eid+n,u);Link(eid+n,v);
	UFS[Find(u)]=Find(v);
	return;
}

bool Isroot(int x)
{
	int y=S[x].fa;
	if ((S[y].ch[0]==x)||(S[y].ch[1]==x)) return 0;
	return 1;
}

void Update(int x)
{
	S[x].mxid=x;
	if (S[S[S[x].ch[0]].mxid].key>S[S[x].mxid].key) S[x].mxid=S[S[x].ch[0]].mxid;
	if (S[S[S[x].ch[1]].mxid].key>S[S[x].mxid].key) S[x].mxid=S[S[x].ch[1]].mxid;
	return;
}

void PushDown(int x)
{
	if (S[x].rev)
	{
		swap(S[S[x].ch[0]].ch[0],S[S[x].ch[0]].ch[1]);
		swap(S[S[x].ch[1]].ch[0],S[S[x].ch[1]].ch[1]);
		if (S[x].ch[0]) S[S[x].ch[0]].rev^=1;
		if (S[x].ch[1]) S[S[x].ch[1]].rev^=1;
		S[x].rev=0;
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
	S[x].ch[sx^1]=y;S[y].fa=x;
	Update(y);return;
}

int Stack[maxN];

void Splay(int x)
{
	int now=x;
	int stacktop=1;Stack[1]=now;
	while (Isroot(now)==0){
		now=S[now].fa;Stack[++stacktop]=now;
	}
	while (stacktop) PushDown(Stack[stacktop--]);
	
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

int Findroot(int x)
{
	Access(x);Splay(x);
	while (S[x].ch[0]) x=S[x].ch[0];
	return x;
}

void Makeroot(int x)
{
	Access(x);Splay(x);
	swap(S[x].ch[0],S[x].ch[1]);S[x].rev^=1;
	return;
}

void Link(int x,int y)
{
	Makeroot(x);//Makeroot(y);
	S[x].fa=y;
	return;
}

void Cut(int x,int y)
{
	Makeroot(x);Access(y);Splay(y);
	S[y].ch[0]=S[x].fa=0;Update(y);
	return;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
