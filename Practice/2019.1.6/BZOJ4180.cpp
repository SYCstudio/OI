#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int maxAlpha=4;
const ll INF=1e18;

class SAM{
public:
	int son[maxAlpha],fail,len;
};

ll n,F[maxAlpha][maxAlpha],M[maxAlpha][maxAlpha],Bp[maxAlpha][maxAlpha],G[maxN][maxAlpha];
int nodecnt=1,lst=1;
char Input[maxN];
SAM S[maxN];
bool vis[maxN];

void Insert(int c);
void dfs(int x);
ll calc(ll limit);
void Mul1();
void Mul2();

int main(){
	//freopen("in","r",stdin);
	scanf("%lld",&n);scanf("%s",Input+1);int len=strlen(Input+1);
	for (int i=1;i<=len;i++) Insert(Input[i]-'A');
	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].son[j]) cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'A')<<"]"<<endl;
	//*/
	for (int i=1;i<=nodecnt;i++) dfs(i);
	/*
	for (int i=1;i<=nodecnt;i++){
		for (int j=0;j<maxAlpha;j++)
			cout<<G[i][j]<<" ";cout<<endl;
	}
	//*/
	/*
	for (int i=0;i<maxAlpha;i++){
		for (int j=0;j<maxAlpha;j++)
			cout<<G[S[1].son[i]][j]<<" ";
		cout<<endl;
	}
	//*/
	ll L=0,R=2e18,Ans=0;
	while (L<=R){
		ll mid=(L+R)>>1;
		if (calc(mid)>=n) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%lld\n",Ans);return 0;
}

void Insert(int c){
	int np=++nodecnt,p=lst;lst=np;S[np].len=S[p].len+1;
	while (p&&(S[p].son[c]==0)) S[p].son[c]=np,p=S[p].fail;
	if (p==0) S[np].fail=1;
	else{
		int q=S[p].son[c];
		if (S[q].len==S[p].len+1) S[np].fail=q;
		else{
			int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fail=S[np].fail=nq;
			while (p&&(S[p].son[c]==q)) S[p].son[c]=nq,p=S[p].fail;
		}
	}
	return;
}
void dfs(int x){
	if (vis[x]) return;
	vis[x]=1;
	for (int i=0;i<maxAlpha;i++) G[x][i]=S[x].son[i]?INF:1;
	for (int i=0;i<maxAlpha;i++)
		if (S[x].son[i]){
			dfs(S[x].son[i]);
			for (int j=0;j<maxAlpha;j++)
				G[x][j]=min(G[x][j],G[S[x].son[i]][j]+1);
		}
	return;
}
ll calc(ll limit){
	if (limit==1) return 1;
	for (int i=0;i<maxAlpha;i++) for (int j=0;j<maxAlpha;j++) F[i][j]=M[i][j]=(G[S[1].son[i]][j])?(G[S[1].son[i]][j]):INF;
	--limit;
	while (limit){
		if (limit&1) Mul1();
		Mul2();limit>>=1;
	}
	ll Ans=INF;
	for (int i=0;i<maxAlpha;i++) for (int j=0;j<maxAlpha;j++) Ans=min(Ans,F[i][j]);
	return Ans;
}
void Mul1(){
	for (int i=0;i<maxAlpha;i++) for (int j=0;j<maxAlpha;j++) Bp[i][j]=F[i][j],F[i][j]=INF;
	for (int i=0;i<maxAlpha;i++)
		for (int j=0;j<maxAlpha;j++)
			for (int k=0;k<maxAlpha;k++)
				F[i][j]=min(F[i][j],Bp[i][k]+M[k][j]);
	return;
}
void Mul2(){
	for (int i=0;i<maxAlpha;i++) for (int j=0;j<maxAlpha;j++) Bp[i][j]=M[i][j],M[i][j]=INF;
	for (int i=0;i<maxAlpha;i++)
		for (int j=0;j<maxAlpha;j++)
			for (int k=0;k<maxAlpha;k++)
				M[i][j]=min(M[i][j],Bp[i][k]+Bp[k][j]);
	return;
}
