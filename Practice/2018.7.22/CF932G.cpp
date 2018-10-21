#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxAlpha=26;
const int Mod=1e9+7;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len,nxt,diff;
};

char str[maxN],str2[maxN];
int nodecnt,last;
int F[maxN],G[maxN];
Node S[maxN];

void Insert(int pos,int c);

int main()
{
	scanf("%s",str+1);
	int len=strlen(str+1);
	if (len%2==1){
		printf("0\n");return 0;
	}

	for (int i=1;2*i-1<=len;i++) str2[2*i-1]=str[i];
	for (int i=len;(len-i+1)*2<=len;i--) str2[(len-i+1)*2]=str[i];

	for (int i=1;i<=len;i++) str[i]=str2[i];

	//cout<<(str+1)<<endl;

	nodecnt=1;last=0;
	S[0].len=0;S[1].len=-1;
	S[0].fail=S[1].fail=1;

	F[0]=1;
	for (int i=1;i<=len;i++)
	{
		Insert(i,str[i]-'a');
		for (int p=last;p;p=S[p].nxt)
		{
			G[p]=F[i-S[S[p].nxt].len-S[p].diff];
			if (S[p].diff==S[S[p].fail].diff) G[p]=(G[p]+G[S[p].fail])%Mod;
			if (i%2==0) F[i]=(F[i]+G[p])%Mod;
		}
	}

	printf("%d\n",F[len]);

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
		S[np].fail=S[q].son[c];S[np].len=S[p].len+2;
		S[p].son[c]=np;
		S[np].diff=S[np].len-S[S[np].fail].len;
		if (S[np].diff!=S[S[np].fail].diff) S[np].nxt=S[np].fail;
		else S[np].nxt=S[S[np].fail].nxt;
	}
	last=S[p].son[c];
	return;
}
