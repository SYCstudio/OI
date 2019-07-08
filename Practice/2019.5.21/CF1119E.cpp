#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	long long Ans=0;
	int cnt=0;
	for (int i=1; i<=n; i++) {
		int a;
		scanf("%d",&a);
		if (a/2>=cnt) {
			Ans=Ans+cnt;
			a=a-cnt*2;
			Ans=Ans+a/3;
			cnt=a%3;
		} else {
			Ans=Ans+a/2;
			cnt-=a/2;
			cnt+=(a&1);
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
