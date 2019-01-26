#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000;
const int inf=2147483647;

int n,F[maxN];

int main(){
	scanf("%d",&n);int pls=0,top=0;F[0]=-inf;
	for (int i=1;i<=n;i++){
		char c;scanf(" %c",&c);
		if (c=='K'){
			int x;scanf("%d",&x);x-=pls;
			int l=0,r=top,pos=top;
			while (l<=r){
				int mid=(l+r)>>1;
				if (F[mid]<x) pos=mid,l=mid+1;
				else r=mid-1;
			}
			F[pos+1]=x;top=max(top,pos+1);
		}
		else ++pls;
	}
	printf("%d\n",pls+top);return 0;
}
