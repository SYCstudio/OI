#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=10100;
const int inf=2147483647;

int n,m;
int Tim[maxN],X[maxN],Y[maxN];
int F[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	RG int Ans=0;
	for (RG int i=1;i<=m;++i)
	{
		F[i]=1;cin>>Tim[i]>>X[i]>>Y[i];
		for (RG int j=1;j<i;++j)
			if (abs(X[i]-X[j])+abs(Y[i]-Y[j])<=Tim[i]-Tim[j]) F[i]=max(F[i],F[j]+1);
		Ans=max(Ans,F[i]);
	}
	cout<<Ans<<endl;
	return 0;
}
