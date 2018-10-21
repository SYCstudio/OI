#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

int GetSG(int n,int m);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n;scanf("%d",&n);
		int sum=0;
		while (n--){
			int k1,k2;scanf("%d%d",&k1,&k2);
			n--;
			sum^=GetSG(k1,k2);
		}
		if (sum) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

int GetSG(int n,int m){
	if ((n&1)&&(m&1)) return 0;
	if (n&1) n++;
	if (m&1) m++;
	return GetSG(n>>1,m>>1)+1;
}
