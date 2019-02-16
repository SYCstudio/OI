#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int maxAlpha=26;
const int inf=2147483647;

class SAM
{
public:
	int ch[maxAlpha];
	int fa,len;
};

int L,root=1,last=1,nodecnt=1;
char str[maxN];
SAM S[maxN<<1];
ll F[maxN<<1];
int Degree[maxN<<1],Queue[maxN<<1];

void Insert(int key);

int main()
{
	scanf("%s",str+1);
	L=strlen(str+1);
	for (int i=1;i<=L;i++) Insert(str[i]-'a');

	/*
	for (int i=1;i<=nodecnt;i++)
	{
		for (int j=0;j<maxAlpha;j++)
			if (S[i].ch[j]) cout<<i<<"->"<<S[i].ch[j]<<" "<<(char)(j+'a')<<endl;
	}
	//*/
	
	F[1]=1;
	for (int i=1;i<=nodecnt;i++) for (int j=0;j<maxAlpha;j++) if (S[i].ch[j]) Degree[S[i].ch[j]]++;
	int h=1,t=0;Queue[1]=1;
	ll Ans=0;
	do
	{
		int u=Queue[++t];
		for (int i=0;i<maxAlpha;i++)
			if (S[u].ch[i])
			{
				F[S[u].ch[i]]+=F[u];Degree[S[u].ch[i]]--;
				if (Degree[S[u].ch[i]]==0) Queue[++h]=S[u].ch[i];
			}
		Ans+=F[u];
	}
	while (t!=h);
	printf("%lld\n",Ans-1);
	return 0;
}

void Insert(int key)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;
	while ((p!=0)&&(S[p].ch[key]==0)) S[p].ch[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].ch[key];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;
			S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].ch[key]==q)) S[p].ch[key]=nq,p=S[p].fa;
		}
	}
	return;
}
