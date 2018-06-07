#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

int n;

int main()
{
	int last=0,now;
	int Ans=0;
    cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>now;
		if (now-last>0)
			Ans=Ans+now-last;
		last=now;
	}
	cout<<Ans<<endl;
	return 0;
}
