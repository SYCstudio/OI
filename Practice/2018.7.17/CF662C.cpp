#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=21;
const int maxM=101000;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,inv2;
char Input[maxN][maxM];
int A[1<<(maxN+1)],B[1<<(maxN+1)];

int QPow(int x,int cnt);
void FWT(int *P,int N,int opt);

int main()
{
	scanf("%d%d",&n,&m);
	inv2=QPow(2,Mod-2);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1);
	int mx=0;
	for (int i=1;i<=m;i++)
	{
		int key=0;
		for (int j=1;j<=n;j++) if (Input[j][i]=='1') key|=(1<<(j-1));
		A[key]++;mx=max(mx,key);
		//cout<<key<<" ";
	}
	//cout<<endl;
	int N=1<<n;
	for (int i=0;i<N;i++) B[i]=B[i>>1]+(i&1);
	for (int i=0;i<N;i++) B[i]=min(B[i],n-B[i]);

	FWT(A,N,1);FWT(B,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	FWT(A,N,-1);

	int Ans=inf;
	for (int i=0;i<N;i++) Ans=min(Ans,A[i]);

	printf("%d\n",Ans);
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void FWT(int *P,int N,int opt)
{
	for (int i=1;i<N;i<<=1)
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0;k<i;k++)
			{
				int X=P[j+k],Y=P[j+k+i];
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
				if (opt==-1) P[j+k]=1ll*P[j+k]*inv2%Mod,P[j+k+i]=1ll*P[j+k+i]*inv2%Mod;
			}
	return;
}
/*
3 9
010100100
101011011
101011101
//*/
