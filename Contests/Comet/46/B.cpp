#include<bits/stdc++.h>
using namespace std;

int Mk[10000],mcnt=0;

int main(){
    for (int i=1;i<=100000;i++){
	int sum=0,u=i;
	while (u) sum+=u%10,u/=10;
	if (sum==i/2) Mk[++mcnt]=i;
    }
    int Q;scanf("%d",&Q);
    while (Q--){
	long long X;scanf("%lld",&X);int ans=0;
	for (int i=1;i<=mcnt;i++) if (X%Mk[i]==0) ++ans;
	printf("%d\n",ans);
    }
    return 0;
}
