#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const ull base=2333;
const int inf=2147483647;

int n;
char A[maxN],B[maxN],C[maxN];
int P1[maxN],P2[maxN];
ull Bs[maxN],H1[maxN],H2[maxN];

int Manacher(char *S,int *P);
ull Get1(int l,int r);
ull Get2(int l,int r);
int Solve(int l,int r);

int main()
{
	Bs[0]=1;for (int i=1;i<maxN;i++) Bs[i]=Bs[i-1]*base;
	scanf("%d",&n);
	scanf("%s",A+1);
	scanf("%s",B+1);

	//cout<<(A+1)<<" "<<(B+1)<<endl;

	int Ans=0;
	Ans=max(Ans,Manacher(A,P1));
	Ans=max(Ans,Manacher(B,P2));
	for (int i=1;i<=n;i++) H1[i]=H1[i-1]*base+A[i]-'A'+1;
	for (int i=n;i>=1;i--) H2[i]=H2[i+1]*base+B[i]-'A'+1;

	for (int i=1;i<=n*2;i++) P1[i]--,P2[i]--;

	//cout<<Ans<<endl;
	
	for (int i=2;i<=n+n;i++)
	{
		int p1=i-P1[i]+1,p2=i+P1[i];
		p1/=2;p2/=2;
		Ans=max(Ans,P1[i]+Solve(p1-1,p2)*2);
	}

	for (int i=2;i<=n+n;i++)
	{
		int p1=i-P2[i]+1,p2=i+P2[i];
		p1/=2;p2/=2;
		Ans=max(Ans,P2[i]+Solve(p1,p2+1)*2);
	}

	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=i;j++) cout<<A[j];
		for (int j=i;j<=n;j++) cout<<B[j];
		cout<<endl;
	}
	//*/

	printf("%d\n",Ans);
	return 0;
}

int Manacher(char *S,int *P)
{
	mem(P,0);
	for (int i=n;i>=1;i--) C[2*i]=S[i],C[2*i-1]='#';
	C[0]='@';C[2*n+1]='#';
	
	int mx=0,pos=0;
	for (int i=1;i<=n+n;i++)
	{
		if (i<mx) P[i]=min(P[pos*2-i],mx-i);
		else P[i]=1;
		while (C[i+P[i]]==C[i-P[i]]) P[i]++;
		if (i+P[i]>mx){
			mx=i+P[i];pos=i;
		}
	}

	//for (int i=1;i<=n+n;i++) cout<<C[i]<<" ";cout<<endl;
	//for (int i=1;i<=n+n;i++) cout<<P[i]<<" ";cout<<endl;

	int ret=0;
	for (int i=1;i<=n+n;i++) ret=max(ret,P[i]-1);
	return ret;
}

ull Get1(int l,int r){
	return H1[r]-H1[l-1]*Bs[r-l+1];
}

ull Get2(int l,int r){
	return H2[l]-H2[r+1]*Bs[r-l+1];
}

int Solve(int l,int r)
{
	int L=0,R=min(l,n-r+1);
	int ret=0;
	do{
		int mid=(L+R)>>1;
		if (Get1(l-mid+1,l)==Get2(r,r+mid-1)) ret=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);
	return ret;
}
