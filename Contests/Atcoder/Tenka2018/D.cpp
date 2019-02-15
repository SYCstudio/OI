#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

int Mt[500][500];

int main(){
	int n,d;scanf("%d",&n);
	for (d=1;d*(d-1)<n+n;d++);
	if (d*(d-1)!=n+n){
		printf("No\n");return 0;
	}
	printf("Yes\n");
	for (int i=1,now=0,lst=0;i<=d+1;i++){
		for (int j=1;j<i;j++) Mt[i][j]=Mt[j][i-1];
		for (int j=i;j<d;j++) Mt[i][j]=++now;
	}
	printf("%d\n",d);
	for (int i=1;i<=d;i++){
		printf("%d ",d-1);
		for (int j=1;j<d;j++) printf("%d ",Mt[i][j]);
		printf("\n");
	}
	return 0;
}
