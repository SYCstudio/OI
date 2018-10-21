#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200;
const int inf=2147483647;

int n;
char str[maxN];

int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);
	for (int i=1;i<=n;i++)
		if ((str[i]=='a')||(str[i]=='e')||(str[i]=='i')||(str[i]=='o')||(str[i]=='u')||(str[i]=='y'))
		{
			if ((str[i-1]=='a')||(str[i-1]=='e')||(str[i-1]=='i')||(str[i-1]=='o')||(str[i-1]=='u')||(str[i-1]=='y'));
			else printf("%c",str[i]);
		}
		else printf("%c",str[i]);
	return 0;
}
