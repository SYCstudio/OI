#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxAlpha=26;
const int inf=2147483647;

int n;
int Next[maxN];
bool Alpha[maxAlpha][maxN];
char str[maxN];

int main()
{
	//ios::sync_with_stdio(false);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int len;//cin>>len;
		scanf("%d",&len);
		Next[i]=i-len;
	}
	Next[0]=-1;
	for (int i=1;i<=n;i++)
	{
		int j=Next[i-1];
		while ((j!=-1)&&(Next[i]!=j+1))
		{
			Alpha[str[j+1]-'a'][i]=1;
			j=Next[j];
		}
		if (j!=-1) str[i]=str[j+1];
		else
			for (int pos=0;pos<maxAlpha;pos++)
				if (Alpha[pos][i]==0)
				{
					str[i]=pos+'a';
					break;
				}
	}
	for (int i=1;i<=n;i++) printf("%c",str[i]);
	return 0;
}
