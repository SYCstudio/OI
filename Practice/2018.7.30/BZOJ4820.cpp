#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int inf=2147483647;

int n,m,Next[maxN*2];
char str[maxN][maxN];
char s[maxN*2];
ld Mat[maxN][maxN],Two[maxN];

ld GetKMP(int i1,int i2);
void Guass();

int main()
{
	Two[0]=1;for (int i=1;i<maxN;i++) Two[i]=Two[i-1]*0.5;
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",str[i]+1);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			Mat[i][j]=GetKMP(i,j);
		Mat[i][n+1]-=Two[m];
	}
	Mat[n+1][n+2]=1;
	for (int i=1;i<=n;i++) Mat[n+1][i]=1;

	/*
	for (int i=1;i<=n+1;i++){
		for (int j=1;j<=n+2;j++)
			printf("%5LF ",Mat[i][j]);
		printf("\n");
	}
	//*/

	Guass();

	/*
	for (int i=1;i<=n+1;i++){
		for (int j=1;j<=n+2;j++)
			printf("%5LF ",Mat[i][j]);
		printf("\n");
	}
	//*/

	for (int i=1;i<=n;i++) printf("%.10LF\n",Mat[i][n+2]/Mat[i][i]);
	return 0;
}

ld GetKMP(int i1,int i2){
	for (int i=1;i<=m;i++) s[i]=str[i1][i];
	for (int i=m+1;i<=m+m;i++) s[i]=str[i2][i-m];
	int len=m+m;
	Next[0]=Next[1]=0;
	for (int i=2,j=0;i<=len;i++){
		while ((j!=0)&&(s[j+1]!=s[i])) j=Next[j];
		if (s[j+1]==s[i]) j++;
		Next[i]=j;
	}

	ld ret=0;
	for (int now=Next[len];now;now=Next[now]) ret=ret+Two[m-now];
	return ret;
}

void Guass(){
	for (int i=1;i<=n+1;i++)
	{
		int now=i;
		for (int j=i+1;j<=n+1;j++)
			if (fabs(Mat[j][i])>fabs(Mat[now][i])) now=j;
		if (now!=i) swap(Mat[now],Mat[i]);
		for (int j=1;j<=n+1;j++)
			if (j!=i){
				ld p=Mat[j][i]/Mat[i][i];
				for (int k=1;k<=n+2;k++) Mat[j][k]=Mat[j][k]-Mat[i][k]*p;
			}
	}
	return;
}
