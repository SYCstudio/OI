#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=42;
const int maxT=130;
const int maxB=63;/////////////////////
class Mat
{
public:
	ll M[maxT][maxT];
	bool sum(ll K)
	{
		if (M[0][0]==-1||M[0][0]>=K) return 0;
		return 1;
	}
};
int n,m;
ll K;
Mat Pw[maxB],Tr,Bp;

Mat operator * (Mat A,Mat B);
void outp(Mat A);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d%lld",&n,&m,&K);
	K=K+n;
	for (int i=1; i<=m; i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if (w==1) ++Tr.M[u][v];
		if (w==2) ++Tr.M[u][v+n];
		if (w==3) ++Tr.M[u][v+n+n];
	}
	for (int i=1; i<=n; i++) ++Tr.M[i+n][i],++Tr.M[i+n+n][i+n],++Tr.M[i][0];
	Tr.M[0][0]=1;
	Pw[0]=Tr;
	//outp(Pw[0]);
	for (int i=1; i<maxB; i++) Pw[i]=Pw[i-1]*Pw[i-1];

	//for (int i=1;i<maxB;i++) outp(Pw[i]);
	ll Ans=0;
	mem(Tr.M,0);
	for (int i=1; i<=n; i++) Tr.M[0][i]=1;
	for (int i=maxB-1; i>=0; i--) {
		Bp=Tr*Pw[i];
		//cout<<i<<endl;
		//cout<<"BP:"<<endl;outp(Bp);
		//cout<<"TR:"<<endl;outp(Tr);
		//cout<<"PW:"<<endl;outp(Pw[i]);
		if (Bp.sum(K)) Tr=Bp,Ans|=(1ll<<i);
	}
	if ((Tr*Pw[0]).sum(K)) printf("-1\n");
	else printf("%lld\n",Ans);
	return 0;
}
Mat operator * (Mat A,Mat B)
{
	Mat C;
	mem(C.M,0);
	for (int i=0; i<=n+n+n; i++)
		for (int j=0; j<=n+n+n; j++)
			for (int k=0; k<=n+n+n; k++) {
				if (A.M[i][k]<0||B.M[k][j]<0) {
					C.M[i][j]=-1;
					break;
				} else {
					C.M[i][j]+=A.M[i][k]*B.M[k][j];
					if (C.M[i][j]<0) {
						C.M[i][j]=-1;
						break;
					}
				}
			}
	return C;
}
void outp(Mat A)
{
	for (int i=0; i<=n+n+n; i++) {
		for (int j=0; j<=n+n+n; j++)
			cout<<A.M[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}
