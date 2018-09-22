#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40;
const int maxM=1010000;
const int inf=2147483647;

int n,m,Seq[maxN];
int n1,n2,N1[maxM],N2[maxM];

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);

	int mid=n/2;
	for (int S=0;S<(1<<mid);S++){
		int sum=0;
		for (int i=0;i<mid;i++)
			if (S&(1<<i)) sum=(sum+Seq[i+1])%m;
		N1[++n1]=sum;
	}
	for (int S=0;S<(1<<(n-mid));S++){
		int sum=0;
		for (int i=0;i<n-mid;i++)
			if (S&(1<<i)) sum=(sum+Seq[i+mid+1])%m;
		N2[++n2]=sum;
	}

	sort(&N1[1],&N1[n1+1]);n1=unique(&N1[1],&N1[n1+1])-N1-1;
	sort(&N2[1],&N2[n2+1]);n2=unique(&N2[1],&N2[n2+1])-N2-1;

	//for (int i=1;i<=n1;i++) cout<<N1[i]<<" ";cout<<endl;
	//for (int i=1;i<=n2;i++) cout<<N2[i]<<" ";cout<<endl;
	
	int mx=max(N1[n1],N2[n2]);
	for (int i=1;i<=n1;i++){
		int p=lower_bound(&N2[1],&N2[n2+1],m-1-N1[i])-N2;
		mx=max(mx,N1[i]+N2[p]);
		mx=max(mx,(N1[i]+N2[n2])%m);
	}

	printf("%d\n",mx);return 0;
}
