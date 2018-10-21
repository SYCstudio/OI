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

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n,sum=0;scanf("%d",&n);
		for (int i=1;i<=n;i++){
			int key;scanf("%d",&key);
			sum^=key;
		}
		if (sum==0) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}
