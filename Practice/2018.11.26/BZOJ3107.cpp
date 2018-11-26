#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=32;
const int inf=2147483647;
const int meminf=2130706432;

int A,B,C;
int cntA,cntB,cntC,mxw;
int F[maxN][maxN][maxN][maxN][2];

void Min(int &x,int y);

int main(){
	scanf("%d%d%d",&A,&B,&C);
	int mx=max(max(A,B),C);
	while (mx) ++mxw,mx>>=1;
	while (A) cntA+=(A&1),A>>=1;
	while (B) cntB+=(B&1),B>>=1;
	while (C) cntC+=(C&1),C>>=1;
	//cout<<mxw<<" "<<cntA<<" "<<cntB<<endl;
	mem(F,127);
	F[0][0][0][0][0]=0;
	for (int i=0;i<mxw;i++)
		for (int a=0;a<=min(i,cntA);a++)
			for (int b=0;b<=min(i,cntB);b++)
				for (int c=0;c<=min(i,cntC);c++)
					for (int f=0;f<2;f++)
						if (F[i][a][b][c][f]<=meminf){
							int key=F[i][a][b][c][f];
							Min(F[i+1][a][b][c+f][0],key+(f<<i));
							if (a!=cntA){
								if (f==0) Min(F[i+1][a+1][b][c+1][0],key+(1<<i));
								else Min(F[i+1][a+1][b][c][1],key);
							}
							if (b!=cntB){
								if (f==0) Min(F[i+1][a][b+1][c+1][0],key+(1<<i));
								else Min(F[i+1][a][b+1][c][1],key);
							}
							if ((a!=cntA)&&(b!=cntB)){
								if (f==0) Min(F[i+1][a+1][b+1][c][1],key);
								else Min(F[i+1][a+1][b+1][c+1][1],key+(1<<i));
							}
						}
	if (F[mxw][cntA][cntB][cntC][0]>meminf) printf("-1\n");
	else printf("%d\n",F[mxw][cntA][cntB][cntC][0]);
	return 0;
}

void Min(int &x,int y){
	if (y<x) x=y;return;
}
