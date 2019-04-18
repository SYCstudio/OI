#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

typedef long long ll;
typedef long double ld;
const int maxK=802000;
const int maxN=4;
const ld Pi=acos(-1);

class Complex{
public:
    ld x,y;
    Complex(){
	x=y=0;return;
    }
    Complex(ld a){
	x=a;y=0;return;
    }
    Complex(ld a,ld b){
	x=a;y=b;return;
    }
};
class Matrix{
public:
    int T[maxN][maxN];
    Matrix(){
	memset(T,0,sizeof(T));return;
    }
};

int n,K,L,X,Y,P,G;
int Dw[maxK];
Matrix Tr;
int A[maxK],B[maxK];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
ostream & operator << (ostream & os,Complex A);
void FFT(Complex *P,int N,int opt);
Matrix operator + (Matrix A,Matrix B);
Matrix operator * (Matrix A,int B);
Matrix operator * (Matrix A,Matrix B);
void GetG();
int QPow(int x,int cnt);
Matrix MPow(Matrix M,int cnt);
void Mul(int len,int *A,int *B);
int main(){
    scanf("%d%d%d%d%d%d",&n,&K,&L,&X,&Y,&P);GetG();
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&Tr.T[i][j]);
    Dw[0]=1;Dw[1]=QPow(G,(P-1)/K);
    for (int i=2;i<=K;i++) Dw[i]=1ll*Dw[i-1]*Dw[1]%P;

    Matrix Base,I;Base.T[1][X]=1;for (int i=1;i<=n;i++) I.T[i][i]=1;
    for (int i=0;i<=K+K;i++) A[i]=Dw[(K-(1ll*i*(i-1)/2)%K)%K];
    for (int i=0;i<K;i++) B[i]=1ll*Dw[(1ll*i*(i-1)/2)%K]*(Base*MPow(Tr*Dw[i]+I,L)).T[1][Y]%P;

    reverse(&B[0],&B[K+1]);int N=1;while (N<=K+K+K) N<<=1;
    //cout<<"A:";for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
    //for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
    Mul(N,A,B);int invk=QPow(K,P-2);
    //for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
    for (int i=0;i<K;i++){
	int mul=A[i+K];
	mul=1ll*mul*invk%P*Dw[(1ll*i*(i-1)/2)%K]%P;
	printf("%d\n",mul);
    }
    return 0;
}
Complex operator + (Complex A,Complex B){
    return ((Complex){A.x+B.x,A.y+B.y});
}
Complex operator - (Complex A,Complex B){
    return ((Complex){A.x-B.x,A.y-B.y});
}
Complex operator * (Complex A,Complex B){
    return ((Complex){A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x});
}
ostream & operator << (ostream & os,Complex A){
    os<<"("<<A.x<<","<<A.y<<")";return os;
}
void FFT(Complex *P,int N,int opt){
    static int _N,l,R[maxK];
    _N=N;l=-1;while (_N) _N>>=1,++l;for (int i=0;i<N;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(l-1));
    for (int i=0;i<N;i++) if (i<R[i]) swap(P[i],P[R[i]]);
    for (int i=1;i<N;i<<=1){
	Complex dw(cos(Pi/i),sin(Pi/i)*opt);
	for (int j=0;j<N;j+=(i<<1)){
	    Complex w(1,0);
	    for (int k=0;k<i;k++,w=w*dw){
		Complex X=P[j+k],Y=w*P[j+k+i];
		P[j+k]=X+Y;P[j+k+i]=X-Y;
	    }
	}
    }
    if (opt==-1){
	for (int i=0;i<N;i++) P[i].x=((ll)(P[i].x/N+0.5));
    }
    return;
}
Matrix operator + (Matrix A,Matrix B){
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) A.T[i][j]=(A.T[i][j]+B.T[i][j])%P;
    return A;
}
Matrix operator * (Matrix A,int B){
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) A.T[i][j]=1ll*A.T[i][j]*B%P;
    return A;
}
Matrix operator * (Matrix A,Matrix B){
    static Matrix Bp;for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Bp.T[i][j]=A.T[i][j],A.T[i][j]=0;
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) for (int k=1;k<=n;k++) A.T[i][j]=(A.T[i][j]+1ll*Bp.T[i][k]*B.T[k][j]%P)%P;
    return A;
}
void GetG(){
    int X=P-1;static int pri[1000],pcnt;
    for (int i=2;1ll*i*i<=X;i++)
	if (X%i==0){
	    pri[++pcnt]=i;while (X%i==0) X/=i;
	}
    if (X!=1) pri[++pcnt]=X;
    for (int g=1;;g++){
	bool flag=1;
	for (int i=1;i<=pcnt&&flag;i++) if (QPow(g,(P-1)/pri[i])==1) flag=0;
	if (flag){
	    G=g;return;
	}
    }
    return;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%P;
	x=1ll*x*x%P;cnt>>=1;
    }
    return ret;
}
Matrix MPow(Matrix A,int cnt){
    Matrix R;for (int i=1;i<=n;i++) R.T[i][i]=1;
    while (cnt){
	if (cnt&1) R=R*A;
	A=A*A;cnt>>=1;
    }
    return R;
}
void Mul(int len,int *A,int *B){
    static Complex a[maxK],b[maxK],c[maxK],d[maxK],e[maxK],f[maxK],g[maxK];
    int M=sqrt(P);
    for (int i=0;i<len;i++){
	a[i]=((Complex){A[i]%M,0});b[i]=((Complex){A[i]/M,0});
	c[i]=((Complex){B[i]%M,0});d[i]=((Complex){B[i]/M,0});
    }

    //cout<<"A:";for (int i=0;i<10;i++) cout<<A[i]<<" ";cout<<endl;
    //cout<<"B:";for (int i=0;i<10;i++) cout<<B[i]<<" ";cout<<endl;
    //cout<<"a:";for (int i=0;i<10;i++) cout<<a[i]<<" ";cout<<endl;
    //cout<<"b:";for (int i=0;i<10;i++) cout<<b[i]<<" ";cout<<endl;
    //cout<<"c:";for (int i=0;i<10;i++) cout<<c[i]<<" ";cout<<endl;
    //cout<<"d:";for (int i=0;i<10;i++) cout<<d[i]<<" ";cout<<endl;
    
    FFT(a,len,1);FFT(b,len,1);FFT(c,len,1);FFT(d,len,1);
    for (int i=0;i<len;i++) e[i]=a[i]*c[i],f[i]=a[i]*d[i]+b[i]*c[i],g[i]=b[i]*d[i];
    FFT(e,len,-1);FFT(f,len,-1);FFT(g,len,-1);

    //cout<<"e:";for (int i=0;i<10;i++) cout<<e[i]<<" ";cout<<endl;
    //cout<<"f:";for (int i=0;i<10;i++) cout<<f[i]<<" ";cout<<endl;
    //cout<<"g:";for (int i=0;i<10;i++) cout<<g[i]<<" ";cout<<endl;
    
    for (int i=0;i<len;i++){
	A[i]=((ll)e[i].x)%P;
	A[i]=(A[i]+1ll*(ll)f[i].x%P*M%P)%P;
	A[i]=(A[i]+1ll*(ll)g[i].x%P*M%P*M%P)%P;
    }
    return;
}
