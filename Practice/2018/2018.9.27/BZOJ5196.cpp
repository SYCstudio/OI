#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int inf=2147483647;

int n;
int Rc[maxN];
int F[maxN][maxN][maxN],Mn[maxN][maxN],Ans[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Rc[i]);

	mem(F,63);mem(Mn,63);
	F[0][0][0]=0;Mn[0][0]=0;
	for (int i=1;i<=n;i++){
		Ans[i]=inf;
		for (int j=1;j<=i;j++){
			Mn[i][j]=inf;
			for (int k=i;k>=j;k--){
				if (k==i) F[i][j][k]=Mn[i-1][j-1]+(Rc[i]!=0);
				else F[i][j][k]=F[i-1][j][k]+(Rc[i]!=i-k);
				Mn[i][j]=min(Mn[i][j],F[i][j][k]);
			}
		}
		/*
		cout<<i<<":"<<endl;
		for (int j=1;j<=i;j++)
		{
			for (int k=1;k<=i;k++)
				cout<<F[i][j][k]<<" ";
			cout<<endl;
		}
		//*/
	}

	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			Ans[i]=min(Ans[i],F[n][i][j]);
	for (int i=1;i<=n;i++) printf("%d\n",Ans[i]);
	return 0;
}
