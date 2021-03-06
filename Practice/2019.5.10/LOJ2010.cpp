#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<iostream>
#include<cassert>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
#define lb lower_bound
#define ub upper_bound
#define DEBUG(p) assert((p)>=1&&(p)<=n)
const int maxN=101000;

int n,Q;
int Key[maxN],Val[maxN],Opr[maxN];
set<pair<int,int> > St;

int Calc(int p);
void Replace(int p,int key);
int Query(int q,int p);
int Dist(int a,int b);
int main()
{
	scanf("%d%d",&n,&Q);
	memset(Val,-1,sizeof(Val));
	for (int i=1; i<=n; i++) {
		char c;
		scanf("%d %c",&Key[i],&c);
		if (c=='+') Opr[i]=1;
		else Opr[i]=2;
	}
	for (int i=1; i<=n; i++) Val[i]=Calc(i);

	for (int i=1,l=-1; i<=n; i++)
		if (Val[i]==0) {
			if (l==-1) l=i;
			if (i==n||Val[i+1]!=0) St.insert(mp(l,i)),l=-1;
		}

	while (Q--) {
		int opt;
		scanf("%d",&opt);
		if (opt==1) {
			int pos,num;
			char c;
			scanf("%d%d %c",&pos,&num,&c);
			++pos;
			Key[pos]=num;
			if (c=='+') Opr[pos]=1;
			else Opr[pos]=2;
			Replace(pos,Calc(pos));
			if (pos==n) Replace(1,Calc(1));
			else Replace(pos+1,Calc(pos+1));
		} else {
			int pos;
			scanf("%d",&pos);
			++pos;
			int val=Val[pos];
			Replace(pos,Key[pos]);
			int Ans=-1;
			for (int i=-5; i<=5; i++) Ans=max(Ans,Query(pos,pos+n/2+i));
			printf("%d\n",Ans);
			Replace(pos,val);
		}
	}
	return 0;
}
int Calc(int p)
{
	int pre=(p==1?n:p-1);
	if (Opr[p]==1) return (Key[p]+Key[pre])%10;
	else return Key[p]*Key[pre]%10;
}
void Replace(int p,int val)
{
	DEBUG(p);
	if (Val[p]==0) {
		if (Val[p-1]!=0&&Val[p+1]!=0) St.erase(mp(p,p));
		else if (Val[p-1]==0&&Val[p+1]!=0) {
			int l=(*--St.lb(mp(p,n+1))).ft;
			St.erase(mp(l,p));
			St.insert(mp(l,p-1));
			DEBUG(l);
			DEBUG(p-1);
		} else if (Val[p-1]!=0&&Val[p+1]==0) {
			int r=(*--St.lb(mp(p,n+1))).sd;
			St.erase(mp(p,r));
			St.insert(mp(p+1,r));
			DEBUG(r);
			DEBUG(p+1);
		} else {
			int l=(*--St.lb(mp(p,n+1))).ft,r=(*--St.lb(mp(p,n+1))).sd;
			St.erase(mp(l,r));
			St.insert(mp(l,p-1));
			St.insert(mp(p+1,r));
			DEBUG(l);
			DEBUG(r);
			DEBUG(p);
			DEBUG(p+1);
			DEBUG(p-1);
		}
	}

	Val[p]=val;
	if (Val[p]==0) {
		if (Val[p-1]!=0&&Val[p+1]!=0) St.insert(mp(p,p));
		else if (Val[p-1]==0&&Val[p+1]!=0) {
			int l=(*--St.lb(mp(p,n+1))).ft;
			St.erase(mp(l,p-1));
			St.insert(mp(l,p));
			DEBUG(l);
			DEBUG(p-1);
		} else if (Val[p-1]!=0&&Val[p+1]==0) {
			int r=(*St.lb(mp(p,n+1))).sd;
			St.erase(mp(p+1,r));
			St.insert(mp(p,r));
			DEBUG(r);
			DEBUG(p+1);
		} else {
			int l=(*--St.lb(mp(p,n+1))).ft,r=(*St.lb(mp(p,n+1))).sd;
			St.erase(mp(l,p-1));
			St.erase(mp(p+1,r));
			St.insert(mp(l,r));
			DEBUG(l);
			DEBUG(r);
			DEBUG(p+1);
			DEBUG(p-1);
		}
	}
	return;
}
int Query(int q,int p)
{
	p=(p+n-1)%n+1;
	int ret=-1,pl,pr,opt=0;
	DEBUG(p);
	if (Val[1]==0&&Val[n]==0) {
		if (St.size()==1) opt=2,St.erase(mp(1,n)),ret=max(ret,0);
		else {
			pl=(*St.begin()).sd;
			pr=(*--St.end()).ft;
			DEBUG(pl);
			DEBUG(pr);
			St.erase(mp(1,pl));
			St.erase(mp(pr,n));
			if (q<=pl||q>=pr) ret=max(ret,0);
			else ret=max(ret,min(Dist(pl,q),Dist(pr,q)));
			opt=1;
		}
	}
	if (!St.empty()) {
		set<pair<int,int> >::iterator it=St.lb(mp(p,n+1)),now=it;
		int c=0;
		if (now==St.end()) now=St.begin();
		for (c=0; c<=10; c++) {
			if (q>=(*now).ft&&q<=(*now).sd) ret=max(ret,0);
			else ret=max(ret,min(Dist((*now).ft,q),Dist((*now).sd,q)));
			++now;
			if (now==St.end()) now=St.begin();
		}
		now=it;
		if (now==St.end()) --now;
		for (c=0; c<=10; c++) {
			if (q>=(*now).ft&&q<=(*now).sd) ret=max(ret,0);
			else ret=max(ret,min(Dist((*now).ft,q),Dist((*now).sd,q)));
			if (now==St.begin()) now=St.end();
			--now;
		}
	}
	if (opt==2) St.insert(mp(1,n));
	else if (opt==1) St.insert(mp(1,pl)),St.insert(mp(pr,n));
	return ret;
}
int Dist(int a,int b)
{
	if (a<b) swap(a,b);
	return min(a-b,b+n-a);
}
