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
char str[maxN];
int Next[maxN];
bool Pre[maxN];

int main()
{
	ios::sync_with_stdio(false);
	int T;cin>>T;
	while (T--)
	{
		cin>>(str+1);n=strlen(str+1);
		Next[0]=-1;Next[1]=0;
		for (int i=2;i<=n;i++)
		{
			int j=Next[i-1];
			while ((j!=0)&&(str[j+1]!=str[i])) j=Next[j];
			if (str[j+1]==str[i]) Next[i]=j+1;
			else Next[i]=0;
		}
		//for (int i=1;i<=n;i++) cout<<Next[i]<<" ";cout<<endl;
		mem(Pre,0);Pre[0]=1;
		for (int i=n;i!=0;i=Next[i]) Pre[i]=1;
		//for (int i=1;i<=n;i++) cout<<Pre[i]<<" ";cout<<endl;
		int mn=n;
		for (int i=1;i<=n;i++)
		{
			int cnt=n/i,pos=cnt*i;
			if ((pos%(pos-Next[pos])!=0)||(pos-Next[pos]!=i)) continue;
			if (Pre[n-pos]==0) continue;
			cnt=pos/(pos-Next[pos]);
			if ((pos==n)&&(cnt>1)) mn=0;
			mn=min(mn,pos+i-n);
			//cout<<i<<" "<<pos<<" "<<cnt<<endl;
		}
		printf("%d\n",mn);
	}
	return 0;
}
