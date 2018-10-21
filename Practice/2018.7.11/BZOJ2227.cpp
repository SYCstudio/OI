#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210*210;
const int inf=2147483647;

int n,K;
int pricnt=0,Prime[80];
int Cnt[80];
int A[maxN],B[maxN];

void Fac(int key,int opt);
int Times(int *P,int cnt,int key,int len);

int main()
{
	int TTT;scanf("%d",&TTT);

	for (int i=2;i<=200;i++)
	{
		bool flag=1;
		for (int j=2;j<=sqrt(i);j++)
			if (i%j==0){
				flag=0;break;
			}
		if (flag) Prime[++pricnt]=i;
	}
	
	while (TTT--)
	{
		mem(Cnt,0);mem(A,0);mem(B,0);
		
		scanf("%d%d",&n,&K);
		if (n>K){
			printf("0 1\n");continue;
		}
		
		Fac(K+1,n-1);
		Fac(K-n+1,1);
		Fac(K,-n);

		mem(A,0);mem(B,0);
		A[0]=1;B[0]=1;
		int l1=0,l2=0;

		for (int i=1;i<=pricnt;i++)
			if (Cnt[i]>0) l1=Times(A,Cnt[i],Prime[i],l1);
			else l2=Times(B,-Cnt[i],Prime[i],l2);

		for (int i=l1;i>=0;i--) printf("%d",A[i]);printf(" ");
		for (int i=l2;i>=0;i--) printf("%d",B[i]);printf("\n");
	}
	return 0;
}

void Fac(int key,int opt)
{
	for (int i=1;i<=pricnt;i++)
		if (key%Prime[i]==0){
			int cnt=0;
			while (key%Prime[i]==0) key/=Prime[i],cnt++;
			Cnt[i]+=opt*cnt;
		}
	return;
}

int Times(int *P,int cnt,int key,int len)
{
	while (cnt--)
	{
		for (int i=0;i<=len;i++) P[i]=P[i]*key;
		for (int i=0;i<len;i++) P[i+1]+=P[i]/10,P[i]%=10;
		while (P[len]>=10) P[len+1]+=P[len]/10,P[len]%=10,len++;
	}
	return len;
}
