#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;
const int inf=2147483647;

int n;
int A[maxN],B[maxN];
int T[maxN];

void dfs(int d);

int main(){
	cin>>n;
	for (int i=1;i<n;i++) cin>>A[i];
	for (int i=1;i<n;i++) cin>>B[i];
	for (int i=0;i<=3;i++){
		T[n]=i;dfs(n-1);
	}
	printf("NO\n");return 0;
}

void dfs(int d){
	if (d==0){
		printf("YES\n");
		for (int i=1;i<=n;i++) cout<<T[i]<<" ";cout<<endl;
		exit(0);
	}
	for (int i=0;i<=3;i++) if ( ((T[d+1]|i)==A[d]) && ((T[d+1]&i)==B[d]) ){
			T[d]=i;dfs(d-1);
		}
	return;
}
