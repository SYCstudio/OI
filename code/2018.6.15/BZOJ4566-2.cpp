#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=401000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fa,len;
};

int l1,l2;
int nodecnt=1,root=1,last=1;
char str[maxN];
Node S[maxN<<1];
ll Sum[2][maxN<<1];
vector<int> Son[maxN<<1];
ll Ans=0;

int Insert(int c);
void dfs(int u);

int main()
{
	scanf("%s",str+1);
	l1=strlen(str+1);
	//int k;
	for (int i=1;i<=l1;i++) Sum[0][Insert(str[i]-'a')]++;
	scanf("%s",str+1);
	l2=strlen(str+1);
	last=1;
	for (int i=1;i<=l2;i++) Sum[1][Insert(str[i]-'a')]++;

	for (int i=2;i<=nodecnt;i++) Son[S[i].fa].push_back(i);
	dfs(1);

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].son[j])
				cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;

	for (int i=1;i<=nodecnt;i++) cout<<Sum[0][i]<<" ";cout<<endl;
	for (int i=1;i<=nodecnt;i++) cout<<Sum[1][i]<<" ";cout<<endl;
	//*/
	
	printf("%lld\n",Ans);
	return 0;
}

int Insert(int c)
{
	if ((S[last].son[c]!=0)&&(S[last].len+1==S[S[last].son[c]].len)) return last=S[last].son[c];
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;
	while ((p!=0)&&(S[p].son[c]==0)) S[p].son[c]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].son[c];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].son[c]==q)) S[p].son[c]=nq,p=S[p].fa;
		}
	}
	return last;
}

void dfs(int u)
{
	for (int i=0;i<Son[u].size();i++)
	{
		int v=Son[u][i];
		dfs(v);
		Sum[0][u]+=Sum[0][v];Sum[1][u]+=Sum[1][v];
	}
	if (u!=1) Ans=Ans+(S[u].len-S[S[u].fa].len)*Sum[0][u]*Sum[1][u];
	return;
}
