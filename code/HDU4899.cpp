#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxS=15;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m;
char str[maxS+10];
int F[2][1<<maxS],G1[maxS+10],G2[maxS+10];
int Trans[4][1<<maxS];
int Ans[maxS+10];

void Plus(int &x,int y);

int main(){
	int Case;scanf("%d",&Case);
	while (Case--){
		scanf("%s",str);n=strlen(str);
		for (int i=0;i<n;i++)
			if (str[i]=='A') str[i]=0;
			else if (str[i]=='G') str[i]=1;
			else if (str[i]=='C') str[i]=2;
			else str[i]=3;
		
		scanf("%d",&m);

		for (int i=0;i<4;i++)
			for (int j=0;j<(1<<n);j++){
				G2[0]=G1[0]=j&1;
				for (int k=1;k<n;k++)
					if (j&(1<<k)) G2[k]=G1[k]=G1[k-1]+1;
					else G2[k]=G1[k]=G1[k-1];
				
				if (str[0]==i) G2[0]=1;
				for (int k=1;k<n;k++)
					G2[k]=max(G2[k],max(G2[k-1],G1[k-1]+(str[k]==i)));
				Trans[i][j]=G2[0];
				for (int k=1;k<n;k++)
					if (G2[k]>G2[k-1]) Trans[i][j]|=(1<<k);
			}
		mem(F,0);
		F[0][0]=1;
		for (int i=0;i<m;i++){
			int now=i&1;
			mem(F[now^1],0);
			for (int j=0;j<(1<<n);j++)
				if (F[now][j])
					for (int k=0;k<4;k++)
						Plus(F[now^1][Trans[k][j]],F[now][j]);
		}

		mem(Ans,0);
		for (int i=0;i<(1<<n);i++) Plus(Ans[__builtin_popcount(i)],F[m&1][i]);

		for (int i=0;i<=n;i++) printf("%d\n",Ans[i]);
	}

	return 0;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}
