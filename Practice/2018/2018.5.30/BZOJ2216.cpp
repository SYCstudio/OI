#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int inf=2147483647;

int n;
int H[maxN];
int P1[maxN],P2[maxN];
int Q[maxN];

void Do(int *P);
int Beyond(int i,int j);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&H[i]);
	Do(P1);
	reverse(&H[1],&H[n+1]);
	Do(P2);
	reverse(&P2[1],&P2[n+1]);
	for (int i=1;i<=n;i++) printf("%d\n",max(P1[i],P2[i]));
	//for (int i=1;i<=n;i++) cout<<P1[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<P2[i]<<" ";cout<<endl;
	return 0;
}

void Do(int *P)
{
	int L=1,R=0;
	//for (int i=1;i<=n;i++) cout<<H[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++)
	{
		while ((L<R)&&(Beyond(Q[R-1],Q[R])>Beyond(Q[R],i))) R--;
		Q[++R]=i;
		while ((L<R)&&(Beyond(Q[L],Q[L+1])<=i)) L++;
		int sq=sqrt(i-Q[L]);
		if (sq*sq<i-Q[L]) sq=sq+1;
		//cout<<Q[L]<<"->"<<i<<endl;
		P[i]=H[Q[L]]+sq-H[i];
	}
	return;
}

int Beyond(int i,int j)
{
	//cout<<"Beyond:"<<i<<" "<<j<<":";
	int l=max(i,j),r=n;
	int Ret=n+1;
	do
	{
		int mid=(l+r)>>1;
		if (1.0*H[i]+1.0*sqrt(mid-i)<1.0*H[j]+1.0*sqrt(mid-j)) Ret=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	//cout<<Ret<<endl;
	return Ret;
}

