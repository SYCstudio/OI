#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500100;
const int inf=2147483647;
const ll INF=1e18;

ll size,Num[maxN];

class Segment
{
public:
	ll S[maxN*4];
	ll Sum[maxN*4];
	Segment()
		{
			mem(S,0);
		}
	void Modify(int now,int l,int r,int pos,ll opt)
		{
			if (l==r){
				S[now]+=opt;Sum[now]+=opt*Num[l];return;
			}
			int mid=(l+r)>>1;
			if (pos<=mid) Modify(now*2,l,mid,pos,opt);
			if (pos>=mid+1) Modify(now*2+1,mid+1,r,pos,opt);
			S[now]=S[now*2]+S[now*2+1];Sum[now]=Sum[now*2]+Sum[now*2+1];
			return;
		}
	int GetMid()
		{
			return Querymid(1,1,size,S[1]/2);
		}
	int Querymid(int now,int l,int r,int q)
		{
			if (l==r) return l;
			int mid=(l+r)>>1;
			if (S[now*2]>=q) return Querymid(now*2,l,mid,q);
			else return Querymid(now*2+1,mid+1,r,q-S[now*2]);
		}
	ll Querysum(int now,int l,int r,int ql,int qr)
		{
			if ((l==ql)&&(r==qr)) return Sum[now];
			int mid=(l+r)>>1;
			if (qr<=mid) return Querysum(now*2,l,mid,ql,qr);
			if (ql>=mid+1) return Querysum(now*2+1,mid+1,r,ql,qr);
			return Querysum(now*2,l,mid,ql,mid)+Querysum(now*2+1,mid+1,r,mid+1,qr);
		}
	ll Querycnt(int now,int l,int r,int ql,int qr)
		{
			if ((l==ql)&&(r==qr)) return S[now];
			int mid=(l+r)>>1;
			if (qr<=mid) return Querycnt(now*2,l,mid,ql,qr);
			if (ql>=mid+1) return Querycnt(now*2+1,mid+1,r,ql,qr);
			return Querycnt(now*2,l,mid,ql,mid)+Querycnt(now*2+1,mid+1,r,mid+1,qr);
		}
};

class RANGE
{
public:
	ll l,r;
};

bool operator < (RANGE A,RANGE B){
	return A.l+A.r<B.l+B.r;
}

ll n,pl,K;
ll Ans=0;
ll L[maxN],R[maxN];
Segment S1,S2;
RANGE Range[maxN];

int Find(int key);

int main()
{
	//freopen("cstdiorank1AK.in","r",stdin);freopen("cstdiorank1AK.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>K>>n;
	for (int i=1;i<=n;i++)
	{
		char opt1,opt2;ll a,b;
		cin>>opt1>>a>>opt2>>b;
		if (opt1==opt2) Ans=Ans+abs(a-b);
		else
		{
			if (a>b) swap(a,b);
			pl++;L[pl]=a;R[pl]=b;
		}
	}
	if (K==1)
	{
		for (int i=pl+1;i<=pl+pl;i++) L[i]=R[i-pl];
		sort(&L[1],&L[pl+pl+1]);
		int pos=L[pl];
		for (int i=1;i<=pl+pl;i++) Ans=Ans+abs(L[i]-pos);
		printf("%lld\n",Ans+1ll*pl);
	}
	if (K==2)
	{
		//return 1;
		if (pl==0){
			printf("%lld\n",Ans);
			return 0;
		}
		for (int i=1;i<=pl;i++){
			Num[i]=L[i];Num[i+pl]=R[i];
			Range[i].l=L[i];Range[i].r=R[i];
		}
		sort(&Num[1],&Num[pl+pl+1]);size=unique(&Num[1],&Num[pl+pl+1])-Num-1;sort(&Range[1],&Range[pl+1]);
		
		//for (int i=1;i<=size;i++) cout<<Num[i]<<" ";cout<<endl;
		
		for (int i=1;i<=pl;i++) S2.Modify(1,1,size,Find(Range[i].l),1),S2.Modify(1,1,size,Find(Range[i].r),1);
		
		ll Ans2;int mid=S2.GetMid();//cout<<"mid:"<<mid<<endl;
		Ans2=Num[mid]*S2.Querycnt(1,1,size,1,mid)-S2.Querysum(1,1,size,1,mid)+S2.Querysum(1,1,size,mid,size)-Num[mid]*S2.Querycnt(1,1,size,mid,size);
		//cout<<Ans2<<endl;
		
		for (int i=1;i<=pl;i++)
		{
			S1.Modify(1,1,size,Find(Range[i].l),1);S1.Modify(1,1,size,Find(Range[i].r),1);
			S2.Modify(1,1,size,Find(Range[i].l),-1);S2.Modify(1,1,size,Find(Range[i].r),-1);
			int md1=S1.GetMid(),md2=S2.GetMid();
			ll nowans
				=Num[md1]*S1.Querycnt(1,1,size,1,md1)-S1.Querysum(1,1,size,1,md1)+S1.Querysum(1,1,size,md1,size)-Num[md1]*S1.Querycnt(1,1,size,md1,size)
				+Num[md2]*S2.Querycnt(1,1,size,1,md2)-S2.Querysum(1,1,size,1,md2)+S2.Querysum(1,1,size,md2,size)-Num[md2]*S2.Querycnt(1,1,size,md2,size);
			Ans2=min(Ans2,nowans);
		}
		printf("%lld\n",Ans+Ans2+pl);
	}
	return 0;
}

int Find(int key)
{
	int l=1,r=size,ret=0;
	do
	{
		int mid=(l+r)>>1;
		if (Num[mid]<=key) ret=mid,l=mid+1;
		else r=mid-1;
	}
	while (l<=r);
	return ret;
}
