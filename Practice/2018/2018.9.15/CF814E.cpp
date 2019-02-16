#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=52;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
int Dg[maxN];
int F[2][maxN][maxN][maxN][maxN];

void Plus(int &x,int y);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Dg[i]);
	if (Dg[1]+1>n){
		printf("0\n");return 0;
	}
	if (Dg[1]==2){
		if (Dg[2]==2) F[2&1][1][0][1][0]=1;
		else F[2&1][1][0][0][1]=1;
	}
	else{
		if (Dg[2]==2) F[2&1][0][1][1][0]=1;
		else F[2&1][0][1][0][1]=1;
	}
	for (int i=2;i<n;i++){
		int now=i&1;
		mem(F[now^1],0);
		for (int a=0;a<=i;a++)
			for (int b=0;a+b<=i;b++)
				for (int c=0;c+a+b<=i;c++)
					for (int d=0;a+b+c+d<=i;d++){
						//cout<<"("<<i<<','<<a<<','<<b<<','<<c<<','<<d<<") "<<F[now][a][b][c][d]<<endl;
						if (F[now][a][b][c][d]){
							int key=F[now][a][b][c][d];
							//if ((a==0)&&(b==0)) Plus(F[now][c][d][0][0],key);
							if (a>=1){
								if (Dg[i+1]==2){
									if (c>=1) Plus(F[now^1][a-1][b][c-1][d],1ll*key*a%Mod*c%Mod);
									if (d>=1) Plus(F[now^1][a-1][b][c+1][d-1],1ll*key*a%Mod*d%Mod);
									Plus(F[now^1][a-1][b][c+1][d],1ll*key*a%Mod);
								}
								else{
									if (c>=2) Plus(F[now^1][a-1][b][c-2][d],1ll*c*(c-1)/2%Mod*key%Mod*a%Mod);
									if (c>=1) Plus(F[now^1][a-1][b][c][d],1ll*key*a%Mod*c%Mod);
									if (d>=2) Plus(F[now^1][a-1][b][c+2][d-2],1ll*d*(d-1)/2%Mod*key%Mod*a%Mod);
									if (d>=1) Plus(F[now^1][a-1][b][c+2][d-1],1ll*key*a%Mod*d%Mod);
									if ((c>=1)&&(d>=1)) Plus(F[now^1][a-1][b][c][d-1],1ll*key*a%Mod*c%Mod*d%Mod);
									Plus(F[now^1][a-1][b][c][d+1],1ll*key*a%Mod);
								}
							}
							if (b>=1){
								if (Dg[i+1]==2){
									if (c>=1) Plus(F[now^1][a+1][b-1][c-1][d],1ll*key*b%Mod*c%Mod);
									if (d>=1) Plus(F[now^1][a+1][b-1][c+1][d-1],1ll*key*b%Mod*d%Mod);
									Plus(F[now^1][a+1][b-1][c+1][d],1ll*key*b%Mod);
								}
								else{
									if (c>=2) Plus(F[now^1][a+1][b-1][c-2][d],1ll*c*(c-1)/2%Mod*key%Mod*b%Mod);
									if (c>=1) Plus(F[now^1][a+1][b-1][c][d],1ll*key*b%Mod*c%Mod);
									if (d>=2) Plus(F[now^1][a+1][b-1][c+2][d-2],1ll*d*(d-1)/2%Mod*key%Mod*b%Mod);
									if (d>=1) Plus(F[now^1][a+1][b-1][c+2][d-1],1ll*key*b%Mod*d%Mod);
									if ((c>=1)&&(d>=1)) Plus(F[now^1][a+1][b-1][c][d-1],1ll*key*b%Mod*c%Mod*d%Mod);
									Plus(F[now^1][a+1][b-1][c][d+1],1ll*key*b%Mod);
								}
							}

							
							if ((a==0)&&(b==0)){
								if (Dg[i+1]==2){
									if (c>=1) Plus(F[now^1][c-1][d][1][0],1ll*key*c%Mod);
									if (d>=1) Plus(F[now^1][c+1][d-1][1][0],1ll*key*d%Mod);
								}
								else{
									if (c>=1) Plus(F[now^1][c-1][d][0][1],1ll*key*c%Mod);
									if (d>=1) Plus(F[now^1][c+1][d-1][0][1],1ll*key*d%Mod);
								}
							}
							//*/
						}
					}
	}

	printf("%d\n",F[n&1][0][0][0][0]);

	return 0;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}
