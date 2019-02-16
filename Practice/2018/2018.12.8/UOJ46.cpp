#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class Data
{
public:
	int a,b,t;
	Data(){
		a=1;b=0;t=0;return;
	}
	Data(int x,int y,int z){
		a=x;b=y;t=z;return;
	}
};

class SegmentData
{
public:
	int ls,rs;vector<pair<int,Data> > V;
};

int n,m;
int Rt[maxN],Sz[maxN],rcnt=0,scnt=0;
SegmentData S[maxN*50];
int Seq[maxN];

Data operator + (Data A,Data B);
SegmentData Merge(int u,int v);
Data Query(int now,int l,int r,int ql,int qr,int pos);

int main(){
	int Key;scanf("%d",&Key);
	scanf("%d%d",&n,&m);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	int Q,lst=0;scanf("%d",&Q);
	for (int qi=1;qi<=Q;qi++){
		//cerr<<qi<<endl;
		int opt;scanf("%d",&opt);
		if (opt==1){
			int l,r,a,b;scanf("%d%d%d%d",&l,&r,&a,&b);
			if (Key&1) l^=lst,r^=lst;
			Rt[++rcnt]=++scnt;Sz[rcnt]=1;
			if (l!=1) S[Rt[rcnt]].V.push_back(make_pair(1,((Data){1,0,qi})));
			S[Rt[rcnt]].V.push_back(make_pair(l,((Data){a,b,qi})));
			if (r+1<=n) S[Rt[rcnt]].V.push_back(make_pair(r+1,((Data){1,0,qi})));
			while ((rcnt>1)&&(Sz[rcnt]==Sz[rcnt-1])){
				S[++scnt]=Merge(Rt[rcnt-1],Rt[rcnt]);
				Sz[rcnt-1]+=Sz[rcnt];--rcnt;Rt[rcnt]=scnt;
			}
		}
		if (opt==2){
			int l,r,p;scanf("%d%d%d",&l,&r,&p);
			if (Key&1) l^=lst,r^=lst,p^=lst;
			Data R;
			for (int i=1,sl=1,sr;i<=rcnt;i++){
				sr=sl+Sz[i]-1;
				//cerr<<sl<<" "<<sr<<" "<<Rt[i]<<endl;
				if ((r<sl)||(l>sr));
				else R=R+Query(Rt[i],sl,sr,max(l,sl),min(r,sr),p);
				sl=sr+1;
			}
			printf("%d\n",lst=(1ll*Seq[p]*R.a%m+R.b)%m);
		}
	}
	return 0;
}

Data operator + (Data A,Data B){
	if (A.t>B.t) swap(A,B);
	return ((Data){1ll*A.a*B.a%m,(1ll*A.b*B.a%m+B.b)%m,B.t});
}

SegmentData Merge(int u,int v){
	SegmentData R;R.ls=u;R.rs=v;R.V.clear();
	int sz1=S[u].V.size(),sz2=S[v].V.size();
	//for (int i=0;i<sz1;i++) cout<<S[u].V[i].first<<" ("<<S[u].V[i].second.a<<","<<S[u].V[i].second.b<<") ";cout<<endl;
	//for (int i=0;i<sz2;i++) cout<<S[v].V[i].first<<" ("<<S[v].V[i].second.a<<","<<S[v].V[i].second.b<<") ";cout<<endl;
	for (int p1=0,p2=0;(p1<sz1)||(p2<sz2);){
		//cout<<p1<<" "<<p2<<endl;
		if (p1==sz1) R.V.push_back(make_pair(S[v].V[p2].first,S[u].V[p1-1].second+S[v].V[p2].second)),++p2;
		else if (p2==sz2) R.V.push_back(make_pair(S[u].V[p1].first,S[u].V[p1].second+S[v].V[p2-1].second)),++p1;
		else if (S[u].V[p1].first==S[v].V[p2].first) R.V.push_back(make_pair(S[u].V[p1].first,S[u].V[p1].second+S[v].V[p2].second)),++p1,++p2;
		else if (S[u].V[p1].first<S[v].V[p2].first) R.V.push_back(make_pair(S[u].V[p1].first,S[u].V[p1].second+S[v].V[p2-1].second)),++p1;
		else R.V.push_back(make_pair(S[v].V[p2].first,S[u].V[p1-1].second+S[v].V[p2].second)),++p2;
	}
	//cout<<"G:";for (int i=0,sz=R.V.size();i<sz;i++) cout<<R.V[i].first<<" ("<<R.V[i].second.a<<","<<R.V[i].second.b<<") ";cout<<endl;
	return R;
}

Data Query(int now,int l,int r,int ql,int qr,int pos){
	//cerr<<"Q:"<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<now<<endl;
	if ((l==ql)&&(r==qr)){
		int l=0,r=S[now].V.size()-1,p;
		do{
			int mid=(l+r)>>1;
			if (S[now].V[mid].first<=pos) p=mid,l=mid+1;
			else r=mid-1;
		}
		while (l<=r);
		return S[now].V[p].second;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[now].ls,l,mid,ql,qr,pos);
	else if (ql>=mid+1) return Query(S[now].rs,mid+1,r,ql,qr,pos);
	else return Query(S[now].ls,l,mid,ql,mid,pos)+Query(S[now].rs,mid+1,r,mid+1,qr,pos);
}
