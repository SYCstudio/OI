#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int len,fa;
};

int n,nodecnt=1,root=1,last=1;
char str[maxN];
Node S[maxN<<1];
int edgecnt=0,Head[maxN<<1],Next[maxN<<1],V[maxN<<1];
ll Depth[maxN<<1],Endpos[maxN<<1];
ll Ans=0;

void Insert(int key);
void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main()
{
	mem(Head,-1);
	scanf("%s",str+1);
	n=strlen(str+1);
	for (int i=n;i>=1;i--) Insert(str[i]-'a');

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].son[j])
				cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;

	for (int i=2;i<=nodecnt;i++) cout<<S[i].fa<<"->"<<i<<endl;
	//*/

	for (int i=2;i<=nodecnt;i++) Add_Edge(S[i].fa,i);

	Depth[1]=0;
	dfs(1,0);
	//cout<<Ans<<endl;
	Ans=-Ans;
	for (int i=1;i<=n;i++) Ans=Ans+1ll*(i)*(n-1ll);

	printf("%lld\n",Ans);
	return 0;
}

void Insert(int key)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;Endpos[np]=1;
	while ((p!=0)&&(S[p].son[key]==0)) S[p].son[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].son[key];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;
			S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].son[key]==q)) S[p].son[key]=nq,p=S[p].fa;
		}
	}
	return;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		Depth[V[i]]=Depth[u]+1;
		dfs(V[i],u);
		Endpos[u]+=Endpos[V[i]];
	}
	Ans=Ans+(Endpos[u]-1)*(Endpos[u])*(S[u].len-S[fa].len);
	return;
}
