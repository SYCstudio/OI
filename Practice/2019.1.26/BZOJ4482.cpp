#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long

const int maxN=202000;

class Data
{
public:
	int val,in;
};

int n;
Data D[maxN];
multiset<int> Ms;

bool cmp(Data A,Data B);

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		int out;
		scanf("%d",&out);
		Ms.insert(out);
		scanf("%d%d",&D[i].in,&D[i].val);
	}
	sort(&D[1],&D[n+1],cmp);
	ll Ans=0;
	for (int i=1; i<=n; i++) {
		Ans=Ans+1ll*D[i].in*D[i].val;
		multiset<int>::iterator it=Ms.lower_bound(D[i].in);
		if (it==Ms.begin()) continue;
		--it;
		Ans=Ans-1ll*D[i].val*(*it);
		Ms.erase(it);
	}
	printf("%lld\n",Ans);
	return 0;
}
bool cmp(Data A,Data B)
{
	return A.val>B.val;
}
