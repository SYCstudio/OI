#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,K;scanf("%d%d",&n,&K);
    if (n%2==0) --n;
    n=n/2+1;
    (n>=K)?puts("YES"):puts("NO");
    return 0;
}