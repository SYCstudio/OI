#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxsize=200;
const int inf=2147483647;

int n;
int Height[maxsize];
int F1[maxsize];
int F2[maxsize];

int main()
{
	cin>>n;
	for (int i=1; i<=n; i++)
		cin>>Height[i];
	for (int i=1; i<=n; i++)
		F1[i]=F2[i]=1;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=i; j++)
			if (Height[i]>Height[j])
				F1[i]=max(F1[i],F1[j]+1);
	}
	for (int i=n; i>=1; i--) {
		for (int j=i; j<=n; j++)
			if (Height[i]>Height[j])
				F2[i]=max(F2[i],F2[j]+1);
	}
	int Ans=0;
	for (int i=1; i<=n; i++)
		Ans=max(Ans,F1[i]+F2[i]-1);
	cout<<n-Ans<<endl;
	return 0;
}
