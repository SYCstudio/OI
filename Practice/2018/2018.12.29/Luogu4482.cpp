#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=202000*2;
const int maxAlpha=26;
const int inf=1000000000;

class Question
{
public:
	int l,r,id;
};

int n,Q;
char Input[maxN];
vector<int> T[maxN];
int Pos[maxN],Sz[maxN],Hs[maxN],Top[maxN],Fa[maxN];
Question Qn[maxN];
vector<Question> Qs[maxN];
int Ans[maxN];

void dfs1(int u);
void dfs2(int u,int top);
void Skip(Question Q);
void dfs_solve(int u);
void dfs_push(int u,int rt);

namespace SAM{
	class SAM{
	public:
		int son[maxAlpha],fail,len;
	};
	int root=1,lst=1,nodecnt=1,Ep[maxN];
	SAM S[maxN];
	void Insert(int c);
}

namespace S1{
	class SegmentData{
	public:
		int ls,rs,mn;
	};
	int nodecnt=0,rt[maxN];
	SegmentData S[maxN*40];
	void Insert(int &x,int l,int r,int pos,int key);
	void Update(int x);
	int Merge(int x,int y);
	int Query(int x,int l,int r,int right,int limit);
}

namespace S2{
	int Mn[maxN*4],Clr[maxN*4];
	void PushDown(int x);
	void Update(int x);
	void Insert(int x,int l,int r,int pos,int key);
	int Query(int x,int l,int r,int right,int limit);
	void outp(int x,int l,int r);
}

int main(){
	scanf("%s",Input+1);n=strlen(Input+1);
	S2::Clr[1]=1;
	for (int i=1;i<=n;i++) SAM::Insert(Input[i]-'a'),Pos[i]=SAM::lst,S1::Insert(S1::rt[Pos[i]],1,n,i,i),SAM::Ep[SAM::lst]=i;
	for (int i=2;i<=SAM::nodecnt;i++) T[SAM::S[i].fail].push_back(i);

	/*
	for (int i=1;i<=SAM::nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (SAM::S[i].son[j]) cout<<i<<" -> "<<SAM::S[i].son[j]<<" "<<(char)(j+'a')<<endl;
	for (int i=1;i<=SAM::nodecnt;i++) cout<<SAM::S[i].fail<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Pos[i]<<" ";cout<<endl;
	//*/
	
	dfs1(1);dfs2(1,1);
	scanf("%d",&Q);
	for (int i=1;i<=Q;i++){
		scanf("%d%d",&Qn[i].l,&Qn[i].r);Qn[i].id=i;
		Skip(Qn[i]);
	}
	dfs_solve(1);
	for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);return 0;
}
void dfs1(int u){
	Sz[u]=1;
	for (int i=0,sz=T[u].size();i<sz;i++){
		Fa[T[u][i]]=u;dfs1(T[u][i]);Sz[u]+=Sz[T[u][i]];
		if (Sz[T[u][i]]>Sz[Hs[u]]) Hs[u]=T[u][i];
		S1::rt[u]=S1::Merge(S1::rt[u],S1::rt[T[u][i]]);
	}
	return;
}
void dfs2(int u,int top){
	Top[u]=top;if (Hs[u]==0) return;
	dfs2(Hs[u],top);
	for (int i=0,sz=T[u].size();i<sz;i++)
		if (T[u][i]!=Hs[u]) dfs2(T[u][i],T[u][i]);
	return;
}
void Skip(Question Q){
	int u=Pos[Q.r],mx=-1;
	while (u){
		Qs[u].push_back(Q);
		mx=max(mx,S1::Query(S1::rt[u],1,n,Q.r-1,Q.l+SAM::S[u].len-1));
		u=Fa[Top[u]];
	}
	if (mx>=Q.l) Ans[Q.id]=mx-Q.l+1;return;
}
void dfs_solve(int u){
	if (SAM::Ep[u]) S2::Insert(1,1,n,SAM::Ep[u],SAM::Ep[u]-SAM::S[u].len+1);
	for (int i=0,sz=T[u].size();i<sz;i++)
		if (T[u][i]!=Hs[u]) dfs_push(T[u][i],u);
	//cout<<"running on :"<<u<<endl;
	//S2::outp(1,1,n);cout<<endl;
	for (int i=0,sz=Qs[u].size();i<sz;i++){
		int r=S2::Query(1,1,n,Qs[u][i].r-1,Qs[u][i].l);
		//cout<<"Get ans at "<<u<<" id "<<Qs[u][i].id<<" ["<<Qs[u][i].l<<","<<Qs[u][i].r<<"]:"<<r<<endl;
		if (r>=Qs[u][i].l) Ans[Qs[u][i].id]=max(Ans[Qs[u][i].id],r-Qs[u][i].l+1);
	}
	if (Hs[u]==0){
		S2::Clr[1]=1;S2::Mn[1]=inf;return;
	}
	dfs_solve(Hs[u]);
	for (int i=0,sz=T[u].size();i<sz;i++) if (T[u][i]!=Hs[u]) dfs_solve(T[u][i]);
	return;
}
void dfs_push(int u,int rt){
	if (SAM::Ep[u]) S2::Insert(1,1,n,SAM::Ep[u],SAM::Ep[u]-SAM::S[rt].len+1);
	for (int i=0,sz=T[u].size();i<sz;i++) dfs_push(T[u][i],rt);return;
}
namespace SAM{
	void Insert(int c){
		int np=++nodecnt,p=lst;lst=nodecnt;S[np].len=S[p].len+1;
		while (p&&(S[p].son[c]==0)) S[p].son[c]=np,p=S[p].fail;
		if (p==0) S[np].fail=root;
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
}
namespace S1{
	void Update(int x){
		S[x].mn=inf;
		if (S[x].ls) S[x].mn=min(S[x].mn,S[S[x].ls].mn);
		if (S[x].rs) S[x].mn=min(S[x].mn,S[S[x].rs].mn);
		return;
	}
	void Insert(int &x,int l,int r,int pos,int key){
		if (x==0) x=++nodecnt;
		if (l==r){
			S[x].mn=key;return;
		}
		int mid=(l+r)>>1;
		if (pos<=mid) Insert(S[x].ls,l,mid,pos,key);
		else Insert(S[x].rs,mid+1,r,pos,key);
		Update(x);return;
	}
	int Merge(int x,int y){
		if ((!x)||(!y)) return x+y;
		int u=++nodecnt;
		S[u].ls=Merge(S[x].ls,S[y].ls);S[u].rs=Merge(S[x].rs,S[y].rs);
		Update(u);return u;
	}
	int Query(int x,int l,int r,int right,int limit){
		if (x==0) return 0;
		if (l==r) return (l<=limit)?l:0;
		int mid=(l+r)>>1;
		if ((right<=mid)||(S[S[x].rs].mn>limit)) return Query(S[x].ls,l,mid,right,limit);
		int ret=Query(S[x].rs,mid+1,r,right,limit);
		return ret?ret:Query(S[x].ls,l,mid,right,limit);
	}
}
namespace S2{
#define ls (x<<1)
#define rs (ls|1)
	void PushDown(int x){
		if (Clr[x]){
			Clr[ls]=1;Mn[ls]=inf;
			Clr[rs]=1;Mn[rs]=inf;
		}
		Clr[x]=0;return;
	}
	void Update(int x){
		Mn[x]=min(Mn[ls],Mn[rs]);return;
	}
	void Insert(int x,int l,int r,int pos,int key){
		if (l==r){
			Mn[x]=min(Mn[x],key);return;
		}
		PushDown(x);int mid=(l+r)>>1;
		if (pos<=mid) Insert(ls,l,mid,pos,key);
		else Insert(rs,mid+1,r,pos,key);
		Update(x);return;
	}
	int Query(int x,int l,int r,int right,int limit){
		//cout<<"Q:"<<x<<" ["<<l<<","<<r<<"] "<<right<<" "<<limit<<endl;
		if (l==r) return (Mn[x]<=limit)?l:0;
		PushDown(x);int mid=(l+r)>>1;
		if ((right<=mid)||(Mn[rs]>limit)) return Query(ls,l,mid,right,limit);
		int ret=Query(rs,mid+1,r,right,limit);
		return ret?ret:Query(ls,l,mid,right,limit);
	}
	void outp(int x,int l,int r){
		if (l==r){
			if (Mn[x]==inf) cout<<"inf ";
			else cout<<Mn[x]<<" ";return;
		}
		PushDown(x);int mid=(l+r)>>1;
		outp(ls,l,mid);outp(rs,mid+1,r);
		return;
	}
}
