#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=101000;
const int Alpha=26;

class PAM
{
public:
	int son[Alpha],fail,len,delta,nxt;
};

int n,Q;
char Input[maxN];
int nodecnt=1,last=0,Pos[maxN];
PAM P[maxN];
vector<int> T[maxN];
int dfncnt,dfn[maxN],lst[maxN];

void Extend(int pos,int c);
void dfs(int u);
namespace S1
{
int Mx[maxN<<2];
void Modify(int x,int l,int r,int pos,int key);
int Query(int x,int l,int r,int ql,int qr);
}
namespace S2
{
class SegmentData
{
public:
	int ls,rs,sum;
};
int nodecnt=0,rt[maxN];
SegmentData S[maxN*120];
void Modify(int &x,int l,int r,int pos,int key);
int Query(int x,int l,int r,int ql,int qr);
void outp(int x,int l,int r);
}

int main()
{
	//freopen("in","r",stdin);
	int type;
	scanf("%d",&type);
	scanf("%d%d",&n,&Q);
	scanf("%s",Input+1);

	P[0].fail=1;
	P[0].len=0;
	P[1].len=-1;
	P[1].fail=1;
	for (int i=1; i<=n; i++) Extend(i,Input[i]-'a'),Pos[i]=last;

	/*
	for (int i=0;i<=nodecnt;i++)
	for (int j=0;j<Alpha;j++)
	    if (P[i].son[j]) cout<<i<<" -> "<<P[i].son[j]<<" "<<(char)(j+'a')<<endl;
	for (int i=0;i<=nodecnt;i++) cout<<P[i].fail<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Pos[i]<<" ";cout<<endl;
	for (int i=0;i<=nodecnt;i++) cout<<P[i].len<<" ";cout<<endl;
	//*/

	for (int i=0; i<=nodecnt; i++) if (i!=1) T[P[i].fail].push_back(i);
	dfs(1);

	for (int i=1; i<=n; i++) {
		S2::rt[i]=S2::rt[i-1];
		//cout<<"Pos:"<<Pos[i]<<endl;
		for (int j=Pos[i]; j; j=P[P[j].nxt].fail) {
			//cout<<i<<" "<<j<<" "<<max(1,S1::Query(1,1,dfncnt,dfn[j],lst[j])-P[j].len+2)<<" "<<i-P[P[j].nxt].len+2<<endl;
			S2::Modify(S2::rt[i],1,n,max(1,S1::Query(1,1,dfncnt,dfn[j],lst[j])-P[j].len+2),1);
			S2::Modify(S2::rt[i],1,n,i-P[P[j].nxt].len+2,-1);
		}
		S1::Modify(1,1,dfncnt,dfn[Pos[i]],i);
	}
	/*
	for (int i=1;i<=n;i++){
	S2::outp(S2::rt[i],1,n);cout<<endl;
	}//*/

	int lstans=0;
	while (Q--) {
		int l,r;
		scanf("%d%d",&l,&r);
		if (type) l^=lstans,r^=lstans;
		printf("%d\n",lstans=S2::Query(S2::rt[r],1,n,1,l));
	}
	return 0;
}

void Extend(int pos,int c)
{
	int p=last;
	while (Input[pos-P[p].len-1]!=Input[pos]) p=P[p].fail;
	if (P[p].son[c]==0) {
		int np=++nodecnt,q=P[p].fail;
		while (Input[pos-P[q].len-1]!=Input[pos]) q=P[q].fail;
		P[np].len=P[p].len+2;
		P[np].fail=P[q].son[c];
		P[p].son[c]=np;

		P[np].delta=P[np].len-P[P[np].fail].len;
		if (P[np].delta!=P[P[np].fail].delta) P[np].nxt=np;
		else P[np].nxt=P[P[np].fail].nxt;
	}
	last=P[p].son[c];
	return;
}
void dfs(int x)
{
	dfn[x]=++dfncnt;
	for (int i=0,sz=T[x].size(); i<sz; i++) dfs(T[x][i]);
	lst[x]=dfncnt;
	return;
}
namespace S1
{
#define ls (x<<1)
#define rs (ls|1)
void Modify(int x,int l,int r,int pos,int key)
{
	if (l==r) {
		Mx[x]=key;
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(ls,l,mid,pos,key);
	else Modify(rs,mid+1,r,pos,key);
	Mx[x]=max(Mx[ls],Mx[rs]);
	return;
}
int Query(int x,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return Mx[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return max(Query(ls,l,mid,ql,mid),Query(rs,mid+1,r,mid+1,qr));
}
#undef ls
#undef rs
}
namespace S2
{
void Modify(int &x,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[x];
	x=nodecnt;
	if (l==r) {
		S[x].sum+=key;
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[x].ls,l,mid,pos,key);
	else Modify(S[x].rs,mid+1,r,pos,key);
	S[x].sum=S[S[x].ls].sum+S[S[x].rs].sum;
	return;
}
int Query(int x,int l,int r,int ql,int qr)
{
	if (x==0) return 0;
	if ((l==ql)&&(r==qr)) return S[x].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[x].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(S[x].rs,mid+1,r,ql,qr);
	else return Query(S[x].ls,l,mid,ql,mid)+Query(S[x].rs,mid+1,r,mid+1,qr);
}
void outp(int x,int l,int r)
{
	if (l==r) {
		cout<<S[x].sum<<" ";
		return;
	}
	int mid=(l+r)>>1;
	outp(S[x].ls,l,mid);
	outp(S[x].rs,mid+1,r);
	return;
}
}
