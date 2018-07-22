#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int depth,len,fail;
};

char str[maxN];
int nodecnt,last;
Node S[maxN];
int C1[maxN],C2[maxN];

void Insert(int pos,int c);

int main()
{
	scanf("%s",str+1);
	int len=strlen(str+1);

	nodecnt=1;last=0;
	S[1].fail=S[0].fail=1;
	S[1].len=-1;S[0].len=0;
	S[0].depth=S[1].depth=0;
	for (int i=1;i<=len;i++){
		Insert(i,str[i]-'a');
		C1[i]=S[last].depth;
	}

	reverse(&str[1],&str[len+1]);
	mem(S,0);
	nodecnt=1;last=0;
	S[1].fail=S[0].fail=1;
	S[1].len=-1;S[0].len=0;
	S[0].depth=S[1].depth=0;
	for (int i=1;i<=len;i++)
	{
		Insert(i,str[i]-'a');
		C2[i]=S[last].depth;
	}
	reverse(&C2[1],&C2[len+1]);

	for (int i=2;i<=len;i++) C1[i]+=C1[i-1];

	ll Ans=0;
	for (int i=1;i<len;i++) Ans=Ans+1ll*C1[i]*C2[i+1];

	printf("%lld\n",Ans);
	return 0;
}

void Insert(int pos,int c)
{
	int p=last;
	while (str[pos-1-S[p].len]!=str[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;
		while (str[pos-1-S[q].len]!=str[pos]) q=S[q].fail;
		S[np].len=S[p].len+2;S[np].fail=S[q].son[c];S[np].depth=S[S[np].fail].depth+1;
		S[p].son[c]=np;
	}
	last=S[p].son[c];return;
}
