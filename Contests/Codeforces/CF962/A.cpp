#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210010;
const int inf=2147483647;

int n;
ll Arr[maxN];
ll sum=0;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>Arr[i];
		sum+=Arr[i];
	}
	ll nowsum=0;
	for (int i=1;i<=n;i++)
	{
		nowsum+=Arr[i];
		if (nowsum*2>=sum)
		{
			cout<<i<<endl;
			break;
		}
	}
	return 0;
}
