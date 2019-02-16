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

class Data
{
public:
	int key,pos;
};

int n;
Data D[maxN];
ll Cnt[maxN];

bool cmp(Data A,Data B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].key),D[i].pos=i;
	sort(&D[1],&D[n+1],cmp);
	for (int i=1,mx=0;i<=n;i++){
		mx=max(mx,D[i].pos);
		Cnt[i]=mx-i;
	}
	ll Ans=0;
	for (int i=1;i<=n;i++) Ans=Ans+max(max(Cnt[i-1],Cnt[i]),1ll);
	printf("%lld\n",Ans);return 0;
}

bool cmp(Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	return A.pos<B.pos;
}
