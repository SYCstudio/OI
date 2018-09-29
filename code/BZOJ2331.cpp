#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=10;
const int inf=2147483647;

int R,C;
char Map[maxN][maxN],Pm[maxN][maxN];
int F[maxN][1<<maxM];

int main(){
	scanf("%d%d",&R,&C);
	for (int i=1;i<=R;i++) scanf("%s",Map[i]+1);
	if (R<C){
		for (int i=1;i<=R;i++) for (int j=1;j<=C;j++) Pm[j][i]=Map[i][j];
		swap(R,C);
		for (int i=1;i<=R;i++) for (int j=1;j<=C;j++) Map[i][j]=Pm[i][j];
	}
	
}
