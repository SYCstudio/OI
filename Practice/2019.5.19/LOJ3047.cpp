#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
typedef long double ld;
#define mp make_pair
#define ft first
#define sd second
const int maxN=101000;
const int maxM=25;

class Fraction{
public:
	ll a,b;
	Fraction(){
		a=0;b=1;return;
	}
	Fraction(ll x,ll y){
		if (y<0) x=-x,y=-y;
		a=x;b=y;return;
	}
	ld r(){
		return (ld)a/(ld)b;
	}
	ll ceil(){
		if (a<0) return a/b+((-a)%b>0);
		return a/b+(a%b>0);
	}
	ll floor(){
		if (a<0) return a/b-((-a)%b>0);
		return a/b;
	}
};

int n,m,Ans[maxN],Id[maxN];
ll A[maxN],B[maxN];
int St[maxN];
Fraction Crp[maxN];
pair<ll,int> Cov[maxN+maxN];

bool operator < (Fraction A,Fraction B);
bool operator <= (Fraction A,Fraction B);
bool kcmp(int a,int b);
Fraction Cross(int a,int b);
void Work(int kth);
int main(){
	scanf("%d%d",&n,&m);for (int i=1;i<=n;i++) scanf("%lld%lld",&A[i],&B[i]),Id[i]=i;
	sort(&Id[1],&Id[n+1],kcmp);memset(Ans,-1,sizeof(Ans));
	for (int i=1;i<=m;i++) Work(i);
	for (int i=1;i<=n;i++) printf("%d ",Ans[i]);printf("\n");
	return 0;
}
bool kcmp(int a,int b){
	if (A[a]==A[b]) return B[a]>B[b];
	return A[a]<A[b];
}
bool operator < (Fraction A,Fraction B){
	return (__int128)A.a*B.b<(__int128)B.a*A.b;
}
bool operator <= (Fraction A,Fraction B){
	return !(B<A);
}
Fraction Cross(int a,int b){
	return Fraction(B[b]-B[a],A[a]-A[b]);
}
void Work(int kth){
	int top=0;Crp[1]=Crp[0]=Fraction(0,1);
	for (int i=1;i<=n;i++)
		if (Ans[Id[i]]==-1&&A[Id[i]]>A[St[top]]){
			while (top&&Cross(Id[i],St[top]).floor()<Crp[top].ceil()) --top;
			St[++top]=Id[i];if (top>1) Crp[top]=Cross(St[top],St[top-1]);
		}
	Crp[top+1]=Fraction(1e18,1);
	int scnt=0;
	for (int i=1;i<=n;i++)
		if (Ans[i]>=1){
			int l=1,r=top-1,p=top;
			while (l<=r){
				int mid=(l+r)>>1;
				if (A[i]<=A[St[mid]]||Cross(i,St[mid])<=Crp[mid+1]) p=mid,r=mid-1;
				else l=mid+1;
			}
			if (A[i]<=A[St[p]]) Cov[++scnt]=mp(0,1);else Cov[++scnt]=mp(Cross(i,St[p]).floor()+1,1);
			l=2;r=top;p=1;
			while (l<=r){
				int mid=(l+r)>>1;
				if (A[i]>=A[St[mid]]||Crp[mid]<=Cross(i,St[mid])) p=mid,l=mid+1;
				else r=mid-1;
			}
			if (A[i]<A[St[p]]) Cov[++scnt]=mp(Cross(i,St[p]).ceil(),-1);
		}
	sort(&Cov[1],&Cov[scnt+1]);
	for (int i=1,sum=0,j=1;i<=top;i++){
		while (j<=scnt&&Cov[j].ft<=Crp[i].ceil()) sum+=Cov[j++].sd;
		if (sum<kth) Ans[St[i]]=kth;
		while (j<=scnt&&Cov[j].ft<=Crp[i+1].floor()){
			sum+=Cov[j++].sd;
			while (j<=scnt&&Cov[j].ft==Cov[j-1].ft) sum+=Cov[j++].sd;
			if (sum<kth) Ans[St[i]]=kth;
		}
	}
	return;
}
