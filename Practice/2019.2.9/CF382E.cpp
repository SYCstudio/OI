#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=57;
const int Mod=1000000007;

int n,K,C[maxN][maxN];
int F[maxN][maxN][2];

void Plus(int &x,int y);

int main()
{
	scanf("%d%d",&n,&K);
	F[1][0][0]=1;
	F[0][0][1]=1;
	for (int i=0; i<=n; i++) for (int j=C[i][0]=1; j<=i; j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	for (int i=2; i<=n; i++)
		for (int j=0; j<=K; j++) {
			for (int sz=i-1; sz>=i-1-sz; sz--)
				for (int mt=0; mt<=j; mt++) {
					if (mt*2>sz||(j-mt)*2>i-1-sz) continue;
					int c=1ll*((sz==i-1-sz)?C[i-2][sz-1]:C[i-1][sz])*((i==n)?1:i)%Mod;
					Plus(F[i][j][0],1ll*F[sz][mt][1]*F[i-sz-1][j-mt][1]%Mod*c%Mod);
				}
			for (int sz=i-1; sz>=i-1-sz; sz--)
				for (int mt=0; mt<j; mt++) {
					if (mt*2>sz||(j-mt-1)*2>i-sz-1) continue;
					int c=1ll*((sz==i-1-sz)?C[i-2][sz-1]:C[i-1][sz])*((i==n)?1:i)%Mod;
					Plus(F[i][j][1],1ll*F[sz][mt][0]*F[i-sz-1][j-mt-1][0]%Mod*c%Mod);
					Plus(F[i][j][1],1ll*F[sz][mt][1]*F[i-sz-1][j-mt-1][0]%Mod*c%Mod);
					Plus(F[i][j][1],1ll*F[sz][mt][0]*F[i-sz-1][j-mt-1][1]%Mod*c%Mod);
				}
		}
	/*
	for (int i=1;i<=n;i++){
	    for (int j=0;j<=K;j++)
	        cout<<"("<<F[i][j][0]<<","<<F[i][j][1]<<") ";
	    cout<<endl;
	}
	//*/
	printf("%d\n",(F[n][K][0]+F[n][K][1])%Mod);
	return 0;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}