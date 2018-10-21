#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

int n;
char str1[maxN],str2[maxN];
int UFS[maxN];
int cnt;
char Ans1[maxN],Ans2[maxN];

int Find(int x);

int main()
{
	for (int i=1;i<=100;i++) UFS[i]=i;
	scanf("%d",&n);scanf("%s",str1+1);scanf("%s",str2+1);
	for (int i=1;i<=n;i++)
	{
		if (str1[i]==str2[i]) continue;
		if (Find(str1[i]-'a'+1)!=Find(str2[i]-'a'+1)){
			++cnt;Ans1[cnt]=str1[i];Ans2[cnt]=str2[i];
			UFS[Find(str1[i]-'a'+1)]=Find(str2[i]-'a'+1);
		}
	}
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++) printf("%c %c\n",Ans1[i],Ans2[i]);
	return 0;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
