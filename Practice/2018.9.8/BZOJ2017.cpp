#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2020;
const int maxM=20;
const int inf=2147483647;

int n;
int C[maxN];
int F[maxN][maxN];

int main(){
	freopen("in","r",stdin);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&C[i]),C[i]+=C[i-1];

	for (int i=1;i<=n;i++){
		int mn=inf;
		for (int j=1;j<=n;j++){
			int p=min(j*2-1,i);
			mn=min(mn,F[i-p][p]);
			p=min(j*2,i);
			mn=min(mn,F[i-p][p]);
			F[i][j]=C[n]-C[n-i]-mn;
			//cout<<"("<<i<<","<<j<<") "<<mn<<endl;
		}
	}

	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<maxM;j++)
			cout<<F[i][j]<<" ";
		cout<<endl;
	}
	//*/

	printf("%d\n",F[n][1]);
	return 0;
}
