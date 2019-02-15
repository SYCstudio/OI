#include "seats.h"
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ls (x<<1)
#define rs (ls|1)
#define pb push_back
#define mp make_pair
#define ft first
#define sd second

const int maxN=1010000;
const int F1[]={0,0,1,-1};
const int F2[]={1,-1,0,0};
const int inf=2147483647;

int X[maxN],Y[maxN],n,m,N,Pls[maxN<<2],Pre[maxN];
vector<int> Mp[maxN];
pair<int,int> S[maxN<<2];

pair<int,int> operator + (pair<int,int> A,pair<int,int> B);
void Build(int x,int l,int r);
void Update(int x,int y,int opt);
void Add(int x,int k);
void PushDown(int x);
void Plus(int x,int l,int r,int ql,int qr,int k);

void give_initial_chart(int H,int W,vector<int> R,vector<int> C){
	n=H;m=W;N=n*m;
	for (int i=1;i<=n;i++) Mp[i].resize(m+2);
	for (int i=1,cnt=0;i<=n;i++) for (int j=1;j<=m;j++) ++cnt,X[cnt]=R[cnt-1]+1,Y[cnt]=C[cnt-1]+1,Mp[X[cnt]][Y[cnt]]=cnt;

	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			int mn1=inf,mn2=inf,key=Mp[i][j];
			for (int f=0;f<4;f++){
				int xx=i+F1[f],yy=j+F2[f];
				if (xx<=0||yy<=0||xx>n||yy>m) continue;
				if (Mp[xx][yy]<mn1) mn2=mn1,mn1=Mp[xx][yy];
				else if (Mp[xx][yy]<mn2) mn2=Mp[xx][yy];
			}
			if (mn2<=key-1) ++Pre[mn2],--Pre[key];
			int mn=N+1;
			if (i>1) mn=min(mn,Mp[i-1][j]);
			if (j>1) mn=min(mn,Mp[i][j-1]);
			if (mn-1>=key) ++Pre[key],--Pre[mn];
		}
	for (int i=1;i<=N;i++) Pre[i]+=Pre[i-1];
	
	Build(1,1,N);
	return;
}

int swap_seats(int a,int b){
	//cerr<<"swap:"<<a<<" "<<b<<endl;
	++a;++b;vector<pair<int,int> > P;
	P.pb(mp(X[a],Y[a]));P.pb(mp(X[b],Y[b]));
	for (int f=0;f<4;f++){
		int xx=X[a]+F1[f],yy=Y[a]+F2[f];
		if (xx<=0||yy<=0||xx>n||yy>m) continue;
		P.pb(mp(xx,yy));
	}
	for (int f=0;f<4;f++){
		int xx=X[b]+F1[f],yy=Y[b]+F2[f];
		if (xx<=0||yy<=0||xx>n||yy>m) continue;
		P.pb(mp(xx,yy));
	}
	//for (int i=0;i<P.size();i++) cout<<P[i].ft<<" "<<P[i].sd<<endl;
	sort(P.begin(),P.end());P.erase(unique(P.begin(),P.end()),P.end());
	for (int i=0;i<P.size();i++) Update(P[i].ft,P[i].sd,-1);
	swap(X[a],X[b]);swap(Y[a],Y[b]);
	Mp[X[a]][Y[a]]=a;Mp[X[b]][Y[b]]=b;

	/*
	  for (int i=1;i<=n;i++){
	  for (int j=1;j<=m;j++)
	  cout<<Mp[i][j]<<" ";
	  cout<<endl;
	  }
	//*/
	
	for (int i=0;i<P.size();i++) Update(P[i].ft,P[i].sd,1);
	return (S[1].ft!=1)?0:S[1].sd;
}
pair<int,int> operator + (pair<int,int> A,pair<int,int> B){
	pair<int,int> R=mp(min(A.ft,B.ft),0);
	if (R.ft==A.ft) R.sd+=A.sd;
	if (R.ft==B.ft) R.sd+=B.sd;
	return R;
}
void Build(int x,int l,int r){
	if (l==r){
		S[x]=mp(Pre[l],1);return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);Build(rs,mid+1,r);
	S[x]=S[ls]+S[rs];
	return;
}
void Update(int x,int y,int opt){
	int mn1=inf,mn2=inf,key=Mp[x][y];
	for (int f=0;f<4;f++){
		int xx=x+F1[f],yy=y+F2[f];
		if (xx<=0||yy<=0||xx>n||yy>m) continue;
		if (Mp[xx][yy]<mn1) mn2=mn1,mn1=Mp[xx][yy];
		else if (Mp[xx][yy]<mn2) mn2=Mp[xx][yy];
	}
	if (mn2<=key-1) Plus(1,1,N,mn2,key-1,opt);
	int mn=N+1;
	if (x>1) mn=min(mn,Mp[x-1][y]);
	if (y>1) mn=min(mn,Mp[x][y-1]);
	if (mn-1>=key) Plus(1,1,N,key,mn-1,opt);
	//cout<<"Update:"<<x<<" "<<y<<" "<<opt<<" ["<<mn2<<","<<key-1<<"] ["<<key<<","<<mn-1<<"]"<<endl;
	return;
}
void Add(int x,int k){
	Pls[x]+=k;S[x].ft+=k;
	return;
}
void PushDown(int x){
	if (Pls[x]){
		Add(ls,Pls[x]);Add(rs,Pls[x]);
		Pls[x]=0;
	}
	return;
}
void Plus(int x,int l,int r,int ql,int qr,int k){
	if (l==ql&&r==qr){
		Add(x,k);return;
	}
	int mid=(l+r)>>1;PushDown(x);
	if (qr<=mid) Plus(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Plus(rs,mid+1,r,ql,qr,k);
	else Plus(ls,l,mid,ql,mid,k),Plus(rs,mid+1,r,mid+1,qr,k);
	S[x]=S[ls]+S[rs];return;
}
