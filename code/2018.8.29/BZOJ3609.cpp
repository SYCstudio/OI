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
		int n,m;scanf("%d%d",&n,&m);
		if ( (n-(n+m-1)/m)%2==0) printf("1\n");
		else printf("0\n");
	}
	return 0;
}
