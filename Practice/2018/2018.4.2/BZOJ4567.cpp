#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

//const int maxN=101000;
const int maxTrie=600010;
const int maxAlpha=26;
const int inf=2147483647;

class Trie
{
public:
	int end;
	int son[maxAlpha];
	int id;
};

int n,nodecnt;
Trie T[maxTrie];
char str[maxTrie];
vector<int> Son[maxTrie];
ll Size[maxTrie];
ll Ans=0;
ll idcnt=0,Id[maxTrie];

void dfs(int u,int top);
void GetSize(int u);
void Calc(int u);
bool cmp(int a,int b);

int main()
{
	//ios::sync_with_stdio(false);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		//cout<<i<<endl;
		scanf("%s",str+1);
		int len=strlen(str+1);
		int now=0;
		for (int j=len;j>=1;j--)
		{
			//cout<<j<<" "<<now<<" "<<str[j]-'a'<<endl;
			if (T[now].son[str[j]-'a']==0) T[now].son[str[j]-'a']=++nodecnt;
			now=T[now].son[str[j]-'a'];
		}
		T[now].end=1;T[now].id=i;
	}
	//cout<<"Input over"<<endl;
	dfs(0,0);
	//cout<<"dfs over"<<endl;
	GetSize(0);
	//cout<<"Size over"<<endl;
	Calc(0);
	///cout<<Ans<<endl;
	printf("%lld\n",Ans);
	return 0;
}

void dfs(int u,int top)
{
	if (T[u].end){
		Son[top].push_back(u);
		top=u;
	}
	for (int i=0;i<maxAlpha;i++) if (T[u].son[i]) dfs(T[u].son[i],top);
	return;
}

void GetSize(int u)
{
	Size[u]=1;
	int cnt=Son[u].size();
	for (int i=0;i<cnt;i++) GetSize(Son[u][i]),Size[u]+=Size[Son[u][i]];
	return;
}

void Calc(int u)
{
	sort(Son[u].begin(),Son[u].end(),cmp);
	int cnt=Son[u].size();if (u!=0) Id[u]=++idcnt;
	//for (int i=0;i<cnt;i++) cout<<u<<"->"<<Son[u][i]<<" ["<<T[Son[u][i]].id<<"] "<<Size[Son[u][i]]<<endl;
	for (int i=0;i<cnt;i++){
		Calc(Son[u][i]);Ans+=Id[Son[u][i]]-Id[u];
	}
	return;
}

bool cmp(int a,int b)
{
	return Size[a]<Size[b];
}
