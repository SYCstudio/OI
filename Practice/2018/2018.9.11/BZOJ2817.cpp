#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
//#define T double

const int maxN=102;
const int maxKey=9010;
const int Mid=4500;
const int inf=2147483647;

namespace db{
	double F[2][maxKey][maxN][3];
}

namespace ft{
	__float128 F[2][maxKey][maxN][3];
}

int n,m,K;

template<class T>
void Dp(T F[][maxKey][maxN][3]);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	if (K<=8) Dp(db::F);
	else Dp(ft::F);

	return 0;
}

template<class T>
void Dp(T F[][maxKey][maxN][3]){
	F[1][Mid-2][1][0]=1;F[1][Mid-1][1][1]=2;
	for (int i=1;i<n;i++){
		int now=i&1;
		/*
		for (int j=Mid-n;j<=Mid+n;j++)
			for (int k=1;k<=n;k++)
				for (int l=0;l<=2;l++)
					cout<<"("<<i<<","<<j-Mid<<","<<k<<","<<l<<") "<<F[i][j][k][l]<<endl;
		//*/
		mem(F[now^1],0);
		for (int j=0;j<maxKey;j++)
			for (int k=1;k<n;k++)
				for (int l=0;l<=2;l++)
					if (F[now][j][k][l]){
						T key=F[now][j][k][l];
						if ((j+2*(i+1)<maxKey)&&(k>1)) F[now^1][j+2*(i+1)][k-1][l]+=key*(k-1);
						F[now^1][j][k][l]+=key*(2*k-l);
						if (j-2*(i+1)>=0) F[now^1][j-2*(i+1)][k+1][l]+=key*(k-l+1);
						if ((l<2)&&(j+i+1<maxKey)) F[now^1][j+i+1][k][l+1]+=key*(2-l);
						if ((l<2)&&(j-(i+1)>=0)) F[now^1][j-(i+1)][k+1][l+1]+=key*(2-l);
					}
	}
	T sum=0;
	for (int i=Mid+m;i<maxKey;i++) sum+=F[n&1][i][1][2];
	for (int i=1;i<=n;i++) sum/=i;
	//cout<<sum<<endl;
	int k=K;
	printf("%lld.",(ll)sum);
	while (k--){
		sum=(T)(sum-(ll)sum)*10;
		if (k==0) sum+=0.5;
		printf("%lld",(ll)sum);
	}
	printf("\n");
	return;
}
