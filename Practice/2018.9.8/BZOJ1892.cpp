#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
string Seq[maxN];

void Do();

int main(){
	while (cin>>n){
		Do();
	}
	return 0;
}

void Do(){
	for (int i=1;i<=n;i++) cin>>Seq[i];
	if (n&1){
		printf("first player\n");return;
	}
	sort(&Seq[1],&Seq[n+1]);
	for (int i=1;i<=n;i+=2)
		if (Seq[i]!=Seq[i+1]){
			printf("first player\n");return;
		}
	printf("second player\n");return;
}
