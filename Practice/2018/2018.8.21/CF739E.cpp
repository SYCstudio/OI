#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const ld eps=1e-11;
const int inf=2147483647;

class Data
{
public:
	ld key;int cnt;
};

int n,A,B;
ld P1[maxN],P2[maxN];
Data Ans,F[maxN][maxN];

void Calc(ld ex);
void Update(Data &A,Data B);
bool operator < (Data A,Data B);
Data operator + (Data A,Data B);

int main(){
	scanf("%d%d%d",&n,&A,&B);
	for (int i=1;i<=n;i++) scanf("%lf",&P1[i]);
	for (int i=1;i<=n;i++) scanf("%lf",&P2[i]);

	ld L=-1,R=1,pos=1;
	do{
		ld mid=(L+R)/2.0;
		Calc(mid);//cout<<"mid:"<<mid<<" "<<Ans.cnt<<endl;
		if (Ans.cnt>=B) pos=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);

	Calc(pos);
	printf("%.8lf\n",Ans.key+B*pos);
	return 0;
}

void Calc(ld ex){
	F[0][0]=Ans=((Data){0,0});
	for (int i=1;i<=n;i++)
		for (int j=0;j<=A;j++){
			F[i][j]=F[i-1][j];
			if (j!=0){
				Update(F[i][j],F[i-1][j-1]+((Data){P1[i],0}));
				Update(F[i][j],F[i-1][j-1]+((Data){1.0-(1.0-P1[i])*(1.0-P2[i])-ex,1}));
			}
			Update(F[i][j],F[i-1][j]+((Data){P2[i]-ex,1}));

			Update(Ans,F[i][j]);
		}
	return;
}

void Update(Data &A,Data B){
	if (A<B) A=B;return;
}

bool operator < (Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	return A.cnt<B.cnt;
}

Data operator + (Data A,Data B){
	return ((Data){A.key+B.key,A.cnt+B.cnt});
}
/*
50 50 50
1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000

0.129 0.937 0.854 0.452 0.261 0.337 0.610 0.264 0.833 0.511 0.562 0.564 0.101 0.194 0.306 0.721 0.046 0.956 0.029 0.004 0.317 0.720 0.745 0.104 0.842 0.328 0.526 0.429 0.062 0.891 0.270 0.509 0.943 0.129 0.937 0.854 0.129 0.937 0.854 0.129 0.937 0.854 0.129 0.937 0.854 0.129 0.937 0.854 0.129 0.937
//*/
