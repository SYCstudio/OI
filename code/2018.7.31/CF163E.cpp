#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxN=1010000;
const int maxM=maxN<<1;
const int maxAlpha=26;
const int inf=2147483647;

int n,K;
char Input[maxN];
int root=1,nodecnt=1,son[maxAlpha][maxN],fail[maxN],cnt[maxN];
int Pos[maxN],Bit[maxN];
queue<int> Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Size[maxN],Top[maxN],Fa[maxN],Hson[maxN];
int dfncnt,dfn[maxN],nfd[maxN];
int mark[maxN];

int Insert(char *Input);
void GetFail();
void Add_Edge(int u,int v);
void dfs1(int u);
void dfs2(int u,int top);
int GetPath(int u);
void Add(int pos,int cnt);
int Sum(int pos);
int Query(int l,int r);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&K);
	for (int i=1;i<=K;i++){
		scanf("%s",Input+1);
		Pos[i]=Insert(Input);mark[i]=1;
	}

	GetFail();

	dfs1(1);
	dfs2(1,1);

	for (int i=1;i<=nodecnt;i++) Add(dfn[i],cnt[i]);
	//cout<<"Init finish"<<endl;
	while (n--){
		scanf("%s",Input);
		int len=strlen(Input);
		if (Input[0]=='?'){
			int now=root;
			int tot=0;
			for (int i=1;i<len;i++){
				now=son[Input[i]-'a'][now];
				tot+=GetPath(now);
			}
			printf("%d\n",tot);
		}
		else{
			int num=0;
			for (int i=1;i<len;i++) num=num*10+Input[i]-'0';
			if ((Input[0]=='+')&&(mark[num]==0)){
				Add(dfn[Pos[num]],1);mark[num]=1;
			}
			if ((Input[0]=='-')&&(mark[num]==1)){
				Add(dfn[Pos[num]],-1);mark[num]=0;
			}
		}
	}
	return 0;
}

int Insert(char *str){
	//cout<<"Insert:"<<(str+1)<<endl;
	int now=1,len=strlen(str+1);
	for (int i=1;i<=len;i++){
		if (son[str[i]-'a'][now]==0) son[str[i]-'a'][now]=++nodecnt;
		now=son[str[i]-'a'][now];
	}
	cnt[now]++;return now;
}

void GetFail(){
	while (!Q.empty()) Q.pop();
	for (int i=0;i<maxAlpha;i++)
		if (son[i][1]){
			fail[son[i][1]]=1;Q.push(son[i][1]);
		}
		else son[i][1]=1;
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=0;i<maxAlpha;i++)
			if (son[i][u]){
				fail[son[i][u]]=son[i][fail[u]];
				Q.push(son[i][u]);
			}
			else son[i][u]=son[i][fail[u]];
	}
	//cout<<"Get finish"<<endl;
	//for (int i=1;i<=nodecnt;i++) cout<<fail[i]<<" ";cout<<endl;
	for (int i=2;i<=nodecnt;i++) Add_Edge(fail[i],i);
	return;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u){
	//cout<<"dfs1:"<<u<<endl;
	Size[u]=1;Hson[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i]){
		Fa[V[i]]=u;dfs1(V[i]);Size[u]+=Size[V[i]];
		if (Size[Hson[u]]<Size[V[i]]) Hson[u]=V[i];
	}
	return;
}

void dfs2(int u,int top){
	//cout<<"dfs2:"<<u<<endl;
	Top[u]=top;nfd[dfn[u]=++dfncnt]=u;
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Hson[u]) dfs2(V[i],V[i]);
	return;
}

int GetPath(int u){
	int ret=0;
	while (Top[u]!=1){
		ret+=Query(dfn[Top[u]],dfn[u]);
		u=Fa[Top[u]];
	}
	ret+=Query(dfn[Top[u]],dfn[u]);
	return ret;
}

void Add(int pos,int key){
	while (pos<=nodecnt){
		Bit[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=Bit[pos];pos-=lowbit(pos);
	}
	return ret;
}

int Query(int l,int r){
	return Sum(r)-Sum(l-1);
}
