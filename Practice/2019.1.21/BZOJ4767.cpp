#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=1010000;
const int Mod=1e9+7;

class Point{
public:
	int x,y;
};

int n,Ex,Ey,Ax,Ay,Bx,By;
Point P[maxN];
int Fc[maxN],Ifc[maxN],F[maxN];

Point GET(int a,int b);
int QPow(int x,int cnt);
void Exgcd(int a,int b,int &x,int &y);
bool cmp(Point A,Point B);
int C(int n,int m);

int main(){
	Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fc[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	//for (int i=1;i<=5;i++) cout<<Fc[i]<<" "<<Ifc[i]<<endl;
	scanf("%d%d%d",&Ex,&Ey,&n);
	scanf("%d%d%d%d",&Ax,&Ay,&Bx,&By);
	Point R=GET(Ex,Ey);
	if (R.x<0){
		printf("0\n");return 0;
	}
	for (int i=1;i<=n;i++){
		int x,y;scanf("%d%d",&x,&y);
		P[i]=GET(x,y);
		if (P[i].x>R.x|P[i].y>R.y||P[i].x<0||P[i].y<0){
			--n;--i;continue;
		}
	}
	P[n+1]=R;
	sort(&P[1],&P[n+2],cmp);

	//for (int i=1;i<=n+1;i++) cout<<"("<<P[i].x<<","<<P[i].y<<")"<<endl;

	for (int i=1;i<=n+1;i++){
		F[i]=C(P[i].x+P[i].y,P[i].x);
		for (int j=1;j<i;j++)
			if (P[j].x<=P[i].x&&P[j].y<=P[i].y)
				F[i]=(F[i]-1ll*C(P[i].x-P[j].x+P[i].y-P[j].y,P[i].x-P[j].x)*F[j]%Mod+Mod)%Mod;
	}
	//for (int i=1;i<=n+1;i++) cout<<F[i]<<" ";cout<<endl;
	printf("%d\n",F[n+1]);return 0;
}
Point GET(int a,int b){
	int k2=(a*Ay-b*Ax)/(Bx*Ay-By*Ax),k1=Ax?((a-Bx*k2)/Ax):((b-By*k2)/Ay);
	if (k1*Ax+k2*Bx!=a||k1*Ay+k2*By!=b) return ((Point){-1,-1});
	return ((Point){k1,k2});
}
int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
bool cmp(Point A,Point B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
int C(int n,int m){
	//cout<<"C:"<<n<<" "<<m<<endl;
	if (n<0||m<0||n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
