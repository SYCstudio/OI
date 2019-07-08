#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=604000;

int n;
ll Len;
ll A[maxN],B[maxN];
ll L[maxN],R[maxN];
deque<int> Dq;

int main()
{
	scanf("%d%lld",&n,&Len);
	for (int i=1; i<=n; i++) scanf("%lld",&A[i]);
	for (int i=1; i<=n; i++) scanf("%lld",&B[i]);
	sort(&A[1],&A[n+1]);
	sort(&B[1],&B[n+1]);
	for (int i=1; i<=n; i++) A[i+n]=A[i]+Len,A[i+n+n]=A[i+n]+Len,B[i]+=Len;

	ll l=0,r=Len,Ans=0;
	while (l<=r) {
		ll mid=(l+r)>>1;
		for (int i=1; i<=n+n+n; i++) {
			if (A[i]-mid<=B[1]) L[i]=1;
			else L[i]=lower_bound(&B[1],&B[n+1],A[i]-mid)-B;

			if (A[i]+mid>=B[n]) R[i]=n;
			else R[i]=upper_bound(&B[1],&B[n+1],A[i]+mid)-B-1;
		}
		//cout<<"check:"<<mid<<endl;

		while (!Dq.empty()) Dq.pop_front();

		bool flag=0;

		for (int p1=1,p2=1; p1<=n+n+n; p1++) {
			if (L[p1]>R[p1]) {
				if (!Dq.empty()&&Dq.front()==p1) Dq.pop_front();
				continue;
			}
			p2=max(p2,p1-1);
			while (p2+1<=n+n+n&&R[p2+1]>=L[p2+1]&&
			        (Dq.empty()||R[p2+1]-(p2+1)>=L[Dq.front()]-Dq.front())) {
				++p2;
				while (!Dq.empty()&&L[Dq.back()]-Dq.back()<=L[p2]-p2) Dq.pop_back();
				Dq.push_back(p2);
			}
			//cout<<p1<<" "<<p2<<endl;
			if (p2-p1+1>=n) flag=1;
			if (!Dq.empty()&&Dq.front()==p1) Dq.pop_front();
		}
		if (flag) Ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",Ans);
	return 0;
}
