#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=50100;
const int inf=2147483647;

int n,m;
ll numcnt=0,Num[maxN];

class SegData
{
public:
	ll val,lazy;
	int ls,rs;
};

int nodecnt=0;
SegData S[maxN*200];

class InTree
{
public:
	int root;
	InTree(){
		root=0;return;
	}
	
	void Modify(int &now,int l,int r,int ql,int qr,ll key){
		if (now==0) now=++nodecnt;
		S[now].val+=key*(qr-ql+1);
		if ((l==ql)&&(r==qr)){
			S[now].lazy+=key;return;
		}
		int mid=(l+r)>>1;
		if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr,key);
		else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr,key);
		else
		{
			Modify(S[now].ls,l,mid,ql,mid,key);
			Modify(S[now].rs,mid+1,r,mid+1,qr,key);
		}
		return;
	}
	ll Query(int now,int l,int r,int ql,int qr){
		if (now==0) return 0;
		if ((l==ql)&&(r==qr)) return S[now].val;
		int mid=(l+r)>>1;
		ll Ret=S[now].lazy*(ll)(qr-ql+1);
		if (qr<=mid) return Query(S[now].ls,l,mid,ql,qr)+Ret;
		else if (ql>=mid+1) return Query(S[now].rs,mid+1,r,ql,qr)+Ret;
		else return Query(S[now].ls,l,mid,ql,mid)+Query(S[now].rs,mid+1,r,mid+1,qr)+Ret;
	}
};

class OutTree
{
public:
	InTree T[maxN<<2];
	void Modify(int now,int l,int r,int pos,int Rl,int Rr){
		T[now].Modify(T[now].root,1,n,Rl,Rr,1);
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) Modify(lson,l,mid,pos,Rl,Rr);
		else Modify(rson,mid+1,r,pos,Rl,Rr);
		return;
	}
	ll Query(int now,int l,int r,int Rl,int Rr,ll kth){
		if (l==r) return l;
		int mid=(l+r)>>1;
		ll G=T[rson].Query(T[rson].root,1,n,Rl,Rr);
		if (G>=kth) return Query(rson,mid+1,r,Rl,Rr,kth);
		else return Query(lson,l,mid,Rl,Rr,kth-G);
	}
};

class Question
{
public:
	ll opt,a,b,c;
};

Question Q[maxN];
OutTree T;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld%lld",&Q[i].opt,&Q[i].a,&Q[i].b,&Q[i].c);
		if (Q[i].opt==1) Num[++numcnt]=Q[i].c;
	}
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" ";cout<<endl;
	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	//cout<<numcnt<<endl;
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" ";cout<<endl;
	for (int i=1;i<=m;i++)
		if (Q[i].opt==1)
		{
			//cout<<Q[i].c<<" ";
			Q[i].c=lower_bound(&Num[1],&Num[numcnt+1],Q[i].c)-Num;
			//cout<<Q[i].c<<endl;
			T.Modify(1,1,numcnt,Q[i].c,Q[i].a,Q[i].b);
		}
		else
		{
			printf("%lld\n",Num[T.Query(1,1,numcnt,Q[i].a,Q[i].b,Q[i].c)]);
		}
	return 0;
}
