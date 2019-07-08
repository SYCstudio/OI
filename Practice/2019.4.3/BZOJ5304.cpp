#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<iostream>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int maxN=202000;
const int Alpha=26;
const int maxB=20;
const ull base=233;
const int inf=2000000000;

class SAM
{
public:
	int son[Alpha],len,fail;
};
class SegmentData
{
public:
	int ls,rs;
};
class Question
{
public:
	int s,t,l,r;
};

int n,K;
char S[maxN],T[maxN];
SAM Sm[maxN];
int lst=1,smcnt=1,sgcnt,rt[maxN],Fa[maxB][maxN];
SegmentData Sg[maxN*20];
int Mch[maxN],Mlen[maxN];
ll Ans[maxN];
Question Qm[maxN];
vector<int> HQ[55],Qsam[maxN],Pt[maxN];
ull Hs[maxN],Ht[maxN],Ph[maxN];
map<ull,set<int> > Lp;
int Nxt[maxB][maxN],Nsm[maxB][maxN];

void Extend(int c);
void Insert(int &x,int l,int r,int p);
int Merge(int u,int v);
void dfs_calc(int u);
int QMax(int x,int l,int r,int limit);
ull GetHash(ull *H,int l,int r);
int main()
{
	Ph[0]=1;
	for (int i=1; i<maxN; i++) Ph[i]=Ph[i-1]*base;
	scanf("%d%d",&n,&K);
	scanf("%s",S+1);
	for (int i=1; i<=n; i++) Extend(S[i]-'a'),Insert(rt[lst],1,n,i);
	for (int i=2; i<=smcnt; i++) Pt[Sm[i].fail].push_back(i),Fa[0][i]=Sm[i].fail;
	for (int i=1; i<maxB; i++) for (int j=1; j<=smcnt; j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	scanf("%s",T+1);
	for (int i=1,now=1,len=0; i<=n; i++) {
		int c=T[i]-'a';
		while (now&&!Sm[now].son[c]) now=Sm[now].fail,len=Sm[now].len;
		if (!now) {
			now=1;
			len=0;
		} else {
			now=Sm[now].son[c];
			++len;
		}
		Mch[i]=now;
		Mlen[i]=len;
	}

	int Q;
	scanf("%d",&Q);
	for (int i=1; i<=Q; i++) {
		scanf("%d%d%d%d",&Qm[i].s,&Qm[i].t,&Qm[i].l,&Qm[i].r);
		int len=Qm[i].r-Qm[i].l+1;
		if (len<=50) HQ[len].push_back(i);//----------------------------------warning----------------------------------------
		else {
			if (Mlen[Qm[i].r]<len) continue;
			int now=Mch[Qm[i].r];
			for (int j=maxB-1; j>=0; j--) if (Fa[j][now]&&Sm[Fa[j][now]].len>=len) now=Fa[j][now];
			Qsam[now].push_back(i);
		}
	}

	dfs_calc(1);

	for (int i=1; i<=n; i++) Hs[i]=Hs[i-1]*base+S[i]-'a'+1;
	for (int i=1; i<=n; i++) Ht[i]=Ht[i-1]*base+T[i]-'a'+1;

	for (int i=1; i<=50; i++) { //----------------------------------warning------------------------------------
		Lp.clear();
		for (int j=n-i+1; j>=1; j--) {
			if (j+i+i-1<=n) Lp[GetHash(Hs,j+i,j+i+i-1)].insert(j+i);
			ull h=GetHash(Hs,j,j+i-1);
			if (Lp[h].size()) Nxt[0][j]=*Lp[GetHash(Hs,j,j+i-1)].begin(),Nsm[0][j]=Nxt[0][j];
			else Nxt[0][j]=Nsm[0][j]=0;
		}
		for (int j=i; j>=1; j--) if (j+i-1<=n) Lp[GetHash(Hs,j,j+i-1)].insert(j);
		//cout<<i<<endl;
		//for (int j=1;j<=n;j++) cout<<Nxt[0][j]<<" ";cout<<endl;
		for (int j=1; j<maxB; j++) for (int k=1; k+(1<<j)-1<=n; k++) Nxt[j][k]=Nxt[j-1][Nxt[j-1][k]],Nsm[j][k]=Nsm[j-1][k]+Nsm[j-1][Nxt[j-1][k]];
		for (int j=0,sz=HQ[i].size(); j<sz; j++) {
			int id=HQ[i][j];
			ull ph=GetHash(Ht,Qm[id].l,Qm[id].r);
			set<int>::iterator it=Lp[ph].lower_bound(Qm[id].s);
			if (it!=Lp[ph].end()&&(*it)+i-1<=Qm[id].t) {
				int pos=*it;
				Ans[id]=Ans[id]+K-pos;
				for (int k=maxB-1; k>=0; k--)
					if (Nxt[k][pos]&&Nxt[k][pos]+i-1<=Qm[id].t) {
						Ans[id]=Ans[id]+(1ll<<k)*K-Nsm[k][pos];
						pos=Nxt[k][pos];
					}
			}
		}
	}

	for (int i=1; i<=Q; i++) printf("%lld\n",Ans[i]);
	return 0;
}
void Extend(int c)
{
	int np=++smcnt,p=lst;
	lst=np;
	Sm[np].len=Sm[p].len+1;
	while (p&&Sm[p].son[c]==0) Sm[p].son[c]=np,p=Sm[p].fail;
	if (p==0) Sm[np].fail=1;
	else {
		int q=Sm[p].son[c];
		if (Sm[q].len==Sm[p].len+1) Sm[np].fail=q;
		else {
			int nq=++smcnt;
			Sm[nq]=Sm[q];
			Sm[nq].len=Sm[p].len+1;
			Sm[np].fail=Sm[q].fail=nq;
			while (p&&Sm[p].son[c]==q) Sm[p].son[c]=nq,p=Sm[p].fail;
		}
	}
	return;
}
void Insert(int &x,int l,int r,int p)
{
	if (x==0) x=++sgcnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Insert(Sg[x].ls,l,mid,p);
	else Insert(Sg[x].rs,mid+1,r,p);
	return;
}
int Merge(int u,int v)
{
	if (!u||!v) return u+v;
	Sg[u].ls=Merge(Sg[u].ls,Sg[v].ls);
	Sg[u].rs=Merge(Sg[u].rs,Sg[v].rs);
	return u;
}
void dfs_calc(int u)
{
	for (int i=0,sz=Pt[u].size(); i<sz; i++) dfs_calc(Pt[u][i]),rt[u]=Merge(rt[u],rt[Pt[u][i]]);
	for (int i=0,sz=Qsam[u].size(); i<sz; i++) {
		int id=Qsam[u][i],len=Qm[id].r-Qm[id].l+1,lst=Qm[id].s+len-1;
		while (1) {
			lst=QMax(rt[u],1,n,lst);
			if (lst&&lst<=Qm[id].t) Ans[id]=Ans[id]+K-(lst-len+1),lst=lst+len;
			else break;
		}
	}
	return;
}
int QMax(int x,int l,int r,int limit)
{
	if (!x) return 0;
	if (l==r) return l>=limit?l:0;
	int mid=(l+r)>>1;
	if (limit<=mid) {
		int q=QMax(Sg[x].ls,l,mid,limit);
		if (q) return q;
	}
	return QMax(Sg[x].rs,mid+1,r,limit);
}
ull GetHash(ull *H,int l,int r)
{
	return H[r]-H[l-1]*Ph[r-l+1];
}