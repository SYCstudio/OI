#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int inf=2147483647;

int n;
int Num[maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n;scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&Num[i]);
		bool flag=0;int sum=0;
		for (int i=1;i<=n;i++){
			sum^=Num[i];
			if (Num[i]>1) flag=1;
		}
		if ( ((sum==0)&&(flag==0)) || ((sum)&&(flag==1)) ) printf("John\n");
		else printf("Brother\n");
	}

	return 0;
}
