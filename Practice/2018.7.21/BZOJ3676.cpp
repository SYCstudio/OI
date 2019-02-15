#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,cnt,len;
};

char str[maxN];
int last,nodecnt;
Node S[maxN];

void Insert(int pos,int c);

int main()
{
	scanf("%s",str+1);
	int len=strlen(str+1);

	S[0].fail=S[1].fail=1;
	S[0].len=0;S[1].len=-1;
	last=0;nodecnt=1;
	
	for (int i=1;i<=len;i++) Insert(i,str[i]-'a');

	for (int i=nodecnt;i>=0;i--) if (i!=1) S[S[i].fail].cnt+=S[i].cnt;

	ll Ans=0;
	for (int i=2;i<=nodecnt;i++) Ans=max(Ans,1ll*S[i].cnt*S[i].len);

	printf("%lld\n",Ans);
	return 0;
}

void Insert(int pos,int c){
	int p=last;
	while (str[pos-1-S[p].len]!=str[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;
		while (str[pos-1-S[q].len]!=str[pos]) q=S[q].fail;
		S[np].fail=S[q].son[c];S[np].len=S[p].len+2;S[p].son[c]=np;
	}
	last=S[p].son[c];S[last].cnt++;
	return;
}
