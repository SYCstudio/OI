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

class SAM
{
public:
	int ch[maxAlpha];
	int len,fa;
};

int L;
char str[maxN];
int nodecnt=1,root=1,last=1;
SAM S[maxN<<1];
int Degree[maxN<<1],Queue[maxN<<1],Sum[maxN<<1],Ans[maxN];

void Insert(int key);

int main()
{
	scanf("%s",str+1);
	L=strlen(str+1);
	for (int i=1;i<=L;i++) Insert(str[i]-'a');

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].ch[j]) cout<<i<<"->"<<S[i].ch[j]<<" "<<(char)(j+'a')<<endl;

	for (int i=1;i<=nodecnt;i++) cout<<S[i].fa<<" "<<S[i].len<<endl;
	//*/

	for (int i=2;i<=nodecnt;i++) Degree[S[i].fa]++;
	int h=0,t=0;
	for (int i=1;i<=nodecnt;i++) if (Degree[i]==0) Queue[++h]=i;
	do
	{
		int u=Queue[++t];
		Ans[S[u].len]=max(Ans[S[u].len],Sum[u]);
		Sum[S[u].fa]+=Sum[u];Degree[S[u].fa]--;
		if (Degree[S[u].fa]==0) Queue[++h]=S[u].fa;
	}
	while (t!=h);
	
	for (int i=L-1;i>=1;i--) Ans[i]=max(Ans[i],Ans[i+1]);
	for (int i=1;i<=L;i++) printf("%d\n",Ans[i]);
	return 0;
}

void Insert(int key)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;Sum[np]=1;
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
