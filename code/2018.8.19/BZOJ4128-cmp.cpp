#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<cmath>
#include<vector>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline
#define RG register

const int maxN=70;
const int maxNum=300;
const int inf=2147483647;

int n,P;
class Matrix{
public:
	int M[maxN][maxN];
	Matrix & operator = (const Matrix A){
		for (int i=0;i<n;i++) for (int j=0;j<n;j++) M[i][j]=A.M[i][j];
		return *this;
	}
	
	void Outp(){
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++) cout<<M[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
		return;
	}
};

Matrix A,B,C,T,now,Hash[maxNum];

Matrix Mul1(const Matrix A,const Matrix B);
Matrix QPow(RG Matrix A,RG int cnt);
Matrix Mul2(const Matrix A,const Matrix B);
bool Equ(const Matrix A,const Matrix B);

int main(){
	//freopen("2.in","r",stdin);
	scanf("%d%d",&n,&P);
	RG int i,j;
	for (i=0;i<n;++i) for (j=0;j<n;++j) scanf("%d",&A.M[i][j]);
	for (i=0;i<n;++i) for (j=0;j<n;++j) scanf("%d",&B.M[i][j]);

	for (i=0;i<n;++i) C.M[0][i]=rand()%P;
	//cout<<"C:";for (int i=0;i<n;i++) cout<<C.M[0][i]<<" ";cout<<endl;

	RG int m=ceil(sqrt(P));
	now=B;Hash[0]=Mul2(C,now);
	
	for (i=1;i<=m;++i){
		now=Mul1(now,A);Hash[i]=Mul2(C,now);
		//now.Outp();
	}

	/*
	for (int i=0;i<=m;i++){
		for (int j=0;j<n;j++) cout<<Hash[i].M[0][j]<<" ";
		cout<<endl;
	}
	//*/
	
	T=QPow(A,m);
	
	for (i=1;i<=m;++i){
		C=Mul2(C,T);
		for (j=m-1;j>=0;j--) if (Equ(C,Hash[j])){
			printf("%d\n",((i*m-j)%P+P)%P);break;
		}
		//*/
	}

	return 0;
}

Matrix Mul1(const Matrix A,const Matrix B){
	RG Matrix Ret;
	RG int i,j,k;
	for (i=0;i<n;++i)
		for (j=0;j<n;++j){
			Ret.M[i][j]=0;
			for (k=0;k<n;++k)
				Ret.M[i][j]=(Ret.M[i][j]+A.M[i][k]*B.M[k][j])%P;
		}
	return Ret;
}

Matrix Mul2(const Matrix A,Matrix B){
	RG Matrix Ret;RG int i,j,k;
	for (i=0;i<n;++i) Ret.M[0][i]=0;
	for (j=0;j<n;++j){
		Ret.M[0][j]=0;
		for (k=0;k<n;++k)
			Ret.M[0][j]=(Ret.M[0][j]+A.M[0][k]*B.M[k][j])%P;
	}
	return Ret;
}

Matrix QPow(RG Matrix W,RG int cnt){
	RG Matrix Ret;RG int i;
	for (i=0;i<n;++i) Ret.M[i][i]=1;
	while (cnt){
		if (cnt&1) Ret=Mul1(Ret,W);
		W=Mul1(W,W);cnt>>=1;
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



