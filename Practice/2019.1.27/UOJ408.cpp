#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<iostream>
#include "doll.h"
using namespace std;

const int maxN=202000<<1;

int n,m,N,limit;
int In[maxN],Rader[maxN],P[maxN],O[maxN],nodecnt;
int X[maxN],Y[maxN];

void Divide(int l,int r,int x);

void create_circuit(int M,vector<int> A){
	if (A.size()==1){
		vector<int> R,Rc;
		Rc.push_back(A[0]);for (int i=1;i<=M;i++) Rc.push_back(0);
		answer(Rc,R,R);return;
	}
	n=A.size();m=M;
	for (int i=0;i<n;i++) In[i]=A[i];In[++n]=0;
	N=1;int L=0;while (N<=n) N<<=1,++L;
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) P[i]=i;
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);

	limit=N-n-1;//cout<<limit<<endl;
	for (int i=0,j=0;i<n;i++){
		while (P[j]<=limit) ++j;
		O[P[j]]=In[i];++j;
	}
	//for (int i=0;i<N;i++) cout<<O[i]<<" ";cout<<endl;
	Divide(0,N-1,++nodecnt);

	//for (int i=1;i<=nodecnt;i++) cout<<X[i]<<" ";cout<<endl;
	//for (int i=1;i<=nodecnt;i++) cout<<Y[i]<<" ";cout<<endl;

	vector<int> Rx,Ry,Rc;
	for (int i=0;i<=m;i++) Rc.push_back(-1);
	for (int i=1;i<=nodecnt;i++) Rx.push_back(X[i]),Ry.push_back(Y[i]);
	answer(Rc,Rx,Ry);return;
}

void Divide(int l,int r,int x){
	int mid=(l+r)>>1,ls=-1,rs=-1;
	if (l<=mid){
		if (mid<=limit) X[x]=-1;
		else if (l==mid) X[x]=O[l];
		else ls=++nodecnt,X[x]=-ls;
	}
	else X[x]=-1;
	if (mid+1<=r){
		if (r<=limit) Y[x]=-1;
		else if (mid+1==r) Y[x]=O[r];
		else rs=++nodecnt,Y[x]=-rs;
	}
	else Y[x]=-1;
	//cout<<mid<<" "<<mid+1<<" "<<n<<endl;
	//cout<<"("<<l<<" "<<r<<")"<<x<<" "<<X[x]<<" "<<Y[x]<<endl;
	if (ls!=-1) Divide(l,mid,ls);
	if (rs!=-1) Divide(mid+1,r,rs);
	return;
}
