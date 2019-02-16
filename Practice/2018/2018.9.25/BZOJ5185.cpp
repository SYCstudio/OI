#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxK=110;
const int inf=2147483647;

class Range
{
public:
	int l,r;
};

int n,K;
Range Rg[maxN],R[maxN];
int F[maxN][maxK];

bool cmp1(Range A,Range B);
bool cmp2(Range A,Range B);

int main(){
	//freopen("in.in","r",stdin);
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d%d",&Rg[i].l,&Rg[i].r);
	sort(&Rg[1],&Rg[n+1],cmp1);
	int rcnt=0;
	for (int i=1,nowr=0;i<=n;i++)
		if (Rg[i].r>nowr) R[++rcnt]=Rg[i],nowr=Rg[i].r;
		else K--;

	K=max(K,0);
	n=rcnt;
	sort(&R[1],&R[n+1],cmp2);

	//cout<<n<<" "<<K<<endl;
	mem(F,128);
	F[0][0]=0;
	for (int i=1,p=1;i<=n;i++){
		while ((p<=i)&&(R[p].r<R[i].l)) p++;
		//cout<<i<<":"<<p<<endl;
		for (int j=0;j<=K;j++){
			if (j!=0) F[i][j]=max(F[i][j],F[i-1][j-1]);
			if (j==K) F[i][j]=max(F[i][j],F[i-1][j]);
			if (i!=p) F[i][min(j+(i-p-1),K)]=max(F[i][min(j+(i-p-1),K)],F[p][j]+R[i].r-R[p].r);
			F[i][min(j+(i-p-1)+1,K)]=max(F[i][min(j+(i-p-1)+1,K)],F[p-1][j]+R[i].r-R[i].l);
		}
	}
	/*
	for (int i=1;i<=n;i++){
		for (int j=0;j<=K;j++)
			cout<<F[i][j]<<" ";cout<<endl;
	}
	//*/
	
	printf("%d\n",F[n][K]);return 0;
}

bool cmp1(Range A,Range B){
	if (A.l!=B.l) return A.l<B.l;
	else return A.r>B.r;
}

bool cmp2(Range A,Range B){
	return A.l<B.l;
}
