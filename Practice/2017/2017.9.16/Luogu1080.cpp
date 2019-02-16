#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2000;
const int maxNum=5000;
const int inf=2147483647;

#define ll long long

class People
{
public:
	ll l,r;
};

bool operator < (People A,People B)
{
	return A.l*A.r<B.l*B.r;
}

class BigInteger
{
public:
	int siz;
	ll Num[maxNum];
	BigInteger();
	BigInteger(int x);
	BigInteger(ll x);
	void operator = (int B);
	bool operator == (int B);
	bool operator == (BigInteger B);
	BigInteger operator + (BigInteger B);
	BigInteger operator * (ll B);
	BigInteger operator / (ll B);
};

ostream& operator << (ostream & os,BigInteger A)
{
	if (A.siz==0)
	{
		os<<0;
		return os;
	}
	for (int i=A.siz;i>=1;i--)
		os<<A.Num[i];
	return os;
}


bool operator < (BigInteger A,BigInteger B)
{
	if (A.siz<B.siz)
		return 1;
	if (A.siz>B.siz)
		return 0;
	for (int ii=A.siz;ii>=1;ii--)
	{
		if (A.Num[ii]>B.Num[ii])
			return 0;
		if (A.Num[ii]<B.Num[ii])
			return 1;
	}
}

ll n;
People P[maxN];

ll read();

int main()
{
	n=read();
	P[0].l=read();
	P[0].r=read();
	for (int i=1;i<=n;i++)
	{
		P[i].l=read();
		P[i].r=read();
	}
	sort(&P[1],&P[n+1]);
	BigInteger ret=P[0].l;
	BigInteger Ans=0;
	for (int i=1;i<=n;i++)
	{
		Ans=max(Ans,ret/P[i].r);
		ret=ret*P[i].l;
	}
	cout<<Ans<<endl;
	return 0;
}

ll read()
{
	ll x=0;
	char ch=getchar();
	while ((ch<'0')||(ch>'9'))
		ch=getchar();
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x;
}

BigInteger::BigInteger()
{
	siz=0;
	mem(Num,0);
}

BigInteger::BigInteger(int B)
{
	siz=0;
	mem(Num,0);
	while (B!=0)
	{
		siz++;
		Num[siz]=B%10;
		B=B/10;
	}
}

BigInteger::BigInteger(ll B)
{
	siz=0;
	mem(Num,0);
	while (B!=0)
	{
		siz++;
		Num[siz]=B%10;
		B=B/10;
	}
}

void BigInteger::operator = (int B)
{
	siz=0;
	mem(Num,0);
	while (B!=0)
	{
		siz++;
		Num[siz]=B%10;
		B=B/10;
	}
}

bool BigInteger::operator == (BigInteger B)
{
	if (siz!=B.siz)
		return 0;
	for (int ii=1;ii<=siz;ii++)
		if (Num[ii]!=B.Num[ii])
			return 0;
	return 1;
}

bool BigInteger::operator == (int B)
{
	BigInteger A(B);
	if (A==B)
		return 1;
	return 0;
}

BigInteger BigInteger::operator + (BigInteger B)
{
	BigInteger Ans;
	Ans.siz=max(siz,B.siz);
	for (int ii=1;ii<=Ans.siz;ii++)
		Ans.Num[ii]=Num[ii]+B.Num[ii];
	for (int ii=1;ii<Ans.siz;ii++)
	{
		Ans.Num[ii+1]+=Ans.Num[ii]/10;
		Ans.Num[ii]%=10;
	}
	while (Ans.Num[Ans.siz]>=10)
	{
		Ans.Num[Ans.siz+1]+=Ans.Num[Ans.siz]/10;
		Ans.Num[Ans.siz]%=10;
		Ans.siz++;
	}
	return Ans;
}

BigInteger BigInteger::operator * (ll B)
{
	BigInteger Ans;
	for (int ii=1;ii<=siz;ii++)
		Ans.Num[ii]=1ll*Num[ii]*(ll)(B);
	Ans.siz=siz;
	for (int ii=1;ii<Ans.siz;ii++)
	{
		Ans.Num[ii+1]+=Ans.Num[ii]/10;
		Ans.Num[ii]%=10;
	}
	while (Ans.Num[Ans.siz]>=10)
	{
		Ans.Num[Ans.siz+1]+=Ans.Num[Ans.siz]/10;
		Ans.Num[Ans.siz]%=10;
		Ans.siz++;
	}
	return Ans;
}

BigInteger BigInteger::operator / (ll B)
{
	BigInteger Ans;
	int res=0;
	for (int ii=siz;ii>=1;ii--)
	{
		res=res*10+Num[ii];
		Ans.Num[ii]=res/B;
		res=res%B;
	}
	Ans.siz=siz;
	while (Ans.Num[Ans.siz]==0)
		Ans.siz--;
	return Ans;
}
