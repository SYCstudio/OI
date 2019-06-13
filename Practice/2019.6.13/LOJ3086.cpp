#include<bits/stdc++.h>
using namespace std;

const int maxM=6;
const int Mod=1e9+7;
const int TM[6][6]={{1,1,1,1,1,0},
		    {1,0,0,0,0,0},
		    {0,0,0,1,1,0},
		    {0,0,1,0,1,0},
		    {0,0,0,0,1,1},
		    {0,0,0,0,1,0}};

int n;
int M1[maxM][maxM],M2[maxM][maxM],Bp[maxM][maxM];

void Mul1();
void Mul2();
int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
	scanf("%d",&n);memset(M1,0,sizeof(M1));memset(M2,0,sizeof(M2));
	M1[0][0]=1;int N=n;
	for (int i=0;i<6;i++) for (int j=0;j<6;j++) M2[i][j]=TM[i][j];
	while (n){
	    if (n&1) Mul1();Mul2();n>>=1;
	}
	int Ans=M1[0][4];
	Ans=(Ans-1ll*M1[0][0]*N%Mod+Mod)%Mod;
	printf("%d\n",Ans);
    }
    return 0;
}
void Mul1(){
    for (int i=0;i<6;i++) Bp[0][i]=M1[0][i],M1[0][i]=0;
    for (int j=0;j<6;j++){
	unsigned long long sum=0;
	for (int k=0;k<6;k++) sum+=1ll*Bp[0][k]*M2[k][j];
	M1[0][j]=sum%Mod;
    }
    return;
}
void Mul2(){
    for (int i=0;i<6;i++) for (int j=0;j<6;j++) Bp[i][j]=M2[i][j],M2[i][j]=0;
    for (int i=0;i<6;i++)
	for (int j=0;j<6;j++){
	    unsigned long long sum=0;
	    for (int k=0;k<6;k++) sum+=1ll*Bp[i][k]*Bp[k][j];
	    M2[i][j]=sum%Mod;
	}
    return;
}
