#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<cmath>
#include<vector>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline
#define RG register

const int maxN=70;
const ull base=13;
const int Mod=20000007;
const int maxNum=300;
const int inf=2147483647;

int n,P;
class Matrix{
public:
	int M[maxN][maxN];
	IL ull GetHash(){
		RG ull ret=0;RG int i,j;
		for (i=0;i<n;++i) for (j=0;j<n;++j) ret=ret*base+(ull)M[i][j];
		return ret;
	}
};

Matrix A,B,C,T,now,Hash[maxNum];

IL Matrix Mul1(const Matrix A,const Matrix B);
IL Matrix QPow(RG Matrix A,RG int cnt);
Matrix Mul2(const Matrix A,const Matrix B);
bool Equ(const Matrix A,const Matrix B);

int main(){
	//freopen("2.in","r",stdin);
	scanf("%d%d",&n,&P);
	RG int i,j;
	for (i=0;i<n;++i) for (j=0;j<n;++j) scanf("%d",&A.M[i][j]);
	for (i=0;i<n;++i) for (j=0;j<n;++j) scanf("%d",&B.M[i][j]);

	for (i=0;i<n;++i) C.M[0][i]=rand()%P;

	RG int m=ceil(sqrt(P));
	now=B;Hash[0]=Mul2(now,C);
	
	for (i=1;i<=m;++i){
		now=Mul1(now,A);Hash[i]=Mul2(now,C);
	}

	for (int i=0;i<=m;i++){
		for (int j=0;j<n;j++) cout<<Hash[i].M[0][j]<<" ";
		cout<<endl;
	}
	
	T=QPow(A,m);
	
	for (i=1;i<=m;++i){
		C=Mul2(T,C);
		for (j=m;j>=0;j--) if (Equ(C,Hash[j])){
			printf("%d\n",((i*m-j)%P+P)%P);break;
		}
		//*/
	}

	return 0;
}

IL Matrix Mul1(const Matrix A,const Matrix B){
	RG Matrix Ret;
	RG int i,j,k;
	for (i=0;i<n;++i) for (j=0;j<=n;++j) Ret.M[i][j]=0;
	for (i=0;i<n;++i)
		for (j=0;j<n;++j)
			for (k=0;k<n;++k)
				Ret.M[i][j]=(Ret.M[i][j]+1ll*A.M[i][k]*B.M[k][j]%P)%P;
	return Ret;
}

Matrix Mul2(const Matrix A,Matrix B){
	RG Matrix Ret;RG int i,j,k;
	for (i=0;i<n;++i) Ret.M[0][i]=0;
	for (k=0;k<n;++k)
		for (i=0;i<1;++i)
			for (j=0;j<n;++j)
				Ret.M[i][j]=(Ret.M[i][j]+1ll*A.M[i][k]*B.M[k][j]%P)%P;
	return Ret;
}

IL Matrix QPow(RG Matrix A,RG int cnt){
	RG Matrix Ret;RG int i;
	for (i=0;i<n;++i) Ret.M[i][i]=1;
	while (cnt){
		if (cnt&1) Ret=Mul1(Ret,A);
		A=Mul1(A,A);cnt>>=1;
	}
	return Ret;
}

bool Equ(Matrix A,Matrix B){
	for (int i=0;i<n;i++) if (A.M[0][i]!=B.M[0][i]) return 0;
	return 1;
}

/*
2 7
1 1
1 0
5 3
3 2
//*/

