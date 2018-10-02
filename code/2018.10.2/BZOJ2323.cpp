#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int Mod=1e9+7;
const int inf=2147483647;

class Iriya
{
public:
	int M[2][2];
	Iriya & operator = (Iriya I){
		M[0][0]=I.M[0][0];M[0][1]=I.M[0][1];M[1][0]=I.M[1][0];M[1][1]=I.M[1][1];
		return *this;
	}
};

int n;
char Input[maxN];
Iriya F[maxN],Ten[maxN];

Iriya operator + (Iriya A,Iriya B);
Iriya operator * (Iriya A,Iriya B);
Iriya operator ^ (Iriya A,int cnt);
ostream & operator << (ostream &os,Iriya I);

int main(){
	scanf("%d",&n);scanf("%s",Input+1);
	Ten[0].M[0][0]=0;Ten[0].M[0][1]=Ten[0].M[1][0]=Ten[0].M[1][1]=1;
	for (int i=1;i<maxN;i++) Ten[i]=Ten[i-1]^10;

	F[0].M[0][0]=1;
	for (int i=1;i<=n;i++){
		Iriya now;now.M[0][0]=now.M[1][1]=1;now.M[0][1]=now.M[1][0]=0;
		for (int j=i;j>=1;j--){
			int x=Input[j]-'0';
			now=(Ten[i-j]^x)*now;
			F[i]=F[i]+F[j-1]*now;
		}
	}
	printf("%d\n",F[n].M[0][0]);return 0;
}

Iriya operator + (Iriya A,Iriya B){
	for (int i=0;i<2;i++) for (int j=0;j<2;j++) A.M[i][j]=(A.M[i][j]+B.M[i][j])%Mod;
	return A;
}

Iriya operator * (Iriya A,Iriya B){
	Iriya C;mem(C.M,0);
	for (int k=0;k<2;k++)
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				C.M[i][j]=(C.M[i][j]+1ll*A.M[i][k]*B.M[k][j]%Mod)%Mod;
	return C;
}

Iriya operator ^ (Iriya A,int cnt){
	Iriya Ret;Ret.M[0][0]=Ret.M[1][1]=1;Ret.M[0][1]=Ret.M[1][0]=0;
	while (cnt){
		if (cnt&1) Ret=Ret*A;
		A=A*A;cnt>>=1;
	}
	return Ret;
}

ostream & operator << (ostream & os,Iriya I){
	os<<I.M[0][0]<<" "<<I.M[0][1]<<endl<<I.M[1][0]<<" "<<I.M[1][1]<<endl;
	return os;
}
