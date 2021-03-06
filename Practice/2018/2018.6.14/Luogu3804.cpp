#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int len,fa,end;
};

int n,nodecnt=1,last=1,root=1;
char str[maxN];
Node S[maxN<<1];
int Degree[maxN<<1],Q[maxN<<1];
int Endpos[maxN<<1];

void Insert(int key);

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	for (int i=1;i<=n;i++) Insert(str[i]-'a');

	//for (int i=1;i<=n;i++
	
	for (int i=2;i<=nodecnt;i++) Degree[S[i].fa]++;
	int h=0,t=0;
	for (int i=1;i<=nodecnt;i++) if (Degree[i]==0) Q[++h]=i;
	ll Ans=0;
	do
	{
		int u=Q[++t];
		if (Endpos[u]>1) Ans=max(Ans,1ll*(ll)Endpos[u]*(ll)S[u].len);
		Endpos[S[u].fa]+=Endpos[u];
		if ((--Degree[S[u].fa])==0) Q[++h]=S[u].fa;
	}
	while (t!=h);
	printf("%lld\n",Ans);
	return 0;
}

void Insert(int key)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;S[np].end=1;Endpos[np]=1;
	while ((p!=0)&&(S[p].son[key]==0)) S[p].son[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].son[key];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;
			S[nq]=S[q];S[nq].end=0;S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].son[key]==q)) S[p].son[key]=nq,p=S[p].fa;
		}
	}
	return;
}
