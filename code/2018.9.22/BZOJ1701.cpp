#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int inf=2147483647;
const ll INF=1e18;

class Score
{
public:
	ll t,p;
};

int n;
Score S[maxN];
ll F[maxN],G[maxN],SumT[maxN],SumP[maxN];
int anscnt=0,Ans[maxN];

void SolveF(int l,int r,int sl,int sr);
void SolveG(int l,int r,int sl,int sr);
bool cmp(Score A,Score B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&S[i].t,&S[i].p);
	sort(&S[1],&S[n+1],cmp);
	for (int i=1;i<=n;i++) SumT[i]=SumT[i-1]+S[i].t,SumP[i]=SumP[i-1]+S[i].p;
	SolveF(1,n-1,1,n);SolveG(1,n-1,1,n);
	//cout<<"finish"<<endl;
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<G[i]<<" ";cout<<endl;
	for (int i=n;i>=1;i--) if (F[i]<G[i]) Ans[++anscnt]=n-i;
	printf("%d\n",anscnt);
	for (int i=1;i<=anscnt;i++) printf("%d\n",Ans[i]);
	return 0;
}

void SolveF(int l,int r,int sl,int sr){
	//cout<<"SolveF:"<<l<<" "<<r<<" "<<sl<<" "<<sr<<endl;
	if (l>r) return;
	int mid=(l+r)>>1,pos=sl;
	F[mid]=INF;
	for (int i=sl;i<=min(sr,mid);i++){
		ll t=SumP[mid]*S[i].t-SumT[mid]*S[i].p;
		if (t<F[mid]) F[mid]=t,pos=i;
	}
	SolveF(l,mid-1,sl,pos);SolveF(mid+1,r,pos,sr);
}

void SolveG(int l,int r,int sl,int sr){
	//cout<<"SolveG:"<<l<<" "<<r<<" "<<sl<<" "<<sr<<endl;
	if (l>r) return;
	int mid=(l+r)>>1,pos=sl;
	G[mid]=-INF;
	for (int i=sr;(i>mid)&&(i>=sl);i--){
		ll t=SumP[mid]*S[i].t-SumT[mid]*S[i].p;
		if (t>G[mid]) G[mid]=t,pos=i;
	}
	SolveG(l,mid-1,sl,pos);SolveG(mid+1,r,pos,sr);return;
}

bool cmp(Score A,Score B){
	return A.t*B.p>A.p*B.t;
}
