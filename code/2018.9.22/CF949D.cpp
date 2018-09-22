#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
ll d,B;
ll A[maxN],Sum[maxN];

int main(){
	scanf("%d%lld%lld",&n,&d,&B);
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]),Sum[i]=Sum[i-1]+A[i];

	int cnt1=0,cnt2=0;
	for(int i=1;i<=n/2;i++){
		if (Sum[min((ll)n,i+i*d)]-B*cnt1>=B) cnt1++;
		if (Sum[n]-Sum[max(0ll,n-i-i*d)]-B*cnt2>=B) cnt2++;
	}
	
	printf("%d\n",max(n/2-cnt1,n/2-cnt2));return 0;
}
