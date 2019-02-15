#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010000;
const int inf=2147483647;

int n,P;
bool notprime[maxN];
int pricnt,Prime[maxN],Pw[maxN],Id[maxN];
int Cnt[maxN];

void Init();
void Add(int key,int c);
int QPow(int x,int cnt);

int main()
{
	Init();
	scanf("%d%d",&n,&P);
	for (int i=2;i<=n;i++) Add(i,-1);
	for (int i=n+2;i<=2*n;i++) Add(i,1);

	//for (int i=1;i<=2*n;i++) cout<<Prime[i]<<" "<<Cnt[i]<<endl;
	
	int Ans=1;
	for (int i=1;i<=pricnt;i++)
		Ans=1ll*Ans*QPow(Prime[i],Cnt[i])%P;

	printf("%d\n",Ans);
	return 0;
}

void Init()
{
	notprime[1]=1;Pw[1]=1;
	for (int i=2;i<maxN;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Pw[i]=i,Id[i]=pricnt;
		for (int j=1;(j<=pricnt)&&(1ll*i*Prime[j]<maxN);j++)
		{
			notprime[i*Prime[j]]=Prime[j];
			Pw[i*Prime[j]]=Prime[j];
			if (i%Prime[j]==0) break;
		}
	}
	return;
}

void Add(int key,int c)
{
	while (key!=1){
		Cnt[Id[Pw[key]]]+=c;key/=Pw[key];
	}
	return;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%P;
		x=1ll*x*x%P;cnt>>=1;
	}
	return ret;
}
