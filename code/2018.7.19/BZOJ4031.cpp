#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxMap=10;
const int maxN=maxMap*maxMap;
const int Mod=1e9;
const int inf=2147483647;

int n,m,idcnt;
char Input[maxMap][maxMap];
int Mat[maxN][maxN],Id[maxMap][maxMap];

int Guass();

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1);

	idcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) if (Input[i][j]=='.') Id[i][j]=++idcnt;

	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (Input[i][j]=='.')
			{
				if (Input[i-1][j]=='.') Mat[Id[i][j]][Id[i][j]]++,Mat[Id[i][j]][Id[i-1][j]]--;
				if (Input[i][j-1]=='.') Mat[Id[i][j]][Id[i][j]]++,Mat[Id[i][j]][Id[i][j-1]]--;
				if (Input[i+1][j]=='.') Mat[Id[i][j]][Id[i][j]]++,Mat[Id[i][j]][Id[i+1][j]]--;
				if (Input[i][j+1]=='.') Mat[Id[i][j]][Id[i][j]]++,Mat[Id[i][j]][Id[i][j+1]]--;
			}

	/*
	for (int i=1;i<=idcnt;i++)
	{
		for (int j=1;j<=idcnt;j++)
			cout<<Mat[i][j]<<" ";
		cout<<endl;
	}
	//*/

	printf("%d\n",Guass());
	return 0;
}

int Guass()
{
	int Ans=1;
	for (int i=1;i<idcnt;i++)
	{
		for (int j=i+1;j<idcnt;j++)
			while (Mat[j][i])
			{
				int p=Mat[i][i]/Mat[j][i];
				for (int k=i;k<idcnt;k++)
					Mat[i][k]=(Mat[i][k]-1ll*Mat[j][k]*p%Mod+Mod)%Mod;
				swap(Mat[i],Mat[j]);
				Ans=-Ans;
			}
		Ans=1ll*Ans*Mat[i][i]%Mod;
	}
	/*
	for (int i=1;i<=idcnt;i++){
		for (int j=1;j<=idcnt;j++)
			cout<<Mat[i][j]<<" ";
		cout<<endl;
	}
	//*/
	return (Ans+Mod)%Mod;
}
/*
3 3
...
...
.*.
//*/
