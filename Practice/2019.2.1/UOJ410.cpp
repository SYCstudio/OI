#include "meetings.h"
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ls (x<<1)
#define rs (ls|1)
#define Min(x,y) x=min(x,y)

const int maxB=20;
const int maxN=750101;
const ll INF=1e18;

class Question
{
public:
	int l,r;
	ll Ans;
};
class SegmentTree
{
public:
	ll Lv[maxN<<2],Rv[maxN<<2],Pk[maxN<<2],Pb[maxN<<2],Pls[maxN<<2];
	void Cover(int x,int l,int r,ll K,ll B)
	{
		Lv[x]=K*l+B;
		Rv[x]=K*r+B;
		Pls[x]=0;
		Pk[x]=K;
		Pb[x]=B;
		return;
	}
	void Plus(int x,ll p)
	{
		Lv[x]+=p;
		Rv[x]+=p;
		Pls[x]+=p;
		return;
	}
	void Update(int x)
	{
		Lv[x]=Lv[ls];
		Rv[x]=Rv[rs];
		return;
	}
	void PushDown(int x,int l,int r,int mid)
	{
		if (Pk[x]||Pb[x]) {
			Cover(ls,l,mid,Pk[x],Pb[x]);
			Cover(rs,mid+1,r,Pk[x],Pb[x]);
			Pk[x]=Pb[x]=0;
		}
		if (Pls[x]) {
			Plus(ls,Pls[x]);
			Plus(rs,Pls[x]);
			Pls[x]=0;
		}
		return;
	}
	void Add(int x,int l,int r,int ql,int qr,ll p)
	{
		if (l==ql&&r==qr) {
			Plus(x,p);
			return;
		}
		int mid=(l+r)>>1;
		PushDown(x,l,r,mid);
		if (qr<=mid) Add(ls,l,mid,ql,qr,p);
		else if (ql>=mid+1) Add(rs,mid+1,r,ql,qr,p);
		else Add(ls,l,mid,ql,mid,p),Add(rs,mid+1,r,mid+1,qr,p);
		Update(x);
		return;
	}
	void Cover(int x,int l,int r,int ql,int qr,ll K,ll B)
	{
		if (l==ql&&r==qr) {
			ll lft=K*l+B,rht=K*r+B;
			if (lft>=Lv[x]&&rht>=Rv[x]) return;
			if (lft<=Lv[x]&&rht<=Rv[x]) {
				Cover(x,l,r,K,B);
				return;
			}
		}
		int mid=(l+r)>>1;
		PushDown(x,l,r,mid);
		if (qr<=mid) Cover(ls,l,mid,ql,qr,K,B);
		else if (ql>=mid+1) Cover(rs,mid+1,r,ql,qr,K,B);
		else Cover(ls,l,mid,ql,mid,K,B),Cover(rs,mid+1,r,mid+1,qr,K,B);
		Update(x);
		return;
	}
	ll Query(int x,int l,int r,int p)
	{
		if (l==r) return Lv[x];
		int mid=(l+r)>>1;
		PushDown(x,l,r,mid);
		if (p<=mid) return Query(ls,l,mid,p);
		else if (p>=mid+1) return Query(rs,mid+1,r,p);
	}
};

int n,Q;
Question Ot[maxN];
SegmentTree SL,SR;
int Mx[maxB][maxN],Mxp[maxB][maxN],Lg[maxN];
vector<int> Qid[maxN];

int Gm(int l,int r);
void Divide(int l,int r);

vector<long long> minimum_costs(vector<int> H,vector<int> L,vector<int> R)
{
	n=H.size();
	Q=L.size();
	for (int i=2; i<maxN; i++) Lg[i]=Lg[i>>1]+1;
	for (int i=1; i<=n; i++) Mx[0][i]=H[i-1],Mxp[0][i]=i;
	for (int i=1; i<maxB; i++)
		for (int j=1; j+(1<<i)-1<=n; j++)
			if (Mx[i-1][j]>=Mx[i-1][j+(1<<(i-1))]) Mx[i][j]=Mx[i-1][j],Mxp[i][j]=Mxp[i-1][j];
			else Mx[i][j]=Mx[i-1][j+(1<<(i-1))],Mxp[i][j]=Mxp[i-1][j+(1<<(i-1))];
	for (int i=1; i<=Q; i++) {
		Ot[i]=((Question) {
			L[i-1]+1,R[i-1]+1,INF
		});
		Qid[Gm(Ot[i].l,Ot[i].r)].push_back(i);
	}
	Divide(1,n);
	vector<ll> Rt;
	for (int i=1; i<=Q; i++) Rt.push_back(Ot[i].Ans);
	return Rt;
}

int Gm(int l,int r)
{
	int lg=Lg[r-l+1];
	if (Mx[lg][l]>=Mx[lg][r-(1<<lg)+1]) return Mxp[lg][l];
	else return Mxp[lg][r-(1<<lg)+1];
}
void Divide(int l,int r)
{
	if (l>r) return;
	int mid=Gm(l,r),key=Mx[0][mid];
	Divide(l,mid-1);
	Divide(mid+1,r);
	for (int i=0,sz=Qid[mid].size(); i<sz; i++) {
		int id=Qid[mid][i];
		//cout<<"("<<l<<" "<<r<<")"<<id<<endl;
		Ot[id].Ans=1ll*key*(Ot[id].r-Ot[id].l+1);
		//cout<<Ot[id].Ans<<endl;
		if (Ot[id].l<mid) Min(Ot[id].Ans,SL.Query(1,1,n,Ot[id].l)+1ll*key*(Ot[id].r-mid+1));
		if (Ot[id].r>mid) Min(Ot[id].Ans,SR.Query(1,1,n,Ot[id].r)+1ll*key*(mid-Ot[id].l+1));
	}
	ll tl=SL.Query(1,1,n,l),tr=SR.Query(1,1,n,r);
	SL.Add(1,1,n,l,mid,1ll*(r-mid+1)*key);
	SL.Cover(1,1,n,l,mid,-key,tr+1ll*(mid+1)*key);
	SR.Add(1,1,n,mid,r,1ll*(mid-l+1)*key);
	SR.Cover(1,1,n,mid,r,key,tl-1ll*(mid-1)*key);
	return;
}
