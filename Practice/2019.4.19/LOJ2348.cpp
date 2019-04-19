#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxN=505000;

int n;
pair<ll,ll> S[maxN];

int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%lld%lld",&S[i].first,&S[i].second);
    sort(&S[1],&S[n+1]);
    ll Ans=0,premx=S[1].first,sum=0;
    for (int i=1;i<=n;i++){
	premx=max(premx,S[i].first-sum);
	sum=sum+S[i].second;
	Ans=max(Ans,premx+sum-S[i].first);
    }
    printf("%lld\n",Ans);return 0;
}
