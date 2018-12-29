#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long
#define NAME "name"

const int maxL=505000*2;
const int maxAlpha=26;

class Node{
public:
	int son[maxAlpha],fail,len;
};

class SAM{
public:
	int nodecnt,root,lst,Pos[maxL];
	Node S[maxL];
	SAM(){
		nodecnt=root=lst=1;return;
	}
	void Init(){
		nodecnt=root=lst=1;mem(S[1].son,0);S[1].fail=S[1].len=0;Pos[1]=0;
		return;
	}
	int New(){
		int p=++nodecnt;S[p].len=S[p].fail=0;mem(S[p].son,0);Pos[p]=0;return p;
	}
	void Extend(int c,int id){
		int np=New(),p=lst;lst=np;S[np].len=S[p].len+1;Pos[np]=id;
		while (p&&!S[p].son[c]) S[p].son[c]=np,p=S[p].fail;
		if (!p) S[np].fail=root;
		else{
			int q=S[p].son[c];
			if (S[q].len==S[p].len+1) S[np].fail=q;
			else{
				int nq=New();S[nq]=S[q];S[q].fail=S[np].fail=nq;S[nq].len=S[p].len+1;Pos[nq]=Pos[q];
				while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
			}
		}
		return;
	}
};

int n,Mtc[maxL];
char Input[maxL];
SAM S,T;
vector<int> TS[maxL];

void dfs_build(int x);

namespace DS{
	class SegmentData{
	public:
		int ls,rs;
	};
	int nodecnt,root[maxL];
	SegmentData S[maxL*20];
	void Insert(int &x,int l,int r,int pos);
	int Query(int x,int l,int r,int ql,int qr);
	int Merge(int x,int y);
	void outp(int x,int l,int r);
}

int main(){
	//freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	scanf("%s",Input+1);n=strlen(Input+1);
	for (int i=1;i<=n;i++){
		S.Extend(Input[i]-'a',i);
		DS::Insert(DS::root[S.lst],1,n,i);
	}
	/*
	for (int i=1;i<=S.nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S.S[i].son[j]) cout<<i<<"->"<<S.S[i].son[j]<<" "<<(char)(j+'a')<<endl;
	for (int i=1;i<=S.nodecnt;i++) cout<<S.S[i].len<<" ";cout<<endl;
	for (int i=1;i<=S.nodecnt;i++) cout<<S.S[i].fail<<" ";cout<<endl;
	//*/
	for (int i=2;i<=S.nodecnt;i++) TS[S.S[i].fail].push_back(i);
	dfs_build(1);
	int Q;scanf("%d",&Q);
	while (Q--){
		int L,R,m;scanf("%s",Input+1);scanf("%d%d",&L,&R);
		m=strlen(Input+1);T.Init();
		for (int i=1;i<=m;i++) T.Extend(Input[i]-'a',i);
		for (int i=1,x=1,cnt=0;i<=m;i++){
			int c=Input[i]-'a';
			//cout<<"running on :"<<i<<endl;
			while (x&&((!S.S[x].son[c])||(
						   !DS::Query(DS::root[S.S[x].son[c]],1,n,L+S.S[S.S[S.S[x].son[c]].fail].len,R)))){
				//cout<<"GetQ:"<<S.S[x].son[c]<<" ["<<L<<"+"<<S.S[S.S[S.S[x].son[c]].fail].len<<","<<R<<"]"<<endl;
				x=S.S[x].fail,cnt=S.S[x].len;
			}
			//cout<<"now:"<<x<<" "<<cnt<<endl;
			if (x==0){
				x=1;cnt=0;Mtc[i]=0;continue;
			}
			x=S.S[x].son[c];++cnt;
			//cout<<"Q:"<<i<<" "<<x<<" "<<S.S[S.S[x].fail].len+1<<" "<<cnt<<endl;
			if (S.S[S.S[x].fail].len+1!=cnt){
				int l=S.S[S.S[x].fail].len+1,r=cnt;
				do{
					int mid=(l+r)>>1;
					if (DS::Query(DS::root[x],1,n,L+mid-1,R)) cnt=mid,l=mid+1;
					else r=mid-1;
				}
				while (l<=r);
			}
			Mtc[i]=cnt;
		}
		ll Ans=0;
		//for (int i=1;i<=m;i++) cout<<Mtc[i]<<" ";cout<<endl;
		for (int i=1;i<=T.nodecnt;i++) Ans=Ans+max(0,T.S[i].len-max(T.S[T.S[i].fail].len,Mtc[T.Pos[i]]));
		printf("%lld\n",Ans);
	}
	return 0;
}

void dfs_build(int x){
	for (int i=0,sz=TS[x].size();i<sz;i++){
		dfs_build(TS[x][i]);
		DS::root[x]=DS::Merge(DS::root[x],DS::root[TS[x][i]]);
	}
	return;
}
namespace DS{
	void Insert(int &x,int l,int r,int pos){
		if (x==0) x=++nodecnt;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) Insert(S[x].ls,l,mid,pos);
		else Insert(S[x].rs,mid+1,r,pos);
		return;
	}
	int Query(int x,int l,int r,int ql,int qr){
		//cout<<"Q:"<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
		if (ql>qr) return 0;
		if (x==0) return 0;if ((l==ql)&&(r==qr)) return 1;
		int mid=(l+r)>>1;
		if (qr<=mid) return Query(S[x].ls,l,mid,ql,qr);
		else if (ql>=mid+1) return Query(S[x].rs,mid+1,r,ql,qr);
		else return Query(S[x].ls,l,mid,ql,mid)|Query(S[x].rs,mid+1,r,mid+1,qr);
	}
	int Merge(int x,int y){
		if ((!x)||(!y)) return x+y;
		int u=++nodecnt;
		S[u].ls=Merge(S[x].ls,S[y].ls);S[u].rs=Merge(S[x].rs,S[y].rs);
		return u;
	}
	void outp(int x,int l,int r){
		if (x==0) return;
		if (l==r){
			return;
		}
		int mid=(l+r)>>1;
		outp(S[x].ls,l,mid);outp(S[x].rs,mid+1,r);return;
	}
}
