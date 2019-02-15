#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20;
const int inf=100000000;

ll num;
ll cnt;

int main(){
	scanf("%lld",&num);
	ll key=0,Ans=0;
	while (key*10ll+9<=num) Ans+=9,key=key*10ll+9;
	num-=key;
	while (num) Ans+=num%10,num/=10;
	printf("%lld\n",Ans);return 0;
}
