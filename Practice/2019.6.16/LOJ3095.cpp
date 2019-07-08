#include<bits/stdc++.h>
using namespace std;

const int maxN=1010000;

char S[maxN];
int n,sa[maxN],srt[maxN];

bool cmp(int a,int b);
int main()
{
	scanf("%d",&n);
	scanf("%s",S+1);
	for (int i=1; i<=n; i++) {
		sa[i]=max(0,sa[i-1]-1);
		srt[i]=i;
		while (i+sa[i]+1<=n&&S[i+sa[i]]==S[i+sa[i]+1]) ++sa[i];
	}
	//for (int i=1;i<=n;i++) cout<<sa[i]<<" ";cout<<endl;
	sort(&srt[1],&srt[n+1],cmp);
	for (int i=1; i<=n; i++) printf("%d ",srt[i]);
	return 0;
}
bool cmp(int a,int b)
{
	int opt=0;
	if (a>b) swap(a,b),opt=1;
	if (a+sa[a]>=b) return (a<b)^opt;
	return (S[a+sa[a]+1]<S[a+sa[a]])^opt;
}
