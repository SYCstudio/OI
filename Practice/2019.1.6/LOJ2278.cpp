#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=202000*2;
const int maxAlpha=94;

class Trie
{
public:
	int son[maxAlpha],fail;
};

int n,K;
char S[maxN],T[maxN];
int root=1,nodecnt=1;
Trie TC[maxN];
int dfncnt,dfn[maxN],lst[maxN],B[2][maxN];
vector<int> FT[maxN],Mtc[maxN];
vector<pair<int,int> > Qe[maxN];
int Ans[maxN],L[maxN],R[maxN],Que[maxN];

int Insert(int p,int c);
void GetFail();
void dfs(int x);
void solve(int x);
void Add(int opt,int pos,int key);
int Sum(int opt,int pos);
int Query(int opt,int u);

int main()
{
	//freopen("B3.in","r",stdin);
	scanf("%d",&K);
	scanf("%s",S+1);
	scanf("%d",&n);
	int lenS=strlen(S+1);
	for (int id=1; id<=n; id++) {
		scanf("%s",T+1);
		int len=strlen(T+1);
		if (len<=K) {
			Ans[id]=lenS-len+1;
			continue;
		}
		L[0]=1;
		for (int i=1; i<=len; i++) L[i]=Insert(L[i-1],T[i]-33);
		R[len+1]=1;
		for (int i=len; i>=1; i--) R[i]=Insert(R[i+1],T[i]-33);
		//for (int i=0;i<=len+1;i++) cout<<L[i]<<" ";cout<<endl;
		//for (int i=0;i<=len+1;i++) cout<<R[i]<<" ";cout<<endl;
		for (int i=0; i+K<=len; i++) Qe[L[i]].push_back(make_pair(id,R[i+K+1]));
		for (int i=1; i+K<=len; i++) Qe[L[i]].push_back(make_pair(id,-R[i+K]));
	}
	//cout<<nodecnt<<endl;

	GetFail();
	dfs(1);
	//for (int i=1;i<=nodecnt;i++) cout<<TC[i].fail<<" ";cout<<endl;
	//for (int i=1;i<=nodecnt;i++) cout<<dfn[i]<<" "<<lst[i]<<endl;

	L[0]=1;
	for (int i=1,now=1; i<=lenS; i++) L[i]=TC[L[i-1]].son[S[i]-33];
	R[lenS+1]=1;
	for (int i=lenS,now=1; i>=1; i--) R[i]=TC[R[i+1]].son[S[i]-33];
	//for (int i=0;i<=lenS+1;i++) cout<<L[i]<<" ";cout<<endl;
	//for (int i=0;i<=lenS+1;i++) cout<<R[i]<<" ";cout<<endl;
	for (int i=0; i+K<=lenS; i++) Mtc[L[i]].push_back(R[i+K+1]);
	for (int i=1; i+K<=lenS; i++) Mtc[L[i]].push_back(-R[i+K]);

	solve(1);

	for (int i=1; i<=n; i++) printf("%d\n",Ans[i]);
	return 0;
}

int Insert(int p,int c)
{
	if (TC[p].son[c]) return TC[p].son[c];
	else return TC[p].son[c]=++nodecnt;
}

void GetFail()
{
	int L=0,R=0;
	TC[1].fail=1;
	for (int i=0; i<maxAlpha; i++)
		if (TC[1].son[i]) Que[++R]=TC[1].son[i],TC[TC[1].son[i]].fail=1;
		else TC[1].son[i]=1;
	while (L<=R) {
		int u=Que[++L];
		for (int i=0; i<maxAlpha; i++)
			if (TC[u].son[i]) {
				TC[TC[u].son[i]].fail=TC[TC[u].fail].son[i];
				Que[++R]=TC[u].son[i];
			} else TC[u].son[i]=TC[TC[u].fail].son[i];
	}
	for (int i=2; i<=nodecnt; i++) FT[TC[i].fail].push_back(i);
	return;
}

void dfs(int x)
{
	dfn[x]=++dfncnt;
	for (int i=0,sz=FT[x].size(); i<sz; i++) dfs(FT[x][i]);
	lst[x]=dfncnt;
	return;
}

void solve(int x)
{
	for (int i=0,sz=Qe[x].size(); i<sz; i++)
		if (Qe[x][i].second>0) Ans[Qe[x][i].first]-=Query(0,Qe[x][i].second);
		else Ans[Qe[x][i].first]+=Query(1,-Qe[x][i].second);
	for (int i=0,sz=FT[x].size(); i<sz; i++) solve(FT[x][i]);
	for (int i=0,sz=Mtc[x].size(); i<sz; i++)
		if (Mtc[x][i]>0) Add(0,dfn[Mtc[x][i]],1);
		else Add(1,dfn[-Mtc[x][i]],1);
	for (int i=0,sz=Qe[x].size(); i<sz; i++)
		if (Qe[x][i].second>0) Ans[Qe[x][i].first]+=Query(0,Qe[x][i].second);
		else Ans[Qe[x][i].first]-=Query(1,-Qe[x][i].second);
	return;
}

void Add(int opt,int pos,int key)
{
	while (pos<=nodecnt) {
		B[opt][pos]+=key;
		pos+=(pos)&(-pos);
	}
	return;
}

int Sum(int opt,int pos)
{
	int ret=0;
	while (pos) {
		ret+=B[opt][pos];
		pos-=(pos)&(-pos);
	}
	return ret;
}

int Query(int opt,int u)
{
	return Sum(opt,lst[u])-Sum(opt,dfn[u]-1);
}
