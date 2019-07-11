#include<bits/stdc++.h>
using namespace std;

const int Mod=998244353;

int main(){
	int n;
	scanf("%d",&n);
	int mul=4;
	for (int i=1;i<n;i++) mul=3ll*mul%Mod;
	printf("%d\n",mul);
	for (int i=1;i<=n;i++) puts("A 0 0 0 0");
	return 0;
}
