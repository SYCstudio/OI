#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxK=25;
const int inf=1000000000;

int n,m,K;
int Mp[maxN][maxN],S[maxN][maxN];
int F[maxK][maxN][maxN],up[maxK][maxN][maxN],down[maxK][maxN][maxN];

int main(){
	scanf("%d%d%d",&n,&m,&K);K=K+K+1;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mp[i][j]);

	int Ans=-inf;
	for (int i=n;i>=1;i--){
		//cout<<"i:"<<i<<endl;
		for (int j=0;j<=i+1;j++) for (int k=0;k<=m+1;k++) for (int l=0;l<=K;l++) F[l][j][k]=-inf;
		for (int j=1;j<=m;j++) S[i][j]=Mp[i][j];
		for (int j=i-1;j>=1;j--) for (int k=1;k<=m;k++) S[j][k]=S[j+1][k]+Mp[j][k];

		/*
		cout<<"S:"<<endl;
		for (int j=1;j<=i;j++){
			for (int k=1;k<=m;k++)
				cout<<S[j][k]<<" ";
			cout<<endl;
		}
		//*/
		
		F[1][i][1]=Mp[i][1];
		for (int j=2;j<=m;j++) F[1][i][j]=max(F[1][i][j-1]+Mp[i][j],Mp[i][j]);
		for (int j=i-1;j>=1;j--) F[1][j][1]=F[1][j+1][1]+Mp[j][1];
		for (int l=1;l<=K;l++){
			up[l][i][1]=F[l][i][1];
			for (int j=i-1;j>=1;j--) up[l][j][1]=max(up[l][j+1][1],F[l][j][1]);
		}
		for (int l=1;l<=K;l++){
			down[l][1][1]=F[l][1][1];
			for (int j=2;j<=i;j++) down[l][j][1]=max(down[l][j-1][1],F[l][j][1]);
		}
		for (int j=2;j<=m;j++){
			for (int k=i;k>=1;k--)
				for (int l=1;l<=K;l++){
					if ((l==1)&&(k!=i)) F[l][k][j]=max(F[l][k][j],S[k][j]);
					F[l][k][j]=max(F[l][k][j],F[l][k][j-1]+S[k][j]);
					if ((l&1)&&(l>1)&&(k!=i)) F[l][k][j]=max(F[l][k][j],up[l-1][k+1][j-1]+S[k][j]);
					if (((l&1)==0)&&(k!=1)) F[l][k][j]=max(F[l][k][j],down[l-1][k-1][j-1]+S[k][j]);
				}
			for (int l=1;l<=K;l++) up[l][i][j]=F[l][i][j],down[l][1][j]=F[l][1][j];
			for (int k=i-1;k>=1;k--) for (int l=1;l<=K;l++) up[l][k][j]=max(up[l][k+1][j],F[l][k][j]);
			for (int k=2;k<=i;k++) for (int l=1;l<=K;l++) down[l][k][j]=max(down[l][k-1][j],F[l][k][j]);
		}
		/*
		cout<<"F"<<endl;
		for (int j=1;j<=i;j++){
			for (int k=1;k<=m;k++){
				cout<<"(";
				for (int l=1;l<=K;l++){
					if (F[l][j][k]==-inf) cout<<"-inf";
					else cout<<F[l][j][k];if (l!=K) cout<<" ";
				}
				cout<<") ";
			}
			cout<<endl;
		}
		cout<<"up"<<endl;
		for (int j=1;j<=i;j++){
			for (int k=1;k<=m;k++){
				cout<<"(";
				for (int l=1;l<=K;l++){
					if (up[l][j][k]==-inf) cout<<"-inf";
					else cout<<up[l][j][k];if (l!=K) cout<<" ";
				}
				cout<<") ";
			}
			cout<<endl;
		}
		cout<<"down"<<endl;
		for (int j=1;j<=i;j++){
			for (int k=1;k<=m;k++){
				cout<<"(";
				for (int l=1;l<=K;l++){
					if (down[l][j][k]==-inf) cout<<"-inf";
					else cout<<down[l][j][k];if (l!=K) cout<<" ";
				}
				cout<<") ";
			}
			cout<<endl;
		}
		//*/
		for (int j=1;j<=i;j++) for (int k=1;k<=m;k++) Ans=max(Ans,F[K][j][k]);
	}
	printf("%d\n",Ans);return 0;
}
