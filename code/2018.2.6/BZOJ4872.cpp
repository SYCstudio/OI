#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int Mod=100003;
const int inf=2147483647;

int n,K;
int Light[maxN];
ll Inv[maxN];
ll g[maxN];

int main()
{
	ll Fac=1;
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&Light[i]),Fac=Fac*i%Mod;
	int tot=0;
	for (int i=n;i>=1;i--)
		if (Light[i])
		{
			for (int j=1;j*j<=i;j++)
			{
				if (i%j==0) Light[j]^=1;
				if ((i%j==0)&&(j*j!=i)) Light[i/j]^=1;
			}
			tot++;
		}
	if (tot<=K)
	{
		printf("%lld\n",tot*Fac%Mod);
		return 0;
	}
	//预处理逆元
	Inv[1]=1;for (int i=2;i<=n;i++) Inv[i]=(ll)(Mod-Mod/i)*Inv[Mod%i]%Mod;
	//求解
	//先处理i<=K的
	for (int i=1;i<=K;i++) g[i]=1;
	g[n]=1;
	for (int i=n-1;i>K;i--) g[i]=(ll)((n-i)*g[i+1]%Mod+n)%Mod*Inv[i]%Mod;
	ll Ans=0;
	for (int i=tot;i>=1;i--) Ans=(Ans+g[i])%Mod;
	printf("%lld\n",Ans*Fac%Mod);
	return 0;
}
