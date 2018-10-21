#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-(x)))

const int maxN=100100;
const int inf=2147483647;

int n;
ll Pl[maxN];
ll S[maxN*10],Lazy[maxN*10];

void Modify(int now,int l,int r,int ql,int qr,ll key);
void PushDown(int now);
ll Query(int now,int l,int r,int pos);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Pl[i]);
	int St,T;scanf("%d%d",&St,&T);T--;
	for (int i=1;i<=n;i++)
	{
		int s=((St-1)-(i-1)+n)%n+1;
		int t=((T-1)-(i-1)+n)%n+1;
		if (t<s) Modify(1,1,n,s,n,Pl[i]),Modify(1,1,n,1,t,Pl[i]);
		else Modify(1,1,n,s,t,Pl[i]);
	}
	ll id,mx=0;
	for (int i=1;i<=n;i++)
		if (Query(1,1,n,i)>mx){
			mx=Query(1,1,n,i);id=i;
		}
	printf("%lld\n",id);
	return 0;
}

void Modify(int now,int l,int r,int ql,int qr,ll key)
{
	if ((l==ql)&&(r==qr))
	{
		S[now]+=key;Lazy[now]+=key;
		return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(now*2,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(now*2+1,mid+1,r,ql,qr,key);
	else
	{
		Modify(now*2,l,mid,ql,mid,key);
		Modify(now*2+1,mid+1,r,mid+1,qr,key);
	}
	S[now]=max(S[now*2],S[now*2+1]);
	return;
}

void PushDown(int now)
{
	S[now*2]+=Lazy[now];S[now*2+1]+=Lazy[now];
	Lazy[now*2]+=Lazy[now];Lazy[now*2+1]+=Lazy[now];
	Lazy[now]=0;
	return;
}

ll Query(int now,int l,int r,int pos)
{
	if (l==r) return S[now];
	PushDown(now);
	int mid=(l+r)>>1;
	if (pos<=mid) return Query(now*2,l,mid,pos);
	else return Query(now*2+1,mid+1,r,pos);
}
