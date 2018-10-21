#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

int n;
char S1[maxN],S2[maxN];

int main(){
	scanf("%d",&n);
	scanf("%s",S1+1);scanf("%s",S2+1);
	ll c1=0,c2=0,c3=0,c4=0;
	for (int i=1;i<=n;i++)
		if ((S1[i]=='0')&&(S2[i]=='0')) c1++;
		else if ((S1[i]=='0')&&(S2[i]=='1')) c2++;
		else if ((S1[i]=='1')&&(S2[i]=='0')) c3++;
		else c4++;

	printf("%lld\n",c1*c3+c1*c4+c2*c3);

	return 0;
}
