#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ft first
#define sd second
#define mp make_pair

const int maxN=1010;
const int Mod=998244353;
const int Id[3][3]={{0,1,2},
		    {3,4,5},
		    {6,7,8}};
class Matrix{
public:
    int M[9][9];
    Matrix(){
	memset(M,0,sizeof(M));return;
    }
};

ll n;
int X,C;
pair<ll,int> Cd[maxN];
Matrix T[maxN],pw[70];

void Plus(int &x,int y);
Matrix operator * (Matrix A,Matrix B);
Matrix Mul(ll L);
int main(){
    scanf("%lld%d%d",&n,&C,&X);
    for (int i=1;i<=X;i++) scanf("%lld%d",&Cd[i].ft,&Cd[i].sd);
    sort(&Cd[1],&Cd[X+1]);
    for (int i=C;i>=0;i--){
	T[i]=T[i+1];
	for (int j=0;j<9;j++) if (i>=j%3+j/3) ++T[i].M[j][j%3*3+(i-j%3-j/3)%3];
    }
    pw[0]=T[0];for (int i=1;i<70;i++) pw[i]=pw[i-1]*pw[i-1];
    ll lst=0;Matrix Ans;Ans.M[0][0]=1;
    for (int i=1;i<=X;i++){
	Ans=Ans*Mul(Cd[i].ft-lst-1);lst=Cd[i].ft;
	Ans=Ans*T[Cd[i].sd];
    }
    Ans=Ans*Mul(n-Cd[X].ft);
    printf("%d\n",Ans.M[0][0]);return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
Matrix operator * (Matrix A,Matrix B){
    Matrix C;
    for (int i=0;i<9;i++)
	for (int j=0;j<9;j++){
	    unsigned long long sum=0;
	    for (int k=0;k<9;k++) sum+=1ll*A.M[i][k]*B.M[k][j];
	    C.M[i][j]=sum%Mod;
	}
    return C;
}
Matrix Mul(ll L){
    Matrix ret;for (int i=0;i<9;i++) ret.M[i][i]=1;
    for (int i=63;i>=0;i--) if ((L>>i)&1) ret=ret*pw[i];
    return ret;
}
