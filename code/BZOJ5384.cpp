#include<iostream>
#include<cstdio>
#include<cstdib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=301000;
const int maxM=1010000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int len,fail,nxt,diff;
};

class Question
{
public:
	int L,id;
};

int n,m;
char str[maxN];
int last,nodecnt;
Node P[maxN];
int Mx[maxN<<2];
int Bit[maxN];
vector<Question> Q[maxN];
vector<int> Son[maxN];
int dfncnt,fst[maxN],lst[maxN];

void Insert(int pos,int c);
void dfs(int u);

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);

	last=0;nodecnt=1;
	S[0].fail=S[1].fail=1;
	S[0].len=0;S[1].len=-1;
	for (int i=1;i<=n;i++) Insert(i,str[i]-'a');

	for (int i=0;i<=nodecnt;i++) if (i!=1) Son[P[i].fail].push_back(i);
	dfs(1);

	for (int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		Q[r].push_back((Question){l,i});
	}

	for (int i=1;i<=n;i++){
		
	}
}

void Insert(int pos,int c){
	int p=last;
	while (str[pos-1-P[p].len]!=str[pos]) p=P[p].fail;
	if (P[p].son[c]==0){
		int np=++nodecnt,q=S[p].fail;
		while (str[pos-1-P[q].len]!=str[pos]) q=P[q].fail;
		P[np].fail=P[q].son[c];P[np].len=P[p].len+2;
		P[np].diff=P[np].len-P[P[np].fail].len;
		if (P[np].diff==P[P[np].fail].diff) P[np].nxt=P[P[np].fail].nxt;
		else P[np].nxt=np;

		P[p].son[c]=np;
	}
	last=P[p].son[c];
	return;
}
	
void dfs(int u){
	fst[u]=++dfncnt;
	for (int sz=Son[u].size(),i=0;i<sz;i++) dfs(Son[u][i]);
	lst[u]=dfncnt;
	return;
}

