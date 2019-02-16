#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n;scanf("%d",&n);
		int sum=0;
		for (int i=1;i<=n;i++){
			int key;scanf("%d",&key);
			if (key%4==0) key--;
			else if (key%4==3) key++;
			sum^=key;
		}
		if (sum==0) printf("Bob\n");
		else printf("Alice\n");
	}

	return 0;
}
