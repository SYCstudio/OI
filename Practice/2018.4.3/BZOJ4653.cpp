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

const int maxN=501000*2;
const int inf=2147483647;

class Range
{
public:
	int l,r,len;
};

class SegmentData
{
public:
	int mx,lazy;
};

int n,m;
Range R[maxN];
int numcnt,Num[maxN*2];
SegmentData S[maxN*4];

bool operator < (Range A,Range B);
void PushDown(int now);
void Modify(int now,int l,int r,int ql,int qr,int key);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		cin>>R[i].l>>R[i].r;R[i].len=R[i].r-R[i].l;
		Num[++numcnt]=R[i].l;Num[++numcnt]=R[i].r;
	}
	sort(&Num[1],&Num[numcnt+1]);
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" ";cout<<endl;
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	//cout<<numcnt<<endl;
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++)
	{
		//cout<<R[i].l<<" "<<R[i].r<<endl;
		R[i].l=lower_bound(&Num[1],&Num[numcnt+1],R[i].l)-Num;
		R[i].r=lower_bound(&Num[1],&Num[numcnt+1],R[i].r)-Num;
		//cout<<R[i].l<<" "<<R[i].r<<endl;
	}
	sort(&R[1],&R[n+1]);
	int Ans=inf;
	for (int i=1,j=0;i<=n;i++)
	{
		while ((j<n)&&(S[1].mx<m))
		{
			j++;
			Modify(1,1,numcnt,R[j].l,R[j].r,1);
		}
		if (S[1].mx==m) Ans=min(Ans,R[j].len-R[i].len);
		else break;
		Modify(1,1,numcnt,R[i].l,R[i].r,-1);
	}
	if (Ans==inf) cout<<-1<<endl;
	else cout<<Ans<<endl;
	return 0;
}

bool operator < (Range A,Range B)
{
	return A.len<B.len;
}

void PushDown(int now)
{
	if (S[now].lazy)
	{
		int lz=S[now].lazy;
		S[lson].mx+=lz;S[lson].lazy+=lz;
		S[rson].mx+=lz;S[rson].lazy+=lz;
		S[now].lazy=0;
	}
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
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
