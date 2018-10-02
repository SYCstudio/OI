#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Max(a,b,c) max(a,max(b,c))

const int maxN=101000;
const int inf=2147483647;

int n;
int Seq[maxN],Sufmx[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	Sufmx[n-1]=Seq[n-1];
	for (int i=n-2;i>=2;i--) Sufmx[i]=max(Sufmx[i+1],Seq[i]);
	ll Ans=inf;
	for (int i=3,mx=Seq[2];i<=n-2;i++){
		Ans=min(Ans,(ll)Max(0,Seq[1]-mx+1,Seq[i]-mx+1)+(ll)Max(0,Seq[n]-Sufmx[i+1]+1,Seq[i]-Sufmx[i+1]+1));
	}
	printf("%lld\n",Ans);return 0;
}
