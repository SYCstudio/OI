#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200;
const int inf=2147483647;

int n;
char Input[maxN];

int main(){
	scanf("%d",&n);scanf("%s",Input+1);
	int cnt=0;
	for (int i=1;i<=n;i++) cnt+=Input[i]=='8';
	printf("%d\n",min(cnt,n/11));return 0;
}
