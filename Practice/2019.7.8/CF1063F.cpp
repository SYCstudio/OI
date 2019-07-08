#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=505000;
const int Alpha=26;
const int maxB=20;

class SAM{
public:
	int son[Alpha],len,fail;
};

int n,smcnt=1,lst=1,Pos[maxN];
char In[maxN];
SAM Sm[maxN<<1];
int Dp[maxN],Mx[maxN<<3];
vector<int> Vt[maxN<<1];
int Fa[maxB][maxN<<1],dfncnt,dfn[maxN<<1],rht[maxN<<1];

void Extend(int c);
void dfs_init(int u);
bool check(int len,int r,int limit);
void Push(int pos);
void Modify(int x,int l,int r,int pos,int key);
int Query(int x,int l,int r,int ql,int qr);
int main(){
	scanf("%d",&n);scanf("%s",In+1);reverse(&In[1],&In[n+1]);

	for (int i=1;i<=n;i++) Extend(In[i]-'a'),Pos[i]=lst;
	for (int i=2;i<=smcnt;i++) Vt[Sm[i].fail].pb(i),Fa[0][i]=Sm[i].fail;
	for (int i=1;i<maxB;i++) for (int j=1;j<=smcnt;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	dfs_init(1);

	Dp[1]=1;int Ans=1;
	for (int i=2;i<=n;i++){
		Dp[i]=Dp[i-1]+1;
		while (!check(Dp[i]-1,i-1,Dp[i]-1)&&!check(Dp[i]-1,i,Dp[i]-1)){
			--Dp[i];Push(i-Dp[i]);
		}
		//cout<<Dp[i]<<" ";
		Ans=max(Ans,Dp[i]);
	}//cout<<endl;
	printf("%d\n",Ans);return 0;
}
void Extend(int c){
	int np=++smcnt,p=lst;lst=np;Sm[np].len=Sm[p].len+1;
	while (Sm[p].son[c]==0) Sm[p].son[c]=np,p=Sm[p].fail;
	if (p==0) Sm[np].fail=1;
	else{
		int q=Sm[p].son[c];
		if (Sm[q].len==Sm[p].len+1) Sm[np].fail=q;
		else{
			int nq=++smcnt;Sm[nq]=Sm[q];Sm[nq].len=Sm[p].len+1;Sm[q].fail=Sm[np].fail=nq;
			while (Sm[p].son[c]==q) Sm[p].son[c]=nq,p=Sm[p].fail;
		}
	}
	return;
}
void dfs_init(int u){
	dfn[u]=++dfncnt;
	for (int i=0;i<Vt[u].size();i++) dfs_init(Vt[u][i]);
	rht[u]=dfncnt;return;
}
bool check(int len,int r,int limit){
	int now=Pos[r];
	for (int i=maxB-1;i>=0;i--) if (Fa[i][now]&&Sm[Fa[i][now]].len>=len) now=Fa[i][now];
	return Query(1,1,dfncnt,dfn[now],rht[now])>=limit;
}
void Push(int pos){
	Modify(1,1,dfncnt,dfn[Pos[pos]],Dp[pos]);
}
#define ls (x<<1)
#define rs (ls|1)
void Modify(int x,int l,int r,int p,int key){
	Mx[x]=max(Mx[x],key);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Modify(ls,l,mid,p,key);else Modify(rs,mid+1,r,p,key);
	return;
}
int Query(int x,int l,int r,int ql,int qr){
	if (l==ql&&r==qr) return Mx[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return max(Query(ls,l,mid,ql,mid),Query(rs,mid+1,r,mid+1,qr));
}
