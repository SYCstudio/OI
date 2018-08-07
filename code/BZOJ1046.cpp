#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int inf=2147483647;

int n;
int A[maxN],F[maxN],Seq[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	int top=n+1;
	for (int i=n;i>=1;i--){
		if (A[i]<Seq[top]){
			F[i]=n-top+2;Seq[--top]=A[i];continue;
		}
		int p=lower_bound(&Seq[top],&Seq[n+1],A[i]);
		if (
		F[i]=n-p+1;
		Seq[p]=A[i];
	}
}
