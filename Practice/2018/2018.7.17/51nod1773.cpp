#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=21;
const int Mod=1e9+7;
const int inf=2147483647;

int n,t,inv2;
int Val[1<<maxN];
int A[1<<maxN];

IL int Input();
IL int QPow(RG int x,RG int cnt);
void FWT(RG int *P,RG int N,RG int opt);
void Print(int x);

int main()
{
	inv2=QPow(2,Mod-2);
	n=Input();t=Input();//scanf("%d%d",&n,&t);
	for (RG int i=0;i<(1<<n);i++) Val[i]=Input();//scanf("%d",&Val[i]);
	A[0]=1;
	for (RG int i=0;i<n;i++) A[1<<i]=1;

	FWT(A,1<<n,1);FWT(Val,1<<n,1);
	for (RG int i=0;i<(1<<n);++i) A[i]=1ll*QPow(A[i],t)*Val[i]%Mod;
	FWT(A,1<<n,-1);

	for (RG int i=0;i<(1<<n);++i) Print(A[i]),putchar(' ');putchar('\n');
	return 0;
}

IL int Input()
{
	RG int x=0;RG char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=(x<<3)+(x<<1)+ch-48,ch=getchar();
	return x;
}

IL int QPow(RG int x,RG int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void FWT(int *P,RG int N,RG int opt)
{
	for (RG int i=1;i<N;i<<=1)
		for (RG int j=0,l=i<<1;j<N;j+=l)
			for (RG int k=j;k<i+j;++k)
			{
				RG int X=P[k],Y=P[k+i];
				P[k]=X+Y;P[k+i]=X-Y;
				if (P[k]>=Mod) P[k]-=Mod;
				if (P[k+i]<0) P[k+i]+=Mod;
				if (opt==-1){
					P[k]=1ll*P[k]*inv2%Mod;
					P[k+i]=1ll*P[k+i]*inv2%Mod;
				}
			}
	return;
}

void Print(int x)
{
	if (x>9) Print(x/10);
	putchar('0'+x%10);
	return;
}
