#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxN=301000;
const int maxM=maxN<<1;
const int inf=2147483647;

class Question
{
public:
	int k,id;
};

int n,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Depth[maxN],Hson[maxN],MxD[maxN],Top[maxN],Size[maxN],Fa[maxN];
int dfncnt,dfn[maxN];
vector<Question> Qn[maxN];
ll BIT[maxN],Ans[maxN],F[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void dp(int u);
void Add(int pos,ll key);
ll Sum(int pos);
ll Query(int l,int r);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&Q);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	Depth[1]=1;dfs1(1,1);dfs2(1,1);

	for (int i=1;i<=Q;i++){
		int p,k;scanf("%d%d",&p,&k);
		Qn[p].push_back((Question){k,i});
	}

	dp(1);
	
	for (int i=1;i<=Q;i++) printf("%lld\n",Ans[i]);

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	MxD[u]=Depth[u];Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Depth[V[i]]=Depth[u]+1;Fa[V[i]]=u;dfs1(V[i],u);
			Size[u]+=Size[V[i]];
			if (MxD[V[i]]>MxD[u]) Hson[u]=V[i],MxD[u]=MxD[V[i]];
		}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;dfn[u]=++dfncnt;
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i],V[i]);
	return;
}

void dp(int u){
	if (Hson[u]!=0){
		dp(Hson[u]);
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((V[i]!=Fa[u])&&(V[i]!=Hson[u])){
				int v=V[i];
				dp(v);int fv=dfn[v],len=MxD[v]-Depth[v];
				for (int j=0;j<=len;j++){
					F[dfn[u]+j+1]+=F[fv+j];
					Add(dfn[u]+j+1,F[fv+j]);
				}
			}
	}

	int mxd=MxD[u]-Depth[u];
	for (int sz=Qn[u].size(),i=0;i<sz;i++) Ans[Qn[u][i].id]=Query(dfn[u],dfn[u]+min(mxd,Qn[u][i].k))+1ll*(Size[u]-1)*min(Depth[u]-1,Qn[u][i].k);
	
	F[dfn[u]]=Size[u]-1;
	Add(dfn[u],Size[u]-1);
	return;
}
	
void Add(int pos,ll key){
	while (pos<=n){
		BIT[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

ll Query(int l,int r){
	return Sum(r)-Sum(l-1);
}

ll Sum(int pos){
	ll ret=0;
	while (pos){
		ret+=BIT[pos];pos-=lowbit(pos);
	}
	return ret;
}
