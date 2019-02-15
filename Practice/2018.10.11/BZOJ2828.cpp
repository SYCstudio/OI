#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int maxM=maxN*8;
const int Key[10]={119,96,62,124,105,93,95,100,127,125};
const int inf=2147483647;
const int meminf=1061109567;

int L,p1,q1,p2,q2,p3,q3;
char I1[maxN],I2[maxN];
int F[maxN][maxM];
int add[10][10],del[10][10];

int Calc(int n1,int n2,int n3);

int main(){
	scanf("%d",&L);
	scanf("%s",I1+1);scanf("%s",I2+1);
	for (int i=1;i<=L;i++) I1[i]-='0',I2[i]-='0';
	scanf("%d%d%d%d%d%d",&p1,&q1,&p2,&q2,&p3,&q3);

	mem(F,63);
	F[0][0]=0;
	for (int i=0;i<=9;i++)
		for (int j=0;j<=9;j++)
			for (int k=0;k<=6;k++){
				if ((Key[i]&(1<<k)) && ((Key[j]&(1<<k))==0) ) del[i][j]++;
				if ( ((Key[i]&(1<<k))==0) && (Key[j]&(1<<k)) ) add[i][j]++;
			}

	for (int i=1;i<=L;i++)
		for (int j=0;j<=i*8;j++)
			for (int k=0;k<=9;k++)
				if (j-add[I1[i]][k]-add[I2[i]][k]>=0) F[i][j]=min(F[i][j],F[i-1][j-add[I1[i]][k]-add[I2[i]][k]]+del[I1[i]][k]+del[I2[i]][k]);

	int Ans=inf;
	for (int i=0;i<=L*8;i++)
		if (F[L][i]!=meminf){
			for (int j=0;j<=min(i,F[L][i]);j++)
				Ans=min(Ans,Calc(i-j,F[L][i]-j,j));
		}
	printf("%d\n",Ans);
}

int Calc(int n1,int n2,int n3){
	return q1*n1+q2*n2+q3*n3+n1*(n1+1)/2*p1+n2*(n2+1)/2*p2+n3*(n3+1)/2*p3;
}
