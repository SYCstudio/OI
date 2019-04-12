#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxN=303000;

int n;
ll Mt[2][maxN],Sm1[2][maxN],Sm2[2][maxN],Sm3[2][maxN];

int main(){
    scanf("%d",&n);
    for (int j=0;j<=1;j++) for (int i=1;i<=n;i++) scanf("%lld",&Mt[j][i]);
    for (int i=n;i>=1;i--)
	for (int j=0;j<=1;j++){
	    Sm1[j][i]=Sm1[j][i+1]+Mt[j][i];
	    Sm2[j][i]=Sm2[j][i+1]+Sm2[j][i+1]+Mt[j][i];
	    Sm3[j][i]=Sm3[i][j+1]+Mt[j][i]*(n-i+1);
	}
}
