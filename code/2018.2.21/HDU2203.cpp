#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100*2;
const int inf=2147483647;

int n1,n2;
char str1[maxN],str2[maxN];
int Next[maxN];

int main()
{
	ios::sync_with_stdio(false);
	while (cin>>(str1+1))
	{
		cin>>(str2+1);
		n1=strlen(str1+1);n2=strlen(str2+1);
		for (int i=1;i<=n1;i++) str1[i+n1]=str1[i];
		str1[n1+n1+1]='\0';n1=strlen(str1+1);
		Next[0]=-1;Next[1]=0;
		for (int i=2;i<=n2;i++)
		{
			int j=Next[i-1];
			while ((j!=0)&&(str2[j+1]!=str2[i])) j=Next[j];
			if (str2[j+1]==str2[i]) Next[i]=j+1;
			else Next[i]=0;
		}
		bool flag=0;
		for (int i=1,j=0;i<=n1;i++)
		{
			while ((j!=0)&&(str2[j+1]!=str1[i])) j=Next[j];
			if (str2[j+1]==str1[i]) j++;
			if (j==n2){
				flag=1;break;
			}
		}
		if (flag) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
