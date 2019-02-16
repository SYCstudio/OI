#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int Mod=1e9;
const int inf=2147483647;

int n,m,K;
int X[maxN],Y[maxN],O[maxN];
int UFS[maxN],Opt[maxN];

int Calc();
int Find(int x);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	int f0=1,f1=1;
	for (int i=1;i<=K;i++){
		scanf("%d%d%d",&X[i],&Y[i],&O[i]);
		if ((X[i]==1)&&(Y[i]==1)){
			if (O[i]==0) f1=0;
			else f0=0;
			i--;K--;
		}
	}
	int Ans=0;
	if (f0) Ans=Calc();
	if (f1){
		for (int i=1;i<=K;i++)
			if ((X[i]>1)&&(Y[i]>1)) O[i]^=1;
		Ans=(Ans+Calc())%Mod;
	}
	printf("%d\n",Ans);return 0;
}

int Calc(){
	for (int i=1;i<=n+m;i++) UFS[i]=i,Opt[i]=0;
	UFS[n+1]=1;
	for (int i=1;i<=K;i++){
		int b=((X[i]%2==0)&&(Y[i]%2==0));
		int fu=Find(X[i]),fv=Find(Y[i]+n),o=b^Opt[X[i]]^Opt[Y[i]+n]^O[i];
		if (fu!=fv) UFS[fv]=fu,Opt[fv]=o;
		else if (o) return 0;
	}
	int ret=1,cnt=0;
	for (int i=1;i<=n+m;i++)
		if (Find(i)==i){
			if (cnt) ret=(ret<<1)%Mod;
			cnt++;
		}
	return ret;
}

int Find(int x){
	if (UFS[x]==x) return x;
	int fa=UFS[x];UFS[x]=Find(UFS[x]);
	Opt[x]=Opt[x]^Opt[fa];
	return UFS[x];
}
