#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int inf=2147483647;

int n,m;
char Input[maxN];
ll Arr[maxN];

int main()
{
	ios::sync_with_stdio(false);
	
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		cin>>(Input+1);
		for (int j=1;j<=m;j++)
			if (Input[j]=='.') Arr[i]=Arr[i]<<1ll;
			else Arr[i]=(Arr[i]<<1ll)|1ll;
	}
	bool flag=1;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			if (((Arr[i]&Arr[j])!=0)&&(Arr[i]!=Arr[j])){
				flag=0;break;
			}
	if (flag) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
