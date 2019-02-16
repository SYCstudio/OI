#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=1<<19;
const int inf=2147483647;

int n,m;
int A[maxN],B[maxN];

void FWT(int *P,int N,int opt);

int main()
{
	int TTT;scanf("%d",&TTT);
	for (int ti=1;ti<=TTT;ti++)
	{
		mem(A,0);mem(B,0);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			ll k;scanf("%lld",&k);
			int key=0;
			for (int j=0;j<m;j++,k/=10)
				if (k%10==1) key|=(1<<j);
			A[key]++;
		}
		for (int i=1;i<=n;i++)
		{
			ll k;scanf("%lld",&k);
			int key=0;
			for (int j=0;j<m;j++,k/=10)
				if (k%10==1) key|=(1<<j);
			B[key]++;
		}

		FWT(A,1<<m,1);FWT(B,1<<m,1);
		for (int i=0;i<(1<<m);i++) A[i]=A[i]*B[i];
		FWT(A,1<<m,-1);

		int Q;scanf("%d",&Q);
		printf("Case #%d:\n",ti);
		while (Q--)
		{
			ll k;scanf("%lld",&k);
			int key=0;
			for (int j=0;j<m;j++,k/=10)
				if (k%10==1) key|=(1<<j);
			printf("%d\n",A[key]);
		}
	}
	return 0;
}

void FWT(int *P,int N,int opt)
{
	for (int i=1;i<N;i<<=1)
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0;k<i;k++)
				P[j+k+i]+=opt*P[j+k];
	return;
}
