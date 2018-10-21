#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200010;
const int inf=2147483647;

int n,m;

namespace LCT
{
	class Splay_Data
	{
	public:
		int fa,ch[2];
		int rev;
		int key;
		int mnid;
		int d1,d2;
	};

	int nodecnt=0;
	Splay_Data S[maxN*2];
	int Stack[maxN*2];
	
	bool Isroot(int x)
	{
		if ((S[S[x].fa].ch[0]==x)||(S[S[x].fa].ch[1]==x)) return 0;
		return 1;
	}
	
	void Update(int x)
	{
		S[x].mnid=x;
		if (S[S[S[x].ch[0]].mnid].key<S[S[x].mnid].key) S[x].mnid=S[S[x].ch[0]].mnid;
		if (S[S[S[x].ch[1]].mnid].key<S[S[x].mnid].key) S[x].mnid=S[S[x].ch[1]].mnid;
		return;
	}
	
	void PushDown(int x)
	{
		if (S[x].rev)
		{
			S[x].rev=0;int ls=S[x].ch[0],rs=S[x].ch[1];
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
		Access(x);Splay(x);S[x].rev^=1;
		swap(S[x].ch[0],S[x].ch[1]);
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
	void Add_Edge(int u,int v,int id)
	{
		Makeroot(u);Makeroot(v);
		++nodecnt;
		S[nodecnt].key=id;
		S[u].fa=nodecnt;S[v].fa=nodecnt;
		S[nodecnt].d1=u;S[nodecnt].d2=v;
		return;
	}
};

namespace Seg
{
	class SegmentData
	{
	public:
		int ls,rs;
		int sum;
	};

	int nodecnt=0;
	int root[maxN];
	SegmentData S[maxN*30];
	void Build(int &now,int l,int r)
	{
		now=++nodecnt;
		if (l==r) return;
		int mid=(l+r)>>1;
		Build(S[now].ls,l,mid);
		Build(S[now].rs,mid+1,r);
		return;
	}

	void Update(int &now,int l,int r,int num)
	{
		S[++nodecnt]=S[now];now=nodecnt;
		S[nodecnt].sum++;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (num<=mid) Update(S[now].ls,l,mid,num);
		else Update(S[now].rs,mid+1,r,num);
		return;
	}

	int Query(int now1,int now2,int l,int r,int ql,int qr)
	{
		if ((l==ql)&&(r==qr)) return S[now2].sum-S[now1].sum;
		int mid=(l+r)/2;
		if (qr<=mid) return Query(S[now1].ls,S[now2].ls,l,mid,ql,qr);
		else if (ql>=mid+1) return Query(S[now1].rs,S[now2].rs,mid+1,r,ql,qr);
		return Query(S[now1].ls,S[now2].ls,l,mid,ql,mid)+Query(S[now1].rs,S[now2].rs,mid+1,r,mid+1,qr);
	}
};

int K,type;
int ntr[maxN];

int main()
{
	scanf("%d%d%d%d",&n,&m,&K,&type);
	for (int i=0;i<=n;i++) LCT::S[i].key=inf;
	LCT::nodecnt=n;
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		if (u==v) {ntr[i]=i;continue;}//自环
		if (LCT::Findroot(u)!=LCT::Findroot(v))
			LCT::Add_Edge(u,v,i);
		else
		{
			LCT::Makeroot(u);LCT::Access(v);LCT::Splay(v);
			int mnid=LCT::S[v].mnid;
			ntr[i]=LCT::S[mnid].key;
			LCT::Cut(LCT::S[mnid].d1,LCT::S[mnid].d2);
			LCT::Add_Edge(u,v,i);
		}
	}
	//for (int i=1;i<=m;i++) cout<<ntr[i]<<" ";cout<<endl;
	Seg::Build(Seg::root[0],0,m);
	for (int i=1;i<=m;i++)
	{
		Seg::root[i]=Seg::root[i-1];
		Seg::Update(Seg::root[i],0,m,ntr[i]);
	}
	int ans=0;
	while (K--)
	{
		int l,r;scanf("%d%d",&l,&r);
		if (type) l^=ans,r^=ans;
		ans=n-Seg::Query(Seg::root[l-1],Seg::root[r],0,m,0,l-1);
		//cout<<"Q:"<<Seg::Query(Seg::root[l-1],Seg::root[r],0,m,0,l-1)<<endl;
		printf("%d\n",ans);
	}
	return 0;
}
