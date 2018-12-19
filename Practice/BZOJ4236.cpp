#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int inf=2147483647;

int n;
char Input[maxN];
map<ll,int> Mp;

ll calc(int a,int b,int c);

int main(){
	scanf("%d",&n);scanf("%s",Input+1);
	int Ans=0,cj=0,co=0,ci=0;Mp[calc(0,0,0)]=0;
	for (int i=1;i<=n;i++){
		if (Input[i]=='J') ++cj;
		if (Input[i]=='O') ++co;
		if (Input[i]=='I') ++ci;
		ll d=calc(cj,co,ci);
		if (Mp.count(d)==0) Mp[d]=i;
		else Ans=max(Ans,i-Mp[d]);
	}
	printf("%d\n",Ans);return 0;
}

ll calc(int a,int b,int c){
	int d1=a-b+n,d2=a-c+n,d3=b-c+n;
	return 1ll*(n+n)*(n+n)*d1+1ll*(n+n)*d2+1ll*d3;
}
