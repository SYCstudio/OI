#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int maxBit=30;
const int inf=2147483647;

int n,Seq[maxN],Log[maxN];
int lst[maxBit],L[maxN],R[maxN],Mx[maxBit][maxN];
ll Ans=0;

int GetMx(int l,int r);
void Solve(int l,int r);

int main(){
	for (int i=1;i<maxN;i++) Log[i]=log2(i);
	scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	mem(lst,0);
	for (int i=1;i<=n;i++){
		L[i]=0;
		for (int j=0;j<maxBit;j++)
			if (Seq[i]&(1<<j)) lst[j]=i;
			else L[i]=max(L[i],lst[j]+1);
	}
	for (int i=0;i<maxBit;i++) lst[i]=n+1;
	for (int i=n;i>=1;i--){
		R[i]=n+1;
		for (int j=0;j<maxBit;j++)
			if (Seq[i]&(1<<j)) lst[j]=i;
			else R[i]=min(R[i],lst[j]-1);
	}

	for (int i=1;i<=n;i++) Mx[0][i]=i;
	for (int i=1;i<maxBit;i++)
		for (int j=1;j+(1<<(i-1))<=n;j++)
			if (Seq[Mx[i-1][j]]>=Seq[Mx[i-1][j+(1<<(i-1))]]) Mx[i][j]=Mx[i-1][j];
			else Mx[i][j]=Mx[i-1][j+(1<<(i-1))];
	
	
	//for (int i=1;i<=n;i++) cout<<L[i]<<" "<<R[i]<<" "<<Lm[i]<<" "<<Rm[i]<<endl;

	Solve(1,n);
	printf("%lld\n",1ll*n*(n-1)/2-Ans);

	/*
	Ans=0;
	for (int l=1;l<=n;l++)
		for (int r=l;r<=n;r++){
			int mx=0,sum=0;
			for (int k=l;k<=r;k++) mx=max(mx,Seq[k]),sum|=Seq[k];
			if (sum>mx) Ans++;
		}
	printf("%lld\n",Ans);
	//*/
	return 0;
}

int GetMx(int l,int r){
	int lg=Log[r-l+1];
	if (Seq[Mx[lg][l]]>=Seq[Mx[lg][r-(1<<lg)+1]]) return Mx[lg][l];
	else return Mx[lg][r-(1<<lg)+1];
}

void Solve(int l,int r){
	if (l==r) return;
	if (l>r) return;
	int p=GetMx(l,r);
	//cout<<p<<" "<<l<<" "<<r<<" "<<L[p]<<" "<<R[p]<<":"<<(p-max(L[p],l)+1)*(min(R[p],r)-p+1)<<endl;
	Ans=Ans+1ll*(p-max(L[p],l)+1)*(min(R[p],r)-p+1)-1;
	Solve(l,p-1);Solve(p+1,r);
}
