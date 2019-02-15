#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*22;
const int maxM=maxN;
const int maxAlpha=10;
const int inf=2147483647;

class SAM
{
public:
	int son[maxAlpha],fa,len,cnt;
};

int n,C;
int nodecnt=1,Last[maxN],NodeW[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Degree[maxN];
SAM S[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa,int depth);
int Insert(int c,int last);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&C);
	for (int i=1;i<=n;i++) scanf("%d",&NodeW[i]),NodeW[i];
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	for (int i=1;i<=n;i++)
		if (Degree[i]==1){
			Last[0]=1;
			Last[1]=Insert(NodeW[i],Last[0]);
			dfs(i,i,1);
		}

	ll Ans=0;
	for (int i=1;i<=nodecnt;i++) Ans=Ans+S[i].len-S[S[i].fa].len;
	printf("%lld\n",Ans);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Degree[u]++;return;
}

void dfs(int u,int fa,int depth){
	//cout<<"dfs:"<<u<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Last[depth+1]=Insert(NodeW[V[i]],Last[depth]);
			dfs(V[i],u,depth+1);
		}
	return;
}

int Insert(int c,int last){
	if ((S[last].son[c])&&(S[S[last].son[c]].len==S[last].len+1)) return S[last].son[c];
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;
	while ((p!=0)&&(S[p].son[c]==0)) S[p].son[c]=np,p=S[p].fa;
	if (p==0) S[np].fa=1;
	else{
		int q=S[p].son[c];
		if (S[q].len==S[p].len+1) S[np].fa=q;
		else{
			int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].son[c]==q)) S[p].son[c]=nq,p=S[p].fa;
		}
	}
	return last;
}
