#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)
#define lson (now<<1)
#define rson (lson|1)

const int maxN=50100;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt;
	int ls,rs;
};

class Question
{
public:
	int opt,a,b,c;
};

int n,m,nodecnt;
int Arr[maxN];
int numcnt=0,Num[maxN*10];
int root[maxN*40];
SegmentData S[maxN*200];
Question Qs[maxN];

void Modify_out(int now,int l,int r,int val,int pos,int opt);
void Modify_in(int &now,int l,int r,int pos,int opt);
int Query_out_rank(int now,int l,int r,int rl,int rr,int key);//查询[rl,rr]内key的排名
int Query_out_kth(int now,int l,int r,int rl,int rr,int kth);//查询[rl,rr]内排名为kth的数
int Query_out_cnt(int now,int l,int r,int vl,int vr,int rl,int rr);//查询区间内[vl,vr]的数的个数
int Query_in(int now,int l,int r,int ql,int qr);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&Arr[i]);
		Num[++numcnt]=Arr[i];
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&Qs[i].opt);
		if (Qs[i].opt==3)
		{
			scanf("%d%d",&Qs[i].a,&Qs[i].b);
			Num[++numcnt]=Qs[i].b;
		}
		else
		{
			scanf("%d%d%d",&Qs[i].a,&Qs[i].b,&Qs[i].c);
			Num[++numcnt]=Qs[i].c;
		}
	}
	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	for (int i=1;i<=n;i++) Modify_out(1,1,numcnt,Arr[i]=find(Arr[i]),i,1);

	for (int i=1;i<=m;i++)
	{
		if (Qs[i].opt==1) printf("%d\n",Query_out_rank(1,1,numcnt,Qs[i].a,Qs[i].b,find(Qs[i].c)));
		if (Qs[i].opt==2) printf("%d\n",Num[Query_out_kth(1,1,numcnt,Qs[i].a,Qs[i].b,Qs[i].c)]);
		if (Qs[i].opt==3)
		{
			int val=find(Qs[i].b),pos=Qs[i].a;
			Modify_out(1,1,numcnt,Arr[pos],pos,-1);
			Modify_out(1,1,numcnt,val,pos,1);
			Arr[pos]=val;
		}
		if (Qs[i].opt==4)
		{
			int val=find(Qs[i].c);
			int kcnt=Query_out_cnt(1,1,numcnt,val,val,Qs[i].a,Qs[i].b);
			int sumcnt=Query_out_cnt(1,1,numcnt,1,val,Qs[i].a,Qs[i].b);
			if (kcnt==sumcnt) printf("%d\n",-inf);
			else printf("%d\n",Num[Query_out_kth(1,1,numcnt,Qs[i].a,Qs[i].b,sumcnt-kcnt)]);
		}
		if (Qs[i].opt==5)
		{
			int val=find(Qs[i].c);
			int sumcnt=Query_out_cnt(1,1,numcnt,1,val,Qs[i].a,Qs[i].b);
			int allcnt=Query_out_cnt(1,1,numcnt,1,numcnt,Qs[i].a,Qs[i].b);
			if (sumcnt==allcnt) printf("%d\n",inf);
			else printf("%d\n",Num[Query_out_kth(1,1,numcnt,Qs[i].a,Qs[i].b,sumcnt+1)]);
		}
	}
	return 0;
}

void Modify_out(int now,int l,int r,int val,int pos,int opt)
{
	Modify_in(root[now],1,n,pos,opt);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (val<=mid) Modify_out(lson,l,mid,val,pos,opt);
	else Modify_out(rson,mid+1,r,val,pos,opt);
}

void Modify_in(int &now,int l,int r,int pos,int opt)
{
	if (now==0) now=++nodecnt;
	S[now].cnt+=opt;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify_in(S[now].ls,l,mid,pos,opt);
	else Modify_in(S[now].rs,mid+1,r,pos,opt);
}

int Query_out_rank(int now,int l,int r,int rl,int rr,int key)//查询[rl,rr]内key的排名
{
	if (l==r) return 1;
	int lsize=Query_in(root[lson],1,n,rl,rr);
	int mid=(l+r)>>1;
	if (key<=mid) return Query_out_rank(lson,l,mid,rl,rr,key);
	else return Query_out_rank(rson,mid+1,r,rl,rr,key)+lsize;
}

int Query_out_kth(int now,int l,int r,int rl,int rr,int kth)//查询[rl,rr]内排名为kth的数
{
	if (l==r) return l;
	int lsize=Query_in(root[lson],1,n,rl,rr);
	int mid=(l+r)>>1;
	if (lsize>=kth) return Query_out_kth(lson,l,mid,rl,rr,kth);
	else return Query_out_kth(rson,mid+1,r,rl,rr,kth-lsize);
}

int Query_out_cnt(int now,int l,int r,int vl,int vr,int rl,int rr)//查询[rl,rr]内[vl,vr]的数的个数
{
	if ((l==vl)&&(r==vr)) return Query_in(root[now],1,n,rl,rr);
	int mid=(l+r)>>1;
	if (vr<=mid) return Query_out_cnt(lson,l,mid,vl,vr,rl,rr);
	else if (vl>=mid+1) return Query_out_cnt(rson,mid+1,r,vl,vr,rl,rr);
	else return Query_out_cnt(lson,l,mid,vl,mid,rl,rr)+Query_out_cnt(rson,mid+1,r,mid+1,vr,rl,rr);
}

int Query_in(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].cnt;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_in(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_in(S[now].rs,mid+1,r,ql,qr);
	else return Query_in(S[now].ls,l,mid,ql,mid)+Query_in(S[now].rs,mid+1,r,mid+1,qr);
}
