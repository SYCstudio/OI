#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len;
};

char Input[maxN];
int nodecnt,last;
Node S[maxN];
int Len1[maxN],Len2[maxN];

void Insert(int pos,int c,int *L);

int main()
{
	scanf("%s",Input+1);
	int len=strlen(Input+1);

	last=0;nodecnt=1;
	S[1].fail=S[0].fail=1;S[1].len=-1;S[0].len=0;
	for (int i=1;i<=len;i++) Insert(i,Input[i]-'a',Len1);
	
	reverse(&Input[1],&Input[len+1]);
	//for (int i=1;i<=len;i++) cout<<Input[i]<<" ";cout<<endl;
	
	mem(S,0);
	last=0;nodecnt=1;
	S[1].fail=S[0].fail=1;S[1].len=-1;S[0].len=0;
	for (int i=1;i<=len;i++) Insert(i,Input[i]-'a',Len2);

	//for (int i=1;i<=len;i++) cout<<Len2[i]<<" ";cout<<endl;

	reverse(&Len2[1],&Len2[len+1]);

	//for (int i=1;i<=len;i++) cout<<Len1[i]<<" ";cout<<endl;
	//for (int i=1;i<=len;i++) cout<<Len2[i]<<" ";cout<<endl;

	int Ans=0;
	for (int i=1;i<len;i++) Ans=max(Ans,Len1[i]+Len2[i+1]);

	printf("%d\n",Ans);
	return 0;
}

void Insert(int pos,int c,int *L)
{
	int p=last;
	while (Input[pos-1-S[p].len]!=Input[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;
		while (Input[pos-1-S[q].len]!=Input[pos]) q=S[q].fail;
		S[np].fail=S[q].son[c];S[np].len=S[p].len+2;S[p].son[c]=np;
	}
	last=S[p].son[c];
	L[pos]=S[last].len;
	return;
}
