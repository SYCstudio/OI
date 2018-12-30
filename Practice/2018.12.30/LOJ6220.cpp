#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=1010000;

int n;
int Pos[maxN];
ll A[maxN];

int main(){
	scanf("%d",&n);Pos[0]=1;ll sum=0;
	for (int i=1;i<=n;i++){
		scanf("%lld",&A[i]);sum=(sum+A[i])%n;
		if (Pos[sum]){
			for (int j=Pos[sum];j<=i;j++) printf("%d %lld\n",j,A[j]);
			return 0;
		}
		Pos[sum]=i+1;
	}
	return 0;
}
