#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=6000;
const int inf=2147483647;

int n;
int Arr[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);
	for (int i=1;i<=n;i++)
		if (Arr[Arr[Arr[i]]]==i){
			printf("YES");return 0;
		}
	printf("NO");
	return 0;
}
