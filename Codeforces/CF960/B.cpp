#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (((ll)x)*((ll)x))

const int maxN=1010;
const int inf=2147483647;

class Queue_Data
{
public:
	ll u;ll key;
};

int n,K;
ll A[maxN],B[maxN],D[maxN];
ll Ans=0;
priority_queue<Queue_Data> H;

bool operator < (Queue_Data A,Queue_Data B);

int main()
{
	ios::sync_with_stdio(false);
	int k1,k2;
	cin>>n>>k1>>k2;K=k1+k2;
	for (int i=1;i<=n;i++) cin>>A[i];
	for (int i=1;i<=n;i++) cin>>B[i];
	for (int i=1;i<=n;i++) Ans+=sqr(A[i]-B[i]),D[i]=abs(A[i]-B[i]);
	for (int i=1;i<=n;i++) H.push((Queue_Data){i,sqr(D[i]-1ll)-sqr(D[i])});
	while (K--)
	{
		Queue_Data u=H.top();H.pop();
		Ans+=u.key;
		if (D[u.u]>0) D[u.u]--;
		else D[u.u]++;
		H.push((Queue_Data){u.u,sqr(D[u.u]-1ll)-sqr(D[u.u])});
	}
	cout<<Ans<<endl;
	return 0;
}

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.key>B.key;
}
