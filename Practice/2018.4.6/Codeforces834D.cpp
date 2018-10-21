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

const int maxN=45101;
const int inf=2147483647;

class SegmentData
{
public:
	int mx,lazy;
};

int n,K;
int Arr[maxN],Last[maxN],Num[maxN];
SegmentData S[maxN<<2];
int F[maxN];

void Build(int now,int l,int r);
void PushDown(int now);
void Modify(int now,int l,int r,int ql,int qr,int key);
int Query(int now,int l,int r,int ql,int qr);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>K;
	for (int i=1;i<=n;i++)
	{
		cin>>Arr[i];Last[i]=Num[Arr[i]];
		Num[Arr[i]]=i;
	}
	//for (int i=1;i<=n;i++) cout<<Last[i]<<" ";cout<<endl;
	for (int i=1;i<=K;i++)
	{
		Build(1,0,n);
		for (int j=1;j<=n;j++)
		{
			//cout<<i<<" "<<j<<endl;
			Modify(1,0,n,Last[j],j-1,1);
			F[j]=Query(1,0,n,0,j-1);
		}
	}
	cout<<F[n]<<endl;
	return 0;
}

void Build(int now,int l,int r)
{
	S[now].lazy=S[now].mx=0;
	if (l==r){
		S[now].mx=F[l];return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now].mx=max(S[lson].mx,S[rson].mx);
	return;
}

void PushDown(int now)
{
	if (S[now].lazy)
	{
		int lz=S[now].lazy;
		S[lson].mx+=lz;S[rson].mx+=lz;
		S[lson].lazy+=lz;S[rson].lazy+=lz;
		S[now].lazy=0;
	}
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
	//cout<<"M:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if ((l==ql)&&(r==qr))
	{
		S[now].mx+=key;S[now].lazy+=key;
		return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	S[now].mx=max(S[lson].mx,S[rson].mx);
	return;
}

int Query(int now,int l,int r,int ql,int qr)
{
	//cout<<"Q:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if ((l==ql)&&(r==qr)) return S[now].mx;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return max(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}
