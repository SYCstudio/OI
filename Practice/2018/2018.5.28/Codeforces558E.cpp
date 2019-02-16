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

const int maxN=101000;
const int maxAlpha=26;
const int inf=2147483647;

class Bucket
{
public:
	int Cnt[maxAlpha];
	void init(){
		mem(Cnt,0);return;
	}
};

class SegmentData
{
public:
	Bucket B;
	int opt;
};

int n,m;
char str[maxN];
SegmentData S[maxN<<2];

Bucket operator + (Bucket A,Bucket B);
void Build(int now,int l,int r);
void PushDown(int now,int l,int r);
Bucket Query(int now,int l,int r,int ql,int qr);
void Modify(int now,int l,int r,int ql,int qr,Bucket T,int opt);

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	Build(1,1,n);
	for (int i=1;i<=m;i++)
	{
		int l,r,k;scanf("%d%d%d",&l,&r,&k);
		if (k==0) k=-1;
		Bucket R=Query(1,1,n,l,r);
		Modify(1,1,n,l,r,R,k);
	}
	for (int i=1;i<=n;i++)
	{
		Bucket R=Query(1,1,n,i,i);
		for (int j=0;j<maxAlpha;j++) if (R.Cnt[j]) printf("%c",(char)(j+'a'));
	}
	printf("\n");
	return 0;
}

Bucket operator + (Bucket A,Bucket B)
{
	Bucket Ret;Ret.init();
	for (int i=0;i<maxAlpha;i++) Ret.Cnt[i]=A.Cnt[i]+B.Cnt[i];
	return Ret;
}

void Build(int now,int l,int r)
{
	if (l==r)
	{
		S[now].B.Cnt[str[l]-'a']++;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now].B=S[lson].B+S[rson].B;
	return;
}

void PushDown(int now,int l,int r)
{
	if (S[now].opt==0) return;
	int mid=(l+r)>>1;
	int lsize=mid-l+1,rsize=r-mid;
	Bucket L,R;L.init();R.init();
	if (S[now].opt==1)
	{
		int pos,sum=0;
		for (pos=0;pos<maxAlpha;pos++)
			if (sum+S[now].B.Cnt[pos]<=lsize) sum+=S[now].B.Cnt[pos],L.Cnt[pos]=S[now].B.Cnt[pos];
			else
			{
				L.Cnt[pos]=lsize-sum;R.Cnt[pos]+=S[now].B.Cnt[pos]-L.Cnt[pos];pos++;
				break;
			}
		for (;pos<maxAlpha;pos++) R.Cnt[pos]=S[now].B.Cnt[pos];
		S[lson].B=L;S[rson].B=R;
		S[lson].opt=S[rson].opt=1;
	}
	else
	{
		int pos,sum=0;
		for (pos=maxAlpha-1;pos>=0;pos--)
			if (sum+S[now].B.Cnt[pos]<=lsize) sum+=S[now].B.Cnt[pos],L.Cnt[pos]=S[now].B.Cnt[pos];
			else
			{
				L.Cnt[pos]=lsize-sum;R.Cnt[pos]+=S[now].B.Cnt[pos]-L.Cnt[pos];pos--;
				break;
			}
		for (;pos>=0;pos--) R.Cnt[pos]=S[now].B.Cnt[pos];
		S[lson].B=L;S[rson].B=R;
		S[lson].opt=S[rson].opt=-1;
	}
	S[now].opt=0;
	return;
}

Bucket Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now].B;
	int mid=(l+r)>>1;
	PushDown(now,l,r);
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}

void Modify(int now,int l,int r,int ql,int qr,Bucket T,int opt)
{
	if ((l==ql)&&(r==qr))
	{
		S[now].opt=opt;S[now].B=T;
		return;
	}
	int mid=(l+r)>>1;
	PushDown(now,l,r);
	if (qr<=mid) Modify(lson,l,mid,ql,qr,T,opt);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,T,opt);
	else
	{
		Bucket L,R;L.init();R.init();
		int lsize=mid-ql+1,rsize=qr-mid;
		if (opt==1)
		{
			int pos,sum=0;
			for (pos=0;pos<maxAlpha;pos++)
				if (sum+T.Cnt[pos]<=lsize) sum+=T.Cnt[pos],L.Cnt[pos]=T.Cnt[pos];
				else
				{
					L.Cnt[pos]=lsize-sum;R.Cnt[pos]=T.Cnt[pos]-L.Cnt[pos];pos++;
					break;
				}
			for (;pos<maxAlpha;pos++) R.Cnt[pos]=T.Cnt[pos];
		}
		else
		{
			int pos,sum=0;
			for (pos=maxAlpha-1;pos>=0;pos--)
				if (sum+T.Cnt[pos]<=lsize) sum+=T.Cnt[pos],L.Cnt[pos]=T.Cnt[pos];
				else
				{
					L.Cnt[pos]=lsize-sum;R.Cnt[pos]=T.Cnt[pos]-L.Cnt[pos];pos--;
					break;
				}
			for (;pos>=0;pos--) R.Cnt[pos]=T.Cnt[pos];
		}
		Modify(lson,l,mid,ql,mid,L,opt);
		Modify(rson,mid+1,r,mid+1,qr,R,opt);
	}
	S[now].B=S[lson].B+S[rson].B;
	return;
}
