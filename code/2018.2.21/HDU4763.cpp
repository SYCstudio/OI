#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int inf=2147483647;

int n;
char str[maxN];
int Next[maxN];
bool GoLast[maxN];

int main()
{
	ios::sync_with_stdio(false);
	int T;cin>>T;
	while (T--)
	{
		mem(GoLast,0);
		cin>>(str+1);n=strlen(str+1);
		Next[0]=-1;Next[1]=0;
		for (int i=2;i<=n;i++)
		{
			int j=Next[i-1];
			while ((j!=0)&&(str[j+1]!=str[i])) j=Next[j];
			if (str[j+1]==str[i]) Next[i]=j+1;
			else Next[i]=0;
		}
		int Ans=0;
		for (int i=n;i!=0;i=Next[i]) if (i+i<=n) GoLast[i]=1;
		for (int i=n-1;i>=1;i--)
		{
			int now=i;
			while (now)
			{
				if ((GoLast[now])&&(now+now<=i)&&(now+i<=n)){
					Ans=max(Ans,now);break;
				}
				now=Next[now];
			}
		}
		printf("%d\n",Ans);
	}
	return 0;
}
