#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizoef(Arr))

const int maxN=101000;
const int inf=2147483647;

class SegData
{
public:
	ll sum,lazy;
	int ls,rs;
	void init(){
		sum=lazy=ls=rs=0;return;
	}
};

int n,m,nodecnt;
SegData S[maxN*100];
int root[maxN],Arr[maxN];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int ql,int qr,ll key);
ll Query(int r1,int r2,int l,int r,int ql,int qr);

int main()
{
	ios::sync_with_stdio(false);
	int cas=0;
	while (cin>>n>>m)
	{
		if (cas!=0) cout<<endl;cas++;
		nodecnt=0;root[0]=0;
		for (int i=1;i<=n;i++) cin>>Arr[i];
		Build(root[0],1,n);
		
		int tim=0;
		while (m--)
		{
			char opt;cin>>opt;S[0].init();
			if (opt=='C')
			{
				int l,r,d;cin>>l>>r>>d;
				tim++;root[tim]=root[tim-1];
				Modify(root[tim],1,n,l,r,d);
			}
			if (opt=='Q')
			{
				int l,r;cin>>l>>r;
				cout<<Query(0,root[tim],1,n,l,r)<<endl;
			}
			if (opt=='H')
			{
				int l,r,t;cin>>l>>r>>t;
				cout<<Query(0,root[t],1,n,l,r)<<endl;
			}
			if (opt=='B')
			{
				int t;cin>>t;
				tim=t;
			}
		}
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;S[now].init();
	if (l==r){
		S[now].sum=Arr[l];return;
	}
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	S[now].sum=S[S[now].ls].sum+S[S[now].rs].sum;
	return;
}

void Modify(int &now,int l,int r,int ql,int qr,ll key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].sum+=(ll)(qr-ql+1)*(ll)key;
	if ((l==ql)&&(r==qr)){
		S[now].lazy+=(ll)key;return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr,key);
	else{
		Modify(S[now].ls,l,mid,ql,mid,key);
		Modify(S[now].rs,mid+1,r,mid+1,qr,key);
	}
	return;
}

ll Query(int r1,int r2,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[r2].sum-S[r1].sum;
	int mid=(l+r)>>1;
	ll sum=(ll)(S[r2].lazy-S[r1].lazy)*(ll)(qr-ql+1);
	if (qr<=mid) return Query(S[r1].ls,S[r2].ls,l,mid,ql,qr)+sum;
	else if (ql>=mid+1) return Query(S[r1].rs,S[r2].rs,mid+1,r,ql,qr)+sum;
	else return Query(S[r1].ls,S[r2].ls,l,mid,ql,mid)+Query(S[r1].rs,S[r2].rs,mid+1,r,mid+1,qr)+sum;
}
