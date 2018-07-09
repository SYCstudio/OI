#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
#include<set>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int len,fa;
	set<int> Id;
};

int n,K;
int nodecnt=1,root=1,last=1;
string str[maxN];
Node S[maxN<<1];
int Sorter[maxN<<1],Id[maxN<<1];
vector<int> Son[maxN];

void Insert(int c,int id);
void dfs(int u);

int main()
{
	ios::sync_with_stdio(false);

	cin>>n>>K;
	for (int i=1;i<=n;i++)
	{
		cin>>str[i];
		last=1;
		for (int j=0;j<str[i].size();j++) Insert(str[i][j]-'a',i);
	}

	//cout<<nodecnt<<" "<<endl;
	
	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].son[j])
				cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;

	for (int i=1;i<=nodecnt;i++)
	{
		cout<<i<<":";
		for (set<int>::iterator it=S[i].Id.begin();it!=S[i].Id.end();it++)
			cout<<(*it)<<" ";
		cout<<endl;
	}
	//*/

	if (n<K){
		printf("0");
		for (int i=2;i<=n;i++) printf(" 0");
		return 0;
	}

	/*
	for (int i=1;i<=nodecnt;i++) Sorter[S[i].len]++;
	for (int i=1;i<=nodecnt;i++) Sorter[i]+=Sorter[i-1];
	for (int i=nodecnt;i>=1;i--) Id[Sorter[S[i].len]--]=i;

	for (int i=nodecnt;i>=1;i--)
		for (set<int>::iterator it=S[Id[i]].Id.begin();it!=S[Id[i]].Id.end();it++)
			S[S[Id[i]].fa].Id.insert((*it));
	//*/

	for (int i=1;i<=nodecnt;i++) Son[S[i].fa].push_back(i);
	dfs(1);

	//for (int i=1;i<=nodecnt;i++) cout<<S[i].Id.size()<<" ";cout<<endl;
	
	/*
	for (int i=1;i<=nodecnt;i++)
	{
		cout<<i<<":";
		for (set<int>::iterator it=S[i].Id.begin();it!=S[i].Id.end();it++)
			cout<<(*it)<<" ";
		cout<<endl;
	}
	cout<<"GetAns:"<<endl;
	//*/
	for (int i=1;i<=n;i++)
	{
		int now=root;
		ll Ans=0;
		for (int j=0;j<str[i].size();j++)
		{
			while ((now!=0)&&(S[now].son[str[i][j]-'a']==0)) now=S[now].fa;
			if (now==0){
				now=root;continue;
			}
			now=S[now].son[str[i][j]-'a'];
			while (S[now].Id.size()<K) now=S[now].fa;
			Ans+=S[now].len;
		}
		if (i!=1) printf(" ");
		printf("%lld",Ans);
	}
	return 0;
}

void Insert(int c,int id)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;S[np].Id.insert(id);
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
	return;
}


void dfs(int u)
{
	for (int i=0;i<Son[u].size();i++)
	{
		int v=Son[u][i];
		dfs(v);
		for (set<int>::iterator it=S[v].Id.begin();it!=S[v].Id.end();it++)
			S[u].Id.insert(*it);
	}
	return;
}
