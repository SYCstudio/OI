#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memeset(Arr,x,sizeof(Arr))

const int maxN=15100;
const int inf=2147483647;

char str[maxN];
int L,K;
int Next[maxN];
int Min[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>(str+1);cin>>K;
	L=strlen(str+1);
	int Ans=0;
	for (int i=1;i+K+K<=L;i++)
	{
		int now;
		Next[i]=now=i-1;Min[i]=i;
		for (int j=i+1;j<=L;j++)
		{
			while ((now!=i-1)&&(str[now+1]!=str[j])) now=Next[now];
			if (str[now+1]==str[j]) now++;
			Next[j]=now;
			if (now<i+K-1) Min[j]=j;
			else Min[j]=Min[now];
			if (Min[j]<(i+j)/2) Ans++;
		}
	}
	printf("%d\n",Ans);
	return 0;
}
