#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

int n;
int Belong[maxN];

int main(){
	//freopen("out.out","w",stdout);
	scanf("%d",&n);
	int p=sqrt(n);
	for (int i=1;i<=n;i++) Belong[i]=(i-1)/p+1;
	//for (int i=1;i<=n;i++) cout<<Belong[i]<<" ";cout<<endl;
	for (int i=n,last;i>=1;i=last-1){
		last=i;
		while ((last>=1)&&(Belong[last-1]==Belong[last])) last--;
		for (int j=last;j<=i;j++) printf("%d ",j);
	}

	printf("\n");

	return 0;
}
