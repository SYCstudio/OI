#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60010;
const int maxM=maxN*2;
const int Mod=201314;
const int inf=2147483647;

class Question
{
public:
	int pos,id;
	int lr;
};

bool operator < (Question A,Question B)
{
	return A.pos<B.pos;
}

int n;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int Depth[maxN],Fa[maxN],Size[maxN],Hson[maxN],Top[maxN];
int idcnt=0,Id[maxN];
int Seg[maxN*8],Lazy[maxN*8];
Question Qn[maxN*4];
int QPos[maxN],Ans[maxN];

void Add_Edge(int u,int v);
void dfs1(int u);
void dfs2(int u,int nowtop);
void TCAdd(int pos);
int TCQuery(int pos);
void SegModify(int now,int l,int r,int ql,int qr,int delta);
int SegQuery(int now,int l,int r,int ql,int qr);
void PushDown(int now,int l,int r);
void SegOutp(int now,int l,int r);

int main()
{
	mem(Head,-1);int Q;
	scanf("%d%d",&n,&Q);
	for (int i=1;i<n;i++){ int fa;scanf("%d",&fa);Add_Edge(fa+1,i+1);Fa[i+1]=fa+1; }
	Depth[1]=1;
	dfs1(1);
	dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<i<<" "<<Id[i]<<" "<<Fa[i]<<" "<<Depth[i]<<" "<<Size[i]<<" "<<Top[i]<<" "<<Hson[i]<<endl;
	int qtot=0;
	for (int i=1;i<=Q;i++)
	{
		int l,r;scanf("%d%d%d",&l,&r,&QPos[i]);l++;r++;QPos[i]++;
		if (l!=1) {Qn[++qtot].id=i;Qn[qtot].pos=l-1;Qn[qtot].lr=0;}
		Qn[++qtot].id=i;Qn[qtot].pos=r;Qn[qtot].lr=1;
	}
	sort(&Qn[1],&Qn[qtot+1]);
	//for (int i=1;i<=qtot;i++) cout<<Qn[i].pos<<" ";cout<<endl;
	int nowr=0;
	for (int i=1;i<=qtot;i++)
	{
		while (nowr<Qn[i].pos)
		{
			nowr++;TCAdd(nowr);
		}
		//cout<<i<<" "<<Qn[i].id<<" "<<Qn[i].pos<<" "<<Qn[i].lr<<endl;
		//SegOutp(1,1,n);
		//cout<<"Pos:"<<QPos[Qn[i].id]<<endl;
		if (Qn[i].lr==0) Ans[Qn[i].id]-=TCQuery(QPos[Qn[i].id]);
		else Ans[Qn[i].id]+=TCQuery(QPos[Qn[i].id]);
	}
	for (int i=1;i<=Q;i++)
		printf("%d\n",(Ans[i]%Mod+Mod)%Mod);
	/*
	{
		int l,r,x;scanf("%d%d%d",&l,&r,&x);l++;r++;x++;
		mem(Seg,0);mem(Lazy,0);
		for (int i=l;i<=r;i++)
			TCAdd(i);
		printf("%d\n",TCQuery(x));
	}
	//*/
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u)
{
	Size[u]=1;
	int mxsz=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		Depth[V[i]]=Depth[u]+1;
		dfs1(V[i]);
		Size[u]+=Size[V[i]];
		if (Size[V[i]]>Size[Hson[u]]) Hson[u]=V[i];
	}
	return;
}

void dfs2(int u,int nowtop)
{
	Top[u]=nowtop;
	Id[u]=++idcnt;
	if (Hson[u]!=0) dfs2(Hson[u],nowtop);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Hson[u])
			dfs2(V[i],V[i]);
	return;
}

void TCAdd(int pos)
{
	while (Top[pos]!=1)
	{
		SegModify(1,1,n,Id[Top[pos]],Id[pos],1);
		//cout<<"Add:"<<Id[Top[pos]]<<" "<<Id[pos]<<endl;
		pos=Fa[Top[pos]];
	}
	SegModify(1,1,n,1,Id[pos],1);
	return;
}

int TCQuery(int pos)
{
	int ret=0;
	while (Top[pos]!=1)
	{
		ret=(ret+SegQuery(1,1,n,Id[Top[pos]],Id[pos])%Mod)%Mod;
		//cout<<"Query:"<<Id[Top[pos]]<<" "<<Id[pos]<<endl;
		pos=Fa[Top[pos]];
	}
	ret=(ret+SegQuery(1,1,n,1,Id[pos])%Mod)%Mod;
	return ret;
}

void SegModify(int now,int l,int r,int ql,int qr,int delta)
{
	PushDown(now,l,r);
	if ((l==ql)&&(r==qr))
	{
		Seg[now]=(Seg[now]+(ll)(r-l+1)*(ll)delta%Mod)%Mod;
		Lazy[now]+=delta;
		return;
	}
	int mid=(l+r)/2;
	if (qr<=mid) SegModify(now*2,l,mid,ql,qr,delta);
	else if (ql>mid) SegModify(now*2+1,mid+1,r,ql,qr,delta);
	else
	{
		SegModify(now*2,l,mid,ql,mid,delta);
		SegModify(now*2+1,mid+1,r,mid+1,qr,delta);
	}
	Seg[now]=(Seg[now*2]+Seg[now*2+1])%Mod;
	return;
}

int SegQuery(int now,int l,int r,int ql,int qr)
{
	PushDown(now,l,r);
	if ((ql==l)&&(qr==r))
		return Seg[now]%Mod;
	int mid=(l+r)/2;
	if (qr<=mid) return SegQuery(now*2,l,mid,ql,qr)%Mod;
	if (ql>=mid+1) return SegQuery(now*2+1,mid+1,r,ql,qr)%Mod;
	return (SegQuery(now*2,l,mid,ql,mid)+SegQuery(now*2+1,mid+1,r,mid+1,qr))%Mod;
}

void PushDown(int now,int l,int r)
{
	if (Lazy[now]==0) return;
	int mid=(l+r)/2;
	Seg[now*2]=(Seg[now*2]+(ll)Lazy[now]*(ll)(mid-l+1))%Mod;
	Seg[now*2+1]=(Seg[now*2+1]+(ll)Lazy[now]*(ll)(r-mid)%Mod);
	Lazy[now*2]=(Lazy[now*2]+Lazy[now])%Mod;
	Lazy[now*2+1]=(Lazy[now*2+1]+Lazy[now])%Mod;
	Lazy[now]=0;
	return;
}

void SegOutp(int now,int l,int r)
{
	PushDown(now,l,r);
	printf("[%d,%d] %d\n",l,r,Seg[now]);
	if (l==r) return;
	int mid=(l+r)/2;
	SegOutp(now*2,l,mid);
	SegOutp(now*2+1,mid+1,r);
	return;
}
