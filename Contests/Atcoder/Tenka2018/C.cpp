#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int maxN=101000;
const int inf=2147483647;

int n;
ll A[maxN],B[maxN+maxN];

int main(){
	cin>>n;
	for (int i=1;i<=n;i++) cin>>A[i];
	sort(&A[1],&A[n+1]);
	ll sum=0,Ans=0;
	int l=1,r=n;
	for (int i=2;i<n;i++)
		if (i&1) B[i]=A[l++];
		else B[i]=A[r--];
	B[1]=A[l++];B[n]=A[l++];
	
	for (int i=1;i<n;i++) sum=sum+abs(B[i+1]-B[i]);
	//for (int i=1;i<=n;i++) cout<<B[i]<<" ";cout<<endl;

	Ans=sum;sum=0;
	l=1;r=n;
	for (int i=2;i<n;i++)
		if (i&1) B[i]=A[r--];
		else B[i]=A[l++];
	B[1]=A[l++];B[n]=A[l++];
	for (int i=1;i<n;i++) sum=sum+abs(B[i+1]-B[i]);
	Ans=max(Ans,sum);
	cout<<Ans<<endl;return 0;
}
