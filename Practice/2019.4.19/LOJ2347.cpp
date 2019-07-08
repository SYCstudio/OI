#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=101000;

int n,K,T[maxN];
priority_queue<int> H;

int main()
{
	scanf("%d%d",&n,&K);
	--K;
	for (int i=1; i<=n; i++) scanf("%d",&T[i]);
	int Ans=T[n]-T[1]+1;
	for (int i=1; i<n; i++) H.push(T[i+1]-T[i]-1);
	while (K--) Ans-=H.top(),H.pop();
	printf("%d\n",Ans);
	return 0;
}
