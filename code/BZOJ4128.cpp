#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=70;
const ull base=13;
const int inf=2147483647;

int n,P;
class Matrix{
public:
	int M[maxN][maxN];
	ull GetHash(){
		ull ret=0;
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) ret=ret*base+(ull)M[i][j];
		return ret;
	}
	void Outp(){
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++)
				cout<<M[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
};

Matrix A,B;
map<ull,int> M;

Matrix Mul(Matrix A,Matrix B);

int main(){
	scanf("%d%d",&n,&P);
	for (int i=0;i<n;i++) for (int j=0;j<n;j++) scanf("%d",&A.M[i][j]);
	for (int i=0;i<n;i++) for (int j=0;j<n;j++) scanf("%d",&B.M[i][j]);

	int m=ceil(sqrt(P));
	Matrix now=B,T;M[now.GetHash()]=0;
	mem(T.M,0);for (int i=0;i<n;i++) T.M[i][i]=1;
	for (int i=1;i<=m;i++){
		now=Mul(now,A);T=Mul(T,A);
		M[now.GetHash()]=i;
		cout<<now.GetHash()<<endl;
		//cout<<i<<":"<<now.GetHash()<<endl;
		//now.Outp();
	}
	mem(now.M,0);
	bool getans=0;
	for (int i=0;i<n;i++) now.M[i][i]=1;
	for (int i=1;i<=m;i++){
		now=Mul(now,T);
		ull hs=now.GetHash();
		cout<<hs<<endl;
		if (M.count(hs)){
			ll Ans=i*m-M[hs];
			Ans=(Ans%P+P)%P;
			printf("%lld\n",Ans);break;
		}
	}

	return 0;
}

Matrix Mul(Matrix A,Matrix B){
	Matrix Ret;
	for (int i=0;i<n;i++) for (int j=0;j<=n;j++) Ret.M[i][j]=0;
	for (int k=0;k<n;k++)
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				Ret.M[i][j]=(Ret.M[i][j]+1ll*A.M[i][k]*B.M[k][j]%P)%P;
	return Ret;
}
/*
2 7
1 1
1 0
5 3
3 2
//*/
