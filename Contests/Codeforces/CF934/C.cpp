#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int inf=2147483647;

class Segment
{
public:
	int mx;
	int lazy;
};

int n;
int Dr[maxN];
int OnePre[maxN],TwoPre[maxN],OneSuf[maxN],TwoSuf[maxN];
Segment S[maxN*8];

void PushDown(int now,int l,int r);
void Update(int now,int l,int r);
void Modefy(int now,int l,int r,int ql,int qr,int opt);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Dr[i]);
	Dr[0]=1;Dr[n+1]=2;
	for (int i=1;i<=n;i++) OnePre[i]=OnePre[i-1]+(Dr[i]==1),TwoPre[i]=TwoPre[i-1]+(Dr[i]==2);
	for (int i=n;i>=1;i--) OneSuf[i]=OneSuf[i+1]+(Dr[i]==1),TwoSuf[i]=TwoSuf[i+1]+(Dr[i]==2);
	int Ans=0;
	for (int l=1;l<=n;l++)
	{
		mem(S,0);
		for (int r=l;r<=n;r++)
		{
			if (Dr[r]==2) Modefy(1,1,n+1,r+1,n+1,1);
			if (Dr[r]==1) Modefy(1,1,n+1,1,r+1,1);
			Ans=max(Ans,OnePre[l-1]+S[1].mx+TwoSuf[r+1]);
			//cout<<"["<<l<<','<<r<<"] "<<OnePre[l-1]+S[1].mx+TwoSuf[r+1]<<" "<<OnePre[l-1]<<" "<<S[1].mx<<" "<<TwoSuf[r+1]<<endl;
		}
	}
	printf("%d\n",Ans);
	return 0;
}

void Modefy(int now,int l,int r,int ql,int qr,int opt)
{
	PushDown(now,l,r);
	if ((l==ql)&&(r==qr))
	{
		S[now].mx+=opt;
		S[now].lazy=opt;
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modefy(now*2,l,mid,ql,qr,opt);
	else if (ql>=mid+1) Modefy(now*2+1,mid+1,r,ql,qr,opt);
	else
	{
		Modefy(now*2,l,mid,ql,mid,opt);
		Modefy(now*2+1,mid+1,r,mid+1,qr,opt);
	}
	Update(now,l,r);return;
}

void PushDown(int now,int l,int r)
{
	int lz=S[now].lazy;S[now].lazy=0;
	if (l==r) return;
	S[now*2].mx+=lz;S[now*2+1].mx+=lz;
	S[now*2].lazy+=lz;S[now*2+1].lazy+=lz;
	return;
}

void Update(int now,int l,int r)
{
	if (l==r) return;
	S[now].mx=max(S[now*2].mx,S[now*2+1].mx);
	return;
}
