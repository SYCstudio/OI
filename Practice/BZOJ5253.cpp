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
const int maxQ=303000;
const int maxAlpha=10;
const int maxBit=20;

class Question{
public:
	int l,r,id;
};

int n,Q,Pos[maxN];
ll Ans[maxN];
char Input[maxN];
vector<int> T[maxN];
vector<Question> Qs[maxN];
int Fa[maxBit][maxN];

void dfs(int u);

namespace SAM{
	class SAM{
	public:
		int son[maxAlpha],fail,len;
	};
	int nodecnt=1,lst=1,root=1;
	SAM S[maxN];
	void Insert(int c);
}

namespace DS{
	class Data{
	public:
		int mn,mx;ll s1,s2;
		Data(){}
		Data(int a,int b,ll c,ll d){
			mn=a;mx=b;s1=c;s2=d;return;
		}
	};
	class SegmentData{
	public:
		int ls,rs;Data d;
	};
	int nodecnt,rt[maxN];
	SegmentData S[maxN*20];
	void Insert(int &x,int l,int r,int pos);
	void Update(int x);
	int Merge(int x,int y);
	Data operator + (Data A,Data B);
	Data QueryS(int x,int l,int r,int ql,int qr);
	int Pre(int x,int l,int r,int right);
	int Nxt(int x,int l,int r,int left);
	void outp(int x,int l,int r);
}

int main(){
	freopen("in","r",stdin);
	scanf("%d%d",&n,&Q);scanf("%s",Input+1);
	for (int i=1;i<=n;i++) SAM::Insert(Input[i]-'0'),DS::Insert(DS::rt[SAM::lst],1,n,i),Pos[i]=SAM::lst;
	for (int i=2;i<=SAM::nodecnt;i++) T[SAM::S[i].fail].push_back(i),Fa[0][i]=SAM::S[i].fail;

	/*
	for (int i=1;i<=SAM::nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (SAM::S[i].son[j]) cout<<i<<" -> "<<SAM::S[i].son[j]<<" "<<j<<endl;
	for (int i=1;i<=SAM::nodecnt;i++) cout<<SAM::S[i].fail<<" ";cout<<endl;
	//*/
	
	for (int i=1;i<maxBit;i++) for (int j=1;j<=SAM::nodecnt;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	for (int i=1;i<=Q;i++){
		int l,r,id=i,len,x;scanf("%d%d",&l,&r);len=r-l+1;x=Pos[r];
		for (int j=maxBit-1;j>=0;j--) if ((Fa[j][x])&&(SAM::S[Fa[j][x]].len>=len)) x=Fa[j][x];
		Qs[x].push_back((Question){l,r,id});
	}
	dfs(1);
	ll mul=1ll*(n-1)*(n-2)/2;
	for (int i=1;i<=Q;i++) printf("%lld\n",mul-Ans[i]);
	return 0;
}

void dfs(int u){
	for (int i=0,sz=T[u].size();i<sz;i++){
		dfs(T[u][i]);DS::rt[u]=DS::Merge(DS::rt[u],DS::rt[T[u][i]]);
	}
	//cout<<"u "<<u<<":";DS::outp(DS::rt[u],1,n);cout<<endl;
	for (int i=0,sz=Qs[u].size();i<sz;i++){
		int l=Qs[u][i].l,r=Qs[u][i].r,len=r-l+1,id=Qs[u][i].id;
		int mnr=DS::S[DS::rt[u]].d.mn,mxr=DS::S[DS::rt[u]].d.mx,mxl=mxr-len+1;
		cout<<"Q:"<<u<<" "<<id<<" "<<mnr<<" "<<mxr<<endl;
		if (mnr>mxl){
			DS::Data R=DS::QueryS(DS::rt[u],1,n,mnr,mxr);
			//cout<<"R:"<<R.s1<<" "<<R.s2<<" "<<R.mn<<" "<<R.mx<<endl;
			Ans[id]=R.s2-1ll*mxl*R.s1+1ll*(mnr-mxl)*(mnr-mxl-1)/2+1ll*(n-len)*(mnr-mxl);
		}
		else{
			int tt=DS::Nxt(DS::rt[u],1,n,mnr+len-2);if (tt<=mxl) continue;
			int p=DS::Nxt(DS::rt[u],1,n,mxl);p=DS::Pre(DS::rt[u],1,n,p);
			int q=DS::Pre(DS::rt[u],1,n,mnr+len-1);int nq=DS::Nxt(DS::rt[u],1,n,q);
			cout<<"p:"<<p<<" q:"<<q<<" nq:"<<nq<<endl;
			DS::Data R=DS::QueryS(DS::rt[u],1,n,p,q);
			cout<<R.s1<<" "<<R.s2<<endl;
			Ans[id]=R.s2-1ll*mxl*R.s1+1ll*(mnr-(q-len+1))*(nq-mxl);
		}
	}
	return;
}
namespace SAM{
	void Insert(int c){
		int np=++nodecnt,p=lst;lst=nodecnt;S[np].len=S[p].len+1;
		while (p&&!S[p].son[c]) S[p].son[c]=np,p=S[p].fail;
		if (!p) S[np].fail=root;
		else{
			int q=S[p].son[c];
			if (S[q].len==S[p].len+1) S[np].fail=q;
			else{
				int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
				S[np].fail=S[q].fail=nq;
				while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
			}
		}
		return;
	}
}
namespace DS{
	void Insert(int &x,int l,int r,int pos){
		if (x==0) x=++nodecnt;
		if (l==r){
			S[x].d=((Data){l,l,l,0});
			return;
		}
		int mid=(l+r)>>1;
		if (pos<=mid) Insert(S[x].ls,l,mid,pos);else Insert(S[x].rs,mid+1,r,pos);
		Update(x);return;
	}
	void Update(int x){
		if (S[x].ls==0) S[x].d=S[S[x].rs].d;
		else if (S[x].rs==0) S[x].d=S[S[x].ls].d;
		else S[x].d=S[S[x].ls].d+S[S[x].rs].d;
		return;
	}
	int Merge(int x,int y){
		if (!x||!y) return x+y;
		S[x].ls=Merge(S[x].ls,S[y].ls);S[x].rs=Merge(S[x].rs,S[y].rs);
		Update(x);return x;
	}
	Data operator + (Data A,Data B){
		if (A.mn==0) return B;
		else if (B.mn==0) return A;
		A.s1+=B.s1;A.s2+=B.s2;
		A.s2+=B.mn-A.mx;A.mx=B.mx;
		return A;
	}
	Data QueryS(int x,int l,int r,int ql,int qr){
		if ((x==0)||(ql>qr)) return ((Data){0,0,0,0});
		if ((l==ql)&&(r==qr)) return S[x].d;
		int mid=(l+r)>>1;
		if (qr<=mid) return QueryS(S[x].ls,l,mid,ql,qr);
		else if (ql>=mid+1) return QueryS(S[x].rs,mid+1,r,ql,qr);
		else return QueryS(S[x].ls,l,mid,ql,mid)+QueryS(S[x].rs,mid+1,r,mid+1,qr);
	}
	int Pre(int x,int l,int r,int right){
		if (x==0) return 0;if (l==r) return l<right?l:0;int mid=(l+r)>>1;
		if ((right<=mid)||(S[x].rs==0)||(S[S[x].rs].d.mn>=right)) return Pre(S[x].ls,l,mid,right);
		return Pre(S[x].rs,mid+1,r,right);
	}
	int Nxt(int x,int l,int r,int left){
		if (x==0) return 0;if (l==r) return l>left?l:0;int mid=(l+r)>>1;
		if ((left>=mid+1)||(S[x].ls==0)||(S[S[x].ls].d.mx<=left)) return Nxt(S[x].rs,mid+1,r,left);
		return Nxt(S[x].ls,l,mid,left);
	}
	void outp(int x,int l,int r){
		if (x==0) return;
		if (l==r){
			cout<<l<<" ";return;
		}
		int mid=(l+r)>>1;
		outp(S[x].ls,l,mid);outp(S[x].rs,mid+1,r);
		return;
	}
}
