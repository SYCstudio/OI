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
	    Sm2[j][i]=Sm2[j][i+1]+Sm1[j][i];
	    Sm3[j][i]=Sm3[j][i+1]+Mt[j][i]*(n-i+1);
	}
    ll Ans=0,sum=0;
    for (int i=1;i<=n;i++)
	if (i&1){
	    Ans=max(Ans,sum+Sm2[0][i]+Sm3[1][i]+Sm1[0][i]*(i-1+i-1)+Sm1[1][i]*(i-1+n));
	    Ans=max(Ans,sum+Sm3[0][i+1]+Sm2[1][i+1]+Sm1[0][i+1]*(n+i)+Sm1[1][i+1]*(i+i)+Mt[0][i]*(i-1+i)+Mt[1][i]*(i+i));
	    sum=sum+Mt[0][i]*(i-1+i)+Mt[1][i]*(i+i);
	}
	else{
	    Ans=max(Ans,sum+Sm3[0][i]+Sm2[1][i]+Sm1[0][i]*(i-1+n)+Sm1[1][i]*(i-1+i-1));
	    Ans=max(Ans,sum+Sm2[0][i+1]+Sm3[1][i+1]+Sm1[0][i+1]*(i+i)+Sm1[1][i+1]*(n+i)+Mt[0][i]*(i+i)+Mt[1][i]*(i-1+i));
	    sum=sum+Mt[0][i]*(i+i)+Mt[1][i]*(i-1+i);
	}
    Ans=max(Ans,sum);
    Ans=Ans-Sm1[0][1]-Sm1[1][1];
    printf("%lld\n",Ans);return 0;
}
