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

int n,m;
ll F[8][maxN];
char str[maxN];

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	F[0][0]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<8;j++)
			if (F[j][i]){
				int f1,f2,f3;
				if (j&1) f1=max(0,i-1);else f1=max(0,i-2);
				if (j&2) f2=i;else f2=max(0,i-1);
				if (j&4) f3=i;else f3=max(0,i-1);
				for (int k=0;k<m;k++){
					int g1=f1,g2=f2,g3=f3;
					g1=max(g1,max(f1+(str[i]-'a'==k),f2));
					g2=max(max(g2,f2+(str[i+1]-'a'==k)),max(f3,g1));
					g3=max(g3,max(f3+(str[i+2]-'a'==k),g2));
					if ((g1<i-1)||(g2<i)||(g3<i)) continue;
					int key=0;
					if (g1==i) key|=1;if (g2==i+1) key|=2;if (g3==i+1) key|=4;
					F[key][i+1]+=F[j][i];
				}
			}
	printf("%lld\n",F[0][n]+F[1][n]+F[4][n]+F[5][n]);
	return 0;
}
