#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*4;
const int maxAlpha=26;
const int maxBit=20;
const int inf=2147483647;

int last=1,nodecnt=1,St[maxN],Last[maxN];
int son[maxN][maxAlpha],len[maxN],fa[maxN];
char Input[maxN];
vector<int> T[maxN],F[maxN];
int Fa[maxBit][maxN],dfncnt,dfn[maxN],nfd[maxN],Depth[maxN];
ll Ans=0;
set<int> S;

void dfs1(int u);
int Insert(int c,int last);
void dfs2(int u);
void Modify(int pos,int opt);
int GetLCA(int u,int v);

int main()
{
	int n;scanf("%d",&n);
	scanf("%s",Input+1);
	int len=strlen(Input+1);
	St[1]=1;
	for (int i=1,top=1;i<=len;i++)
		if (Input[i]=='-') top--;
		else{
			top++;
			T[St[top-1]].push_back(St[top]=i+1);
		}
	Last[1]=1;
	dfs1(1);

	/*
	for (int i=1;i<=len+1;i++)
		for (int sz=T[i].size(),j=0;j<sz;j++)
			cout<<i<<"->"<<T[i][j]<<endl;
	cout<<endl;
	
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (son[i][j]) cout<<i<<"->"<<son[i][j]<<" ["<<(char)(j+'a')<<"]"<<endl;
	for (int i=1;i<=nodecnt;i++) cout<<fa[i]<<" ";cout<<endl;
    //*/

	for (int i=2;i<=nodecnt;i++) F[fa[i]].push_back(i);
	Depth[1]=1;
	dfs2(1);

	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=nodecnt;j++)
			if (Fa[i-1][j])
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	St[1]=1;
	for (int i=1,top=1;i<=len;i++){
		if (Input[i]=='-') Modify(dfn[St[top--]],-1);
		else Modify(dfn[St[++top]=Last[i+1]],1);
		printf("%lld\n",Ans);
	}

	return 0;
}

void dfs1(int u){
	for (int sz=T[u].size(),i=0;i<sz;i++)
	{
		Last[T[u][i]]=Insert(Input[T[u][i]-1]-'a',Last[u]);
		dfs1(T[u][i]);
	}
	return;
}

int Insert(int c,int last){
	//cout<<"Insert:"<<c<<endl;
	if ((son[last][c]!=0)&&(len[son[last][c]]==len[last]+1)) return son[last][c];
	int np=++nodecnt,p=last;last=nodecnt;
	len[np]=len[p]+1;
	while ((p!=0)&&(son[p][c]==0)) son[p][c]=np,p=fa[p];
	if (p==0) fa[np]=1;
	else{
		int q=son[p][c];
		if (len[q]==len[p]+1) fa[np]=q;
		else{
			int nq=++nodecnt;fa[nq]=fa[q];len[nq]=len[p]+1;
			for (int i=0;i<maxAlpha;i++) son[nq][i]=son[q][i];
			fa[q]=fa[np]=nq;
			while ((p!=0)&&(son[p][c]==q)) son[p][c]=nq,p=fa[p];
		}
	}
	return last;
}

void dfs2(int u){
	nfd[dfn[u]=++dfncnt]=u;
	for (int sz=F[u].size(),i=0;i<sz;i++){
		Depth[F[u][i]]=Depth[u]+1;Fa[0][F[u][i]]=u;
		dfs2(F[u][i]);
	}
	return;
}

void Modify(int p,int opt){
	if (opt==1) S.insert(p);
	set<int>::iterator p1,p2;
	p1=p2=S.find(p);
	Ans=Ans+1ll*opt*len[nfd[p]];
	if (p1!=S.begin()){
		p1--;Ans=Ans-1ll*opt*len[GetLCA(nfd[p],nfd[*p1])];
	}
	if (p2!=(--S.end())){
		p2++;Ans=Ans-1ll*opt*len[GetLCA(nfd[p],nfd[*p2])];
	}
	if (((*p1)!=p)&&((*p2)!=p)) Ans=Ans+opt*len[GetLCA(nfd[*p1],nfd[*p2])];
	if (opt==-1) S.erase(p);
	return;
}

int GetLCA(int u,int v){
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}
