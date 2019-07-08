#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=710;
const int Mod=1e9+7;

char Input[maxN];
int n,Num[maxN];
int F[maxN][maxN][10][2];

void Plus(int &x,int y);
int main()
{
	scanf("%s",Input+1);
	n=strlen(Input+1);
	reverse(&Input[1],&Input[n+1]);
	for (int i=1; i<=n; i++) Num[i]=Input[i]-'0';
	++Num[1];
	for (int i=1; i<=n; i++) Num[i+1]+=Num[i]/10,Num[i]%=10;
	if (Num[n+1]) ++n;

	for (int i=0; i<=9; i++) F[0][0][i][1]=1;
	for (int i=0; i<n; i++)
		for (int j=0; j<=i; j++)
			for (int k=0; k<=9; k++)
				for (int b=0; b<=1; b++)
					if (F[i][j][k][b])
						for (int c=0; c<=9; c++)
							Plus(F[i+1][j+(c>=k)][k][(b==0&&c>Num[i+1])||(b==1&&c>=Num[i+1])],F[i][j][k][b]);
	int Ans=0;
	for (int k=1; k<=9; k++)
		for (int i=1,mul=1; i<=n; i++,mul=(10ll*mul+1)%Mod)
			if (k!=9) Plus(Ans,1ll*(F[n][i][k][0])%Mod*mul%Mod);
			else Plus(Ans,1ll*F[n][i][k][0]*mul%Mod);
	printf("%d\n",Ans);
	return 0;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}