#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
int To[maxN],Cnt[maxN];

bool check(int mid);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&To[i]),To[i]=n-To[i];

	int L=1,R=n,pos=0;
	do{
		int mid=(L+R)>>1;
		if (check(mid)) pos=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);

	printf("%d\n",n-pos+1);return 0;
}

bool check(int mid){
	mem(Cnt,0);
	for (int i=1;i<mid;i++) Cnt[To[i]]++;
	for (int i=1,sum=0;i<mid;i++){
		sum+=Cnt[i];
		if (sum>=i) return 1;
	}
	return 0;
}
